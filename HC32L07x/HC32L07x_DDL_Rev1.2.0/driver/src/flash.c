/******************************************************************************
 * Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************/

/******************************************************************************
 * @file   flash.c
 *
 * @brief  Source file for FLASH functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "flash.h"
/**
 *******************************************************************************
 ** \addtogroup FlashGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define FLASH_END_ADDR              (0x0001FFFFu)
#define FLASH_BYPASS()              M0P_FLASH->BYPASS = 0x5A5A;\
                                    M0P_FLASH->BYPASS = 0xA5A5; 
#define FLASH_IE_TRUE               (0x03)
#define FLASH_IE_FALSE              (0x00)

#define FLASH_TIMEOUT_INIT          (0xFFu)
#define FLASH_TIMEOUT_PGM           (0xFFu)
#define FLASH_TIMEOUT_ERASE         (0xFFu)

#define FLASH_LOCK_ALL              (0u)
#define FLASH_UNLOCK_ALL            (0xFFFFFFFFu)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
**********************************************************************************
** \brief FLASH OP
**
** Flash operation control data type redefinition
**************************************************************************/
typedef enum en_flash_op
{
    Read        = 0u,           ///<Read configuration value
    Program     = 1u,           ///<Program configuration value
    SectorErase = 2u,           ///<Sector erase configuration value
    ChipErase   = 3u,           ///<Chip erase configuration value
} en_flash_op_t;

/**
******************************************************************************
** \brief FLASH programming time parameter configuration
**
** FLASH programming time parameter configuration array definition (4MHz)
**************************************************************************/
const uint32_t pu32PcgTimer4M[] = { 
                                    0x20u,          //Tnvs   
                                    0x17u,          //Tpgs   
                                    0x1Bu,          //Tprog  
                                    0x4650u,        //Tserase
                                    0x222E0u,       //Tmerase
                                    0x18u,          //Tprcv  
                                    0xF0u,          //Tsrcv  
                                    0x3E8u          //Tmrcv  
                                  };
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
*****************************************************************************
** \brief Flash interrupt flag retrieval
**
**
** \param [in] enFlashIntType Flash interrupt type
**
** \retval TRUE or FALSE
*****************************************************************************/
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType)
{
    boolean_t bRetVal = FALSE;
    
    if(M0P_FLASH->IFR & enFlashIntType)
    {
        bRetVal =  TRUE;
    }
    
    return bRetVal;
}

/**
***********************************************************************
** \brief Flash interrupt flag clear
**
**
** \param [in] enFlashIntType Flash interrupt type
**
** \retval Ok or Error
*******************************************************************/
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    M0P_FLASH->ICLR &= ~(uint32_t)enFlashIntType;
    enResult = Ok;
    
    return enResult;
}

/** 
******************************************************************************* 
** \brief Flash interrupt enable 
** 
** 
** \param [in] enFlashIntType Flash interrupt type 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Flash_EnableIrq (en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE |= enFlashIntType;
    
    enResult = Ok;

    return enResult;
}

/** 
******************************************************************************* 
** \brief Flash interrupt disable 
** 
** 
** \param [in] enFlashIntType Flash interrupt type 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE &= ~(uint32_t)enFlashIntType;
    
    enResult = Ok;

    return enResult;
}

/** 
******************************************************************************* 
** \brief FLASH Initialization Function - Interrupt Service Routine, Programming Time Configuration, and Low-Power Mode
**
** This function is used to configure the interrupt service routine, low-power mode, and FLASH programming time-related registers based on the system clock.
**
** \param [in] u8FreqCfg FLASH programming clock frequency configuration (select the value based on the HCLK frequency):
** 1 - 4MHz;
** 2 - 8MHz;
** 4 - 16MHz;
** 6 - 24MHz;
** 8 - 32MHz;
** 12 - 48MHz;
** other - invalid value
** \param [in] bDpstbEn TRUE - When the system enters DeepSleep mode, the FLASH enters low-power mode;
** FALSE - When the system enters DeepSleep mode, the FLASH does not enter low-power mode;
**
** \retval Ok Operation successful.
** \retval ErrorInvalidParameter Parameter invalid.
** \retval ErrorUninitialized Initialization failed. 
*******************************************************************************/
en_result_t Flash_Init(uint8_t u8FreqCfg, boolean_t bDpstbEn)
{
    uint32_t                u32Index  = 0;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_INIT;
    en_result_t             enResult  = Ok;
    uint32_t                u32PrgTimer[8] = {0}; 
    volatile uint32_t       *pu32PrgTimerReg = (volatile uint32_t*)M0P_FLASH;
    
    if ((1  != u8FreqCfg) && (2  != u8FreqCfg) &&
        (4  != u8FreqCfg) && (6  != u8FreqCfg) &&
        (8  != u8FreqCfg) && (12 != u8FreqCfg))
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    M0P_FLASH->CR_f.DPSTB_EN = bDpstbEn;
    
    //Flash time parameter configuration value calculation
    for(u32Index=0; u32Index<8; u32Index++)
    {
        u32PrgTimer[u32Index] = u8FreqCfg * pu32PcgTimer4M[u32Index];
    } 
    
    if(12 == u8FreqCfg)
    {
        u32PrgTimer[1] = 0xFF;
    }
    
    //Flash time parameter register configuration
    for(u32Index=0; u32Index<8; u32Index++)
    {
        u32TimeOut = FLASH_TIMEOUT_INIT;
        while(pu32PrgTimerReg[u32Index]  != u32PrgTimer[u32Index])
        {
            if(u32TimeOut--)
            {
                FLASH_BYPASS();
                pu32PrgTimerReg[u32Index] = u32PrgTimer[u32Index];
            }
            else
            {
                return ErrorUninitialized;
            }
        }
    }
    
    return (enResult);
}

/**
*****************************************************************************
** \brief FLASH byte write
**
** Used to write 1 byte of data to FLASH.
**
** \param [in] u32Addr Flash address
** \param [in] u8Data 1 byte of data
** 
** \retval Ok Writing successful. 
** \retval ErrorInvalidParameter FLASH address is invalid 
** \retval ErrorTimeout operation timeout 
*******************************************************************************/
en_result_t Flash_WriteByte(uint32_t u32Addr, uint8_t u8Data)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    
    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //Flash unlock
    Flash_UnlockAll();
    
    //write data
    *((volatile uint8_t*)u32Addr) = u8Data;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash lock
    Flash_LockAll();
    
    return (enResult);
}

/**
*************************************************************************
** \brief FLASH half-word write
**
** Used to write half-word (2-byte) data to FLASH.
**
** \param [in] u32Addr Flash address
** \param [in] u16Data Half-word (2-byte) data
**
** \retval Ok Write successful.
** \retval ErrorInvalidParameter Invalid FLASH address
** \retval ErrorTimeout Operation timed out
*************************************************************************/
en_result_t Flash_WriteHalfWord(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    
    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //Flash unlock
    Flash_UnlockAll();
    
    //write data
    *((volatile uint16_t*)u32Addr) = u16Data;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash lock
    Flash_LockAll();
    
    return (enResult);
}

/**
*************************************************************************
** \brief FLASH word write
**
** Used to write 1 word of data to FLASH.
**
** \param [in] u32Addr Flash address
** \param [in] u32Data 1 word of data
**
** \retval Ok Write successful.
** \retval ErrorInvalidParameter Invalid FLASH address 
** \retval ErrorTimeout operation timeout 
*******************************************************************************/
en_result_t Flash_WriteWord(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    
    if (FLASH_END_ADDR < u32Addr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash unlock
    Flash_UnlockAll();
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while(Program != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = Program;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //write data
    *((volatile uint32_t*)u32Addr) = u32Data;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash lock
    Flash_LockAll();
    
    return (enResult);
}

/** 
******************************************************************************* 
** \brief FLASH sector erase
**
** FLASH sector erase.
**
** \param [in] u32SectorAddr Address within the erased sector
**
** \retval Ok Erase successful.
** \retval ErrorInvalidParameter Invalid FLASH address
** \retval ErrorTimeout Operation timed out
***********************************************************************/
en_result_t Flash_SectorErase(uint32_t u32SectorAddr)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;
    
    if (FLASH_END_ADDR < u32SectorAddr)
    {
        enResult = ErrorInvalidParameter;
        return (enResult);
    }
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash unlock
    Flash_UnlockAll();
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(SectorErase != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = SectorErase;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //write data
    *((volatile uint8_t*)u32SectorAddr) = 0;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash lock
    Flash_LockAll();
    
    return (enResult);
}

/**
***********************************************************************
** \brief FLASH full chip erase (this function only runs in RAM!!!)
**
** FLASH full chip erase.
**
**
** \retval Ok Erase successful.
** \retval ErrorTimeout Operation timed out
**
*****************************************************************************/
en_result_t Flash_ChipErase(void)
{
    en_result_t             enResult = Ok;    
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE; 
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //set OP
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while(ChipErase != M0P_FLASH->CR_f.OP)
    {
        if(u32TimeOut--)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = ChipErase;
        }
        else
        {
            return ErrorTimeout;
        }
    }
    
    //Flash unlock
    Flash_UnlockAll();
    
    //write data
    *((volatile uint8_t*)0) = 0;
    
    //busy?
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if(0 == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    //Flash lock
    Flash_LockAll();
    
    return (enResult);
}

/**
*************************************************************************
** \brief FLASH programming protection lock
**
**
** \retval Null
*************************************************************************/
void Flash_LockAll(void)
{ 
    FLASH_BYPASS();
    M0P_FLASH->SLOCK0 = FLASH_LOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK1 = FLASH_LOCK_ALL;    

}

/** 
******************************************************************************* 
** \brief FLASH programming protection unlock 
** 
** 
** \retval Null 
*******************************************************************************/
void Flash_UnlockAll(void)
{
   
    FLASH_BYPASS();
    M0P_FLASH->SLOCK0 = FLASH_UNLOCK_ALL;
    FLASH_BYPASS();
    M0P_FLASH->SLOCK1 = FLASH_UNLOCK_ALL;

}

/** *****************************************************************************
** \brief FLASH read wait cycle setting
**
** \param [in] enWaitCycle: Insert the number of FLASH read wait cycles (enumeration type)
**
** \retval Ok: Unlock successful
** \retval ErrorInvalidParameter: Parameter error
*************************************************************************/
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle)
{
    en_result_t enResult = Ok;
    
    FLASH_BYPASS();
    M0P_FLASH->CR_f.WAIT = enWaitCycle;
    
    return enResult;
}

/**
*****************************************************************************
** \brief FLASH LOCK setting
**
** \param [in] enLock @ref en_flash_lock_t
** \param [in] u32LockValue 32 bits. If bit = 0, the lock is enabled, and the corresponding sector cannot be erased or written. If bit = 1, the lock is unlocked.
** \note Unlock range: Sector: [enLock*128 + i*4, enLock*128 + i*4+3]
** (i represents the bit position of u32LockValue, 0-31)
** For example: enLock = FlashLock1, u32LockValue = 0x00000002,
** Then the unlock range is: [Sector128, Sector131]
** \retval Ok Unlock successful
** \retval ErrorInvalidParameter Parameter error
*************************************************************************/
en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue)
{
    FLASH_BYPASS();
    *((&M0P_FLASH->SLOCK0) + enLock) = u32LockValue;
    
    return Ok;
}
//@} // FlashGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

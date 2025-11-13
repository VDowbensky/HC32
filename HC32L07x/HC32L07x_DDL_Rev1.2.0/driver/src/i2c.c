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
 * @file   i2c.c
 *
 * @brief  Source file for I2C functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "i2c.h"

/**
 *******************************************************************************
 ** \addtogroup I2cGroup
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/**
********************************************************************************
** \brief I2C baud rate configuration registers
**
** \param [in] u8Tm baud rate configuration value
**
** \retval enRet success or failure
**
************************************************************************/
 en_result_t I2C_SetBaud(M0P_I2C_TypeDef* I2Cx, uint8_t u8Tm)
 {
     en_result_t enRet = Error;
     
     I2Cx->TM = u8Tm;
     
     enRet = Ok;
     return enRet;
 }
 
 /**
************************************************************************************
** \brief I2C function setting related functions
**
** \param [in] enFunc function parameters
**
** \retval enRet success or failure
**
****************************************************************************/
en_result_t I2C_SetFunc(M0P_I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
{
    en_result_t enRet = Error;
    
    SetBit((uint32_t)&I2Cx->CR, enFunc, TRUE);

    enRet = Ok;
    return enRet;
}

/**
********************************************************************************
** \brief I2C function clear related functions
**
** \param [in] enFunc function parameters
**
** \retval enRet success or failure
**
****************************************************************************/
 en_result_t I2C_ClearFunc(M0P_I2C_TypeDef* I2Cx, en_i2c_func_t enFunc)
 {
    en_result_t enRet = Error;
    
    SetBit((uint32_t)&I2Cx->CR, enFunc, FALSE); 
  
    enRet = Ok;
    return enRet; 
 }
 
/**
****************************************************************************
** \brief I2C get interrupt flag function
**
** \param None
**
** \retval bIrq interrupt flag
**
************************************************************************/
boolean_t I2C_GetIrq(M0P_I2C_TypeDef* I2Cx)
{    
    if(I2Cx->CR&0x8)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    } 
}

/**
****************************************************************************************
** \brief I2C clear interrupt flag function
**
** \param None
**
** \retval bIrq interrupt flag
**
********************************************************************/
en_result_t I2C_ClearIrq(M0P_I2C_TypeDef* I2Cx)
{
    en_result_t enRet = Error;
    
    I2Cx->CR &= ~0x8u;
    
    enRet = Ok;
    return enRet; 
}

/**
********************************************************************************
** \brief I2C gets related status
**
** \param None
**
** \retval I2C status
**
****************************************************************************/
uint8_t I2C_GetState(M0P_I2C_TypeDef* I2Cx)
{
    uint8_t u8State = 0;
    
    u8State = I2Cx->STAT;
    
    return u8State;
}

/**
************************************************************************
** \brief Byte data write function
**
** \param u8Data write data
**
** \retval whether the data write was successful
**
****************************************************************************/
en_result_t I2C_WriteByte(M0P_I2C_TypeDef* I2Cx, uint8_t u8Data)
{
    en_result_t enRet = Error;
    
    I2Cx->DATA = u8Data;

    enRet = Ok;
    return enRet;
}

/**
************************************************************************************
** \brief Byte data read function
**
** \param None
**
** \retval read data
**
******************************************************************************/
uint8_t I2C_ReadByte(M0P_I2C_TypeDef* I2Cx)
{
    uint8_t u8Data = 0;
    
    u8Data = I2Cx->DATA;
    
    return u8Data;
}

/**
******************************************************************************
** \brief I2C module initialization
**
** \param pstcI2CCfg initialization configuration structure
**
** \retval initialization success
**
**************************************************************************/
en_result_t I2C_Init(M0P_I2C_TypeDef* I2Cx, stc_i2c_cfg_t *pstcI2CCfg)
{
   en_result_t enRet = Error;
   uint8_t     u8Tm;
   
   if(M0P_I2C0 == I2Cx)
   {
       M0P_RESET->PERI_RESET0 &= ~(uint32_t)0x10u; 
       M0P_RESET->PERI_RESET0 |= (uint32_t)0x10u;   
   }
   else
   {
       M0P_RESET->PERI_RESET0 &= ~(uint32_t)0x20u; 
       M0P_RESET->PERI_RESET0 |= (uint32_t)0x20u;   
   }
    
   I2Cx->CR = 0;
   I2Cx->CR = pstcI2CCfg->enMode;
    
   if((pstcI2CCfg->u32Baud<<4) > pstcI2CCfg->u32Pclk)
   {
        return Error;
   }       
    
   if(I2cMasterMode == pstcI2CCfg->enMode)
   {
        I2Cx->TMRUN = TRUE;
        ///< Fsck = Fpclk/8*(Tm+1)
        u8Tm = ((pstcI2CCfg->u32Pclk / pstcI2CCfg->u32Baud) >> 3) - 1;
        if(9 > u8Tm)
        {
            I2C_SetFunc(I2Cx,I2cHlm_En);
        }
        enRet = I2C_SetBaud(I2Cx, u8Tm);
   }
   else
   {
        I2Cx->TMRUN = FALSE;
        pstcI2CCfg->u8SlaveAddr = (uint8_t)(((uint32_t)pstcI2CCfg->u8SlaveAddr<<1)|(pstcI2CCfg->bGc));
        I2Cx->ADDR = pstcI2CCfg->u8SlaveAddr;
   }
 
   return enRet;
}

//@} // I2cGroup

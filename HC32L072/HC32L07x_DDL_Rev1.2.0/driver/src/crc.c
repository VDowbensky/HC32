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
 * @file   crc.c
 *
 * @brief  Source file for CRC functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "crc.h"
/**
 *******************************************************************************
 ** \addtogroup CrcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

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
** \brief CRC16 encoding (byte-stuffing mode)
**
** This function is mainly used to generate a CRC16 code.
**
** \param [in] pu8Data Pointer to the data to be encoded (byte input)
** \param [in] u32Len Length of the data to be encoded (bytes)
**
** \retval CRC16 CRC16 encoded value.
*************************************************************************/
uint16_t CRC16_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT = 0xFFFF;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
***********************************************************************
** \brief CRC16 encoding (half-word filling)
**
** This function is mainly used to generate a CRC16 code.
**
** \param [in] pu16Data Pointer to the data to be encoded (half-word input)
** \param [in] u32Len Length of the data to be encoded (number of half-words)
**
** \retval CRC16 CRC16 encoded value. 
*******************************************************************************/
uint16_t CRC16_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/** 
******************************************************************************* 
** \brief CRC16 Encoding (Word Filling)
**
** This function is mainly used to generate a CRC16 code.
**
** \param [in] pu32Data Pointer to the data to be encoded (word input)
** \param [in] u32Len Length of the data to be encoded (number of words)
**
** \retval CRC16 CRC16 encoded value.
***********************************************************************/
uint16_t CRC16_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
*************************************************************************
** \brief CRC16 check (byte-stuffing mode)
**
** This function is mainly used to check data and CRC16 value.
**
** \param [in] pu8Data Pointer to the data to be checked (byte input)
** \param [in] u32Len Length of the data to be checked (bytes)
** \param [in] u16CRC CRC16 value to be checked
**
** \retval Ok CRC check is correct
** \retval Error CRC check error
*******************************************************************************/
en_result_t CRC16_Check8(uint8_t* pu8Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((((uint32_t)u16CRC)>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)(((uint32_t)u16CRC>>8)&0xFF);
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
***********************************************************************
** \brief CRC16 check (half-word fill)
**
** This function is used to check data and CRC16 values.
**
** \param [in] pu16Data Pointer to the data to be checked (half-word input)
** \param [in] u32Len Length of the data to be checked (number of half-words)
** \param [in] u16CRC CRC16 value to be checked
**
** \retval Ok CRC check is correct
** \retval Error CRC check error
********************************************************************/
en_result_t CRC16_Check16(uint16_t* pu16Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->CR_f.CR = 0;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = u16CRC;
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
***********************************************************************
** \brief CRC16 check (word fill mode)
**
** This function is mainly used to check data and CRC16 value.
**
** \param [in] pu32Data Pointer to the data to be checked (word input)
** \param [in] u32Len Length of the data to be checked (number of words)
** \param [in] u16CRC CRC16 value to be checked
**
** \retval Ok CRC check is correct
** \retval Error CRC check error 
*******************************************************************************/
en_result_t CRC16_Check32(uint32_t* pu32Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->CR_f.CR = 0;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = ((uint16_t)u16CRC);
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult);
}

/**
*****************************************************************************
** \brief CRC16 encoding (byte-stuffing mode)
**
** This function is mainly used to generate a CRC16 code.
**
** \param [in] pu8Data Pointer to the data to be encoded (byte input)
** \param [in] u32Len Length of the data to be encoded (bytes)
**
** \retval CRC16 CRC16 encoded value.
*************************************************************************/
uint32_t CRC32_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->RESULT = 0xFFFFFFFFu;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
***********************************************************************
** \brief CRC16 encoding (half-word filling)
**
** This function is mainly used to generate CRC16 encoding.
**
** \param [in] pu16Data Pointer to the data to be encoded (half-word input)
** \param [in] u32Len Length of data to be encoded (number of half-words)
**
** \retval CRC16 CRC16 encoded value.
**************************************************************************/
uint32_t CRC32_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
*************************************************************************
** \brief CRC16 encoding (word filling mode)
**
** This function is mainly used to generate a CRC16 code.
**
** \param [in] pu32Data Pointer to the data to be encoded (word input)
** \param [in] u32Len Length of the data to be encoded (number of words)
**
** \retval CRC16 CRC16 encoded value.
*************************************************************************/
uint32_t CRC32_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
***********************************************************************
** \brief CRC16 checksum (byte-stuffing)
**
** This function is mainly used to check data and CRC16 values.
**
** \param [in] pu8Data Pointer to the data to be checked (byte input)
** \param [in] u32Len Length of the data to be checked (bytes)
** \param [in] u16CRC CRC16 value to be checked
**
** \retval Ok CRC check successful
** \retval Error CRC check error
*******************************************************************/
en_result_t CRC32_Check8(uint8_t* pu8Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>8)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>16)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>24)&0xFF);
        
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
***********************************************************************
** \brief CRC16 check (half-word fill mode)
**
** This function is mainly used to check data and CRC16 value.
**
** \param [in] pu16Data Pointer to the data to be checked (half-word input)
** \param [in] u32Len Length of the data to be checked (number of half-words)
** \param [in] u16CRC CRC16 value to be checked
**
** \retval Ok CRC check is correct
** \retval Error CRC check error 
*******************************************************************************/
en_result_t CRC32_Check16(uint16_t* pu16Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = (uint16_t)((u32CRC>>0)&0xFFFF);
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = (uint16_t)((u32CRC>>16)&0xFFFF);

    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
***********************************************************************
** \brief CRC16 check (word fill mode)
**
** This function is mainly used to check data and CRC16 values.
**
** \param [in] pu32Data Pointer to the data to be checked (word input)
** \param [in] u32Len Length of the data to be checked (number of words)
** \param [in] u16CRC CRC16 value to be checked
**
** \retval Ok CRC check is correct
** \retval Error CRC check error
**********************************************************************/
en_result_t CRC32_Check32(uint32_t* pu32Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint32_t*)(&(M0P_CRC->DATA))) = u32CRC;
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult);
}
//@} // CrcGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

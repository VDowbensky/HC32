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
 * @file   wdt.c
 *
 * @brief  Source file for WDT functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "wdt.h"

/**
 ******************************************************************************
 ** \defgroup WdtGroup
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/**
**********************************************************************************
** \brief WDT overflow time setting function
**
** \param [in] u8LoadValue overflow time 
** 
** \retval None 
** 
******************************************************************************/
void Wdt_WriteWdtLoad(uint8_t u8LoadValue)
{
    M0P_WDT->CON_f.WOV = u8LoadValue;
}

/** 
****************************************************************************** 
** \brief WDT initialization function 
** 
** \param [in] enFunc @ref en_wdt_func_t 
** \param [in] enTime @ref en_wdt_time_t 
** 
**\retval Ok 
** 
******************************************************************************/
en_result_t Wdt_Init(en_wdt_func_t enFunc, en_wdt_time_t enTime)
{
    en_result_t enRet = Error;
    
    Wdt_WriteWdtLoad(enTime);
    M0P_WDT->CON_f.WINT_EN = enFunc;
    enRet = Ok;
    return enRet;
}

/**
****************************************************************************
** \brief WDT reset and start function
**
** \param [in] None
**
** \retval None
**
****************************************************************************/
void Wdt_Start(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
************************************************************************************
** \brief WDT dog feed function
**
** \param [in] None
**
** \retval Ok
**
************************************************************************/
void Wdt_Feed(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
****************************************************************************
** \brief WDT interrupt flag clear
**
** \param [in] None
**
** \retval Ok
**
************************************************************************/
void Wdt_IrqClr(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
********************************************************************************
** \brief WDT Read Current Count Value Function
**
** \param [in] None
**
** \retval Count value
**
********************************************************************/
uint8_t Wdt_ReadWdtValue(void)
{
    uint8_t u8Count;
    
    u8Count = M0P_WDT->CON_f.WCNTL;
    
    return u8Count;
}

/**
********************************************************************************
** \brief WDT Reads Current Running Status
**
** \param [in] None
**
** \retval Status value
**
************************************************************************/
boolean_t Wdt_ReadwdtStatus(void)
{
    if(M0P_WDT->CON&0x10u)
    {   
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
****************************************************************************
** \brief WDT interrupt status flag acquisition
**
**
** \retval Interrupt status
********************************************************************/
boolean_t Wdt_GetIrqStatus(void)
{
    if(M0P_WDT->CON&0x80u)
    {   
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


//@} // WdtGroup

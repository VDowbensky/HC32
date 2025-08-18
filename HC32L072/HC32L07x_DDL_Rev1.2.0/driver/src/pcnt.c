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
 * @file   pcnt.c
 *
 * @brief  Source file for PCNT functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "pcnt.h"

/**
 ******************************************************************************
 ** \addtogroup PCNTGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/


/**
******************************************************************************
** \brief PCNT start and stop control
** @param NewState : Run_Enable or Run_Disable
** @param NewState : FALSE or TRUE
** \retval None
**
**************************************************************************/
boolean_t Pcnt_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_PCNT->RUN)), 0, NewState);
    return GetBit((uint32_t)(&(M0P_PCNT->RUN)), 0);
}


/**
******************************************************************************
** \brief Synchronizes the value in BUF to CNT
** @param value : The value to be synchronized to TOP
** \retval ok or ErrorTimeout
**
******************************************************************************/
en_result_t Pcnt_SetB2T(uint16_t value)
{
    uint16_t u16TimeOut;

    u16TimeOut = 1000;
    M0P_PCNT->BUF = value;
    M0P_PCNT->CMD_f.B2T = 1;

    while(u16TimeOut--)
    {
        if(M0P_PCNT->SR2_f.B2T == FALSE)
        {
            break;
        }
    }
    if(u16TimeOut == 0)
    {
        return ErrorTimeout;
    }
        return Ok;
}

/**
******************************************************************************
** \brief Synchronizes the value in BUF to CNT
** @param value: Value to be synchronized to CNT
** \retval ok or ErrorTimeout
**
**********************************************************************************/
en_result_t Pcnt_SetB2C(uint16_t value)
{
    uint16_t u16TimeOut;
    u16TimeOut = 1000;
    M0P_PCNT->BUF = value;
    M0P_PCNT->CMD_f.B2C = 1;

    while(u16TimeOut--)
    {
        if(M0P_PCNT->SR2_f.B2C == FALSE)
        {
            break;
        }
    }
    if(u16TimeOut == 0)
    {
        return ErrorTimeout;
    }
    return Ok;
}

/**
******************************************************************************
** \brief Synchronize the value in TOP to CNT
** @param value: The value to be synchronized to CNT
** \retval OK or ErrorTimeout
**
******************************************************************************/
en_result_t Pcnt_SetT2C(void)
{
    uint16_t u16TimeOut;
    u16TimeOut = 1000;
    M0P_PCNT->CMD_f.T2C = 1;
    while(u16TimeOut--)
    {
        if(M0P_PCNT->SR2_f.T2C == FALSE)
        {
            break;
        }
    }
    if(u16TimeOut == 0)
    {
        return ErrorTimeout;
    }
    return Ok;
}


/**
******************************************************************************
** \brief Assign value to BUF
** @param value: Value to be assigned to BUF
** \retval None
**
******************************************************************************/
void Pcnt_SetBuf(uint16_t value)
{
    M0P_PCNT->TOP_f.TOP = value;
}

/**
**********************************************************************************
** \brief Initialization
** @param start: Value to synchronize to TOP
** @param end: Value to synchronize to CNT
** \retval ok or ErrorTimeout
**
*********************************************************************************/
void Pcnt_Init(stc_pcnt_initstruct_t*  InitStruct)
{
    M0P_PCNT->CTRL_f.S1P = InitStruct->Pcnt_S1Sel;
    M0P_PCNT->CTRL_f.S0P = InitStruct->Pcnt_S0Sel;
    M0P_PCNT->CTRL_f.CLKSEL = InitStruct->Pcnt_Clk;
    M0P_PCNT->CTRL_f.MODE = InitStruct->Pcnt_Mode;
    if(InitStruct->Pcnt_Mode == PcntDoubleMode)//如果是双通道正交脉冲计数模式
    {
        M0P_PCNT->SR1_f.DIR = InitStruct->Pcnt_Dir;
    }
    else
    {
        M0P_PCNT->CTRL_f.DIR = InitStruct->Pcnt_Dir;
    }
    M0P_PCNT->FLT_f.EN = InitStruct->Pcnt_FltEn;
    M0P_PCNT->FLT_f.DEBTOP = InitStruct->Pcnt_DebTop;
    M0P_PCNT->FLT_f.CLKDIV = InitStruct->Pcnt_ClkDiv;
    M0P_PCNT->TOCR_f.EN    = InitStruct->Pcnt_TocrEn;
    M0P_PCNT->TOCR_f.TH    = InitStruct->Pcnt_TocrTh;

    M0P_PCNT->DBG_f.DBG = InitStruct->Pcnt_Dbg;
}

/**
****************************************************************************** 
** \brief Configure the interrupt source enable
** @param IT_Src: Bit position of the interrupt source within PCNT_IEN
** @param NewState: FALSE or TRUE
** \retval None
**
**************************************************************************/
void Pcnt_ItCfg(en_pcnt_itfce_t IT_Src, boolean_t NewState)
{
    if(NewState == TRUE)
    {
        M0P_PCNT->IEN |= (uint32_t)(1<<IT_Src);
    }
    else if(NewState == FALSE)
    {
        M0P_PCNT->IEN &= ~(uint32_t)(1<<IT_Src);
    }
    else
    {
        ;
    }
}

/**
******************************************************************************
** \brief Get the interrupt source flag.
** @param IT_Src: Interrupt source flag.
** \retval FALSE or TRUE
**
**************************************************************************/
boolean_t Pcnt_GetItStatus(en_pcnt_itfce_t IT_Src)
{
    return ((M0P_PCNT->IFR >> IT_Src) & 1u) > 0 ? TRUE : FALSE;
}

/**
******************************************************************************
** \brief Clear the interrupt source flag.
** @param IT_Src: Interrupt source flag.
** \retval None
**
******************************************************************************/
void Pcnt_ClrItStatus(en_pcnt_itfce_t IT_Src)
{
    M0P_PCNT->ICR &= ~(uint32_t)(1<<(uint32_t)IT_Src);
}


/**
**************************************************************************
** \brief Get the value of the PCNT_CNT register
** @param None
** \retval PCNT_CNT value
**
**************************************************************************/
uint16_t Pcnt_GetCnt(void)
{
    return  (uint16_t)(M0P_PCNT->CNT);
}

/**
**********************************************************************************
** \brief Get the value of the PCNT_TOP register
** @param None
** \retval PCNT_TOP value
**
*****************************************************************************/
uint16_t Pcnt_GetTop(void)
{
   return  (uint16_t)(M0P_PCNT->TOP);
}

/**
******************************************************************************
** \brief Get the value of the PCNT_BUF register
** @param None
** \retval PCNT_BUF value
**
******************************************************************************/
uint16_t Pcnt_GetBuf(void)
{
    return (uint16_t)(M0P_PCNT->BUF);
}

//@} // Group
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


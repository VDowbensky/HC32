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
 * @file   lptim.c
 *
 * @brief  Source file for LPTIM functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

#include "lptim.h"

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
** \brief Timer LPTIMx interrupt enable control
** @param Lptimx : LPTIM0 or LPTIM1
** @param NewStatus: TRUE or FALSE
** \retval None
**
**************************************************************************/
void Lptim_ConfIt(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus)
{
    SetBit((uint32_t)(&(Lptimx->CR)), 10, NewStatus);
}

/**
******************************************************************************
** \brief Start/Stop Control for Timer LPTIMx
** @param Lptimx: LPTIM0 or LPTIM1
** @param NewStatus: TRUE or FALSE
** \retval None
**
******************************************************************************/
void Lptim_Cmd(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus)
{
    SetBit((uint32_t)(&(Lptimx->CR)), 0, NewStatus);
}

/**
******************************************************************************
** \brief Get the interrupt flag of the timer LPTIMx
** @param Lptimx: LPTIM0 or LPTIM1
** \retval TRUE or FALSE
**
******************************************************************************/
boolean_t Lptim_GetItStatus(M0P_LPTIMER_TypeDef* Lptimx)
{
    return GetBit((uint32_t)(&(Lptimx->IFR)), 0);
}

/**
******************************************************************************
** \brief Clear the interrupt flag of the timer LPTIMx
** @param Lptimx: LPTIM0 or LPTIM1
** \retval None
**
******************************************************************************/
void Lptim_ClrItStatus(M0P_LPTIMER_TypeDef* Lptimx)
{
    SetBit((uint32_t)(&(Lptimx->ICLR)), 0, 0);
}

/**
**********************************************************************************
** \brief Initialization and configuration of the timer LPTIMx
** @param Lptimx: LPTIM0 or LPTIM1
** @param InitStruct: Initialization structure for LPTIMx
** \retval en_result_t type data 
**
******************************************************************************/
en_result_t Lptim_Init(M0P_LPTIMER_TypeDef* Lptimx, stc_lptim_cfg_t* InitStruct)
{
    uint16_t u16TimeOut;
    u16TimeOut = 1000;
    Lptimx->CR_f.PRS      = InitStruct->enPrs;
    Lptimx->CR_f.TCK_SEL  = InitStruct->enTcksel;
    Lptimx->CR_f.GATE_P   = InitStruct->enGatep;
    Lptimx->CR_f.GATE     = InitStruct->enGate;
    Lptimx->CR_f.TOG_EN   = InitStruct->enTogen;
    Lptimx->CR_f.CT       = InitStruct->enCt;
    Lptimx->CR_f.MD       = InitStruct->enMd;
    while(u16TimeOut--)
    {
        if(Lptimx->CR_f.WT_FLAG)
        {
            break;
        }
    }
    if(u16TimeOut == 0)
    {
        return ErrorTimeout;        
    }
    Lptimx->ARR_f.ARR = InitStruct->u16Arr;
    return Ok;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

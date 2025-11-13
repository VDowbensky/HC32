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
 * @file   lpm.c
 *
 * @brief  Source file for LPM functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "lpm.h"
/**
 *******************************************************************************
 ** \addtogroup LpmGroup
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
*************************************************************************
** \brief Entering deep sleep mode
**
** \input bOnExit - TRUE: Automatically enters sleep again after exiting exception handling;
** FALSE: No longer automatically enters sleep after waking up
**
** \retval NULL
*************************************************************************/
void Lpm_GotoDeepSleep(boolean_t bOnExit)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    SCB->SCR |= 1u<<bOnExit;
    __WFI();
}

/**
*****************************************************************************
** \brief Entering normal sleep mode
**
** \input bOnExit - TRUE: Automatically enters sleep again after exiting exception handling.
** FALSE: Does not automatically enter sleep after waking up.
**
** \retval NULL
*************************************************************************/
void Lpm_GotoSleep(boolean_t bOnExit)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    SCB->SCR |= 1u<<bOnExit;
    __WFI();
}
                        
//@} // LpmGroup                                                                           

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

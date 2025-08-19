/****************************************************************************** 
* Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved. 
* 
* This software component is licensed by XHSC under BSD 3-Clause license 
* (the "License"); You may not use this file except in compliance with the 
* License. You may obtain a copy of the License at: 
* opensource.org/licenses/BSD-3-Clause 
* 
******************************************************************************/

/****************************************************************************** 
* @file lptim.h 
* 
* @brief Header file for LPTIM functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __LPTIM_H__
#define __LPTIM_H__

/*****************************************************************************
* Include files
*************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*******************************************************************************
** \brief LPTIMx prescaler
** \note LPTIMx_CR PRS This value cannot be changed while the timer is running.
**************************************************************************/
typedef enum
{
    LptimPrsDiv1 = 0, // Divide by 1
    LptimPrsDiv2 = 1, // Divide by 2
    LptimPrsDiv4 = 2, // Divide by 4
    LptimPrsDiv8 = 3, // Divide by 8
    LptimPrsDiv16 = 4, // Divide by 16
    LptimPrsDiv32 = 5, // Divide by 32
    LptimPrsDiv64 = 6, // Divide by 64
    LptimPrsDiv256 = 7 // Divide by 256
}en_lptim_prs_t;

/**
************************************************************************************
** \brief LPTIMx clock select
** \note LPTIMx_CR TCK_SEL
****************************************************************************/
typedef enum
{
    LptimPclk = 0,
    LptimXtl = 2,
    LptimRcl = 3
}en_lptim_tcksel_t;

/**
*******************************************************************************
** \brief LPTIMx GATE polarity control bit
** \note LPTIMx_CR GATE_P
************************************************************************/
typedef enum
{
    LptimGatePLow = 0,
    LptimGatePHigh = 1
}en_lptim_gatep_t;

/**
****************************************************************************************
** \brief LPTIMx clock selection
** \note LPTIMx_CR GATE
************************************************************************/
typedef enum
{
    LptimGateLow = 0,
    LptimGateHigh = 1
}en_lptim_gate_t;

/**
*******************************************************************************
** \brief LPTIMx TOG output enable bit
** \note LPTIMx_CR TOG
********************************************************************/
typedef enum
{
    LptimTogEnLow = 0,
    LptimTogEnHigh = 1
}en_lptim_togen_t;

/**
************************************************************************************
** \brief LPTIMx CT counter/timer function selection
** \note LPTIMx_CR CT
************************************************************************/
typedef enum
{
    LptimTimerFun = 0, //Alarm function, the timer counts using the clock selected by TCK_SEL
    LptimCntFun = 1 //Counter function. The counter counts using the falling edge of the external input. The sampling clock uses the clock selected by TCK_SEL.
}en_lptim_ct_t;

/**
****************************************************************************
** \brief LPTIMx timer operating mode
** \note LPTIMx_CR MD
************************************************************************/
typedef enum
{
    LptimMode1 = 0, //Mode 1: No reload, 16-bit counter/timer
    LptimMode2 = 1 //Mode 2: Auto-reload, 16-bit counter/timer
}en_lptim_md_t;

/**
************************************************************************************
** \brief LPTIMx initialization configuration structure
** \note
************************************************************************/
typedef struct
{ 
    en_lptim_prs_t enPrs; 
    en_lptim_tcksel_t enTcksel; 
    en_lptim_gatep_t enGatep; 
    en_lptim_gate_t enGate; 
    en_lptim_togen_t enTogen; 
    en_lptim_ct_t enCt; 
    en_lptim_md_t enMd; 
    uint16_t u16Arr;
}stc_lptim_cfg_t;

/****************************************************************************** 
* Global variable declarations ('extern', definition in C source) 
*******************************************************************************/

/****************************************************************************** 
* Global function prototypes (definition in C source) *******************************************************************************/
extern void Lptim_ConfIt(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus);
extern void Lptim_Cmd(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus);
extern boolean_t Lptim_GetItStatus(M0P_LPTIMER_TypeDef* Lptimx);
extern void Lptim_ClrItStatus(M0P_LPTIMER_TypeDef* Lptimx);
extern en_result_t Lptim_Init(M0P_LPTIMER_TypeDef* Lptimx, stc_lptim_cfg_t* InitStruct);

#ifdef __cplusplus
#endif

#endif //__LPTIM_H__
/****************************************************************************** 
*EOF (not truncated) 
*******************************************************************************/

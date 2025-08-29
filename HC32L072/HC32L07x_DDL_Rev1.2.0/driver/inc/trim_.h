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
* @file trim.h 
* 
* @brief Header file for TRIM functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __TRIM_H__
#define __TRIM_H__

/**************************************************************************** 
* Include files 
*******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup TrimGroup Clock Trimming (TRIM) 
** 
******************************************************************************/
//@{

/****************************************************************************** 
** Global pre-processor symbols/macros ('#define') 
******************************************************************************/

/****************************************************************************** 
* Global type definitions
******************************************************************************/

/**
******************************************************************************
** \brief Monitor mode enable enumeration definition (MON_EN)
*****************************************************************************/
typedef enum en_trim_monitor
{
    TrimMonDisable = 0u, ///< Disable
    TrimMonEnable = 0x40u, ///< Enable
}en_trim_monitor_t;

/**
******************************************************************************
** \brief Calibration/monitor clock selection enumeration definition (CALCLK_SEL)
*****************************************************************************/
typedef enum en_trim_calclksel
{
    TrimCalMskRCH = 0x000u, ///< RCH
    TrimCalMskXTH = 0x010u, ///< XTH
    TrimCalMskRCL = 0x020u, ///< RCL
    TrimCalMskXTL = 0x030u, ///< XTL
    TrimCalMskPLL = 0x100u, ///< PLL
}en_trim_calclksel_t;

/**
******************************************************************************
** \brief Reference Clock Select Enumeration Redefined (REFCLK_SEL)
*************************************************************************/
typedef enum en_trim_refclksel
{
    TrimRefMskRCH = 0x0u, ///< RCH
    TrimRefMskXTH = 0x2u, ///< XTH
    TrimRefMskRCL = 0x4u, ///< RCL
    TrimRefMskXTL = 0x6u, ///< XTL
    TrimRefMskIRC10K = 0x8u, ///< IRC10K
    TrimRefMskExtClk = 0xau, ///< External input clock
}en_trim_refclksel_t;

/**
******************************************************************************
** \brief Interrupt flag type enumeration redefinition
*************************************************************************/
typedef enum en_trim_inttype
{
    TrimStop = 0x01u, ///< Reference counter stop flag
    TrimCalCntOf = 0x02u, ///< Calibration counter overflow flag
    TrimXTLFault = 0x04u, ///< XTL failure flag
    TrimXTHFault = 0x08u, ///< XTH fault flag
    TrimPLLFault = 0x10u, ///< PLL fault flag
}en_trim_inttype_t;

/**
**************************************************************************
** \brief TRIM configuration structure definition
*************************************************************************/
typedef struct stc_trim_cfg
{
    en_trim_monitor_t enMON; ///< Monitor mode enable
    en_trim_calclksel_t enCALCLK; ///< Calibration clock selection
    uint32_t u32CalCon; ///< Calibration counter overflow value configuration
    en_trim_refclksel_t enREFCLK; ///< Reference clock selection
    uint32_t u32RefCon; ///< Reference counter initial value configuration
}stc_trim_cfg_t;

/*******************************************************************************
* Global variable declarations ('extern', definition in C source)
************************************************************************/

/**************************************************************************************
* Global function prototypes (definition in C source)
***************************************************************************/
///<<Function configuration and operation functions
///<Trim configuration and initialization
en_result_t Trim_Init(stc_trim_cfg_t* pstcCfg);
///<Calibration/monitoring start/stop
void Trim_Run(void);
void Trim_Stop(void);

///<Reference counter count value acquisition
uint32_t Trim_RefCntGet(void);
///<Get the calibration counter value
uint32_t Trim_CalCntGet(void);

///<Interrupt operation related functions
///Interrupt enable/disable
void Trim_EnableIrq(void);
void Trim_DisableIrq(void);
///<Get the interrupt flag
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType);
///<Clear the interrupt flag
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType);

//@} // TrimGroup

#ifdef__cplusplus
#endif


#endif /* __TRIM_H__ */
/****************************************************************************** 
* EOF (not truncated) 
*******************************************************************************/

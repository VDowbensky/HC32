/******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file trim.h
 **
 ** TRIM Data structure and API declaration
 **  
 **
 ** History:
 **   - 2018-04-21   Lux     V1.0
 **
 *****************************************************************************/

#ifndef __TRIM_H__
#define __TRIM_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
 ** \brief Monitoring Mode Enable Enumeration definition (MON_EN)
 *****************************************************************************/
typedef enum en_trim_monitor
{
    TrimMonDisable = 0u,            ///< disable
    TrimMonEnable  = 1u,            ///< enable
}en_trim_monitor_t; 
 
 /**
 ******************************************************************************
 ** \brief Calibration / monitoring clock selection enumeration definition (CALCLK_SEL)
 *****************************************************************************/
typedef enum en_trim_calclksel
{
    TrimCalRCH = 0u,            ///< RCH
    TrimCalXTH = 1u,            ///< XTH
    TrimCalRCL = 2u,            ///< RCL
    TrimCalXTL = 3u,            ///< XTL
    TrimCalPLL = 4u,            ///< PLL
}en_trim_calclksel_t;

/**
 ******************************************************************************
 ** \brief Reference clock selection enumeration definition (REFCLK_SEL)
 *****************************************************************************/
typedef enum en_trim_refclksel
{
    TrimRefRCH    = 0u,            ///< RCH
    TrimRefXTH    = 1u,            ///< XTH
    TrimRefRCL    = 2u,            ///< RCL
    TrimRefXTL    = 3u,            ///< XTL
    TrimRefIRC10K = 4u,            ///< IRC10K
    TrimRefExtClk = 5u,            ///< External input clock
}en_trim_refclksel_t;

/**
 ******************************************************************************
 ** \brief Interrupt flag type enumeration definition
 *****************************************************************************/
typedef enum en_trim_inttype
{
    TrimStop     = 0u,            ///< Reference counter stop flag
    TrimCalCntOf = 1u,            ///< Calibration counter overflow flag
    TrimXTLFault = 2u,            ///< XTL Failure flag
    TrimXTHFault = 3u,            ///< XTH Failure flag
    TrimPLLFault = 4u,            ///< PLL Failure flag
}en_trim_inttype_t;

/**
 ******************************************************************************
 ** \brief TRIM Configuration structure definition 
 *****************************************************************************/
typedef struct stc_trim_config
{
    en_trim_monitor_t    enMON;         ///< Monitoring mode enable
    en_trim_calclksel_t  enCALCLK;      ///< Calibration clock selection
    uint32_t             u32CalCon;     ///< Calibration counter overflow value configuration
    en_trim_refclksel_t  enREFCLK;      ///< Reference clock selection
    uint32_t             u32RefCon;     ///< Reference counter initial value configuration
    
    func_ptr_t           pfnTrimCb;     ///< TRIM Interrupt service callback function[void function(void)]
}stc_trim_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
///<<Function configuration and operation function
///<Trim Configuration and initialization
en_result_t Trim_Init(stc_trim_config_t* pstcConfig);
///<Calibration / monitoring start / stop
en_result_t Trim_Run(void);
en_result_t Trim_Stop(void);

///<Reference counter count value acquisition
uint32_t Trim_RefCntGet(void);
///<Calibration counter count value acquisition
uint32_t Trim_CalCntGet(void);
 
///<Interrupt operation related function
///Interrupt enable/disable
en_result_t Trim_EnableIrq(void);
en_result_t Trim_DisableIrq(void);
///<Interrupt flag acquisition
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType);
///<Interrupt flag clear
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType);

//@} // TrimGroup

#ifdef __cplusplus
#endif


#endif /* __TRIM_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



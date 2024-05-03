/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file lpt.h
 **
 ** Low-power timer data structure and API statement
 **  
 **
 ** History:
 **   - 2018-04-15   Husj     First version
 **
 *****************************************************************************/

#ifndef __LPT_H__
#define __LPT_H__

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
 *******************************************************************************
 ** \defgroup LptGroup Low Power Timer (LPT)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief GATE Polarity control data type definition (GATE_P)
 *****************************************************************************/
typedef enum en_lpt_gatep
{
    LptActHighLevel = 0u,            ///< Active high
    LptActLowLevel  = 1u,            ///< Active low
}en_lpt_gatep_t;

/**
 ******************************************************************************
 ** \brief Timer gating data type redefinition (GATE)
 *****************************************************************************/
typedef enum en_lpt_gate
{
    LptGateDisable = 0u,            ///< No gate
    LptGateEnable  = 1u,            ///< Gating enable
}en_lpt_gate_t;

/**
 ******************************************************************************
 ** \brief Lptimer Clock selection data type definition (TCK_SEL)
 *****************************************************************************/
typedef enum en_lpt_clksel
{
    LptPCLK   = 0u,           ///< PCLK
    LptXIL32K = 2u,           ///< XIL32K
    LptIRC32K = 3u,           ///< IRC32K
}en_lpt_clksel_t;

/**
 ******************************************************************************
 ** \brief Toggle output enable data type redefinition (TOG_EN)
 *****************************************************************************/
typedef enum en_lpt_toggle
{
    LptTogDisable = 0u,            ///< Toggle output disable
    LptTogEnable  = 1u,            ///< Toggle output enable
}en_lpt_toggle_t;

/**
 ******************************************************************************
 ** \brief Count/Timer Function Select Data Type Redefinition (CT)
 *****************************************************************************/
typedef enum en_lpt_function
{
    LptTimer   = 0u,            ///< Timer function
    LptCounter = 1u,            ///< Counter function
}en_lpt_function_t;


/**
 ******************************************************************************
 ** \brief Timer working mode data type definition (MD)
 *****************************************************************************/
typedef enum en_lpt_mode
{
    Lpt16bitFreeMode  = 0u,         ///< Free-running 16-bit counter/timer
    Lpt16bitArrMode   = 1u,         ///< Automatically reload 16-bit counter/timer
}en_lpt_mode_t;

/**
 ******************************************************************************
 ** \brief Timer operation control data type definition (TR)
 *****************************************************************************/
typedef enum en_lpt_start
{
    LptTRDisable = 0u,            ///< stop
    LptTREnable  = 1u,            ///< run
}en_lpt_start_t;

/**
 ******************************************************************************
 ** \brief Lptimer Configuration structure definition 
 *****************************************************************************/
typedef struct stc_lpt_config
{
    en_lpt_gatep_t    enGateP;      ///< Gated polarity control
    en_lpt_gate_t     enGate;       ///< Gating enable
    en_lpt_clksel_t   enTckSel;     ///< Clock selection
    en_lpt_toggle_t   enTog;        ///< Toggle output enable
    en_lpt_function_t enCT;         ///< Timing/counting mode selection
    en_lpt_mode_t     enMD;         ///< Work mode selection
    
    func_ptr_t pfnLpTimCb;          ///< LpTimer interrupt service callback function[void function(void)]
}stc_lpt_config_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//Interrupt related function 
//Interrupt flag acquisition
boolean_t Lpt_GetIntFlag(void);
//Interrupt flag clear
en_result_t Lpt_ClearIntFlag(void);
//Interrupt enable/disable
en_result_t Lpt_EnableIrq (void);
en_result_t Lpt_DisableIrq(void);

//Initialization and related function operations
//Lptimer configuration and initialization
en_result_t Lpt_Init(stc_lpt_config_t* pstcConfig);
//Lptimer start stop
en_result_t Lpt_Run(void);
en_result_t Lpt_Stop(void);
//Reload value setting
en_result_t Lpt_ARRSet(uint16_t u16Data);
//Count value acquisition
en_result_t Lpt_Cnt16Set(uint16_t u16Data);
uint16_t Lpt_Cnt16Get(void);

//@} // LptGroup

#ifdef __cplusplus
#endif


#endif /* __LPT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



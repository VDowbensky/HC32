/*******************************************************************************
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
/******************************************************************************/
/** \file OPA.h
 **
 ** Headerfile for OPA functions
 ** @link OPA Group Some description @endlink 
 **
 ** History:
 **   - 2018-04-15   Devi     First Version
 **
 ******************************************************************************/

#ifndef __OPA_H__
#define __OPA_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup OPAGroup  (OPA)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/
/**
************************************************** *****************************
  ** \brief OPA channel selection
  ** \note
  ************************************************** ****************************/
typedef enum en_opa_channel
{
    OPA0 = 0u, ///<<OPA0
    OPA1 = 1u, ///<<OPA1
    OPA2 = 2u, ///<<OPA2
}en_opa_channel_t;

/**
************************************************** *****************************
  ** \brief OPA reverse gain selection
  ** \note
  ************************************************** ****************************/
typedef enum en_opa_invert_pagagain
{
    Gain15         = 0u,               ///< Reverse gain 15 times
    Gain07         = 1u,               ///< Reverse gain 7 times
    Gain13_3       = 2u,               ///< Reverse gain 13/3 times
    Gain03         = 3u,               ///< Reverse gain 3 times
    Gain05_3       = 4u,               ///< Reverse gain 5/3 times
    Gain01         = 5u,               ///< Reverse gain 1 times
    Gain01_3        = 6u,               ///< Reverse gain 1/3 times
    Gain11_5       = 7u,               ///< Reverse gain 11/5 times   
}en_opa_invert_pagagain_t;

/**
************************************************** *****************************
  ** \brief OPA forward gain selection
  ** \note
  ************************************************** ****************************/
typedef enum en_opa_noinvert_pagagain
{
    Gain16         = 0u,               ///< Forward gain16Times
    Gain08         = 1u,               ///< Forward gain8Times
    Gain16_3       = 2u,               ///< Forward gain16/3Times
    Gain04         = 3u,               ///< Forward gain4Times
    Gain08_3       = 4u,               ///< Forward gain8/3Times
    Gain02         = 5u,               ///< Forward gain2Times
    Gain04_3       = 6u,               ///< Forward gain4/3Times
    Gain16_5       = 7u,               ///< Forward gain16/5Times   
}en_opa_noinvert_pagagain_t;

/**
************************************************** *****************************
  ** \brief meter gain configuration
  ************************************************** ****************************/
typedef enum opa_metergain
{
    OpaMeterGain3 = 0u,                        
    OpaMeterGain1_3 = 1u,               
    OpaMeterGain1 = 2u,                             
}en_opa_metergain_t;


/**
************************************************** *****************************
  ** \brief opa mode selection
  ************************************************** ****************************/
typedef enum opa_modesel
{
    OpaUintMode     = 0u,           ///< PGA unit gain        
    OpaForWardMode  = 1u,           ///< Positive input PGA            
    OpaOppositeMode = 2u,           ///< Reverse input PGA              
    OpaThreeOppMode = 3u,           ///< 3 OPA cascade reverse input PGA
    OpaThreeForMode = 4u,           ///< 3 OPA cascade positive input PGA
    OpaDiffMode     = 5u,           ///< Two op amp differential input PGA
    OpaMeterMode    = 6u,           ///< Instrumentation amplifier
    OpaGpMode       = 7u,           ///< Universal op amp       
}en_opa_modesel_t;

/**
************************************************** *****************************
  ** \brief opa calibration mode
  ************************************************** ****************************/
typedef enum opa_calsel
{
    OpaSoftMode         = 0u,           ///< Software control     
    OpaSoftTriggerMode  = 1u,           ///< Software trigger     
    OpaADCTriggerMode   = 2u,           ///< ADC trigger                  
}en_opa_calsel_t;

/**
************************************************** ****************************
  ** \brief OPA gain configuration
  ************************************************** ***************************/
typedef struct stc_opa_gain_config
{
    en_opa_invert_pagagain_t     enInGain;  ///< Reverse gain
    en_opa_noinvert_pagagain_t   enNoInGain;  ///< Forward gain
}stc_opa_gain_config_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< OPA initialization
en_result_t OPA_Init(void);
///< OPA deinitialize
en_result_t OPA_DeInit(void);
///< OPA basic function settings
en_result_t OPA_Operate(en_opa_channel_t enchannel ,en_opa_modesel_t enMode,stc_opa_gain_config_t *pstrGain);
///< OPA triple cascade settings
en_result_t OPA_ThreeOperate(en_opa_modesel_t enMode,stc_opa_gain_config_t *pstrGain0,stc_opa_gain_config_t *pstrGain1,stc_opa_gain_config_t *pstrGain2);
///< OPA meter mode
en_result_t OPA_MeterOperate(en_opa_metergain_t enGainMode);
///< OPA calibration mode
en_result_t OPA_Cal(en_opa_calsel_t enCalMode);


//@} // OPA Group

#ifdef __cplusplus
#endif

#endif /* __OPA_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



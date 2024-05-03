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
/** \file pca.h
 **
** PCA (Programmable Count Array) data structure and API statement
  **
  **
  ** History:
  ** - 2017-04-15 Husj First version
  **
  ************************************************** ***************************/

#ifndef __PCA_H__
#define __PCA_H__

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
 ** \defgroup PcaGroup Programmable Counter Array (PCA)
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
** \brief PCA module select data type definitions
  ************************************************** ***************************/
typedef enum en_pca_module
{
    Module0    = 0u,        ///< Module0
    Module1    = 1u,        ///< Module1
    Module2    = 2u,        ///< Module2
    Module3    = 3u,        ///< Module3
    Module4    = 4u,        ///< Module4
}en_pca_module_t;

/**
************************************************** ****************************
  ** \brief PCA Count Start/Stop Control Data Type definitions (CR)
  ************************************************** ***************************/
typedef enum en_pca_start
{
    CRStop  = 0u,            ///< Stop counting
    CRStart = 1u,            ///< Start counting
}en_pca_start_t;

/**
************************************************** ****************************
  ** \brief PCA IDLE mode start/stop control data type redefinition (CIDL)
  ************************************************** ***************************/
typedef enum en_pca_cidl
{
    IdleGoOn = 0u,            ///< In sleep mode PCA continue working
    IdleStop = 1u,            ///< In sleep mode PCA stops working
}en_pca_cidl_t;

/**
************************************************** ****************************
  ** \brief PCA Module4 WDT Function Control Data Type definitions (WDTE)
  ************************************************** ***************************/
typedef enum en_pca_wdte
{
    PCAWDTDisable = 0u,            ///< Turn off PCAModule4 WDT function
    PCAWDTEnable  = 1u,            ///< Start PCAModule4 WDT function
}en_pca_wdte_t;

/**
************************************************** ****************************
  ** \brief PCA clock division and clock source selection function data type definitions (CPS)
  ************************************************** ***************************/
typedef enum en_pca_clksel
{
    PCAPCLKDiv32  = 0u,         ///< PCLK/32
    PCAPCLKDiv16  = 1u,         ///< PCLK/16
    PCAPCLKDiv8   = 2u,         ///< PCLK/8
    PCAPCLKDiv4   = 3u,         ///< PCLK/4
    PCAPCLKDiv2   = 4u,         ///< PCLK/2
    PCATimer0Over = 5u,         ///< timer0 overflow
    PCATimer1Over = 6u,         ///< timer1 overflow
    PCAECI        = 7u,         ///< ECI external clock, clock PCLK four-way sampling
}en_pca_clksel_t;

/**
************************************************** ****************************
  ** \brief PCA Allows Comparator Function to Control Data Type definitions (ECOM)
  ************************************************** ***************************/
typedef enum en_pca_ecom
{
    ECOMDisable = 0u,            ///< Disable comparator function
    ECOMEnable  = 1u,            ///< Enable comparator function
}en_pca_ecom_t;

/**
************************************************** ****************************
  ** \brief PCA positive edge capture control bit data type definitions (CAPP)
  ************************************************** ***************************/
typedef enum en_pca_capp
{
    CAPPDisable = 0u,            ///< Disable rising edge capture
    CAPPEnable  = 1u,            ///< Enable rising edge capture
}en_pca_capp_t;

/**
************************************************** ****************************
  ** \brief PCA Negative Edge Capture Control Bit Data Type Redefinition (CAPN)
  ************************************************** ***************************/
typedef enum en_pca_capn
{
    CAPNDisable = 0u,            ///< Disable falling edge capture
    CAPNEnable  = 1u,            ///< Enable falling edge capture
}en_pca_capn_t;

/**
************************************************** ****************************
  ** \brief PCA Match Control Bit Data Type Redefinition (MAT)
  ************************************************** ***************************/
typedef enum en_pca_mat
{
    MATDisable = 0u,            ///< Disable matching
    MATEnable  = 1u,            ///< Enable matching
}en_pca_mat_t;

/**
************************************************** ****************************
  ** \brief PCA Flip Control Bit Data Type definitions (TOG)
  ************************************************** ***************************/
typedef enum en_pca_tog
{
    TOGDisable = 0u,            ///< Disable toggle function
    TOGEnable  = 1u,            ///< Enable toggle function
}en_pca_tog_t;

/**
************************************************** ****************************
  ** \brief PCA 8bit Pulse Width Modulation Control Data Type definitions (8bitPWM)
  ************************************************** ***************************/
typedef enum en_pca_pwm_8_bit
{
    PCA8bitPWMDisable = 0u,            ///< Disable PWM function
    PCA8bitPWMEnable  = 1u,            ///< Enable CCPx pin as PWM output
}en_pca_8bit_pwm_t;

/**
************************************************** ****************************
  ** \brief PCA 16bit Pulse Width Modulation Control Data Type definitions (16bitPWM)
  ************************************************** ***************************/
typedef enum en_pca_pwm_16_bit
{
    PCA16bitPWMDisable = 0u,            ///< 16bitPWM disabled
    PCA16bitPWMEnable  = 1u,            ///< 16bitPWM enabled
}en_pca_16bit_pwm_t;

/**
************************************************** ****************************
  ** \brief PCA configuration structure definition
  ************************************************** ***************************/
typedef struct stc_pca_config
{
    en_pca_cidl_t     enCIDL;       ///< Mode start/stop control
    en_pca_wdte_t     enWDTE;       ///< WDT function control
    en_pca_clksel_t   enCPS;        ///< Clock division and clock source selection
    
    func_ptr_t        pfnPcaCb;     ///< Pca interrupt service callback function [void function(void)]
}stc_pca_config_t;

/**
************************************************** ****************************
  ** \brief PCA capture mode configuration structure definition
  ************************************************** ***************************/
typedef struct stc_pca_capmodconfig
{
    en_pca_ecom_t enECOM;                ///< Enable comparator function control
    en_pca_capp_t enCAPP;                ///< Positive edge capture control
    en_pca_capn_t enCAPN;                ///< Negative edge capture control
    en_pca_mat_t  enMAT;                 ///< Match control
    en_pca_tog_t  enTOG;                 ///< Toggle control
    en_pca_8bit_pwm_t  en8bitPWM;        ///< 8-bit pulse width modulation control
}stc_pca_capmodconfig_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//Interrupt related
//PCA interrupt flag acquisition
boolean_t Pca_GetIntFlag(en_pca_module_t enModule);
//PCA counter interrupt flag acquisition
boolean_t Pca_GetCntIntFlag(void);
//PCA interrupt flag clear
en_result_t Pca_ClearIntFlag(en_pca_module_t enModule);
//PCA counter interrupt flag clear
en_result_t Pca_ClearCntIntFlag(void);
//PCA interrupt enable
en_result_t Pca_EnableIrq (en_pca_module_t enModule);
//PCA counter interrupt enable
en_result_t Pca_EnableCntIrq (void);
//PCA interrupt disable
en_result_t Pca_DisableIrq(en_pca_module_t enModule);
//PCA counter interrupt disable
en_result_t Pca_DisableCntIrq(void);

//PCA configuration and operation
//PCA initialization
en_result_t Pca_Init(stc_pca_config_t* pstcConfig);
//PCA capture mode configuration
en_result_t Pca_CapModConfig(en_pca_module_t enModule, stc_pca_capmodconfig_t* pstcCapMod);
//PCA counter start/stop
en_result_t Pca_Run(void);
en_result_t Pca_Stop(void);
//PCA16 bit comparison data setting
en_result_t Pca_CmpData16Set(en_pca_module_t enModule, uint16_t u16Data);
//PCA captures 16-bit data acquisition
uint16_t Pca_CapData16Get(en_pca_module_t enModule);
//PCA comparison data high 8-bit setting
en_result_t Pca_CmpDataHSet(en_pca_module_t enModule, uint8_t u8Data);
//PCA comparison data low 8-bit setting
en_result_t Pca_CmpDataLSet(en_pca_module_t enModule, uint8_t u8Data);
//PCA count value setting / acquisition
en_result_t Pca_Cnt16Set(uint16_t u16Data);
uint16_t Pca_Cnt16Get(void);
//PCA cycle reload value setting/acquisition
en_result_t Pca_CARRSet(uint16_t u16Data);
uint16_t Pca_CARRGet(void);
//PCA Enhanced PWM function enable/disable
en_result_t Pca_Enable16bitPWM(void);
en_result_t Pca_Disable16bitPWM(void);
//PCA compares high speed output flag acquisition
boolean_t Pca_GetCmpHighFlag(en_pca_module_t enModule);
//@} // PcaGroup

#ifdef __cplusplus
#endif


#endif /* __PCA_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



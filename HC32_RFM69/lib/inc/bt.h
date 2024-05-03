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
/** \file bt.h
 **
 ** Basic timer data structure and API declaration
 ** @link BT Group Some description @endlink
 **
 ** History:
 **   - 2018-04-18   Husj     First Version
 **
 *****************************************************************************/

#ifndef __BT_H__
#define __BT_H__

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
 ** \defgroup BtGroup Base Timer (BT)
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
 ** \brief Timer selection data type redefinition
 *****************************************************************************/
typedef enum en_bt_unit
{
    TIM0    = 0u,           ///< Timer 0
    TIM1    = 1u,           ///< Timer 1
    TIM2    = 2u,           ///< Timer 2
}en_bt_unit_t;

/**
 ******************************************************************************
 ** \brief Working mode selection data type redefinition (MODE) (mode 0/1/23)
 *****************************************************************************/
typedef enum en_bt_work_mode
{
    BtWorkMode0  = 0u,         ///< Timer mode
    BtWorkMode1  = 1u,         ///< PWC mode
    BtWorkMode2  = 2u,         ///< Sawtooth mode
    BtWorkMode3  = 3u,         ///< Triangle wave mode
}en_bt_work_mode_t;

/**
 ******************************************************************************
 ** \brief Polarity Control Data Type Redefinition (GATE_P) (Mode 0)
 *****************************************************************************/
typedef enum en_bt_m0_gatep
{
    BtGatePositive = 0u,            ///< Active high
    BtGateOpposite = 1u,            ///< Active low
}en_bt_m0_gatep_t;

/**
 ******************************************************************************
 ** \brief TIM Prescaler Selection (PRS) (Mode 0/1/23)
 *****************************************************************************/
typedef enum en_bt_cr_timclkdiv
{
    BtPCLKDiv1   = 0u,           ///< Div 1
    BtPCLKDiv2   = 1u,           ///< Div 2
    BtPCLKDiv4   = 2u,           ///< Div 4
    BtPCLKDiv8   = 3u,           ///< Div 8
    BtPCLKDiv16  = 4u,           ///< Div 16
    BtPCLKDiv32  = 5u,           ///< Div 32
    BtPCLKDiv64  = 6u,           ///< Div 64
    BtPCLKDiv256 = 7u,           ///< Div 256
}en_bt_cr_timclkdiv_t;

/**
 ******************************************************************************
 ** \brief Count/Timer Function Select Data Type Redefinition (CT) (Mode 0/1/23)
 *****************************************************************************/
typedef enum en_bt_cr_ct
{
    BtTimer   = 0u,            ///< Timer function, the count clock is internal PCLK
    BtCounter = 1u,            ///< Counter function, the count clock is external ETR
}en_bt_cr_ct_t;


/**
 ******************************************************************************
 ** \brief Timer operating mode data type redefinition (MD) (mode 0)
 *****************************************************************************/
typedef enum en_bt_m0cr_md
{
    Bt32bitFreeMode  = 0u,         ///< 32-bit counter/timer
    Bt16bitArrMode  = 1u,         ///< Automatically reload 16-bit counter/timer
}en_bt_m0cr_md_t;

/**
 ******************************************************************************
** \brief BT0/BT1/BT2 interrupt type data type definition (mode 0/1/23)
 *****************************************************************************/
typedef enum en_bt_irq_type
{
    BtUevIrq   = 0u,         ///< Overflow/event update interrupt
    BtCA0Irq   = 2u,         ///< Capture/Compare Interrupt A (Mode 1/23 only)
    BtCB0Irq   = 5u,         ///< Capture/Compare Interrupt B (Mode 23 only)
    BtCA0E     = 8u,         ///< CH0A capture data loss flag (mode 23 only), not interrupt
    BtCB0E     = 11u,        ///< CH0B capture data loss flag (mode 23 only), not interrupt
    BtBkIrq    = 14u,        ///< Brake interrupt (mode 23 only)
    BtTrigIrq  = 15u,        ///< Trigger interrupt (mode 23 only)  
}en_bt_irq_type_t;

/**
 ******************************************************************************
 ** \brief Measurement start end data type definitions (Edg1stEdg2nd) (mode 1)
 *****************************************************************************/
typedef enum en_bt_m1cr_Edge
{
    BtPwcRiseToRise  = 0u,            ///< Rising edge to rising edge (period)
    BtPwcFallToRise  = 1u,            ///< Falling edge to rising edge (low level)
    BtPwcRiseToFall  = 2u,            ///< Rising edge to falling edge (high level)
    BtPwcFallToFall  = 3u,            ///< Falling edge to falling edge (period)
}en_bt_m1cr_Edge_t;

/**
 ******************************************************************************
 ** \brief PWC measurement test mode selection data type definitions (Oneshot) (mode 1)
 *****************************************************************************/
typedef enum en_bt_m1cr_oneshot
{
    BtPwcCycleDetect    = 0u,         ///< PWC cycle measurement
    BtPwcOneShotDetect  = 1u,         ///< PWC single measurement
}en_bt_m1cr_oneshot_t;

/**
 ******************************************************************************
 ** \brief PWC IA0 select data type definitions (IA0S) (mode 1)
 *****************************************************************************/
typedef enum en_bt_m1_mscr_ia0s
{
    BtIA0Input    = 0u,         ///< IAO input
    BtXORInput    = 1u,         ///< IA0 ETR GATE XOR(TIM0/1/2)/IA0 IA1 IA2 XOR(TIM3)
}en_bt_m1_mscr_ia0s_t;

/**
 ******************************************************************************
 ** \brief PWC IB0 select data type definitions (IB0S) (mode 1)
 *****************************************************************************/
typedef enum en_bt_m1_mscr_ib0s
{
    BtIB0Input    = 0u,         ///< IBO input
    BtTsInput     = 1u,         ///< Internal trigger TS selection signal
}en_bt_m1_mscr_ib0s_t;

/**
 ******************************************************************************
 ** \brief Output Polarity, Input Phase Data Type definitions (CCPA0/CCPB0/ETP/BKP) (Mode 1/23)
 *****************************************************************************/
typedef enum en_bt_port_polarity
{
    BtPortPositive      = 0u,         ///< Normal input and output
    BtPortOpposite      = 1u,         ///< 反向输入Output
}en_bt_port_polarity_t;

/**
 ******************************************************************************
 ** \brief Filter Select Data Type definitions (FLTET/FLTA0/FLAB0) (Mode 1/23)
 *****************************************************************************/
typedef enum en_bt_flt
{
    BtFltNone          = 0u,         ///< No filtering
    BtFltPCLKCnt3      = 4u,         ///< PCLK 3 consecutive valid
    BtFltPCLKDiv4Cnt3  = 5u,         ///< PCLK/4 3 consecutive valid
    BtFltPCLKDiv16Cnt3 = 6u,         ///< PCLK/16 3 consecutive valid
    BtFltPCLKDiv64Cnt3 = 7u,         ///< PCLK/64 3 consecutive valid
}en_bt_flt_t;

/**
 ******************************************************************************
 ** \brief Channel Compare Control Data Type definitions (OCMA/OCMB) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_fltr_ocm
{
    BtForceLow      = 0u,         ///< Forced to 0
    BtForceHigh     = 1u,         ///< Forced to 1
    BtCMPForceLow   = 2u,         ///< Forced to 0 when comparing matches
    BtCMPForceHigh  = 3u,         ///< Forced to 1 when comparing matches
    BtCMPInverse    = 4u,         ///< Flip level when comparing matches
    BtCMPOnePrdHigh = 5u,         ///< Output a high level of the count period when the match is matched
    BtPWMMode1      = 6u,         ///< Channel control is PWM mode 1
    BtPWMMode2      = 7u,         ///< Channel control is PWM mode 2
}en_bt_m23_fltr_ocm_t;

/**
 ******************************************************************************
 ** \brief Master-slave mode TS data type definitions (TS) (mode 1/23)
 *****************************************************************************/
typedef enum en_bt_mscr_ts
{
    BtTs0ETR        = 0u,         ///< ETR external input filtered phase selection signal
    BtTs1TIM0TRGO   = 1u,         ///< Timer0 TRGO output signal
    BtTs2TIM1TRGO   = 2u,         ///< Timer1 TRGO output signal
    BtTs3TIM2TRGO   = 3u,         ///< Timer2 TRGO output signal
    BtTs4TIM3TRGO   = 4u,         ///< Timer3 TRGO output signal
    //BtTs5IA0ED    = 5u,         ///< invalid
    BtTs6IAFP       = 6u,         ///< CH0A external input input filtered phase selection signal
    BtTs7IBFP       = 7u,         ///< CH0B external input input filtered phase selection letter
}en_bt_mscr_ts_t;

/**
 ******************************************************************************
 ** \brief PWM Output Mode Select Data Type definitions (COMP) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23cr_comp
{
    BtIndependentPWM      = 0u,         ///< Independent PWM output
    BtComplementaryPWM    = 1u,         ///< Complementary PWM output
}en_bt_m23cr_comp_t;

/**
 ******************************************************************************
 ** \brief Count Direction Select Data Type definitions (DIR) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23cr_dir
{
    BtCntUp      = 0u,         ///< Count up
    BtCntDown    = 1u,         ///< Count down
}en_bt_m23cr_dir_t;

/**
 ******************************************************************************
 ** \brief Count direction selection data type definitions (PWM2S) (mode 23)
 *****************************************************************************/
typedef enum en_bt_m23cr_pwm2s
{
    BtDoublePointCmp      = 0u,         ///< Two-point comparison enable, use CCRA, CCRB compare control OCRFA output
    BtSinglePointCmp      = 1u,         ///< Single point comparison enable, use CCRA comparison control OCRYA output
}en_bt_m23cr_pwm2s_t;

/**
 ******************************************************************************
 ** \brief GATE Capture or Compare Function in PWM Complementary Mode Select Data Type Redefinition (CSG) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23cr_csg
{
     BtPWMCompGateCmpOut    = 0u,         ///< In PWM complementary mode, Gate is used as a comparison output.
     BtPWMCompGateCapIn     = 1u,         ///< Gate is used as capture input in PWM complementary mode
}en_bt_m23cr_csg_t;


/**
 ******************************************************************************
 ** \brief Compare Capture Register Data Type Redefinition (CCR0A, CCR0B) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_ccrx
{
     BtCCR0A    = 0u,         ///< CCR0A compare capture register
     BtCCR0B    = 1u,         ///< CCR0B compare capture register
}en_bt_m23_ccrx_t;

/**
 ******************************************************************************
 ** \brief  OCREF Clear Source Select Data Type Redefinition (OCCS) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23ce_occs
{
     BtOC_Ref_Clr  = 0u,         ///< OC_Ref_Clr from VC
     BtETRf        = 1u,         ///< External ETRf
}en_bt_m23ce_occs_t;

/**
 ******************************************************************************
 ** \brief  Compare Match Interrupt Mode Select Data Type Redefinition (CIS/CISB) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_cisa_cisb
{
     BtCmpIntNone        = 0u,         ///< No comparison match interrupt
     BtCmpIntRise        = 1u,         ///< Compare match rising edge interrupt
     BtCmpIntFall        = 2u,         ///< Compare match falling edge interrupt
     BtCmpIntRiseFall    = 3u,         ///< Compare match rising edge falling edge interrupt
}en_bt_m23_cisa_cisb_t;

/**
 ******************************************************************************
 ** \brief BT port control - CHx output status control (BKSA/BKSB) when braking (mode 23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_bt_m23_crch0_bks
{
    BtCHxBksHiZ         = 0u,         ///< When the brake is enabled, the CHx port outputs a high impedance state.
    BtCHxBksNorm        = 1u,         ///< When the brake is enabled, the CHx port outputs normally.
    BtCHxBksLow         = 2u,         ///< When the brake is enabled, the CHx port outputs a low level.
    BtCHxBksHigh        = 3u,         ///< When the brake is enabled, the CHx port outputs a high level.
}en_bt_m23_crch0_bks_t;

/**
 ******************************************************************************
** \brief BT port control - CHx rising edge falling edge capture (CRx/CFx) (mode 23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_bt_m23_crch0_cfx_crx
{
    BtCHxCapNone        = 0u,         ///< CHx channel capture disabled
    BtCHxCapRise        = 1u,         ///< CHx channel rising edge capture enable
    BtCHxCapFall        = 2u,         ///< CHx channel falling edge capture enable
    BtCHxCapFallRise    = 3u,         ///< CHx channel rising edge falling edge capture is enabled
}en_bt_m23_crch0_cfx_crx_t;

/**
 ******************************************************************************
** \brief BT Port Control - CHx Compare Capture Mode (CSA/CSB) (Mode 23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_bt_m23_crch0_csa_csb
{
    BtCHxCmpMode        = 0u,         ///< CHx channel is set to compare mode
    BtCHxCapMode        = 1u,         ///< CHx channel is set to capture mode
}en_bt_m23_crch0_csa_csb_t;

/**
 ******************************************************************************
 ** \brief  Compare mode DMA comparison trigger selection Data type redefinition (CCDS) (mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_mscr_ccds
{
     BtCmpTrigDMA  = 0u,         ///< Compare match trigger DMA
     BtUEVTrigDMA  = 1u,         ///< Event update instead of compare match trigger DMA
}en_bt_m23_mscr_ccds_t;

/**
 ******************************************************************************
 ** \brief  Master-slave mode selection Data type redefinition (MSM) (mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_mscr_msm
{
     BtSlaveMode    = 0u,         ///< Slave mode
     BtMasterMode   = 1u,         ///< Master mode
}en_bt_m23_mscr_msm_t;

/**
 ******************************************************************************
 ** \brief  Trigger Master Mode Output Source Data Type Redefinition (MMS) (Mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_mscr_mms
{
     BtMasterUG         = 0u,         ///< UG (software update) source
     BtMasterCTEN       = 1u,         ///< CTEN source
     BtMasterUEV        = 2u,         ///< UEV update source
     BtMasterCMPSO      = 3u,         ///< Compare match select output source
     BtMasterOCA0Ref    = 4u,         ///< OCA0_Ref source
     BtMasterOCB0Ref    = 5u,         ///< OCB0_Ref source
     //BtMasterOCB0Ref  = 6u,
     //BtMasterOCB0Ref  = 7u,
}en_bt_m23_mscr_mms_t;

/**
 ******************************************************************************
 ** \brief  Trigger slave mode data type redefinition (SMS) (mode 23)
 *****************************************************************************/
typedef enum en_bt_m23_mscr_sms
{
     BtSlaveIClk        = 0u,         ///< Use internal clock
     BtSlaveResetTIM    = 1u,         ///< Reset function
     BtSlaveTrigMode    = 2u,         ///< Trigger mode
     BtSlaveEClk        = 3u,         ///< External clock mode
     BtSlaveCodeCnt1    = 4u,         ///< Quadrature encoding count mode 1
     BtSlaveCodeCnt2    = 5u,         ///< Quadrature Code Counting Mode 2
     BtSlaveCodeCnt3    = 6u,         ///< Orthogonal code counting mode 3
     BtSlaveGateCtrl    = 7u,         ///< Gating function
}en_bt_m23_mscr_sms_t;

/**
 ******************************************************************************
 ** \brief Timer Run Control Data Type Redefinition (CTEN)
 *****************************************************************************/
typedef enum en_bt_start
{
    BtCTENDisable = 0u,            ///< stop
    BtCTENEnable  = 1u,            ///< run
}en_bt_start_t;

/**
 ******************************************************************************
 ** \brief BaseTimer mode0 Configuration structure definition (mode 0)
 *****************************************************************************/
typedef struct stc_bt_mode0_config
{
    en_bt_work_mode_t     enWorkMode;       ///< Working mode setting
    en_bt_m0_gatep_t      enGateP;          ///< Gated polarity control
    boolean_t             bEnGate;          ///< Gating enable
    en_bt_cr_timclkdiv_t  enPRS;            ///< Pre-frequency configuration
    boolean_t             bEnTog;           ///< Flip output enable
    en_bt_cr_ct_t         enCT;             ///< Timing / counting function selection
    en_bt_m0cr_md_t       enCntMode;        ///< Count mode configuration
    
    func_ptr_t            pfnTim0Cb;        ///< Timer0 Interrupt service callback function[void function(void)]
    func_ptr_t            pfnTim1Cb;        ///< Timer1 Interrupt service callback function[void function(void)]
    func_ptr_t            pfnTim2Cb;        ///< Timer2 Interrupt service callback function[void function(void)]
}stc_bt_mode0_config_t;

/**
 ******************************************************************************
 ** \brief BaseTimer mode1 Configuration Structure Definition (Mode 1)
 *****************************************************************************/
typedef struct stc_bt_mode1_config
{
    en_bt_work_mode_t     enWorkMode;       ///< Working mode setting
    en_bt_cr_timclkdiv_t  enPRS;            ///< Prescaler configuration
    en_bt_cr_ct_t         enCT;             ///< Timing / counting function selection
    en_bt_m1cr_oneshot_t  enOneShot;        ///< Single measurement / cycle measurement selection
    
    
    func_ptr_t          pfnTim0Cb;        ///< Timer0 Interrupt service callback function[void function(void)]
    func_ptr_t          pfnTim1Cb;        ///< Timer1 Interrupt service callback function[void function(void)]
    func_ptr_t          pfnTim2Cb;        ///< Timer2 Interrupt service callback function[void function(void)]
}stc_bt_mode1_config_t;

/**
 ******************************************************************************
 ** \brief PWC input configuration structure definition (mode 1)
 *****************************************************************************/
typedef struct stc_bt_pwc_input_config
{
    en_bt_mscr_ts_t          enTsSel;       ///< Trigger input source selection
    en_bt_m1_mscr_ia0s_t     enIA0Sel;      ///< CHA0 input selection
    en_bt_m1_mscr_ib0s_t     enIB0Sel;      ///< CHB0 input selection
    en_bt_port_polarity_t    enETRPhase;    ///< ETR phase selection
    en_bt_flt_t              enFltETR;      ///< ETR filter settings
    en_bt_flt_t              enFltIA0;      ///< CHA0 filter setting
    en_bt_flt_t              enFltIB0;      ///< CHB0 filter setting
}stc_bt_pwc_input_config_t;

/**
 ******************************************************************************
 ** \brief BaseTimer mode23 Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_bt_mode23_config
{
    en_bt_work_mode_t         enWorkMode;       ///< Working mode setting
    en_bt_m23cr_dir_t         enCntDir;         ///< Counting direction
    en_bt_cr_timclkdiv_t      enPRS;            ///< Clock prescaler configuration
    en_bt_cr_ct_t             enCT;             ///< Timing / counting function selection
    en_bt_m23cr_comp_t        enPWMTypeSel;     ///< PWM mode selection (independent/complementary)
    en_bt_m23cr_pwm2s_t       enPWM2sSel;       ///< OCREFA double point comparison function selection
    boolean_t                 bOneShot;         ///< Single trigger mode enable/disable
    boolean_t                 bURSSel;          ///< Update source selection
    
    func_ptr_t                pfnTim0Cb;        ///< Timer0 Interrupt service callback function [void function(void)]
    func_ptr_t                pfnTim1Cb;        ///< Timer1 Interrupt service callback function [void function(void)]
		func_ptr_t                pfnTim2Cb;        ///< Timer1 Interrupt service callback function [void function(void)]
}stc_bt_mode23_config_t;

/**
 ******************************************************************************
 ** \brief GATE captures or compares functions in PWM Complementary Mode Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_gate_config
{
    en_bt_m23cr_csg_t        enGateFuncSel;      ///< Gate comparison, capture function selection
    boolean_t                bGateRiseCap;       ///< Upper edge capture effective control when GATE is used as capture function
    boolean_t                bGateFallCap;       ///< When GATE is used as a capture function, the lower edge capture is effectively controlled.
}stc_bt_m23_gate_config_t;

/**
 ******************************************************************************
 ** \brief CHA/CHB channel comparison control Configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_compare_config
{
    en_bt_m23_crch0_csa_csb_t  enCh0ACmpCap;     ///< CH0A comparison/Capture function selection
    en_bt_m23_fltr_ocm_t       enCH0ACmpCtrl;    ///< CH0A channel comparison control
    en_bt_port_polarity_t      enCH0APolarity;   ///< CH0AOutput极性control
    boolean_t                  bCh0ACmpBufEn;    ///< Compare A cache function enable/disable
    en_bt_m23_cisa_cisb_t      enCh0ACmpIntSel;  ///< CHA compare match interrupt selection
    
    en_bt_m23_crch0_csa_csb_t  enCh0BCmpCap;     ///< CH0BComparison/Capture function selection
    en_bt_m23_fltr_ocm_t       enCH0BCmpCtrl;    ///< CH0B channel comparison control
    en_bt_port_polarity_t      enCH0BPolarity;   ///< CH0B output polarity control
    boolean_t                  bCH0BCmpBufEn;    ///< Compare B cache function enable/disable
    en_bt_m23_cisa_cisb_t      enCH0BCmpIntSel;  ///< CHB0 Compare match interrupt selection
}stc_bt_m23_compare_config_t;

/**
 ******************************************************************************
 ** \brief CHA/CHB channel capture control Configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_input_config
{
    en_bt_m23_crch0_csa_csb_t  enCh0ACmpCap;     ///< CH0A comparison/Capture function selection
    en_bt_m23_crch0_cfx_crx_t  enCH0ACapSel;     ///< CH0A Capture edge selection
    en_bt_flt_t                enCH0AInFlt;      ///< CH0A Channel capture filter control
    en_bt_port_polarity_t      enCH0APolarity;   ///< CH0A Input phase
    
    en_bt_m23_crch0_csa_csb_t  enCh0BCmpCap;     ///< CH0B Comparison/Capture function selection
    en_bt_m23_crch0_cfx_crx_t  enCH0BCapSel;     ///< CH0B Capture edge selection
    en_bt_flt_t                enCH0BInFlt;      ///< CH0B Channel capture filter control
    en_bt_port_polarity_t      enCH0BPolarity;   ///< CH0B Input phase
    
}stc_bt_m23_input_config_t;   

/**
 ******************************************************************************
 ** \brief ETRInput phase Filter configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_etr_input_config
{
    en_bt_port_polarity_t     enETRPolarity;  ///< ETR Input polarity setting
    en_bt_flt_t               enETRFlt;       ///< ETR Filter setting
}stc_bt_m23_etr_input_config_t;

/**
 ******************************************************************************
 ** \brief brake BKInput phase Filter configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_bk_input_config
{
    boolean_t                 bEnBrake;         ///< Brake enable
    boolean_t                 bEnVC0Brake;      ///< Enable VC0 brake
    boolean_t                 bEnVC1Brake;      ///< Enable VC1 brake
    boolean_t                 bEnSafetyBk;      ///< Enable safety brakes
    boolean_t                 bEnBKSync;        ///< TIM0/TIM1/TIM2 brake synchronization enable
    en_bt_m23_crch0_bks_t     enBkCH0AStat;     ///< When braking CHA Port status setting
    en_bt_m23_crch0_bks_t     enBkCH0BStat;     ///< When braking CHB Port status setting
    en_bt_port_polarity_t     enBrakePolarity;  ///< brake BK Input polarity setting
    en_bt_flt_t               enBrakeFlt;       ///< brake BK Filter setting
}stc_bt_m23_bk_input_config_t;

/**
 ******************************************************************************
** \brief Dead zone function configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_dt_config
{
    boolean_t       bEnDeadTime;      ///< When braking CHA Port status setting
    uint8_t         u8DeadTimeValue;  ///< When braking CHA Port status setting
}stc_bt_m23_dt_config_t;

/**
 ******************************************************************************
 ** \brief Trigger ADC Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_adc_trig_config
{
    boolean_t     bEnTrigADC;          ///< trigger ADC Global control
    boolean_t     bEnUevTrigADC;       ///< Event update trigger ADC
    boolean_t     bEnCH0ACmpTrigADC;   ///< CH0A comparison match trigger ADC
    boolean_t     bEnCH0BCmpTrigADC;   ///< CH0B Comparison matchtrigger ADC
}stc_bt_m23_adc_trig_config_t;

/**
 ******************************************************************************
 ** \brief  DMA trigger Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_trig_dma_config
{
    boolean_t              bUevTrigDMA;      ///< Update trigger DMA Enable
    boolean_t              bTITrigDMA;       ///< Trig trigger DMA Functions
    boolean_t              bCmpATrigDMA;     ///< A Capture comparison trigger DMA Enable
    boolean_t              bCmpBTrigDMA;     ///< B Capture comparisontrigger DMA Enable
    en_bt_m23_mscr_ccds_t  enCmpUevTrigDMA;  ///< Comparison mode DMA Comparison trigger select
}stc_bt_m23_trig_dma_config_t;

/**
 ******************************************************************************
 ** \brief  Master-slave mode Configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_master_slave_config
{
    en_bt_m23_mscr_msm_t      enMasterSlaveSel;  ///< Master-slave mode select
    en_bt_m23_mscr_mms_t      enMasterSrc;       ///< Master mode trigger source select
    en_bt_m23_mscr_sms_t      enSlaveModeSel;    ///< Slave mode select
    en_bt_mscr_ts_t           enTsSel;           ///< trigger Input source select
}stc_bt_m23_master_slave_config_t;

/**
 ******************************************************************************
 ** \brief  OCREF clears the Functions configuration structure definition (Mode 23)
 *****************************************************************************/
typedef struct stc_bt_m23_OCREF_Clr_config
{
    en_bt_m23ce_occs_t       enOCRefClrSrcSel;  ///< OCREF Clear source select
    boolean_t                bVCClrEn;          ///< whether Enable From VC of OCREF_Clr
}stc_bt_m23_OCREF_Clr_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//Interrupt related function

//Interrupt flag acquisition
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Interrupt flag Clear
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//all Interrupt flag Clear
en_result_t Bt_ClearAllIntFlag(en_bt_unit_t enUnit);
//Mode 0 interrupt Enable
en_result_t Bt_Mode0_EnableIrq(en_bt_unit_t enUnit);
//Mode 1 interrupt Enable
en_result_t Bt_Mode1_EnableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Mode 2 interrupt Enable
en_result_t Bt_Mode23_EnableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Mode 0 interrupt disable
en_result_t Bt_Mode0_DisableIrq(en_bt_unit_t enUnit);
//Mode 1 interrupt disable
en_result_t Bt_Mode1_DisableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Mode 2 interrupt disable
en_result_t Bt_Mode23_DisableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);


//mode 0 Initialization and related Functions operating

//timer Configuration and initialization
en_result_t Bt_Mode0_Init(en_bt_unit_t enUnit, stc_bt_mode0_config_t* pstcConfig);
//timer start up/stop
en_result_t Bt_M0_Run(en_bt_unit_t enUnit);
en_result_t Bt_M0_Stop(en_bt_unit_t enUnit);
//Overload value setting
en_result_t Bt_M0_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data);
//16 Bit count value setting/Obtain
en_result_t Bt_M0_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_M0_Cnt16Get(en_bt_unit_t enUnit);
//32 Bit count value setting/Obtain
en_result_t Bt_M0_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data);
uint32_t Bt_M0_Cnt32Get(en_bt_unit_t enUnit);
//Flip output Enable/disable set up
en_result_t Bt_M0_EnTOG_Output(en_bt_unit_t enUnit, boolean_t bEnOutput);


//mode1Initialization and relatedFunctionsoperating

//timerConfiguration and initialization
en_result_t Bt_Mode1_Init(en_bt_unit_t enUnit, stc_bt_mode1_config_t* pstcConfig);
//PWC Input configuration
en_result_t Bt_M1_Input_Config(en_bt_unit_t enUnit, stc_bt_pwc_input_config_t* pstcConfig);
//PWC Measuring edge start select
en_result_t Bt_M1_PWC_Edge_Sel(en_bt_unit_t enUnit,en_bt_m1cr_Edge_t enEdgeSel);
//timer start up/stop
en_result_t Bt_M1_Run(en_bt_unit_t enUnit);
en_result_t Bt_M1_Stop(en_bt_unit_t enUnit);
//16Bit count value setting/Obtain
en_result_t Bt_M1_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_M1_Cnt16Get(en_bt_unit_t enUnit);
//Pulse width measurement result value Obtain
uint16_t Bt_M1_PWC_CapValueGet(en_bt_unit_t enUnit);


//mode23Initialization and relatedFunctionsoperating

//timerConfiguration and initialization
en_result_t Bt_Mode23_Init(en_bt_unit_t enUnit, stc_bt_mode23_config_t* pstcConfig);
//timer start up/stop
en_result_t Bt_M23_Run(en_bt_unit_t enUnit);
en_result_t Bt_M23_Stop(en_bt_unit_t enUnit);
//PWM Output Enable
en_result_t Bt_M23_EnPWM_Output(en_bt_unit_t enUnit, boolean_t bEnOutput, boolean_t bEnAutoOutput);
//Overload value setting
en_result_t Bt_M23_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data, boolean_t bArrBufEn);
//16Bit count value setting/Obtain
en_result_t Bt_M23_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_M23_Cnt16Get(en_bt_unit_t enUnit);
//Comparison Capture register CCR0A/CCR0B Setting/Read
en_result_t Bt_M23_CCR_Set(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Bt_M23_CCR_Get(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel);
//PWM Complementary Output modeunder，GATE Functions select
en_result_t Bt_M23_GateFuncSel(en_bt_unit_t enUnit,stc_bt_m23_gate_config_t* pstcConfig);
//Master-slave mode Configuration
en_result_t Bt_M23_MasterSlave_Set(en_bt_unit_t enUnit, stc_bt_m23_master_slave_config_t* pstcConfig);
//CH0A/CH0B Comparison Channel control
en_result_t Bt_M23_PortOutput_Config(en_bt_unit_t enUnit, stc_bt_m23_compare_config_t* pstcConfig);
//CH0A/CH0B Input control
en_result_t Bt_M23_PortInput_Config(en_bt_unit_t enUnit, stc_bt_m23_input_config_t* pstcConfig);
//ERT Input control
en_result_t Bt_M23_ETRInput_Config(en_bt_unit_t enUnit, stc_bt_m23_etr_input_config_t* pstcConfig);
//brakeBK Input control
en_result_t Bt_M23_BrakeInput_Config(en_bt_unit_t enUnit, stc_bt_m23_bk_input_config_t* pstcConfig);
//triggerADC control
en_result_t Bt_M23_TrigADC_Config(en_bt_unit_t enUnit, stc_bt_m23_adc_trig_config_t* pstcConfig);
//dead zone Functions
en_result_t Bt_M23_DT_Config(en_bt_unit_t enUnit, stc_bt_m23_dt_config_t* pstcConfig);
//Repeat cycle Setting
en_result_t Bt_M23_SetValidPeriod(en_bt_unit_t enUnit, uint8_t u8ValidPeriod);
//OCREFClearFunctions
en_result_t Bt_M23_OCRefClr(en_bt_unit_t enUnit, stc_bt_m23_OCREF_Clr_config_t* pstcConfig);
//EnableDMA transmission
en_result_t Bt_M23_EnDMA(en_bt_unit_t enUnit, stc_bt_m23_trig_dma_config_t* pstcConfig);
//Capture comparisonA software trigger
en_result_t Bt_M23_EnSwTrigCapCmpA(en_bt_unit_t enUnit);
//Capture comparisonB software trigger
en_result_t Bt_M23_EnSwTrigCapCmpB(en_bt_unit_t enUnit);
//software UpdateEnable
en_result_t Bt_M23_EnSwUev(en_bt_unit_t enUnit);
//software triggerEnable
en_result_t Bt_M23_EnSwTrig(en_bt_unit_t enUnit);
//software brakeEnable
en_result_t Bt_M23_EnSwBk(en_bt_unit_t enUnit);


//@} // BtGroup

#ifdef __cplusplus
#endif


#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



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
 * @file   bt.h
 *
 * @brief  Header file for BT functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

#ifndef __BT_H__
#define __BT_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"


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
    TIM0 = 0u, ///< Timer 0
    TIM1 = 1u, ///< Timer 1
    TIM2 = 2u, ///< Timer 2
}en_bt_unit_t;

/**
 ******************************************************************************
 ** \brief Work mode selection data type redefinition (MODE) (Mode 0/1/23)
 *****************************************************************************/
typedef enum en_bt_work_mode
{
    BtWorkMode0 = 0u, ///< Timer mode
    BtWorkMode1 = 1u, ///< PWC mode
    BtWorkMode2 = 2u, ///< Sawtooth mode
    BtWorkMode3 = 3u, ///< Triangle mode
}en_bt_work_mode_t;

/**
 ******************************************************************************
 ** \brief Polarity control data type redefinition (GATE_P) (Mode 0)
 *****************************************************************************/
typedef enum en_bt_m0_gatep
{
    BtGatePositive = 0u, ///< Active high
    BtGateOpposite = 1u, ///< Active low
}en_bt_m0_gatep_t;

/**
 ******************************************************************************
 ** \brief TIM Prescaler Select (PRS) (Mode 0/1/23)
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
 ** \brief Counter/Timer Function Selection Data Type Redefinition (CT)
 *****************************************************************************/
typedef enum en_bt_cr_ct
{
    BtTimer = 0u, ///< Timer function, count clock is internal PCLK
    BtCounter = 1u, ///< Counter function, count clock is external ETR
}en_bt_cr_ct_t;


/**
 ******************************************************************************
 ** \brief Timer Operation Mode Data Type Redefinition (MD) (Mode 0)
 *****************************************************************************/
typedef enum en_bt_m0cr_md
{
    Bt32bitFreeMode = 0u, ///< 32-bit counter/timer
    Bt16bitArrMode = 1u, ///< Auto-reload 16-bit counter/timer
}en_bt_m0cr_md_t;

/**
 ******************************************************************************
** \brief BT0/BT1/BT2 interrupt type data type redefinition (mode 0/1/23)
 *****************************************************************************/
typedef enum en_bt_irq_type
{
    BtUevIrq = 0u, ///< Overflow/event update interrupt
    BtCA0Irq = 2u, ///< Capture/compare interrupt A (only available in modes 1/23)
    BtCB0Irq = 5u, ///< Capture/Compare Interrupt B (only available in mode 23)
    BtCA0E = 8u, ///< CH0A Capture Data Loss Flag (only available in mode 23), not an interrupt
    BtCB0E = 11u, ///< CH0B Capture Data Loss Flag (only available in mode 23), not an interrupt
    BtBkIrq = 14u, ///< Brake Interrupt (only available in mode 23)
    BtTrigIrq = 15u, ///< Trigger Interrupt (only available in mode 23) 
}en_bt_irq_type_t;

/**
 ******************************************************************************
 ** \brief Measurement Start and End Data Type Definition
 *****************************************************************************/
typedef enum en_bt_m1cr_Edge
{
    BtPwcRiseToRise = 0u, ///< Rising edge to rising edge (period)
    BtPwcFallToRise = 1u, ///< Falling edge to rising edge (low level)
    BtPwcRiseToFall = 2u, ///< Rising edge to falling edge (high level)
    BtPwcFallToFall = 3u, ///< Falling edge to falling edge (period)
}en_bt_m1cr_Edge_t;

/**
 ******************************************************************************
 ** \brief PWC Measurement Test Mode Selection Data Type Redefinition (Oneshot) (Mode 1)
 *****************************************************************************/
typedef enum en_bt_m1cr_oneshot
{
    BtPwcCycleDetect = 0u, ///< PWC Cycle Measurement
    BtPwcOneShotDetect = 1u, ///< PWC single-shot measurement
}en_bt_m1cr_oneshot_t;

/**
 ******************************************************************************
 ** \brief PWC IA0 Select Data Type Redefinition (IA0S) (Mode 1)
 *****************************************************************************/
typedef enum en_bt_m1_mscr_ia0s
{
    BtIA0Input = 0u, ///< IAO input
    BtXORInput = 1u, ///< IA0 ETR GATE XOR (TIM0/1/2) / IA0 IA1 IA2 XOR (TIM3)
}en_bt_m1_mscr_ia0s_t;

/**
 ******************************************************************************
 ** \brief PWC IB0 Select Data Type Redefinition (IA0S) (Mode 1)
 *****************************************************************************/
typedef enum en_bt_m1_mscr_ib0s
{
    BtIB0Input = 0u, ///< IBO input
    BtTsInput = 1u, ///< Internal trigger TS selection signal
}en_bt_m1_mscr_ib0s_t;
/**
******************************************************************************
** \brief Output Polarity, Input Phase Data Type Redefinition (CCPA0/CCPB0/ETP/BKP) (Mode 1/23)
*****************************************************************************/
typedef enum en_bt_port_polarity
{
    BtPortPositive = 0u, ///< Normal input/output
    BtPortOpposite = 1u, ///< Inverting input and output
}en_bt_port_polarity_t;

/**
**************************************************************************
** \brief Filter selection data type redefinition (FLTET/FLTA0/FLAB0) (Mode 1/23)
*************************************************************************/
typedef enum en_bt_flt
{
    BtFltNone = 0u, ///< No filtering
    BtFltPCLKCnt3 = 4u, ///< PCLK 3 consecutive valid
    BtFltPCLKDiv4Cnt3 = 5u, ///< PCLK/4 3 consecutive valid
    BtFltPCLKDiv16Cnt3 = 6u, ///< PCLK/16 3 consecutive valid
    BtFltPCLKDiv64Cnt3 = 7u, ///< PCLK/64 3 consecutive valid
}en_bt_flt_t;

/**
****************************************************************************
** \brief Channel Compare Control Data Type Redefinition (OCMA/OCMB) (Mode 23)
***************************************************************************/
typedef enum en_bt_m23_fltr_ocm
{
    BtForceLow = 0u, ///< Force to 0
    BtForceHigh = 1u, ///< Force to 1
    BtCMPForceLow = 2u, ///< Force to 0 on compare match
    BtCMPForceHigh = 3u, ///< Force to 1 on compare match
    BtCMPInverse = 4u, ///< Invert level on compare match
    BtCMPOnePrdHigh = 5u, ///< Output high level for one count cycle on compare match
    BtPWMMode1 = 6u, ///< Channel control is PWM mode 1
    BtPWMMode2 = 7u, ///< Channel control is PWM mode 2
}en_bt_m23_fltr_ocm_t;

/**
******************************************************************************
** \brief Master-slave mode TS data type redefinition (TS) (mode 1/23)
*****************************************************************************/
typedef enum en_bt_mscr_ts
{
    BtTs0ETR = 0u, ///< ETR external input filtered phase selection signal
    BtTs1TIM0TRGO = 1u, ///< Timer0 TRGO output signal
    BtTs2TIM1TRGO = 2u, ///< Timer1 TRGO output signal
    BtTs3TIM2TRGO = 3u, ///< Timer2 TRGO output signal
    BtTs4TIM3TRGO = 4u, ///< Timer3 TRGO output signal
    //BtTs5IA0ED = 5u, ///< Invalid
    BtTs6IAFP = 6u, ///< CH0A external input filtered phase selection signal
    BtTs7IBFP = 7u, ///< CH0B external input filtered phase selection signal
}en_bt_mscr_ts_t;

/**
****************************************************************************
** \brief PWM output mode selection data type redefinition (COMP) (Mode 23)
***********************************************************************/
typedef enum en_bt_m23cr_comp
{
    BtIndependentPWM = 0u, ///< Independent PWM output
    BtComplementaryPWM = 1u, ///< Complementary PWM output
}en_bt_m23cr_comp_t;

/**
************************************************************************
** \brief Count direction selection data type redefine (DIR) (Mode 23)
************************************************************************/
typedef enum en_bt_m23cr_dir
{
    BtCntUp = 0u, ///< Count up
    BtCntDown = 1u, ///< Count down
}en_bt_m23cr_dir_t;

/**
********************************************************************************
** \brief Count direction selection data type redefine (PWM2S) (Mode 23)
***************************************************************************/
typedef enum en_bt_m23cr_pwm2s
{
    BtDoublePointCmp = 0u, ///< Enable dual-point comparison, use CCRA and CCRB to control the OCREFA output.
    BtSinglePointCmp = 1u, ///< Enable single-point comparison, use CCRA to control the OCREFA output.
}en_bt_m23cr_pwm2s_t;
/**
 ******************************************************************************
 ** \brief GATE capture or compare function in PWM complementary mode. Select data type redefinition (CSG) (Mode 23).
 *****************************************************************************/
typedef enum en_bt_m23cr_csg
{
    BtPWMCompGateCmpOut= 0u, ///< In PWM complementary mode, Gate functions as a compare output
    BtPWMCompGateCapIn = 1u, ///< In PWM complementary mode, Gate functions as a capture input
}en_bt_m23cr_csg_t;

/**
**************************************************************************
** \brief Compare Capture Register Data Type Redefinition (CCR0A, CCR0B) (Mode 23)
*****************************************************************************/
typedef enum en_bt_m23_ccrx
{
    BtCCR0A = 0u, ///< CCR0A compare capture register
    BtCCR0B = 1u, ///< CCR0B compare capture register
}en_bt_m23_ccrx_t;

/**
**********************************************************************************
** \brief OCREF Clear Source Select Data Type Redefine (OCCS) (Mode 23)
**************************************************************************/
typedef enum en_bt_m23ce_occs
{
    BtOC_Ref_Clr = 0u, ///< OC_Ref_Clr from VC
    BtETRf = 1u, ///< External ETRf
}en_bt_m23ce_occs_t;

/**
******************************************************************************
** \brief Compare Match Interrupt Mode Select Data Type Redefine (CIS/CISB) (Mode 23)
*********************************************************************************/
typedef enum en_bt_m23_cisa_cisb
{
    BtCmpIntNone = 0u, ///< No compare match interrupt
    BtCmpIntRise = 1u, ///< Compare match rising edge interrupt
    BtCmpIntFall = 2u, ///< Compare match falling edge interrupt
    BtCmpIntRiseFall = 3u, ///< Compare match rising edge falling edge interrupt
}en_bt_m23_cisa_cisb_t;

/**
******************************************************************************
** \brief BT Port Control - CHx Output State Control (BKSA/BKSB) during Brake (Mode 23)
**
** \note
**************************************************************************/
typedef enum en_bt_m23_crch0_bks
{
    BtCHxBksHiZ = 0u, ///< When the brake is enabled, the CHx port outputs high impedance.
    BtCHxBksNorm = 1u, ///< When the brake is enabled, the CHx port outputs normal output.
    BtCHxBksLow = 2u, ///< When the brake is enabled, the CHx port outputs a low level.
    BtCHxBksHigh = 3u, ///< When the brake is enabled, the CHx port outputs a high level.
}en_bt_m23_crch0_bks_t;

/**
******************************************************************************
** \brief BT Port Control - CHx Rising/Falling Edge Capture (CRx/CFx) (Mode 23)
**
** \note
******************************************************************************/
typedef enum en_bt_m23_crch0_cfx_crx
{
    BtCHxCapNone = 0u, ///< Disable CHx channel capture.
    BtCHxCapRise = 1u, ///< Enable CHx channel rising edge capture.
    BtCHxCapFall = 2u, ///< Enable falling edge capture on the CHx channel
    BtCHxCapFallRise = 3u, ///< Enable both rising and falling edge capture on the CHx channel
}en_bt_m23_crch0_cfx_crx_t;

/**
****************************************************************************
** \brief BT Port Control - CHx Compare Capture Mode (CSA/CSB) (Mode 23)
**
** \note
************************************************************************/
typedef enum en_bt_m23_crch0_csa_csb
{
    BtCHxCmpMode = 0u, ///< Set the CHx channel to compare mode
    BtCHxCapMode = 1u, ///< Set the CHx channel to capture mode
}en_bt_m23_crch0_csa_csb_t;

/**
******************************************************************************
** \brief DMA Compare Trigger Selection in Compare Mode: Data Type Redefinition (CCDS) (Mode 23)
*****************************************************************************/
typedef enum en_bt_m23_mscr_ccds
{
    BtCmpTrigDMA = 0u, ///< Compare match triggers DMA
    BtUEVTrigDMA = 1u, ///< Event update instead of compare match triggers DMA
}en_bt_m23_mscr_ccds_t;

/**
******************************************************************************
** \brief Master-Slave Mode Selection: Data Type Redefinition (MSM) (Mode 23)
*********************************************************************************/
typedef enum en_bt_m23_mscr_msm
{
    BtSlaveMode = 0u, ///< Slave mode
    BtMasterMode = 1u, ///< Master mode
}en_bt_m23_mscr_msm_t;

/**
**************************************************************************
** \brief Trigger Master Mode Output Source Data Type Redefinition (MMS) (Mode 23)
*****************************************************************************/
typedef enum en_bt_m23_mscr_mms
{
    BtMasterUG = 0u, ///< UG (Software Update) Source
    BtMasterCTEN = 1u, ///< CTEN Source
    BtMasterUEV = 2u, ///< UEV Update Source
    BtMasterCMPSO = 3u, ///< Compare Match Select Output Source
    BtMasterOCA0Ref = 4u, ///< OCA0_Ref Source
    BtMasterOCB0Ref = 5u, ///< OCB0_Ref source
    //BtMasterOCB0Ref = 6u,
    //BtMasterOCB0Ref = 7u,
}en_bt_m23_mscr_mms_t;

/**
******************************************************************************
** \brief Trigger Slave Mode Selection Data Type Redefinition (SMS) (Mode 23)
*****************************************************************************/
typedef enum en_bt_m23_mscr_sms
{
    BtSlaveIClk = 0u, ///< Use internal clock
    BtSlaveResetTIM = 1u, ///< Reset function
    BtSlaveTrigMode = 2u, ///< Trigger mode
    BtSlaveEClk = 3u, ///< External clock mode
    BtSlaveCodeCnt1 = 4u, ///< Quadrature encoder counting mode 1
    BtSlaveCodeCnt2 = 5u, ///< Quadrature encoder counting mode 2
    BtSlaveCodeCnt3 = 6u, ///< Quadrature encoder counting mode 3
    BtSlaveGateCtrl = 7u, ///< Gate control function
}en_bt_m23_mscr_sms_t;

/**
 ******************************************************************************
 ** \brief Timer operation control data type redefinition (CTEN)
 *****************************************************************************/
typedef enum en_bt_start
{
    BtCTENDisable = 0u, ///< Stop
    BtCTENEnable = 1u, ///< Run
}en_bt_start_t;

/**
******************************************************************************
** \brief BaseTimer mode0 configuration structure definition (mode 0)
*****************************************************************************/
typedef struct stc_bt_mode0_cfg
{
    en_bt_work_mode_t enWorkMode; ///< Working mode setting
    en_bt_m0_gatep_t enGateP; ///< Gate polarity control
    boolean_t bEnGate; ///< Gate enable
    en_bt_cr_timclkdiv_t enPRS; ///< Prescaler configuration
    boolean_t bEnTog; ///< Toggle output enable
    en_bt_cr_ct_t enCT; ///< Timer/Counter function selection
    en_bt_m0cr_md_t enCntMode; ///< Counting mode configuration

    func_ptr_t pfnTim0Cb; ///< Timer0 interrupt service callback function [void function(void)]
    func_ptr_t pfnTim1Cb; ///< Timer1 interrupt service callback function [void function(void)]
    func_ptr_t pfnTim2Cb; ///< Timer2 interrupt service callback function [void function(void)]
}stc_bt_mode0_cfg_t;

/**
**************************************************************************
** \brief BaseTimer mode1 configuration structure definition (mode 1)
*****************************************************************************/
typedef struct stc_bt_mode1_cfg
{
    en_bt_work_mode_t enWorkMode; ///< Working mode setting
    en_bt_cr_timclkdiv_t enPRS; ///< Prescaler configuration
    en_bt_cr_ct_t enCT; ///< Timer/counter function selection
    en_bt_m1cr_oneshot_t enOneShot; ///< Single/loop measurement selection

    func_ptr_t pfnTim0Cb; ///< Timer0 interrupt service callback function [void function(void)]
    func_ptr_t pfnTim1Cb; ///< Timer1 interrupt service callback function [void function(void)]
    func_ptr_t pfnTim2Cb; ///< Timer2 interrupt service callback function [void function(void)] function(void)
}stc_bt_mode1_cfg_t;

/**
****************************************************************************
** \brief PWC input configuration structure definition (mode 1)
****************************************************************************/
typedef struct stc_bt_pwc_input_cfg
{
    en_bt_mscr_ts_t enTsSel; ///< Trigger input source selection
    en_bt_m1_mscr_ia0s_t enIA0Sel; ///< CHA0 input selection
    en_bt_m1_mscr_ib0s_t enIB0Sel; ///< CHB0 input selection
    en_bt_port_polarity_t enETRPhase; ///< ETR phase selection
    en_bt_flt_t enFltETR; ///< ETR filter setting
    en_bt_flt_t enFltIA0; ///< CHA0 filter settings
    en_bt_flt_t enFltIB0; ///< CHB0 filter settings
}stc_bt_pwc_input_cfg_t;

/**
****************************************************************************
** \brief BaseTimer mode23 configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_bt_mode23_cfg
{
    en_bt_work_mode_t enWorkMode; ///< Working mode settings
    en_bt_m23cr_dir_t enCntDir; ///< Counting direction
    en_bt_cr_timclkdiv_t enPRS; ///< Clock prescaler configuration
    en_bt_cr_ct_t enCT; ///< Timer/Counter Function Selection
    en_bt_m23cr_comp_t enPWMTypeSel; ///< PWM Mode Selection (Independent/Complementary)
    en_bt_m23cr_pwm2s_t enPWM2sSel; ///< OCREFA Dual-Point Comparator Function Selection
    boolean_t bOneShot; ///< One-Shot Mode Enable/Disable
    boolean_t bURSSel; ///< Update Source Selection

    func_ptr_t pfnTim0Cb; ///< Timer0 Interrupt Service Callback Function [void function(void)]
    func_ptr_t pfnTim1Cb; ///< Timer1 Interrupt Service Callback Function [void function(void)]
    func_ptr_t pfnTim2Cb; ///< Timer2 Interrupt Service Callback Function [void function(void)] function(void)]
}stc_bt_mode23_cfg_t;

/**
****************************************************************************
** \brief GATE capture or compare function configuration structure definition in PWM complementary mode (mode 23)
*******************************************************************************/
typedef struct stc_bt_m23_gate_cfg
{
    en_bt_m23cr_csg_t enGateFuncSel; ///< Gate compare or capture function selection
    boolean_t bGateRiseCap; ///< When the GATE is used as a capture function, rising edge capture is enabled
    boolean_t bGateFallCap; ///< When the GATE is used as a capture function, falling edge capture is enabled
}stc_bt_m23_gate_cfg_t;

/**
******************************************************************************
** \brief CHA/CHB channel compare control configuration structure definition (mode 23)
*****************************************************************************/
typedef struct stc_bt_m23_compare_cfg
{
    en_bt_m23_crch0_csa_csb_t enCh0ACmpCap; ///< CH0A compare/capture function selection
    en_bt_m23_fltr_ocm_t enCH0ACmpCtrl; ///< CH0A channel compare control
    en_bt_port_polarity_t enCH0APolarity; ///< CH0A output polarity control
    boolean_t bCh0ACmpBufEn; ///< Compare A buffer function enable/disable
    en_bt_m23_cisa_cisb_t enCh0ACmpIntSel; ///< CHA compare match interrupt selection
    en_bt_m23_crch0_csa_csb_t enCh0BCmpCap; ///< CH0B compare/capture function selection
    en_bt_m23_fltr_ocm_t enCH0BCmpCtrl; ///< CH0B channel compare control
    en_bt_port_polarity_t enCH0BPolarity; ///< CH0B output polarity control
    boolean_t bCH0BCmpBufEn; ///< Compare B buffer function enable/disable
    en_bt_m23_cisa_cisb_t enCH0BCmpIntSel; ///< CHB0 compare match interrupt selection
}stc_bt_m23_compare_cfg_t;

/**
 ******************************************************************************
 ** \brief CHA/CHB channel capture control configuration structure definition (mode 23)
*****************************************************************************/
typedef struct stc_bt_m23_input_cfg
{
    en_bt_m23_crch0_csa_csb_t enCh0ACmpCap; ///< CH0A compare/capture function selection
    en_bt_m23_crch0_cfx_crx_t enCH0ACapSel; ///< CH0A capture edge selection
    en_bt_flt_t enCH0AInFlt; ///< CH0A channel capture filter control
    en_bt_port_polarity_t enCH0APolarity; ///< CH0A input phase
    en_bt_m23_crch0_csa_csb_t enCh0BCmpCap; ///< CH0B compare/capture function selection
    en_bt_m23_crch0_cfx_crx_t enCH0BCapSel; ///< HC0B capture edge selection
    en_bt_flt_t enCH0BInFlt; ///< CH0B channel capture filter control
    en_bt_port_polarity_t enCH0BPolarity; ///< CH0B input phase
}stc_bt_m23_input_cfg_t;

/**
****************************************************************************
** \brief ETR input phase filter configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_bt_m23_etr_input_cfg
{
    en_bt_port_polarity_t enETRPolarity; ///< ETR input polarity setting
    en_bt_flt_t enETRFlt; ///< ETR filter settings
}stc_bt_m23_etr_input_cfg_t;

/**
****************************************************************************
** \brief Brake BK input phase filter configuration structure definition (mode 23)
*******************************************************************************/
typedef struct stc_bt_m23_bk_input_cfg
{
    boolean_t bEnBrake; ///< Brake enable
    boolean_t bEnVCBrake; ///< Enable VC0 brake
    boolean_t bEnSafetyBk; ///< Enable safety brake
    boolean_t bEnBKSync; ///< TIM0/TIM1/TIM2 brake synchronization enable
    en_bt_m23_crch0_bks_t enBkCH0AStat; ///< Set the CHA port status during braking.
    en_bt_m23_crch0_bks_t enBkCH0BStat; ///< Set the CHB port status during braking.
    en_bt_port_polarity_t enBrakePolarity; ///< Set the brake BK input polarity.
    en_bt_flt_t enBrakeFlt; ///< Set the brake BK filter.
}stc_bt_m23_bk_input_cfg_t;

/**
****************************************************************************
** \brief Dead zone function configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_bt_m23_dt_cfg
{
    boolean_t bEnDeadTime; ///< Set the CHA port status during braking.
    uint8_t u8DeadTimeValue; ///< Set CHA port status during braking
}stc_bt_m23_dt_cfg_t;

/**
****************************************************************************
** \brief Trigger ADC configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_bt_m23_adc_trig_cfg
{
    boolean_t bEnTrigADC; ///< Trigger ADC global control
    boolean_t bEnUevTrigADC; ///< Event update trigger ADC
    boolean_t bEnCH0ACmpTrigADC; ///< CH0A compare match trigger ADC
    boolean_t bEnCH0BCmpTrigADC; ///< CH0B compare match trigger ADC
}stc_bt_m23_adc_trig_cfg_t;

/**
******************************************************************************
** \brief DMA trigger configuration structure definition (mode 23)
*************************************************************************/
typedef struct stc_bt_m23_trig_dma_cfg
{
    boolean_t bUevTrigDMA; ///< Update trigger DMA enable
    boolean_t bTITrigDMA; ///< Trig trigger DMA function
    boolean_t bCmpATrigDMA; ///< A capture compare trigger DMA enable
    boolean_t bCmpBTrigDMA; ///< B capture compare trigger DMA enable
    en_bt_m23_mscr_ccds_t enCmpUevTrigDMA; ///< DMA compare trigger selection in compare mode
}stc_bt_m23_trig_dma_cfg_t;

/**
******************************************************************************
** \brief Master-Slave Mode Configuration Structure Definition (Mode 23)
*****************************************************************************/
typedef struct stc_bt_m23_master_slave_cfg
{
    en_bt_m23_mscr_msm_t enMasterSlaveSel; ///< Master-slave mode selection
    en_bt_m23_mscr_mms_t enMasterSrc; ///< Master mode trigger source selection
    en_bt_m23_mscr_sms_t enSlaveModeSel; ///< Slave mode selection
    en_bt_mscr_ts_t enTsSel; ///< Trigger input source selection
}stc_bt_m23_master_slave_cfg_t;

/**
******************************************************************************
** \brief OCREF clear function configuration structure definition (mode 23)
****************************************************************************/
typedef struct stc_bt_m23_OCREF_Clr_cfg
{
    en_bt_m23ce_occs_t enOCRefClrSrcSel; ///< OCREF clear source selection
    boolean_t bVCClrEn; ///< Whether to enable OCREF_Clr from VC
}stc_bt_m23_OCREF_Clr_cfg_t;

/**********************************************************************************
* Global variable declarations ('extern', definition in C source)
*********************************************************************************/

/******************************************************************************
* Global function prototypes (definition in C source)
*************************************************************************/
//Interrupt-related functions

//Get interrupt flag
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Clear interrupt flag
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Clear all interrupt flags
en_result_t Bt_ClearAllIntFlag(en_bt_unit_t enUnit);
//Enable mode 0 interrupts
en_result_t Bt_Mode0_EnableIrq(en_bt_unit_t enUnit);
//Mode 1 interrupt enable
en_result_t Bt_Mode1_EnableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Mode 2 interrupt enable
en_result_t Bt_Mode23_EnableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Mode 0 interrupt disable
en_result_t Bt_Mode0_DisableIrq (en_bt_unit_t enUnit);
//Mode 1 interrupt disable
en_result_t Bt_Mode1_DisableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
//Mode 2 interrupt disable
en_result_t Bt_Mode23_DisableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);

//Mode 0 initialization and related functions

//Timer configuration and initialization
en_result_t Bt_Mode0_Init(en_bt_unit_t enUnit, stc_bt_mode0_cfg_t* pstcCfg);
//Timer start/stop
en_result_t Bt_M0_Run(en_bt_unit_t enUnit);
en_result_t Bt_M0_Stop(en_bt_unit_t enUnit);
//Reload value setting
en_result_t Bt_M0_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data);
//Set/get 16-bit count value
en_result_t Bt_M0_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_M0_Cnt16Get(en_bt_unit_t enUnit);
//Set/Get 32-bit counter value
en_result_t Bt_M0_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data);
uint32_t Bt_M0_Cnt32Get(en_bt_unit_t enUnit);
//Set toggle output enable/disable (low level)
en_result_t Bt_M0_EnTOG_Output(en_bt_unit_t enUnit, boolean_t bEnTOG);
//Set port output enable/disable
en_result_t Bt_M0_Enable_Output(en_bt_unit_t enUnit, boolean_t bEnOutput);

//Mode 1 initialization and related functions

//Timer configuration and initialization
en_result_t Bt_Mode1_Init(en_bt_unit_t enUnit, stc_bt_mode1_cfg_t* pstcCfg);
//PWC input configuration
en_result_t Bt_M1_Input_Cfg(en_bt_unit_t enUnit, stc_bt_pwc_input_cfg_t* pstcCfg);
//PWC measurement edge start and end selection
en_result_t Bt_M1_PWC_Edge_Sel(en_bt_unit_t enUnit,en_bt_m1cr_Edge_t enEdgeSel);
//Timer start/stop
en_result_t Bt_M1_Run(en_bt_unit_t enUnit);
en_result_t Bt_M1_Stop(en_bt_unit_t enUnit);
//Set/Get 16-bit counter value
en_result_t Bt_M1_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_M1_Cnt16Get(en_bt_unit_t enUnit);
//Get pulse width measurement result
uint16_t Bt_M1_PWC_CapValueGet(en_bt_unit_t enUnit);

//Mode 23 initialization and related functions

//Timer configuration and initialization
en_result_t Bt_Mode23_Init(en_bt_unit_t enUnit, stc_bt_mode23_cfg_t* pstcCfg);
//Timer start/stop
en_result_t Bt_M23_Run(en_bt_unit_t enUnit);
en_result_t Bt_M23_Stop(en_bt_unit_t enUnit);
//PWM output enable
en_result_t Bt_M23_EnPWM_Output(en_bt_unit_t enUnit, boolean_t bEnOutput, boolean_t bEnAutoOutput);
//Reload value setting
en_result_t Bt_M23_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data, boolean_t bArrBufEn);
//Set/get 16-bit count value
en_result_t Bt_M23_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_M23_Cnt16Get(en_bt_unit_t enUnit);
//Set/read compare capture registers CCR0A/CCR0B
en_result_t Bt_M23_CCR_Set(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Bt_M23_CCR_Get(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel);
//GATE function selection in PWM complementary output mode
en_result_t Bt_M23_GateFuncSel(en_bt_unit_t enUnit,stc_bt_m23_gate_cfg_t* pstcCfg);
//Master-slave mode configuration
en_result_t Bt_M23_MasterSlave_Set(en_bt_unit_t enUnit, stc_bt_m23_master_slave_cfg_t* pstcCfg);
//CH0A/CH0B comparison channel control
en_result_t Bt_M23_PortOutput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_compare_cfg_t* pstcCfg);
//CH0A/CH0B input control
en_result_t Bt_M23_PortInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_input_cfg_t* pstcCfg);
//ERT input control
en_result_t Bt_M23_ETRInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_etr_input_cfg_t* pstcCfg);
//Brake BK input control
en_result_t Bt_M23_BrakeInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_bk_input_cfg_t* pstcCfg);
//Trigger ADC control
en_result_t Bt_M23_TrigADC_Cfg(en_bt_unit_t enUnit, stc_bt_m23_adc_trig_cfg_t* pstcCfg);
//Dead zone function
en_result_t Bt_M23_DT_Cfg(en_bt_unit_t enUnit, stc_bt_m23_dt_cfg_t* pstcCfg);
//Repeat cycle setting
en_result_t Bt_M23_SetValidPeriod(en_bt_unit_t enUnit, uint8_t u8ValidPeriod);
//OCREF clear function
en_result_t Bt_M23_OCRefClr(en_bt_unit_t enUnit, stc_bt_m23_OCREF_Clr_cfg_t* pstcCfg);
//Enable DMA transfer
en_result_t Bt_M23_EnDMA(en_bt_unit_t enUnit, stc_bt_m23_trig_dma_cfg_t* pstcCfg);
//Capture Comparator A software trigger
en_result_t Bt_M23_EnSwTrigCapCmpA(en_bt_unit_t enUnit);
//Capture Comparator B software trigger
en_result_t Bt_M23_EnSwTrigCapCmpB(en_bt_unit_t enUnit);
//Software update enable
en_result_t Bt_M23_EnSwUev(en_bt_unit_t enUnit);
//Software trigger enable
en_result_t Bt_M23_EnSwTrig(en_bt_unit_t enUnit);
//Software brake enable
en_result_t Bt_M23_EnSwBk(en_bt_unit_t enUnit);

//@} // BtGroup

#ifdef __cplusplus
#endif

#endif /* __BT_H__ */
/******************************************************************************
* EOF (not truncated)
***********************************************************************/

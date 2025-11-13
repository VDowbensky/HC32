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
* @file timer3.h 
* 
* @brief Header file for TIMER3 functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __TIMER3_H__
#define __TIMER3_H__

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
** \defgroup Tim3Group Timer3 (TIM3) 
** 
******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/**********************************************************************************/

/******************************************************************************
* Global type definitions
******************************************************************************/

/**
**********************************************************************************
** \brief Timer3 channel definition
*****************************************************************************/
typedef enum en_tim3_channel
{
    Tim3CH0 = 0u, ///< Timer3 channel 0
    Tim3CH1 = 1u, ///< Timer3 channel 1
    Tim3CH2 = 2u, ///< Timer3 channel 2
}en_tim3_channel_t;

/**
**********************************************************************************
** \brief Operating mode selection data type redefinition (MODE) (Mode 0/1/23)
**************************************************************************/
typedef enum en_tim3_work_mode
{
    Tim3WorkMode0 = 0u, ///< Timer mode
    Tim3WorkMode1 = 1u, ///< PWC mode
    Tim3WorkMode2 = 2u, ///< Sawtooth wave mode
    Tim3WorkMode3 = 3u, ///< Triangle wave mode
}en_tim3_work_mode_t;

/**
******************************************************************************
** \brief Polarity control data type redefinition (GATE_P) (Mode 0)
*****************************************************************************/
typedef enum en_tim3_m0cr_gatep
{
    Tim3GatePositive = 0u, ///< Active high
    Tim3GateOpposite = 1u, ///< Active low
}en_tim3_m0cr_gatep_t;

/**
******************************************************************************
** \brief TIM3 Prescaler Select (PRS) (Mode 0/1/23)
*****************************************************************************/
typedef enum en_tim3_cr_timclkdiv
{
    Tim3PCLKDiv1 = 0u, ///< Div 1
    Tim3PCLKDiv2 = 1u, ///< Div 2
    Tim3PCLKDiv4 = 2u, ///< Div 4
    Tim3PCLKDiv8 = 3u, ///< Div 8
    Tim3PCLKDiv16 = 4u, ///< Div 16
    Tim3PCLKDiv32 = 5u, ///< Div 32
    Tim3PCLKDiv64 = 6u, ///< Div 64
    Tim3PCLKDiv256 = 7u, ///< Div 256
}en_tim3_cr_timclkdiv_t;

/**
********************************************************************************
** \brief Counter/Timer Function Selection Data Type Redefinition (CT) (Mode 0/1/23)
*******************************************************************************/
typedef enum en_tim3_cr_ct
{
    Tim3Timer = 0u, ///< Timer function, count clock is internal PCLK
    Tim3Counter = 1u, ///< Counter function, count clock is external ETR
}en_tim3_cr_ct_t;

/**
******************************************************************************
** \brief Timer Operating Mode Data Type Redefinition (MD) (Mode 0)
*****************************************************************************/
typedef enum en_tim3_m0cr_md
{
    Tim332bitFreeMode = 0u, ///< 32-bit counter/timer
    Tim316bitArrMode = 1u, ///< Auto-reload 16-bit counter/timer
}en_tim3_m0cr_md_t;

/**
******************************************************************************
** \brief TIM3 Interrupt Type Data Type Redefinition (Mode 0/1/23)
*********************************************************************************/
typedef enum en_tim3_irq_type
{
    Tim3UevIrq = 0u, ///< Overflow/Event Update Interrupt
    Tim3CA0Irq = 2u, ///< CH0A Capture/Compare Interrupt (only available in Mode 1/23)
    Tim3CA1Irq = 3u, ///< CH1A Capture/Compare Interrupt (only available in Mode 23)
    Tim3CA2Irq = 4u, ///< CH2A Capture/Compare Interrupt (only available in Mode 23)
    Tim3CB0Irq = 5u, ///< CH0B Capture/Compare Interrupt (only available in Mode 23)
    Tim3CB1Irq = 6u, ///< CH1B Capture/Compare Interrupt (only available in Mode 23)
    Tim3CB2Irq = 7u, ///< CH2B Capture/Compare Interrupt (only available in Mode 23)
    Tim3CA0E = 8u, ///< CH0A Capture Data Lost Flag (only available in Mode 23) (not an interrupt)
    Tim3CA1E = 9u, ///< CH1A capture data loss flag (only exists in mode 23) (not an interrupt)
    Tim3CA2E = 10u, ///< CH2A capture data loss flag (only available in mode 23) (not an interrupt)
    Tim3CB0E = 11u, ///< CH0B capture data loss flag (only available in mode 23) (not an interrupt)
    Tim3CB1E = 12u, ///< CH1B capture data loss flag (only available in mode 23) (not an interrupt)
    Tim3CB2E = 13u, ///< CH2B capture data loss flag (only available in mode 23) (not an interrupt)
    Tim3BkIrq = 14u, ///< Brake interrupt (only available in mode 23)
    Tim3TrigIrq = 15u, ///< Trigger interrupt (only available in mode 23)
}en_tim3_irq_type_t;

/**
****************************************************************************
** \brief Redefine measurement start and end data types (Edg1stEdg2nd) (Mode 1)
*****************************************************************************/
typedef enum en_tim3_m1cr_Edge
{
    Tim3PwcRiseToRise = 0u, ///< Rising edge to rising edge (period)
    Tim3PwcFallToRise = 1u, ///< Falling edge to rising edge (low level)
    Tim3PwcRiseToFall = 2u, ///< Rising edge to falling edge (high level)
    Tim3PwcFallToFall = 3u, ///< Falling edge to falling edge (period)
}en_tim3_m1cr_Edge_t;

/**
********************************************************************************
** \brief PWC Measurement Test Mode Selection Data Type Redefinition (Oneshot) (Mode 1)
***************************************************************************/
typedef enum en_tim3_m1cr_oneshot
{
    Tim3PwcCycleDetect = 0u, ///< PWC cycle measurement
    Tim3PwcOneShotDetect = 1u, ///< PWC single-shot measurement
}en_tim3_m1cr_oneshot_t;

/**
********************************************************************************
** \brief PWC IA0 Select Data Type Redefinition (IA0S) (Mode 1)
***************************************************************************/
typedef enum en_tim3_m1_mscr_ia0s
{
    Tim3IA0Input = 0u, ///< IAO input
    Tim3XORInput = 1u, ///< IA0 ETR GATE XOR (TIM0/1/2)/IA0 IA1 IA2 XOR(TIM3)
}en_tim3_m1_mscr_ia0s_t;

/**
************************************************************************
** \brief PWC IB0 Select Data Type Redefinition (IA0S) (Mode 1)
***************************************************************************/
typedef enum en_tim3_m1_mscr_ib0s
{
    Tim3IB0Input = 0u, ///< IBO input
    Tim3TsInput = 1u, ///< Internal trigger TS selection signal
}en_tim3_m1_mscr_ib0s_t;

/**
********************************************************************************
** \brief Output polarity, input phase data type redefinition (CCPA0/CCPB0/ETP/BKP) (Mode 1/23)
*****************************************************************************/
typedef enum en_tim3_port_polarity
{
    Tim3PortPositive = 0u, ///< Normal input and output
    Tim3PortOpposite = 1u, ///< Inverted input and output
}en_tim3_port_polarity_t;

/**
******************************************************************************
** \brief Filter selection data type redefinition (FLTET/FLTA0/FLAB0) (Mode 1/23)
*****************************************************************************/
typedef enum en_tim3_flt
{
    Tim3FltNone = 0u, ///< No filtering
    Tim3FltPCLKCnt3 = 4u, ///< Three consecutive PCLKs valid
    Tim3FltPCLKDiv4Cnt3 = 5u, ///< PCLK/4 3 consecutive valid
    Tim3FltPCLKDiv16Cnt3 = 6u, ///< PCLK/16 3 consecutive valid
    Tim3FltPCLKDiv64Cnt3 = 7u, ///< PCLK/64 3 consecutive valid
}en_tim3_flt_t;

/**
********************************************************************************
** \brief Channel Compare Control Data Type Redefinition (OCMA/OCMB) (Mode 23)
***************************************************************************/
typedef enum en_tim3_m23_fltr_ocm
{
    Tim3ForceLow = 0u, ///< Forced to 0
    Tim3ForceHigh = 1u, ///< Forced to 1
    Tim3CMPForceLow = 2u, ///< Forced to 0 on compare match
    Tim3CMPForceHigh = 3u, ///< Forces the bit to 1 on a compare match
    Tim3CMPInverse = 4u, ///< Inverts the bit level on a compare match
    Tim3CMPOnePrdHigh = 5u, ///< Outputs a high level for one count on a compare match
    Tim3PWMMode1 = 6u, ///< Sets the channel to PWM mode 1
    Tim3PWMMode2 = 7u, ///< Sets the channel to PWM mode 2
}en_tim3_m23_fltr_ocm_t;

/**
******************************************************************************
** \brief Master-slave mode TS data type redefinition (TS) (mode 1/23)
*****************************************************************************/
typedef enum en_tim3_mscr_ts
{
    Tim3Ts0ETR = 0u, ///< Phase selection signal after ETR external input filtering
    Tim3Ts1TIM0TRGO = 1u, ///< Timer0 TRGO output signal
    Tim3Ts2TIM1TRGO = 2u, ///< Timer1 TRGO output signal
    Tim3Ts3TIM2TRGO = 3u, ///< Timer2 TRGO output signal
    Tim3Ts4TIM3TRGO = 4u, ///< Timer3 TRGO output signal
    //Tim3Ts5IA0ED = 5u, ///< Invalid
    Tim3Ts6IAFP = 6u, ///< CH0A external input filtered phase select signal
    Tim3Ts7IBFP = 7u, ///< CH0B external input filtered phase select signal
}en_tim3_mscr_ts_t;

/**
********************************************************************************
** \brief PWM output mode selection data type redefinition (COMP) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23cr_comp
{
    Tim3IndependentPWM = 0u, ///< Independent PWM output
    Tim3ComplementaryPWM = 1u, ///< Complementary PWM output
}en_tim3_m23cr_comp_t;

/**
******************************************************************************
** \brief Count direction selection data type redefinition (DIR) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23cr_dir
{
    Tim3CntUp = 0u, ///< Count up
    Tim3CntDown = 1u, ///< Count down
}en_tim3_m23cr_dir_t;

/**
**************************************************************************
** \brief Count direction selection data type redefinition (PWM2S) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23cr_pwm2s
{
    Tim3DoublePointCmp = 0u, ///< Double point comparison enabled, using CCRA and CCRB comparisons to control OCREFA output
    Tim3SinglePointCmp = 1u, ///< Single point comparison enabled, using CCRA comparisons to control OCREFA output
}en_tim3_m23cr_pwm2s_t;

/**
******************************************************************************
** \brief GATE capture or compare function in PWM complementary mode redefines data type selection (CSG) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23cr_csg
{
    Tim3PWMCompGateCmpOut = 0u, ///< In PWM complementary mode, the gate acts as a compare output.
    Tim3PWMCompGateCapIn = 1u, ///< In PWM complementary mode, the gate acts as a capture input.
}en_tim3_m23cr_csg_t;

/**
******************************************************************************
** \brief Compare Capture Register Data Type Redefinition (CCR0A, CCR0B) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23_ccrx
{
    Tim3CCR0A = 0u, ///< CCR0A compare capture register.
    Tim3CCR0B = 1u, ///< CCR0B Compare Capture Register
    Tim3CCR1A = 2u, ///< CCR1A Compare Capture Register
    Tim3CCR1B = 3u, ///< CCR1B Compare Capture Register
    Tim3CCR2A = 4u, ///< CCR2A Compare Capture Register
    Tim3CCR2B = 5u, ///< CCR2B Compare Capture Register
}en_tim3_m23_ccrx_t;

/**
********************************************************************************
** \brief OCREF Clear Source Select Data Type Redefine (OCCS) (Mode 23)
***************************************************************************/
typedef enum en_tim3_m23ce_occs
{
    Tim3OC_Ref_Clr = 0u, ///< OC_Ref_Clr from VC
    Tim3ETRf = 1u, ///< External ETRf
}en_tim3_m23ce_occs_t;

/**
****************************************************************************
** \brief Compare Match Interrupt Mode Select Data Type Redefine (CIS/CISB) (Mode 23)
***************************************************************************/
typedef enum en_tim3_m23_cisa_cisb
{
    Tim3CmpIntNone = 0u, ///< No compare match interrupt
    Tim3CmpIntRise = 1u, ///< Compare match rising edge interrupt
    Tim3CmpIntFall = 2u, ///< Compare match falling edge interrupt
    Tim3CmpIntRiseFall = 3u, ///< Compare match rising edge or falling edge interrupt
}en_tim3_m23_cisa_cisb_t;

/**
******************************************************************************
** \brief TIM3 Port Control - CHx Output State Control During Braking (BKSA/BKSB) (Mode 23)
**
** \note
**************************************************************************/
typedef enum en_tim3_m23_crchx_bks
{
    Tim3CHxBksHiZ = 0u, ///< When the brake is enabled, the CHx port outputs a high-impedance state.
    Tim3CHxBksNorm = 1u, ///< When the brake is enabled, the CHx port outputs a normal state.
    Tim3CHxBksLow = 2u, ///< When the brake is enabled, the CHx port outputs a low level.
    Tim3CHxBksHigh = 3u, ///< When the brake is enabled, the CHx port outputs a high level.
}en_tim3_m23_crchx_bks_t;

/**
******************************************************************************
** \brief TIM3 Port Control - CHx Rising and Falling Edge Capture (CRx/CFx) (Mode 23)
**
** \note
************************************************************************/
typedef enum en_tim3_m23_crch0_cfx_crx
{
    Tim3CHxCapNone = 0u, ///< CHx channel capture disabled
    Tim3CHxCapRise = 1u, ///< CHx channel rising edge capture enabled
    Tim3CHxCapFall = 2u, ///< CHx channel falling edge capture enabled
    Tim3CHxCapFallRise = 3u, ///< CHx channel both rising and falling edge capture enabled
}en_tim3_m23_crch0_cfx_crx_t;

/**
******************************************************************************
** \brief TIM3 Port Control - CHx Compare Capture Mode (CSA/CSB) (Mode 23)
**
** \note
************************************************************************/
typedef enum en_tim3_m23_crch0_csa_csb
{
    Tim3CHxCmpMode = 0u, ///< Set the CHx channel to compare mode
    Tim3CHxCapMode = 1u, ///< Set the CHx channel to capture mode
}en_tim3_m23_crch0_csa_csb_t;

/**
********************************************************************************
** \brief DMA Compare Trigger Selection in Compare Mode - Data Type Redefinition (CCDS) (Mode 23)
***************************************************************************/
typedef enum en_tim3_m23_mscr_ccds
{
    Tim3CmpTrigDMA = 0u, ///< Compare match triggers DMA
    Tim3UEVTrigDMA = 1u, ///< Event update instead of compare match triggers DMA
}en_tim3_m23_mscr_ccds_t;

/**
********************************************************************************
** \brief Master-Slave Mode Selection Data Type Redefinition (MSM) (Mode 23)
***************************************************************************/
typedef enum en_tim3_m23_mscr_msm
{
    Tim3SlaveMode = 0u, ///< Slave mode
    Tim3MasterMode = 1u, ///< Master mode
}en_tim3_m23_mscr_msm_t;

/**
******************************************************************************
** \brief Trigger Master Mode Output Source Data Type Redefinition (MMS) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23_mscr_mms
{
    Tim3MasterUG = 0u, ///< UG (Software Update) Source
    Tim3MasterCTEN = 1u, ///< CTEN Source
    Tim3MasterUEV = 2u, ///< UEV Update Source
    Tim3MasterCMPSO = 3u, ///< Compare Match Select Output Source
    Tim3MasterOCA0Ref = 4u, ///< OCA0_Ref source
    Tim3MasterOCB0Ref = 5u, ///< OCB0_Ref source
    //Tim3MasterOCB0Ref = 6u,
    //Tim3MasterOCB0Ref = 7u,
}en_tim3_m23_mscr_mms_t;

/**
********************************************************************************
** \brief Trigger Slave Mode Selection Data Type Redefinition (SMS) (Mode 23)
*****************************************************************************/
typedef enum en_tim3_m23_mscr_sms
{
    Tim3SlaveIClk = 0u, ///< Use internal clock
    Tim3SlaveResetTIM = 1u, ///< Reset function
    Tim3SlaveTrigMode = 2u, ///< Trigger mode
    Tim3SlaveEClk = 3u, ///< External clock mode
    Tim3SlaveCodeCnt1 = 4u, ///< Quadrature encoder counting mode 1
    Tim3SlaveCodeCnt2 = 5u, ///< Quadrature encoder counting mode 2
    Tim3SlaveCodeCnt3 = 6u, ///< Quadrature encoder counting mode 3
    Tim3SlaveGateCtrl = 7u, ///< Gate control function
}en_tim3_m23_mscr_sms_t;

/**
********************************************************************************
** \brief Timer run control data type redefinition (CTEN)
***************************************************************************/
typedef enum en_tim3_start
{
    Tim3CTENDisable = 0u, ///< Stop
    Tim3CTENEnable = 1u, ///< Run
}en_tim3_start_t;

/**
******************************************************************************
** \brief TIM3 mode0 configuration structure definition (mode 0)
*************************************************************************/
typedef struct stc_tim3_mode0_cfg
{
    en_tim3_work_mode_t enWorkMode; ///< Working mode setting
    en_tim3_m0cr_gatep_t enGateP; ///< Gate polarity control
    boolean_t bEnGate; ///< Gate enable
    en_tim3_cr_timclkdiv_t enPRS; ///< Prescaler configuration
    boolean_t bEnTog; ///< Toggle output enable
    en_tim3_cr_ct_t enCT; ///< Timer/counter function selection
    en_tim3_m0cr_md_t enCntMode; ///< Counting mode configuration
}stc_tim3_mode0_cfg_t;

/**
****************************************************************************
** \brief TIM3 mode1 configuration structure definition (mode 1)
****************************************************************************/
typedef struct stc_tim3_mode1_cfg
{
    en_tim3_work_mode_t enWorkMode; ///< Working mode setting
    en_tim3_cr_timclkdiv_t enPRS; ///< Prescaler configuration
    en_tim3_cr_ct_t enCT; ///< Timing/counting function selection
    en_tim3_m1cr_oneshot_t enOneShot; ///< Single/cyclic measurement selection
}stc_tim3_mode1_cfg_t;

/**
******************************************************************************
** \brief PWC input configuration structure definition (mode 1)
*************************************************************************/
typedef struct stc_tim3_pwc_input_cfg
{
    en_tim3_mscr_ts_t enTsSel; ///< Trigger input source selection
    en_tim3_m1_mscr_ia0s_t enIA0Sel; ///< CHA0 input selection
    en_tim3_m1_mscr_ib0s_t enIB0Sel; ///< CHB0 input selection
    en_tim3_port_polarity_t enETRPhase; ///< ETR phase selection
    en_tim3_flt_t enFltETR; ///< ETR filter setting
    en_tim3_flt_t enFltIA0; ///< CHA0 filter settings
    en_tim3_flt_t enFltIB0; ///< CHB0 filter settings
}stc_tim3_pwc_input_cfg_t;

/**
****************************************************************************
** \brief TIM3 mode23 configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_tim3_mode23_cfg
{
    en_tim3_work_mode_t enWorkMode; ///< Working mode settings
    en_tim3_m23cr_dir_t enCntDir; ///< Counting direction
    en_tim3_cr_timclkdiv_t enPRS; ///< Clock prescaler configuration
    en_tim3_cr_ct_t enCT; ///< Timing/counting function selection
    en_tim3_m23cr_comp_t enPWMTypeSel; ///< PWM mode selection (independent/complementary)
    en_tim3_m23cr_pwm2s_t enPWM2sSel; ///< OCREFA dual-point comparison function selection
    boolean_t bOneShot; ///< One-shot mode enable/disable
    boolean_t bURSSel; ///< Update source selection
}stc_tim3_mode23_cfg_t;

/**
********************************************************************************
** \brief GATE capture or compare function configuration structure definition in PWM complementary mode (mode 23)
***************************************************************************/
typedef struct stc_tim3_m23_gate_cfg
{
    en_tim3_m23cr_csg_t enGateFuncSel; ///< Gate compare/capture function selection
    boolean_t bGateRiseCap; ///< When the gate is used as a capture function, rising edge capture is enabled.
    boolean_t bGateFallCap; ///< When the gate is used as a capture function, falling edge capture is enabled.
}stc_tim3_m23_gate_cfg_t;

/**
******************************************************************************
** \brief CHA/CHB channel compare control configuration structure definition (mode 23)
*****************************************************************************/
typedef struct stc_tim3_m23_compare_cfg
{
    en_tim3_m23_crch0_csa_csb_t enCHxACmpCap; ///< CH0A compare/capture function selection
    en_tim3_m23_fltr_ocm_t enCHxACmpCtrl; ///< CH0A channel compare control
    en_tim3_port_polarity_t enCHxAPolarity; ///< CH0A output polarity control
    boolean_t bCHxACmpBufEn; ///< Compare A buffer function enable/disable
    en_tim3_m23_cisa_cisb_t enCHxACmpIntSel; ///< CHA compare match interrupt selection
    en_tim3_m23_crch0_csa_csb_t enCHxBCmpCap; ///< CH0B compare/capture function selection
    en_tim3_m23_fltr_ocm_t enCHxBCmpCtrl; ///< CH0B channel compare control
    en_tim3_port_polarity_t enCHxBPolarity; ///< CH0B output polarity control
    boolean_t bCHxBCmpBufEn; ///< Compare B buffer function enable/disable
    en_tim3_m23_cisa_cisb_t enCHxBCmpIntSel; ///< CHB0 compare match interrupt selection
}stc_tim3_m23_compare_cfg_t;

/**
****************************************************************************
** \brief CHA/CHB channel capture control configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_tim3_m23_input_cfg
{
    en_tim3_m23_crch0_csa_csb_t enCHxACmpCap; ///< CH0A compare/capture function selection
    en_tim3_m23_crch0_cfx_crx_t enCHxACapSel; ///< CH0A capture edge selection
    en_tim3_flt_t enCHxAInFlt; ///< CH0A channel capture filter control
    en_tim3_port_polarity_t enCHxAPolarity; ///< CH0A input phase
    en_tim3_m23_crch0_csa_csb_t enCHxBCmpCap; ///< CH0A compare/capture function selection
    en_tim3_m23_crch0_cfx_crx_t enCHxBCapSel; ///< CH0B capture edge selection
    en_tim3_flt_t enCHxBInFlt; ///< CH0B channel capture filter control
    en_tim3_port_polarity_t enCHxBPolarity; ///< CH0B input phase
}stc_tim3_m23_input_cfg_t;

/**
********************************************************************************
** \brief ETR input phase filter configuration structure definition (mode 23)
*******************************************************************************/
typedef struct stc_tim3_m23_etr_input_cfg
{
    en_tim3_port_polarity_t enETRPolarity; ///< ETR input polarity setting
    en_tim3_flt_t enETRFlt; ///< ETR filter setting
}stc_tim3_m23_etr_input_cfg_t;

/**
******************************************************************************
** \brief Brake BK input phase filter configuration structure definition (mode 23)
*****************************************************************************/
typedef struct stc_tim3_m23_bk_input_cfg
{
    boolean_t bEnBrake; ///< Brake enable
    boolean_t bEnVCBrake; ///< Enable VC brake
    boolean_t bEnSafetyBk; ///< Enable safety brake
    boolean_t bEnBKSync; ///< TIM0/TIM1/TIM2 brake synchronization enable
    en_tim3_m23_crchx_bks_t enBkCH0AStat; ///< Set CHA port status during brake
    en_tim3_m23_crchx_bks_t enBkCH0BStat; ///< Set the CHB port status during braking.
    en_tim3_m23_crchx_bks_t enBkCH1AStat; ///< Set the CHA port status during braking.
    en_tim3_m23_crchx_bks_t enBkCH1BStat; ///< Set the CHB port status during braking.
    en_tim3_m23_crchx_bks_t enBkCH2AStat; ///< Set the CHA port status during braking.
    en_tim3_m23_crchx_bks_t enBkCH2BStat; ///< Set the CHB port status during braking.
    en_tim3_port_polarity_t enBrakePolarity; ///< Set the brake BK input polarity.
    en_tim3_flt_t enBrakeFlt; ///< Set the brake BK filter.
}stc_tim3_m23_bk_input_cfg_t;

/**
******************************************************************************
** \brief Dead zone function configuration structure definition (mode 23)
*****************************************************************************/
typedef struct stc_tim3_m23_dt_cfg
{
    boolean_t bEnDeadTime; ///< CHA port status setting during braking
    uint8_t u8DeadTimeValue; ///< CHA port status setting during braking
}stc_tim3_m23_dt_cfg_t;

/**
******************************************************************************
** \brief Trigger ADC configuration structure definition (mode 23)
*****************************************************************************/
typedef struct stc_tim3_m23_adc_trig_cfg
{
    boolean_t bEnDeadTime; ///< CHA port status setting during braking
    uint8_t u8DeadTimeValue; ///< CHA port status setting during braking
}stc_tim3_m23_dt_cfg_t;

/**
**********************************************************************************
** \brief Trigger ADC configuration structure definition (mode 23)
*********************************************************************************/
typedef struct stc_tim3_m23_adc_trig_cfg
{
    boolean_t bEnTrigADC; ///< Trigger ADC global control
    boolean_t bEnUevTrigADC; ///< Event update trigger ADC
    boolean_t bEnCH0ACmpTrigADC; ///< CH0A compare match trigger ADC
    boolean_t bEnCH0BCmpTrigADC; ///< CH0B compare match trigger ADC
    boolean_t bEnCH1ACmpTrigADC; ///< CH0A compare match trigger ADC
    boolean_t bEnCH1BCmpTrigADC; ///< CH0B compare match trigger ADC
    boolean_t bEnCH2ACmpTrigADC; ///< CH0A compare match trigger ADC
    boolean_t bEnCH2BCmpTrigADC; ///< CH0B compare match trigger ADC
}stc_tim3_m23_adc_trig_cfg_t;

/**
******************************************************************************
** \brief DMA Trigger Configuration Structure Definition (Mode 23)
********************************************************************/
typedef struct stc_tim3_m23_trig_dma_cfg
{
    boolean_t bUevTrigDMA; ///< Update trigger DMA enable
    boolean_t bTITrigDMA; ///< Trig trigger DMA function
    boolean_t bCmpA0TrigDMA; ///< CH0A capture compare trigger DMA enable
    boolean_t bCmpB0TrigDMA; ///< CH0B capture compare trigger DMA enable
    boolean_t bCmpA1TrigDMA; ///< CH1A capture compare trigger DMA enable
    boolean_t bCmpB1TrigDMA; ///< CH1B capture compare trigger DMA enable
    boolean_t bCmpA2TrigDMA; ///< CH2A capture compare trigger DMA enable
    boolean_t bCmpB2TrigDMA; ///< Enable DMA for CH2B capture compare trigger
    en_tim3_m23_mscr_ccds_t enCmpUevTrigDMA; ///< DMA compare trigger selection in compare mode
}stc_tim3_m23_trig_dma_cfg_t;

/**
****************************************************************************
** \brief Master-Slave Mode Configuration Structure Definition (Mode 23)
***************************************************************************/
typedef struct stc_tim3_m23_master_slave_cfg
{
    en_tim3_m23_mscr_msm_t enMasterSlaveSel; ///< Master-Slave Mode Selection
    en_tim3_m23_mscr_mms_t enMasterSrc; ///< Master Mode Trigger Source Selection
    en_tim3_m23_mscr_sms_t enSlaveModeSel; ///< Slave mode selection
    en_tim3_mscr_ts_t enTsSel; ///< Trigger input source selection
}stc_tim3_m23_master_slave_cfg_t;

/**
************************************************************************
** \brief OCREF clear function configuration structure definition (mode 23)
***************************************************************************/
typedef struct stc_tim3_m23_OCREF_Clr_cfg
{
    en_tim3_m23ce_occs_t enOCRefClrSrcSel; ///< OCREF clear source selection
    boolean_t bVCClrEn; ///< Enable OCREF_Clr from VC
}stc_tim3_m23_OCREF_Clr_cfg_t;

/**********************************************************************************
* Global variable declarations ('extern', definition in C source)
*****************************************************************************/

/******************************************************************************
* Global function prototypes (definition in C source)
*****************************************************************************/
//Interrupt-related functions

//Interrupt flag acquisition
boolean_t Tim3_GetIntFlag(en_tim3_irq_type_t enTim3Irq);
//Interrupt flag clear
en_result_t Tim3_ClearIntFlag(en_tim3_irq_type_t enTim3Irq);
//Clear all interrupt flags
en_result_t Tim3_ClearAllIntFlag(void);
//Mode 0 interrupt enable
en_result_t Tim3_Mode0_EnableIrq(void);
//Mode 1 interrupt enable
en_result_t Tim3_Mode1_EnableIrq (en_tim3_irq_type_t enTim3Irq);
//Mode 2 interrupt enable
en_result_t Tim3_Mode23_EnableIrq (en_tim3_irq_type_t enTim3Irq);
//Mode 0 interrupt disable
en_result_t Tim3_Mode0_DisableIrq(void);
//Mode 1 interrupt disable
en_result_t Tim3_Mode1_DisableIrq (en_tim3_irq_type_t enTim3Irq);
//Mode 2 interrupt disable
en_result_t Tim3_Mode23_DisableIrq (en_tim3_irq_type_t enTim3Irq);

//Mode 0 initialization and related function operations

//Timer configuration and initialization
en_result_t Tim3_Mode0_Init(stc_tim3_mode0_cfg_t* pstcCfg);
//Timer start/stop
en_result_t Tim3_M0_Run(void);
en_result_t Tim3_M0_Stop(void);
//Reload value setting
en_result_t Tim3_M0_ARRSet(uint16_t u16Data);
//Set/get 16-bit count value
en_result_t Tim3_M0_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M0_Cnt16Get(void);
//Set/get 32-bit count value
en_result_t Tim3_M0_Cnt32Set(uint32_t u32Data);
uint32_t Tim3_M0_Cnt32Get(void);
//Port output enable/disable setting
en_result_t Tim3_M0_Enable_Output(boolean_t bEnOutput);
//Toggle enable/disable (low level) setting
en_result_t Tim3_M0_EnTOG(boolean_t bEnTOG);

//Mode 1 initialization and related functions

//Timer configuration and initialization
en_result_t Tim3_Mode1_Init(stc_tim3_mode1_cfg_t* pstcCfg);
//PWC input configuration
en_result_t Tim3_M1_Input_Cfg(stc_tim3_pwc_input_cfg_t* pstcCfg);
//PWC measurement edge start and end selection
en_result_t Tim3_M1_PWC_Edge_Sel(en_tim3_m1cr_Edge_t enEdgeSel);
//Timer start/stop
en_result_t Tim3_M1_Run(void);
en_result_t Tim3_M1_Stop(void);
//Set/get 16-bit count value
en_result_t Tim3_M1_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M1_Cnt16Get(void);
//Get pulse width measurement result
uint16_t Tim3_M1_PWC_CapValueGet(void);

//Mode 23 initialization and related functions

//Timer configuration and initialization
en_result_t Tim3_Mode23_Init(stc_tim3_mode23_cfg_t* pstcCfg);
//Timer start/stop
en_result_t Tim3_M23_Run(void);
en_result_t Tim3_M23_Stop(void);
//PWM output enable
en_result_t Tim3_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput);
//Reload value setting
en_result_t Tim3_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn);
//Set/get 16-bit count value
en_result_t Tim3_M23_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M23_Cnt16Get(void);
//Set/read compare capture registers CCR0A/CCR0B
en_result_t Tim3_M23_CCR_Set(en_tim3_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Tim3_M23_CCR_Get(en_tim3_m23_ccrx_t enCCRSel);
//PWM complementary output mode, gate function selection
en_result_t Tim3_M23_GateFuncSel(stc_tim3_m23_gate_cfg_t* pstcCfg);
//Master-slave mode configuration
en_result_t Tim3_M23_MasterSlave_Set(stc_tim3_m23_master_slave_cfg_t* pstcCfg);
//CH0A/CH0B comparison channel control
en_result_t Tim3_M23_PortOutput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_compare_cfg_t* pstcCfg);
//CH0A/CH0B input control
en_result_t Tim3_M23_PortInput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_input_cfg_t* pstcCfg);
//ERT input control
en_result_t Tim3_M23_ETRInput_Cfg(stc_tim3_m23_etr_input_cfg_t* pstcCfg);
//Brake BK input control
en_result_t Tim3_M23_BrakeInput_Cfg(stc_tim3_m23_bk_input_cfg_t* pstcBkCfg);
//Trigger ADC control
en_result_t Tim3_M23_TrigADC_Cfg(stc_tim3_m23_adc_trig_cfg_t* pstcCfg);
//Dead zone function
en_result_t Tim3_M23_DT_Cfg(stc_tim3_m23_dt_cfg_t* pstcCfg);
//Repeat period setting
en_result_t Tim3_M23_SetValidPeriod(uint8_t u8ValidPeriod);
//OCREF clear function
en_result_t Tim3_M23_OCRefClr(stc_tim3_m23_OCREF_Clr_cfg_t* pstcCfg);
//Enable DMA transfer
en_result_t Tim3_M23_EnDMA(stc_tim3_m23_trig_dma_cfg_t* pstcCfg);
//Capture Comparator A software trigger
en_result_t Tim3_M23_EnSwTrigCapCmpA(en_tim3_channel_t enTim3Chx);
//Capture Comparator B software trigger
en_result_t Tim3_M23_EnSwTrigCapCmpB(en_tim3_channel_t enTim3Chx);
//Software update enable
en_result_t Tim3_M23_EnSwUev(void);
//Software trigger enable
en_result_t Tim3_M23_EnSwTrig(void);
//Software brake enable
en_result_t Tim3_M23_EnSwBk(void);

//@} // Tim3Group

#ifdef __cplusplus
#endif

#endif /* __BT_H__ */
/****************************************************************************** 
* EOF (not truncated) 
*******************************************************************************/

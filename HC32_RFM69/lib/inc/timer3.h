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
/** \file timer3.h
 **
 ** Basic timer data structure and API declaration
 ** @link BT Timer3 Group Some description @endlink
 **
 ** History:
 **   - 2018-04-29   Husj     First Version
 **
 *****************************************************************************/

#ifndef __TIMER3_H__
#define __TIMER3_H__

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
 ** \defgroup Tim3Group Base Timer (BT)
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
 ** \brief Timer3 Channel definition
 *****************************************************************************/
typedef enum en_tim3_channel
{
    Tim3CH0  = 0u,        ///< Timer3 channel 0
    Tim3CH1  = 1u,        ///< Timer3 channel 1
    Tim3CH2  = 2u,        ///< Timer3 channel 2
}en_tim3_channel_t;

/**
 ******************************************************************************
 ** \brief working mode selection data type redefinition (MODE) (mode 0/1/23)
 *****************************************************************************/
typedef enum en_tim3_work_mode
{
    Tim3WorkMode0  = 0u,         ///< Timer mode
    Tim3WorkMode1  = 1u,         ///< PWC mode
    Tim3WorkMode2  = 2u,         ///< Sawtooth mode
    Tim3WorkMode3  = 3u,         ///< Triangle wave mode
}en_tim3_work_mode_t;

/**
 ******************************************************************************
 ** \brief Polarity Control Data Type Redefinition (GATE_P) (Mode 0)
 *****************************************************************************/
typedef enum en_tim3_m0cr_gatep
{
    Tim3GatePositive = 0u,            ///< Active high
    Tim3GateOpposite = 1u,            ///< Active low
}en_tim3_m0cr_gatep_t;

/**
 ******************************************************************************
 ** \brief TIM3 Prescaler Selection (PRS) (Mode 0/1/23)
 *****************************************************************************/
typedef enum en_tim3_cr_timclkdiv
{
    Tim3PCLKDiv1   = 0u,           ///< Div 1
    Tim3PCLKDiv2   = 1u,           ///< Div 2
    Tim3PCLKDiv4   = 2u,           ///< Div 4
    Tim3PCLKDiv8   = 3u,           ///< Div 8
    Tim3PCLKDiv16  = 4u,           ///< Div 16
    Tim3PCLKDiv32  = 5u,           ///< Div 32
    Tim3PCLKDiv64  = 6u,           ///< Div 64
    Tim3PCLKDiv256 = 7u,           ///< Div 256
}en_tim3_cr_timclkdiv_t;

/**
 ******************************************************************************
 ** \brief Count/Timer Function Select Data Type Redefinition (CT) (Mode 0/1/23)
 *****************************************************************************/
typedef enum en_tim3_cr_ct
{
    Tim3Timer   = 0u,            ///< Timer function, the count clock is internal PCLK
    Tim3Counter = 1u,            ///< Counter function, the count clock is external ETR
}en_tim3_cr_ct_t;


/**
 ******************************************************************************
 ** \brief Timer operating mode data type definition (MD) (mode 0)
 *****************************************************************************/
typedef enum en_tim3_m0cr_md
{
    Tim332bitFreeMode  = 0u,         ///< 32-bit counter/timer
    Tim316bitArrMode  = 1u,         ///< Automatically reload 16-bit counter/timer
}en_tim3_m0cr_md_t;

/**
 ******************************************************************************
** \brief TIM3 interrupt type data type redefinition (mode 0/1/23)
 *****************************************************************************/
typedef enum en_tim3_irq_type
{
    Tim3UevIrq   = 0u,         ///< Overflow/event update interrupt
    Tim3CA0Irq   = 2u,         ///< CH0A capture / Comparative interrupt ( Mode only 1/23 presence )
    Tim3CA1Irq   = 3u,         ///< CH1A capture / Comparative interrupt ( Mode only 23 presence )
    Tim3CA2Irq   = 4u,         ///< CH2A capture / Comparative interrupt ( Mode only 23 presence )
    Tim3CB0Irq   = 5u,         ///< CH0B capture / Comparative interrupt ( Mode only 23 presence )
    Tim3CB1Irq   = 6u,         ///< CH1B capture / Comparative interrupt ( Mode only 23 presence )
    Tim3CB2Irq   = 7u,         ///< CH2B capture / Comparative interrupt ( Mode only 23 presence )
    Tim3CA0E     = 8u,         ///< CH0A capture  Data loss flag ( Mode only 23 presence )(Not interrupted)
    Tim3CA1E     = 9u,         ///< CH1A capture  Data loss flag ( Mode only 23 presence )(Not interrupted)
    Tim3CA2E     = 10u,        ///< CH2A capture  Data loss flag ( Mode only 23 presence )(Not interrupted)
    Tim3CB0E     = 11u,        ///< CH0B capture  Data loss flag ( Mode only 23 presence )(Not interrupted)
    Tim3CB1E     = 12u,        ///< CH1B capture  Data loss flag ( Mode only 23 presence )(Not interrupted)
    Tim3CB2E     = 13u,        ///< CH2B capture  Data loss flag ( Mode only 23 presence )(Not interrupted)
    Tim3BkIrq    = 14u,        ///< Brake interrupt( Mode only 23 presence ）
    Tim3TrigIrq  = 15u,        ///< Trigger interrupt( Mode only 23 presence ）   
}en_tim3_irq_type_t;

/**
 ******************************************************************************
 ** \brief Measurement start end data type definition (Edg1stEdg2nd) (mode 1)
 *****************************************************************************/
typedef enum en_tim3_m1cr_Edge
{
    Tim3PwcRiseToRise  = 0u,            ///< Rising edge to rising edge (period)
    Tim3PwcFallToRise  = 1u,            ///< Falling edge to rising edge (low level)
    Tim3PwcRiseToFall  = 2u,            ///< Rising edge to falling edge (high level)
    Tim3PwcFallToFall  = 3u,            ///< Falling edge to falling edge (period)
}en_tim3_m1cr_Edge_t;

/**
 ******************************************************************************
 ** \brief PWC measurement test mode selection data type definition (Oneshot) (mode 1)
 *****************************************************************************/
typedef enum en_tim3_m1cr_oneshot
{
    Tim3PwcCycleDetect    = 0u,         ///< PWC cycle measurement
    Tim3PwcOneShotDetect  = 1u,         ///< PWC single measurement
}en_tim3_m1cr_oneshot_t;

/**
 ******************************************************************************
 ** \brief PWC IA0 select data type definition (IA0S) (mode 1)
 *****************************************************************************/
typedef enum en_tim3_m1_mscr_ia0s
{
    Tim3IA0Input    = 0u,         ///< IAO input
    Tim3XORInput    = 1u,         ///< IA0 ETR GATE XOR(TIM0/1/2)/IA0 IA1 IA2 XOR(TIM3)
}en_tim3_m1_mscr_ia0s_t;

/**
 ******************************************************************************
 ** \brief PWC IB0 select data type definition (IA0S) (mode 1)
 *****************************************************************************/
typedef enum en_tim3_m1_mscr_ib0s
{
    Tim3IB0Input    = 0u,         ///< IBO input
    Tim3TsInput     = 1u,         ///< Internal trigger TS selection signal
}en_tim3_m1_mscr_ib0s_t;

/**
 ******************************************************************************
 ** \brief Output Polarity, Input Phase Data Type definition (CCPA0/CCPB0/ETP/BKP) (Mode 1/23)
 *****************************************************************************/
typedef enum en_tim3_port_polarity
{
    Tim3PortPositive      = 0u,         ///< Normal input and output
    Tim3PortOpposite      = 1u,         ///< Inverting input and output
}en_tim3_port_polarity_t;

/**
 ******************************************************************************
 ** \brief Filter Select Data Type definition (FLTET/FLTA0/FLAB0) (Mode 1/23)
 *****************************************************************************/
typedef enum en_tim3_flt
{
    Tim3FltNone          = 0u,         ///< No filtering
    Tim3FltPCLKCnt3      = 4u,         ///< PCLK 3 Continuously valid
    Tim3FltPCLKDiv4Cnt3  = 5u,         ///< PCLK/4 3 Continuously valid
    Tim3FltPCLKDiv16Cnt3 = 6u,         ///< PCLK/16 3 Continuously valid
    Tim3FltPCLKDiv64Cnt3 = 7u,         ///< PCLK/64 3 Continuously valid
}en_tim3_flt_t;

/**
 ******************************************************************************
 ** \brief channel Comparison Control Data Type definition (OCMA/OCMB) (Mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_fltr_ocm
{
    Tim3ForceLow      = 0u,         ///< Forced to 0
    Tim3ForceHigh     = 1u,         ///< Forced to 1
    Tim3CMPForceLow   = 2u,         ///< Forced when comparing matches0
    Tim3CMPForceHigh  = 3u,         ///< Forced when comparing matches1
    Tim3CMPInverse    = 4u,         ///< Flip level when comparing matches
    Tim3CMPOnePrdHigh = 5u,         ///< Output a high level of the count period when the match is matched
    Tim3PWMMode1      = 6u,         ///< channel Control PWM mode 1
    Tim3PWMMode2      = 7u,         ///< channel Control PWM mode 2
}en_tim3_m23_fltr_ocm_t;

/**
 ******************************************************************************
 ** \brief Master-slave mode TS data type definition (TS) (mode 1/23)
 *****************************************************************************/
typedef enum en_tim3_mscr_ts
{
    Tim3Ts0ETR        = 0u,         ///< ETR external input filtered phase selection signal
    Tim3Ts1TIM0TRGO   = 1u,         ///< Timer0 of TRGO output signal 
    Tim3Ts2TIM1TRGO   = 2u,         ///< Timer1 of TRGO output signal 
    Tim3Ts3TIM2TRGO   = 3u,         ///< Timer2 of TRGO output signal 
    Tim3Ts4TIM3TRGO   = 4u,         ///< Timer3 of TRGO output signal 
    //Tim3Ts5IA0ED    = 5u,         ///< invalid
    Tim3Ts6IAFP       = 6u,         ///< CH0A After external input input filtering of Phase selection signal
    Tim3Ts7IBFP       = 7u,         ///< CH0B After external input input filtering of Phase selection letter
}en_tim3_mscr_ts_t;

/**
 ******************************************************************************
 ** \brief PWM Output Mode Select Data Type definition (COMP) (Mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23cr_comp
{
    Tim3IndependentPWM      = 0u,         ///< Independent PWM output
    Tim3ComplementaryPWM    = 1u,         ///< Complementary PWM output
}en_tim3_m23cr_comp_t;

/**
 ******************************************************************************
 ** \brief Count Direction Select Data Type definition (DIR) (Mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23cr_dir
{
    Tim3CntUp      = 0u,         ///< Count up
    Tim3CntDown    = 1u,         ///< Count down
}en_tim3_m23cr_dir_t;

/**
 ******************************************************************************
 ** \brief Count direction selection data type definition (PWM2S) (mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23cr_pwm2s
{
    Tim3DoublePointCmp      = 0u,         ///< Two-point comparison enable, use CCRA, CCRB compare control OCREFA output
    Tim3SinglePointCmp      = 1u,         ///< Single point comparison enable, use CCRA comparison control OCREFA output
}en_tim3_m23cr_pwm2s_t;

/**
 ******************************************************************************
 ** \brief GATE capture or compare function in PWM complementary mode Select data type definition (CSG) (mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23cr_csg
{
     Tim3PWMCompGateCmpOut    = 0u,         ///< In PWM complementary mode, Gate is used as a comparison output.
     Tim3PWMCompGateCapIn     = 1u,         ///< In PWM complementary mode, Gate is used as capture input
}en_tim3_m23cr_csg_t;


/**
 ******************************************************************************
 ** \brief Compare capture register data type definition (CCR0A, CCR0B) (mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_ccrx
{
     Tim3CCR0A    = 0u,         ///< CCR0A Compare capture  register 
     Tim3CCR0B    = 1u,         ///< CCR0B Compare capture  register 
     Tim3CCR1A    = 2u,         ///< CCR1A Compare capture  register 
     Tim3CCR1B    = 3u,         ///< CCR1B Compare capture  register 
     Tim3CCR2A    = 4u,         ///< CCR2A Compare capture  register 
     Tim3CCR2B    = 5u,         ///< CCR2B Compare capture  register 
}en_tim3_m23_ccrx_t;

/**
 ******************************************************************************
 ** \brief  OCREF Clear Source Select Data Type definition (OCCS) (Mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23ce_occs
{
     Tim3OC_Ref_Clr  = 0u,         ///< From VC of OC_Ref_Clr
     Tim3ETRf        = 1u,         ///< External ETRf
}en_tim3_m23ce_occs_t;

/**
 ******************************************************************************
 ** \brief  Compare Match Interrupt Mode Select Data Type definition (CIS/CISB) (Mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_cisa_cisb
{
     Tim3CmpIntNone        = 0u,         ///< No comparison match interrupt
     Tim3CmpIntRise        = 1u,         ///< Compare match rising edge interrupt
     Tim3CmpIntFall        = 2u,         ///< Compare match falling edge interrupt
     Tim3CmpIntRiseFall    = 3u,         ///< Compare match rising edge falling edge interrupt
}en_tim3_m23_cisa_cisb_t;

/**
 ******************************************************************************
 ** \brief TIM3 port control - CHx output status control (BKSA/BKSB) when braking (mode 23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_tim3_m23_crchx_bks
{
    Tim3CHxBksHiZ         = 0u,         ///< When the brake is enabled ，CHx Port output high impedance state
    Tim3CHxBksNorm        = 1u,         ///< When the brake is enabled ，CHx Normal port output
    Tim3CHxBksLow         = 2u,         ///< When the brake is enabled ，CHx Port output low level
    Tim3CHxBksHigh        = 3u,         ///< When the brake is enabled ，CHx Port output high level
}en_tim3_m23_crchx_bks_t;

/**
 ******************************************************************************
** \brief TIM3 port control - CHx rising edge falling edge capture (CRx/CFx) (mode 23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_tim3_m23_crch0_cfx_crx
{
    Tim3CHxCapNone        = 0u,         ///< CHxchannel  capture disabled
    Tim3CHxCapRise        = 1u,         ///< CHxchannel Rising edge capture  Enabled
    Tim3CHxCapFall        = 2u,         ///< CHxchannel Falling edge capture  Enabled
    Tim3CHxCapFallRise    = 3u,         ///< CHxchannel All edge capture  Enabled
}en_tim3_m23_crch0_cfx_crx_t;

/**
 ******************************************************************************
** \brief TIM3 Port Control - CHx Compare capture mode (CSA/CSB) (Mode 23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_tim3_m23_crch0_csa_csb
{
    Tim3CHxCmpMode        = 0u,         ///< CHxchannel Set to compare mode
    Tim3CHxCapMode        = 1u,         ///< CHxchannel Set to capture mode
}en_tim3_m23_crch0_csa_csb_t;

/**
 ******************************************************************************
 ** \brief  Compare mode DMA comparison trigger selection Data type definition (CCDS) (mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_mscr_ccds
{
     Tim3CmpTrigDMA  = 0u,         ///< Compare match triggers DMA
     Tim3UEVTrigDMA  = 1u,         ///< Event update instead of compare match triggers DMA
}en_tim3_m23_mscr_ccds_t;

/**
 ******************************************************************************
 ** \brief  Master-slave mode selection Data type definition (MSM) (mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_mscr_msm
{
     Tim3SlaveMode    = 0u,         ///< Slave mode
     Tim3MasterMode   = 1u,         ///< Master mode
}en_tim3_m23_mscr_msm_t;

/**
 ******************************************************************************
 ** \brief  Trigger Master Mode Output Source Data Type definition (MMS) (Mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_mscr_mms
{
     Tim3MasterUG         = 0u,         ///< UG (software update) source
     Tim3MasterCTEN       = 1u,         ///< CTEN source
     Tim3MasterUEV        = 2u,         ///< UEV update source
     Tim3MasterCMPSO      = 3u,         ///< Compare match select output source
     Tim3MasterOCA0Ref    = 4u,         ///< OCA0_Ref source
     Tim3MasterOCB0Ref    = 5u,         ///< OCB0_Ref source
     //Tim3MasterOCB0Ref  = 6u,
     //Tim3MasterOCB0Ref  = 7u,
}en_tim3_m23_mscr_mms_t;

/**
 ******************************************************************************
 ** \brief  Trigger slave mode data type definition (SMS) (mode 23)
 *****************************************************************************/
typedef enum en_tim3_m23_mscr_sms
{
     Tim3SlaveIClk        = 0u,         ///< Use internal clock
     Tim3SlaveResetTIM    = 1u,         ///< Reset function
     Tim3SlaveTrigMode    = 2u,         ///< Trigger mode
     Tim3SlaveEClk        = 3u,         ///< External clock mode
     Tim3SlaveCodeCnt1    = 4u,         ///< Orthogonal coding counting mode 1
     Tim3SlaveCodeCnt2    = 5u,         ///< Orthogonal coding counting mode 2
     Tim3SlaveCodeCnt3    = 6u,         ///< Orthogonal coding counting mode 3
     Tim3SlaveGateCtrl    = 7u,         ///< Gating function
}en_tim3_m23_mscr_sms_t;

/**
 ******************************************************************************
 ** \brief Timer Run Control Data Type definition (CTEN)
 *****************************************************************************/
typedef enum en_tim3_start
{
    Tim3CTENDisable = 0u,            ///< disable
    Tim3CTENEnable  = 1u,            ///< enable
}en_tim3_start_t;

/**
 ******************************************************************************
 ** \brief TIM3 Mode0 configuration structure definition (mode 0)
 *****************************************************************************/
typedef struct stc_tim3_mode0_config
{
    en_tim3_work_mode_t     enWorkMode;       ///< Working mode setting
    en_tim3_m0cr_gatep_t    enGateP;          ///< Gate polarity control
    boolean_t               bEnGate;          ///< Gating Enabled
    en_tim3_cr_timclkdiv_t  enPRS;            ///< Prescaler configuration 
    boolean_t               bEnTog;           ///< Flip output Enabled
    en_tim3_cr_ct_t         enCT;             ///< Timing / counting function selection
    en_tim3_m0cr_md_t       enCntMode;        ///< Count mode configuration
    
    func_ptr_t              pfnTim3Cb;        ///< Timer3 interrupt service callback function [void function(void)]
}stc_tim3_mode0_config_t;

/**
 ******************************************************************************
 ** \brief TIM3 mode1 Configuration Structure Definition (Mode 1)
 *****************************************************************************/
typedef struct stc_tim3_mode1_config
{
    en_tim3_work_mode_t     enWorkMode;       ///< Working mode setting 
    en_tim3_cr_timclkdiv_t  enPRS;            ///< Prescaler configuration 
    en_tim3_cr_ct_t         enCT;             ///< Timing / counting function selection
    en_tim3_m1cr_oneshot_t  enOneShot;        ///< Single measurement / cycle measurement selection
    
    func_ptr_t              pfnTim3Cb;        ///< Timer3 interrupt service callback function [void function(void)]

}stc_tim3_mode1_config_t;

/**
 ******************************************************************************
 ** \brief PWC input configuration structure definition (mode 1)
 *****************************************************************************/
typedef struct stc_tim3_pwc_input_config
{
    en_tim3_mscr_ts_t          enTsSel;       ///<  Trigger input source selection 
    en_tim3_m1_mscr_ia0s_t     enIA0Sel;      ///< CHA0 Input selection 
    en_tim3_m1_mscr_ib0s_t     enIB0Sel;      ///< CHB0 Input selection 
    en_tim3_port_polarity_t    enETRPhase;    ///< ETR Phase selection 
    en_tim3_flt_t              enFltETR;      ///< ETR Filter setting 
    en_tim3_flt_t              enFltIA0;      ///< CHA0 Filter setting 
    en_tim3_flt_t              enFltIB0;      ///< CHB0 Filter setting 
}stc_tim3_pwc_input_config_t;

/**
 ******************************************************************************
 ** \brief TIM3 mode23 Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_tim3_mode23_config
{
    en_tim3_work_mode_t         enWorkMode;       ///< Working mode setting 
    en_tim3_m23cr_dir_t         enCntDir;         ///< Counting direction
    en_tim3_cr_timclkdiv_t      enPRS;            ///< Clock Prescaler configuration 
    en_tim3_cr_ct_t             enCT;             ///< Timing / counting function selection
    en_tim3_m23cr_comp_t        enPWMTypeSel;     ///< PWM mode selection (independent/complementary)
    en_tim3_m23cr_pwm2s_t       enPWM2sSel;       ///< OCREFA double point comparison function selection
    boolean_t                   bOneShot;         ///< Single trigger mode Enabled / Disabled
    boolean_t                   bURSSel;          ///< Update source selection
    
    func_ptr_t                  pfnTim3Cb;        ///< Timer3 interrupt service callback function [void function(void)]
}stc_tim3_mode23_config_t;

/**
 ******************************************************************************
 ** \brief GATE capture or compare function in PWM complementary mode Configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_gate_config
{
    en_tim3_m23cr_csg_t        enGateFuncSel;      ///< Gate comparison, capture function selection
    boolean_t                  bGateRiseCap;       ///< When GATE is used as the capture function, the upper edge capture is effectively controlled.
    boolean_t                  bGateFallCap;       ///< When GATE is used as the capture function, the lower edge capture is effectively controlled.
}stc_tim3_m23_gate_config_t;

/**
 ******************************************************************************
 ** \brief CHA/CHBchannel Comparison Control Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_compare_config
{
    en_tim3_m23_crch0_csa_csb_t  enCHxACmpCap;     ///< CH0A comparison / capture function selection
    en_tim3_m23_fltr_ocm_t       enCHxACmpCtrl;    ///< CH0Achannel Compare control
    en_tim3_port_polarity_t      enCHxAPolarity;   ///< CH0AOutput polarity control
    boolean_t                    bCHxACmpBufEn;    ///< Compare A buffer function Enabled / Disable
    en_tim3_m23_cisa_cisb_t      enCHxACmpIntSel;  ///< CHA compare match interrupt selection
    
    en_tim3_m23_crch0_csa_csb_t  enCHxBCmpCap;     ///< CH0B comparison / capture function selection
    en_tim3_m23_fltr_ocm_t       enCHxBCmpCtrl;    ///< CH0Bchannel Compare control
    en_tim3_port_polarity_t      enCHxBPolarity;   ///< CH0B output polarity control
    boolean_t                    bCHxBCmpBufEn;    ///< Compare B buffer function Enabled / Disable
    en_tim3_m23_cisa_cisb_t      enCHxBCmpIntSel;  ///< CHB0 compare match interrupt selection
}stc_tim3_m23_compare_config_t;

/**
 ******************************************************************************
 ** \brief CHA/CHBchannel  capture Control Configuration Structure Definition (Mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_input_config
{
    en_tim3_m23_crch0_csa_csb_t  enCHxACmpCap;     ///< CH0A comparison / capture function selection
    en_tim3_m23_crch0_cfx_crx_t  enCHxACapSel;     ///< CH0A capture edge selection
    en_tim3_flt_t                enCHxAInFlt;      ///< CH0Achannel capture filter control
    en_tim3_port_polarity_t      enCHxAPolarity;   ///< CH0A input phase
    
    en_tim3_m23_crch0_csa_csb_t  enCHxBCmpCap;     ///< CH0B comparison / capture function selection
    en_tim3_m23_crch0_cfx_crx_t  enCHxBCapSel;     ///< CH0B capture Edge selection
    en_tim3_flt_t                enCHxBInFlt;      ///< CH0Bchannel  capture Filter control
    en_tim3_port_polarity_t      enCHxBPolarity;   ///< CH0B input phase
    
}stc_tim3_m23_input_config_t;   

/**
 ******************************************************************************
 ** \brief ETR input phase filter configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_etr_input_config
{
    en_tim3_port_polarity_t     enETRPolarity;  ///< ETR input polarity setting
    en_tim3_flt_t               enETRFlt;       ///< ETR Filter setting 
}stc_tim3_m23_etr_input_config_t;

/**
 ******************************************************************************
 ** \brief Brake BK input phase filter configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_bk_input_config
{
    boolean_t                   bEnBrake;         ///< brake Enabled
    boolean_t                   bEnVC0Brake;      ///<  EnabledVC0 brake 
    boolean_t                   bEnVC1Brake;      ///<  EnabledVC1 brake 
    boolean_t                   bEnSafetyBk;      ///<  Enabledsafety brake 
    boolean_t                   bEnBKSync;        ///< TIM0/TIM1/TIM2 brake Synchronize Enabled
    en_tim3_m23_crchx_bks_t     enBkCH0AStat;     ///<  brake  CHA port status setting 
    en_tim3_m23_crchx_bks_t     enBkCH0BStat;     ///<  brake  CHB port status setting 
    en_tim3_m23_crchx_bks_t     enBkCH1AStat;     ///<  brake  CHA port status setting 
    en_tim3_m23_crchx_bks_t     enBkCH1BStat;     ///<  brake  CHB port status setting 
    en_tim3_m23_crchx_bks_t     enBkCH2AStat;     ///<  brake  CHA port status setting 
    en_tim3_m23_crchx_bks_t     enBkCH2BStat;     ///<  brake  CHB port status setting 
    en_tim3_port_polarity_t     enBrakePolarity;  ///<  brake BK input polarity setting
    en_tim3_flt_t               enBrakeFlt;       ///<  brake BK Filter setting 
}stc_tim3_m23_bk_input_config_t;

/**
 ******************************************************************************
** \brief Dead zone function configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_dt_config
{
    boolean_t       bEnDeadTime;      ///<  brake  CHA port status setting 
    uint8_t         u8DeadTimeValue;  ///<  brake  CHA port status setting 
}stc_tim3_m23_dt_config_t;

/**
 ******************************************************************************
 ** \brief Trigger ADC configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_adc_trig_config
{
    boolean_t     bEnTrigADC;          ///< Trigger ADC global control
    boolean_t     bEnUevTrigADC;       ///< Event update triggers ADC
    boolean_t     bEnCH0ACmpTrigADC;   ///< CH0A Compare match trigger ADC 
    boolean_t     bEnCH0BCmpTrigADC;   ///< CH0B Compare match trigger ADC 
    boolean_t     bEnCH1ACmpTrigADC;   ///< CH0A Compare match trigger ADC 
    boolean_t     bEnCH1BCmpTrigADC;   ///< CH0B Compare match trigger ADC 
    boolean_t     bEnCH2ACmpTrigADC;   ///< CH0A Compare match trigger ADC 
    boolean_t     bEnCH2BCmpTrigADC;   ///< CH0B Compare match trigger ADC 
}stc_tim3_m23_adc_trig_config_t;

/**
 ******************************************************************************
 ** \brief  DMA trigger configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_trig_dma_config
{
    boolean_t                bUevTrigDMA;      ///< Update trigger DMA Enabled
    boolean_t                bTITrigDMA;       ///< Trig Trigger DMA function
    boolean_t                bCmpA0TrigDMA;    ///< CH0A capture Comparison trigger DMA Enabled
    boolean_t                bCmpB0TrigDMA;    ///< CH0B capture Comparison trigger DMA Enabled
    boolean_t                bCmpA1TrigDMA;    ///< CH1A capture Comparison trigger DMA Enabled
    boolean_t                bCmpB1TrigDMA;    ///< CH1B capture Comparison trigger DMA Enabled
    boolean_t                bCmpA2TrigDMA;    ///< CH2A capture Comparison trigger DMA Enabled
    boolean_t                bCmpB2TrigDMA;    ///< CH2B capture Comparison trigger DMA Enabled
    en_tim3_m23_mscr_ccds_t  enCmpUevTrigDMA;  ///< DMA Comparison trigger selection in compare mode
}stc_tim3_m23_trig_dma_config_t;

/**
 ******************************************************************************
 ** \brief  Master-slave mode Configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_master_slave_config
{
    en_tim3_m23_mscr_msm_t      enMasterSlaveSel;  ///< Master-slave mode selection
    en_tim3_m23_mscr_mms_t      enMasterSrc;       ///< Main mode trigger source selection
    en_tim3_m23_mscr_sms_t      enSlaveModeSel;    ///< Select slave mode
    en_tim3_mscr_ts_t           enTsSel;           ///<  Trigger input source selection 
}stc_tim3_m23_master_slave_config_t;

/**
 ******************************************************************************
 ** \brief  OCREF clear function Configuration structure definition (mode 23)
 *****************************************************************************/
typedef struct stc_tim3_m23_OCREF_Clr_config
{
    en_tim3_m23ce_occs_t       enOCRefClrSrcSel;  ///< OCREF clear source selection
    boolean_t                  bVCClrEn;          ///< Whether Enabled from VC of OCREF_Clr
}stc_tim3_m23_OCREF_Clr_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//Interrupt related function

//Interrupt flag acquisition
boolean_t Tim3_GetIntFlag(en_tim3_irq_type_t enTim3Irq);
//Interrupt flag clear
en_result_t Tim3_ClearIntFlag(en_tim3_irq_type_t enTim3Irq);
//All interrupt flags clear
en_result_t Tim3_ClearAllIntFlag(void);
//Mode 0 interrupt Enable
en_result_t Tim3_Mode0_EnableIrq(void);
//Mode 1 interrupt Enable
en_result_t Tim3_Mode1_EnableIrq (en_tim3_irq_type_t enTim3Irq);
//Mode 2 interrupt Enable
en_result_t Tim3_Mode23_EnableIrq (en_tim3_irq_type_t enTim3Irq);
//Mode 0 interrupt disable
en_result_t Tim3_Mode0_DisableIrq(void);
//Mode 1 interrupt disable
en_result_t Tim3_Mode1_DisableIrq (en_tim3_irq_type_t enTim3Irq);
//Mode 2 interrupt disable
en_result_t Tim3_Mode23_DisableIrq (en_tim3_irq_type_t enTim3Irq);


//Mode 0 initialization and related function operations

//Timer configuration and initialization
en_result_t Tim3_Mode0_Init(stc_tim3_mode0_config_t* pstcConfig);
//timer  start /stop
en_result_t Tim3_M0_Run(void);
en_result_t Tim3_M0_Stop(void);
//Overflow value setting
en_result_t Tim3_M0_ARRSet(uint16_t u16Data);
//16-bit count value setting/read
en_result_t Tim3_M0_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M0_Cnt16Get(void);
//32-bit count value setting/read
en_result_t Tim3_M0_Cnt32Set(uint32_t u32Data);
uint32_t Tim3_M0_Cnt32Get(void);
//Flip output Enabled / disable setting
en_result_t Tim3_M0_EnTOG_Output(boolean_t bEnOutput);


//Mode 1 initialization and related function operations

//Timer configuration and initialization
en_result_t Tim3_Mode1_Init(stc_tim3_mode1_config_t* pstcConfig);
//PWC Input configuration
en_result_t Tim3_M1_Input_Config(stc_tim3_pwc_input_config_t* pstcConfig);
//PWC measurement edge start end selection
en_result_t Tim3_M1_PWC_Edge_Sel(en_tim3_m1cr_Edge_t enEdgeSel);
//timer  start /stop
en_result_t Tim3_M1_Run(void);
en_result_t Tim3_M1_Stop(void);
//16-bit count value setting/read
en_result_t Tim3_M1_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M1_Cnt16Get(void);
//Pulse width measurement result value read
uint16_t Tim3_M1_PWC_CapValueGet(void);


//Mode 1 initialization and related function operations

//Timer configuration and initialization
en_result_t Tim3_Mode23_Init(stc_tim3_mode23_config_t* pstcConfig);
//timer  start /stop
en_result_t Tim3_M23_Run(void);
en_result_t Tim3_M23_Stop(void);
//PWM output Enable
en_result_t Tim3_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput);
//Overflow value setting
en_result_t Tim3_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn);
//16-bit count value setting/read
en_result_t Tim3_M23_Cnt16Set(uint16_t u16Data);
uint16_t Tim3_M23_Cnt16Get(void);
// Compare capture  register CCR0A/CCR0B Set/read
en_result_t Tim3_M23_CCR_Set(en_tim3_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Tim3_M23_CCR_Get(en_tim3_m23_ccrx_t enCCRSel);
//GATE function selection in PWM complementary output mode
en_result_t Tim3_M23_GateFuncSel(stc_tim3_m23_gate_config_t* pstcConfig);
//Master-slave mode configuration
en_result_t Tim3_M23_MasterSlave_Set(stc_tim3_m23_master_slave_config_t* pstcConfig);
//CH0A/CH0B comparison channel control
en_result_t Tim3_M23_PortOutput_Config(en_tim3_channel_t enTim3Chx, stc_tim3_m23_compare_config_t* pstcConfig);
//CH0A/CH0B input control
en_result_t Tim3_M23_PortInput_Config(en_tim3_channel_t enTim3Chx, stc_tim3_m23_input_config_t* pstcConfig);
//ERT input control
en_result_t Tim3_M23_ETRInput_Config(stc_tim3_m23_etr_input_config_t* pstcConfig);
// brake BK input control
en_result_t Tim3_M23_BrakeInput_Config(stc_tim3_m23_bk_input_config_t* pstcConfig);
//Trigger ADC control
en_result_t Tim3_M23_TrigADC_Config(stc_tim3_m23_adc_trig_config_t* pstcConfig);
//Dead zone function
en_result_t Tim3_M23_DT_Config(stc_tim3_m23_dt_config_t* pstcConfig);
//Repeat cycle setting
en_result_t Tim3_M23_SetValidPeriod(uint8_t u8ValidPeriod);
//OCREF clear function
en_result_t Tim3_M23_OCRefClr(stc_tim3_m23_OCREF_Clr_config_t* pstcConfig);
// Enable DMA transfer
en_result_t Tim3_M23_EnDMA(stc_tim3_m23_trig_dma_config_t* pstcConfig);
// capture Compare A software trigger
en_result_t Tim3_M23_EnSwTrigCapCmpA(en_tim3_channel_t enTim3Chx);
// capture Compare B software trigger
en_result_t Tim3_M23_EnSwTrigCapCmpB(en_tim3_channel_t enTim3Chx);
//Software update Enable
en_result_t Tim3_M23_EnSwUev(void);
//Software trigger Enable
en_result_t Tim3_M23_EnSwTrig(void);
//software brake  Enable
en_result_t Tim3_M23_EnSwBk(void);


//@} // Tim3Group

#ifdef __cplusplus
#endif


#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



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
* @file vc.h 
* 
* @brief Header file for VC functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __VC_H__
#define __VC_H__

/****************************************************************************** 
* Include files 
******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup VcGroup Voltage Comparator (VC) 
** 
******************************************************************************/
//@{

/****************************************************************************** 
* Global type definitions 
******************************************************************************/

/** 
****************************************************************************** 
** \brief VC Channel
***********************************************************************/
typedef enum
{
    VcChannel0 = 0u, // Channel 0
    VcChannel1 = 1u, // Channel 1
    VcChannel2 = 2u // Channel 2
}en_vc_channel_t;

/**
********************************************************************************
** \brief VC Hysteresis VC_CR VCx_HYS_SEL(x=0, 1, 2)
***********************************************************************/
typedef enum
{
    VcDelayoff = 0u, // Hysteresis off
    VcDelay10mv = 1u, // Hysteresis 10mv
    VcDelay20mv = 2u, // Hysteresis 20mv
    VcDelay30mv = 3u, // 30mV hysteresis
}en_vc_cmp_delay_t;

/**
************************************************************************
** \brief VC bias current VC_CR VCx_BIAS_SEL(x=0, 1, 2)
*************************************************************************/
typedef enum
{
    VcBias300na = 0u, // 300nA bias current
    VcBias1200na = 1u, // 1.2uA bias current
    VcBias10ua = 2u, // 10uA bias current
    VcBias20ua = 3u, // 20uA bias current
}en_vc_bias_current_t;

/**
************************************************************************************
** \brief VC output filter time VCx_CR debounce_time(x=0, 1, 2)
**************************************************************************/
typedef enum
{
    VcFilter7us = 0u, // Output filter time 7us
    VcFilter14us = 1u, // Output filter time 14us
    VcFilter28us = 2u, // Output filter time 28us
    VcFilter112us = 3u, // Output filter time 112us
    VcFilter450us = 4u, // Output filter time 450us
    VcFilter1800us = 5u, // Output filter time 1.8ms
    VcFilter7200us = 6u, // Output filter time 7.2ms
    VcFilter28800us = 7u, // Output filter time 28.8ms
}en_vc_resp_filter_t;

/**
****************************************************************************
** \brief VC P-terminal input
************************************************************************/
typedef enum
{
    //VC0 //VC1 //VC2
    VcInPCh0 = 0u, // Input channel 0 PC0 Input channel 0 PA0 Input channel 0 PA5
    VcInPCh1 = 1u, // Input channel 1 PC1 Input channel 1 PA1 Input channel 1 PB1
    VcInPCh2 = 2u, // Input channel 2 PC2 Input channel 2 PA2 Input channel 2 PE9
    VcInPCh3 = 3u, // Input channel 3 PC3 Input channel 3 PA3 Input channel 3 PE10
    VcInPCh4 = 4u, // Input channel 4 PA0 Input channel 4 PA4 Input channel 4 PE11
    VcInPCh5 = 5u, // Input channel 5 PA1 Input channel 5 PA5 Input channel 5 PE13
    VcInPCh6 = 6u, // Input channel 6 PA2 Input channel 6 PB1 Input channel 6 PE14
    VcInPCh7 = 7u, // Input channel 7 PA3 Input channel 7 PB2 Input channel 7 PE15
    VcInPCh8 = 8u, // Input channel 7 PA4 Input channel 8 PB10 Input channel 8 PB11
    VcInPCh9 = 9u, // Input channel 7 PA5 Input channel 9 PB12 Input channel 9 PB14
    VcInPCh10 = 10u, // Input channel 7 PA6 Input channel 10 PB13 Input channel 10 PD9
    VcInPCh11 = 11u, // Input channel 7 PA7 Input channel 11 PB14 Input channel 11 PD10
    VcInPCh12 = 12u, // Input channel 7 PB4 Input channel 12 PB4 Input channel 12 PD11
    VcInPCh13 = 13u, // Input channel 7 PB5 Input channel 13 DAC0 Input channel 13 PC7
    VcInPCh14 = 14u, // Input channel 7, PB6, input channel 14, PB6, input channel 14, DAC0
    VcInPCh15 = 15u, // Input channel 7, DAC0, input channel 15, PB7, input channel 15, DAC0
}en_vc_input_p_src_t;

/**
********************************************************************************
** \brief VC N-terminal input
*****************************************************************************/
typedef enum
{
    //VC0 //VC1 //VC2
    VcInNCh0 = 0u, // Input channel 0, PA0, input channel 0, PC0, input channel 0, PA5
    VcInNCh1 = 1u, // Input channel 1, PA1, input channel 1, PC1, input channel 1, PB1
    VcInNCh2 = 2u, // Input channel 2, PA2, input channel 2, PC2, input channel 2 PE11
    VcInNCh3 = 3u, // Input channel 3 PA3 Input channel 3 PC3 Input channel 3 PE15
    VcInNCh4 = 4u, // Input channel 4 PA4 Input channel 4 PA0 Input channel 4 PB11
    VcInNCh5 = 5u, // Input channel 5 PA5 Input channel 5 PA1 Input channel 5 PB14
    VcInNCh6 = 6u, // Input channel 6 PA6 Input channel 6 PB0 Input channel 6 PD10
    VcInNCh7 = 7u, // Input channel 7 PA7 Input channel 7 PB1 Input channel 7 PD11
    VcInNCh8 = 8u, // Input channel 8 PC4 Input channel 8 PB2 Input channel 8 PC7
    VcInNCh9 = 9u, // Input channel 9 PC5 Input channel 9 PB3 Input channel 9 DAC0
    VcInNCh10 = 10u, // Input channel 10 DAC0
    ResDivOut = 11u, // Resistor divider voltage
    AiTs = 12u, // Internal temperature sensor output voltage
    AiBg1p2 = 13u, // Internal reference 1.2V
    AiAdcVref = 14u, // ADC reference voltage VREF
    AiLdo = 15u, // LDO output voltage
}en_vc_input_n_src_t;

/**
****************************************************************************
** \brief VC interrupt trigger method
*****************************************************************************/
typedef enum en_vc_irq_sel
{
    VcIrqNone = 0u, ///< No interrupt
    VcIrqRise = 1u, ///< Rising edge trigger
    VcIrqFall = 2u, ///< Falling edge trigger
    VcIrqHigh = 3u, ///< High level trigger
}en_vc_irq_sel_t;

/**
********************************************************************************
** \brief VC status VC_IFR
***************************************************************************/
typedef enum en_vc_stat
{
    Vc0_Intf = 0u, // VC0 interrupt flag
    Vc1_Intf = 1u, // VC1 interrupt flag
    Vc0_Filter = 2u, // VC0 status after filter
    Vc1_Filter = 3u, // VC1 status after filter
    Vc2_Intf = 4u, // VC2 interrupt flag
    Vc2_Filter = 5u // VC2 status after filter
}en_vc_ifr_t;

/**
********************************************************************************
** \brief VC output configuration VCx_OUT_CFG (x=0, 1, 2)
** \note For VC0, CHX = CHA; for VC1 and VC2, CHX = CHB
***********************************************************************/
typedef enum en_vc_output_cfg
{
    VcOutInvTimer = 0u, // Result output is inverted to Timers 0, 1, 2, and 3 REFCLR
    VcOutTIM0RCLR = 1u, // Output result to TIM0 REFCLR enable control
    VcOutTIM1RCLR = 2u, // Output result to TIM1 REFCLR enable control
    VcOutTIM2RCLR = 3u, // Output result to TIM2 REFCLR enable control
    VcOutTIM3RCLR = 4u, // Output result to TIM3 REFCLR enable control
    VcOutTIMBK = 5u, // Output result to Timer0, 1, 2, 3 brake control
    VcOutInvTIM4 = 9u, // Output result to Timer4 inverse enable
    VcOutTIM4 = 10u, // Output result to Timer4 capture input CHX enable
    VcOutInvTIM5 = 11u, // Output result to Timer5 inverse enable
    VcOutTIM5 = 12u, // Output result to Timer5 capture input CHX enable
    VcOutInvTIM6 = 13u, // Enable the reverse output of the result to Timer6
    VcOutTIM6 = 14u, // Enable the result output to Timer6 capture input CHX
    VcOutBrake = 15u, // Use the result as the brake control for the Advanced Timer
    VcOutDisable = 16u // Disable the result output
}en_vc_output_cfg_t;

/**
********************************************************************************
** \brief VC DIV reference voltage Vref selection VC_CR VC_REF2P5_SEL
***********************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc = 0u, ///< AVCC
    VcDivVrefAdc = 1u, ///< ADC_CR0 SREF selects the reference voltage
}en_vc_div_vref_t;

/**
******************************************************************************
** \brief VC module configuration VC_CR VC_REF2P5_SEL VC_DIV_EN VC_DIV
********************************************************************/
typedef struct stc_vc_dac_cfg
{
    boolean_t bDivEn; // VC_CR: VC_DIV_EN
    uint8_t u8DivVal; // VC_CR: VC_DIV range: 0-63
    en_vc_div_vref_t enDivVref; // VC_CR: VC_REF2P5_SEL
}stc_vc_dac_cfg_t;

/**
****************************************************************************
** \brief VC channel configuration
*************************************************************************/
typedef struct stc_vc_channel_cfg
{
    en_vc_channel_t enVcChannel; // VC channel selection
    en_vc_cmp_delay_t enVcCmpDly; // VC hysteresis
    en_vc_bias_current_t enVcBiasCurrent; // VC power consumption selection
    en_vc_resp_filter_t enVcFilterTime; // Output filter time
    en_vc_input_p_src_t enVcInPin_P; // P-pin input
    en_vc_input_n_src_t enVcInPin_N; // N-pin input
    en_vc_output_cfg_t enVcOutCfg; // Output configuration
    boolean_t bFlten; // Filter output enable
}stc_vc_channel_cfg_t;

/******************************************************************************
* Global definitions
**************************************************************************/

/**********************************************************************************
* Local type definitions ('typedef')
**************************************************************************/

/**********************************************************************************
* Global variable definitions ('extern') 
******************************************************************************/

/****************************************************************************** 
* Global function prototypes (definition in C source) 
******************************************************************************/
extern void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType);
extern void Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus);
extern boolean_t Vc_GetItStatus(en_vc_ifr_t Result);
extern void Vc_ClearItStatus(en_vc_ifr_t NewStatus);
extern en_result_t Vc_DacInit(stc_vc_dac_cfg_t *pstcDacCfg);
extern void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg);
extern void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus);



#ifdef __cplusplus
}
#endif

#endif /* __VC_H__ */
/****************************************************************************** 
* EOF (not truncated) 
******************************************************************************/

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
/******************************************************************************/
/** \file vc.h
 **
 ** Headerfile for Voltage Comparator functions
 ** @link VC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
 ** \brief VC channel
 *****************************************************************************/
typedef enum en_vc_channel
{
    VcChannel0 = 0u,                 ///< channel 0
    VcChannel1 = 1u,                 ///< channel 1
}en_vc_channel_t;


/**
 ******************************************************************************
 ** \brief VCHysteresis
 *****************************************************************************/
typedef enum en_vc_cmp_delay
{
    VcDelayoff  = 0u,            ///< Hysteresis off
    VcDelay10mv = 1u,            ///< Hysteresis 10mv
    VcDelay20mv = 2u,            ///< Hysteresis 20mv
    VcDelay30mv = 3u,            ///< Hysteresis 30mv
}en_vc_cmp_delay_t;

/**
 ******************************************************************************
 ** \brief VC bias current
 *****************************************************************************/
typedef enum en_vc_bias_current
{
    VcBias300na  = 0u,            ///< Bias current 300na
    VcBias1200na = 1u,            ///< Bias current 1.2ua
    VcBias10ua   = 2u,            ///< Bias current 10ua
    VcBias20ua   = 3u,            ///< Bias current 20ua
}en_vc_bias_current_t;

/**
 ******************************************************************************
 ** \brief VC output filter time
 *****************************************************************************/
typedef enum en_vc_resp_filter
{
    VcFilter7us     = 0u,            ///< Output filtering time 7us
    VcFilter14us    = 1u,           ///< Output filtering time 14us
    VcFilter28us    = 2u,           ///< Output filtering time 28us
    VcFilter112us   = 3u,          ///< Output filtering time 112us
    VcFilter450us   = 4u,          ///< Output filtering time 450us
    VcFilter1800us  = 5u,         ///< Output filtering time 1.8ms
    VcFilter7200us  = 6u,         ///< Output filtering time 7.2ms
    VcFilter28800us = 7u,        ///< Output filtering time 28.8ms
}en_vc_resp_filter_t;

/**
 ******************************************************************************
 ** \brief VC P input
 *****************************************************************************/
typedef enum en_vc_input_p_src
{																					
                                   //VC0                        //VC1
    VcInPCh0 = 0u,                ///< Input channel 0 PC0		Input channel 0 PA0
    VcInPCh1 = 1u,                ///< Input channel 1 PC1		Input channel 0 PA1
    VcInPCh2 = 2u,                ///< Input channel 2 PC2		Input channel 0 PA2
    VcInPCh3 = 3u,                ///< Input channel 3 PC3		Input channel 0 PA3
    VcInPCh4 = 4u,                ///< Input channel 4 PA0		Input channel 0 PA4
    VcInPCh5 = 5u,                ///< Input channel 5 PA1		Input channel 0 PA5
    VcInPCh6 = 6u,                ///< Input channel 6 PA2		Input channel 0 PB1
    VcInPCh7 = 7u,                ///< Input channel 7 PA3		Input channel 0 PB2
    VcInPCh8 = 8u,                ///< Input channel 7 PA4		Input channel 0 PB10
    VcInPCh9 = 9u,                ///< Input channel 7 PA5		Input channel 0 PB12
    VcInPCh10 = 10u,                ///< Input channel 7 PA6		Input channel 0 PB13
    VcInPCh11 = 11u,                ///< Input channel 7 PA7		Input channel 0 PB14
    VcInPCh12 = 12u,                ///< Input channel 7 PB4		Input channel 0 PB4
    VcInPCh13 = 13u,                ///< Input channel 7 PB5		Input channel 0 PB5
    VcInPCh14 = 14u,                ///< Input channel 7 PB6		Input channel 0 PB6
    VcInPCh15 = 15u,                ///< Input channel 7 PB7		Input channel 0 PB7                           
}en_vc_input_p_src_t;

/**
 ******************************************************************************
 ** \brief VC N-side Input 
 *****************************************************************************/
typedef enum en_vc_input_n_src
{
                                 //VC0                          //VC1
    VcInNCh0    = 0u,         ///< Input channel 0  PA0	        Input channel 0 PC0
    VcInNCh1    = 1u,         ///< Input channel 1  PA1		Input channel 0 PC1
    VcInNCh2    = 2u,         ///< Input channel 2  PA2		Input channel 0 PC2
    VcInNCh3    = 3u,         ///< Input channel 3  PA3		Input channel 0 PC3
    VcInNCh4    = 4u,         ///< Input channel 4  PA4		Input channel 0 PA0
    VcInNCh5    = 5u,         ///< Input channel 5  PA5		Input channel 0 PA1
    VcInNCh6    = 6u,         ///< Input channel 6  PA6		Input channel 0 PB0
    VcInNCh7    = 7u,         ///< Input channel 7  PA7		Input channel 0 PB1
    VcInNCh8    = 8u,         ///< Input channel 8  PC4		Input channel 0 PB2
    VcInNCh9    = 9u,         ///< Input channel 9  PC5		Input channel 0 PB3
    VcInNCh10   = 10u,        ///< Input channel 10 PB0 		Input channel 0 PB4   
    ResDivOut   = 11u,        ///< VccVCC divider                      VccVCC divider
    AiTs        = 12u,        ///< Temperature Sensor                   Temperature Sensor 
    AiBg1p2     = 13u,        ///< BGR 1.2V                    BGR 1.2V
    AiAdcVref   = 14u,        ///< ADCVREF                     ADCVREF
    AiLdo       = 15u,        ///< LDO                         LDO
}en_vc_input_n_src_t;

/**
 ******************************************************************************
 ** \brief VC interrupt trigger mode
 *****************************************************************************/
typedef enum en_vc_irq_sel
{
    VcIrqNone = 0u,            ///< No interrupt
    VcIrqRise = 1u,            ///< Rising edge trigger
    VcIrqFall = 2u,            ///< Falling edge trigger
    VcIrqHigh = 3u,            ///< High level trigger

}en_vc_irq_sel_t;

/**
 ******************************************************************************
 ** \brief VC status
 *****************************************************************************/
typedef enum en_vc_stat
{
    VcCmpResult  = 0u,                ///< VC comparison output
    VcIntrResult = 1u,               ///< VC interrupt status
}en_vc_stat_t;

/**
 ******************************************************************************
 ** \brief VC output configuration
 *****************************************************************************/
typedef enum en_vc_output_config
{
    VcOutInvTimer = 0u,              ///< Result output negative direction each Timer0,1,2,3
    VcOutTIM0RCLR = 1u,              ///< Result enable output to TIM0 REFCLR
    VcOutTIM1RCLR = 2u,              ///< Result enable output to TIM1 REFCLR
    VcOutTIM2RCLR = 3u,              ///< Result enable output to TIM2 REFCLR
    VcOutTIM3RCLR = 4u,              ///< Result enable output to TIM3 REFCLR
    VcOutTIMBK    = 5u,              ///< Result enable output to Timer0,1,2,3 brake
    VcOutInvTIM4  = 9u,              ///< Result output negative direction Timer4
    VcOutTIM4     = 10u,             ///< Result enable output to Timer4
    VcOutInvTIM5  = 11u,             ///< Result output negative direction Timer5
    VcOutTIM5     = 12u,             ///< Result enable output to Timer5
    VcOutInvTIM6  = 13u,             ///< Result output negative direction Timer6
    VcOutTIM6     = 14u,             ///< Result enable output to Timer6
    VcOutBrake    = 15u,             ///< Result enable output to Advanced Timer brake
    VcOutDisable  = 16u,             ///< Result output disabled
}en_vc_output_config_t;

/**
 ******************************************************************************
 ** \brief VC DIV reference voltage Vref selection
 *****************************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc = 0u,              ///< AVCC
    VcDivVrefAdc  = 1u,               ///< ADC_CR0 SREF selects reference voltage
}en_vc_div_vref_t;

/**
 ******************************************************************************
 ** \brief VC module configuration
 *****************************************************************************/
typedef struct stc_vc_dac_config
{
    boolean_t           bDivEn;       ///< Enable/disable 6-bit VCC divider
    uint8_t             u8DivVal;     ///< 6-bit VCC divider Settings
    en_vc_div_vref_t    enDivVref;    ///< 6-bit VCC divider Input Reference voltage selection
}stc_vc_dac_config_t;

/**
 ******************************************************************************
 ** \brief VCchannel Configuration
 *****************************************************************************/
typedef struct stc_vc_channel_config
{
    en_vc_channel_t         enVcChannel;        ///< VCchannel select
    en_vc_cmp_delay_t       enVcCmpDly;         ///< VCHysteresis
    en_vc_bias_current_t    enVcBiasCurrent;    ///< VC bias current
    en_vc_resp_filter_t     enVcFilterTime;     ///< Output filtering time 
    en_vc_input_p_src_t     enVcInPin_P;        ///< P-side Input 
    en_vc_input_n_src_t     enVcInPin_N;        ///< N-side Input 
    en_vc_output_config_t   enVcOutConfig;      ///< Output configuration
    en_vc_irq_sel_t         enVcIrqSel;         ///< Interrupt trigger mode
    func_ptr_t              pfnAnalogCmpCb;     ///< Interrupt callback function
}stc_vc_channel_config_t;

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

//VC init/deinit

en_result_t Vc_ChannelInit(en_vc_channel_t enChannel,
                            stc_vc_channel_config_t *pstcChannelConfig);
en_result_t Vc_ChannelDeInit(en_vc_channel_t enChannel);
en_result_t Vc_DACInit(stc_vc_dac_config_t *pstcDacConfig);
//VC function enable/disable
en_result_t Vc_EnableChannel(en_vc_channel_t enChannel);
en_result_t Vc_DisableChannel(en_vc_channel_t enChannel);

//VC filter enable/disable
en_result_t Vc_EnableFilter(en_vc_channel_t enChannel);
en_result_t Vc_DisableFilter(en_vc_channel_t enChannel);

//get stat
boolean_t Vc_GetStat(en_vc_channel_t enChannel, en_vc_stat_t enStat);
//clear stat
void Vc_ClearIrq(en_vc_channel_t enChannel);

//irq enable/disable
en_result_t Vc_EnableIrq(en_vc_channel_t enChannel);
en_result_t Vc_DisableIrq(en_vc_channel_t enChannel);
en_result_t Vc_ConfigIrq(en_vc_channel_t enChannel, en_vc_irq_sel_t enSel);
//@} // VcGroup

#ifdef __cplusplus
}
#endif

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


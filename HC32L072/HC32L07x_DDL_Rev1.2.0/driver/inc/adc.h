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
 * @file   adc.h
 *
 * @brief  Header file for ADC functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/
 
//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN模式使用ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN模式使用ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN模式使用ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN模式使用ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN模式使用ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN模式使用ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN模式使用ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN模式使用ADC CH7 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

 /**
 ******************************************************************************
 ** \brief ADC conversion mode
 *****************************************************************************/
typedef enum en_adc_mode
{
    AdcSglMode  = 0u,           /*!< Single-input channel single conversion mode */
    AdcScanMode = 1u,           /*!< Multiple input channels sequential/queue scan conversion mode */  
}en_adc_mode_t;

/**
 ******************************************************************************
 ** \brief ADC clock divider selection
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcMskClkDiv1  = 0u<<2,        /*!< PCLK */
    AdcMskClkDiv2  = 1u<<2,        /*!< 1/2 PCLK */
    AdcMskClkDiv4  = 2u<<2,        /*!< 1/4 PCLK */
    AdcMskClkDiv8  = 3u<<2,        /*!< 1/8 PCLK */
} en_adc_clk_div_t;

/**
 ******************************************************************************
 ** \brief ADC reference voltage
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    AdcMskRefVolSelInBgr1p5 = 0u<<9,        /*!<Internal reference voltage 1.5V (SPS <= 200kHz)*/
    AdcMskRefVolSelInBgr2p5 = 1u<<9,        /*!<Internal reference voltage 2.5V (avdd > 3V, SPS <= 200kHz)*/
    AdcMskRefVolSelExtern1  = 2u<<9,        /*!<External input (max avdd) PB01*/
    AdcMskRefVolSelAVDD     = 3u<<9,        /*!<AVDD*/
}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADC conversion channel selection
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{                                  /*!<CHMAP = 0*/ /*!<CHMAP = 1*/
    AdcExInputCH0    =  0u,        /*!<Use PA00*/ /*!<Use PD08*/
    AdcExInputCH1    =  1u,        /*!<Use PA01*/ /*!<Use PD09*/
    AdcExInputCH2    =  2u,        /*!<Use PA02*/ /*!<Use PD10*/
    AdcExInputCH3    =  3u,        /*!<Use PA03*/ /*!<Use PD11*/
    AdcExInputCH4    =  4u,        /*!<Use PA04*/ /*!<Use PA04*/
    AdcExInputCH5    =  5u,        /*!<Use PA05*/ /*!<Use PA05*/
    AdcExInputCH6    =  6u,        /*!<Use PA06*/ /*!<Use PE08*/
    AdcExInputCH7    =  7u,        /*!<Use PA07*/ /*!<Use PE09*/
    AdcExInputCH8    =  8u,        /*!<Use PB00*/ /*!<Use PE10*/
    AdcExInputCH9    =  9u,        /*!<Use PB01*/ /*!<Use PB01*/
    AdcExInputCH10   =  10u,       /*!<Use PC00*/ /*!<Use PE11*/
    AdcExInputCH11   =  11u,       /*!<Use PC01*/ /*!<Use PE12*/
    AdcExInputCH12   =  12u,       /*!<Use PC02*/ /*!<Use PE13*/
    AdcExInputCH13   =  13u,       /*!<Use PC03*/ /*!<Use PE14*/
    AdcExInputCH14   =  14u,       /*!<Use PC04*/ /*!<Use PC04*/
    AdcExInputCH15   =  15u,       /*!<Use PC05*/ /*!<Use PC05*/
    AdcExInputCH16   =  16u,       /*!<Use PB02*/ /*!<Use PB02*/
    AdcExInputCH17   =  17u,       /*!<Use PB10*/ /*!<Use PB10*/
    AdcExInputCH18   =  18u,       /*!<Use PB11*/ /*!<Use PB11*/
    AdcExInputCH19   =  19u,       /*!<Use PB12*/ /*!<Use PB12*/
    AdcExInputCH20   =  20u,       /*!<Use PB13*/ /*!<Use PB13*/
    AdcExInputCH21   =  21u,       /*!<Use PB14*/ /*!<Use PB14*/
    AdcExInputCH22   =  22u,       /*!<Use PB15*/ /*!<Use PB15*/
    AdcExInputCH23   =  23u,       /*!<Use PE15*/ /*!<Use PE15*/
    AdcExInputCH24   =  24u,       /*!<Use PC07*/ /*!<Use PC07*/

    AdcDac0Input     =  25u,       /*!<Use DAC1 output (must use input gain)*/
    AdcDac1Input     =  26u,       /*!<Use DAC1 output (must use input gain)*/                   
    AdcAVccdiv3Input =  27u,       /*!<Use 1/3 AVCC (must use input gain)*/
    AdcAiTsInput     =  28u,       /*!<Use the built-in temperature sensor BGR_TS (must use input gain)*/
    AdcVref1_2Input  =  29u,       /*!<Use the internal 1.2V reference (must use input gain)*/

}en_adc_samp_ch_sel_t;

 /**
 ******************************************************************************
 ** \brief ADC Input Signal Amplifier Control
 *****************************************************************************/
typedef enum en_adc_op_buf
{
    AdcMskBufEnable  = 1u<<11,          /*!< Enable amplifier BUF */
    AdcMskBufDisable = 0u,              /*!< Disable amplifier BUF */ 
} en_adc_op_buf_t;

/**
 ******************************************************************************
 ** \brief ADC Sampling Cycle Selection
 *****************************************************************************/
typedef enum en_adc_samp_cycle_sel
{
    AdcMskSampCycle4Clk  =  0u<<12,        /*!< 4 sampling clocks */
    AdcMskSampCycle6Clk  =  1u<<12,        /*!<6 sampling clocks*/
    AdcMskSampCycle8Clk  =  2u<<12,        /*!<8 sampling clocks*/
    AdcMskSampCycle12Clk =  3u<<12,        /*!<12 sampling clocks*/

}en_adc_samp_cycle_sel_t;

 /**
 ******************************************************************************
 ** \brief ADC internal reference voltage enable control
 *****************************************************************************/
typedef enum en_adc_in_ref
{
    AdcMskInRefEnable  = 1u<<14,          /*!< Internal reference voltage enabled */
    AdcMskInRefDisable = 0u,              /*!< Internal reference voltage disabled */
}en_adc_in_ref_t; 
}en_adc_in_ref_t;

/**
 ******************************************************************************
 ** \brief ADC peripheral module reflection source selection
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcMskTrigTimer0 = 1u<<0, /*!<Select timer0 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigTimer1 = 1u<<1, /*!<Select timer1 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigTimer2 = 1u<<2, /*!<Select timer2 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigTimer3 = 1u<<3, /*!<Select timer3 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigTimer4 = 1u<<4, /*!<Select Timer4 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigTimer5 = 1u<<5, /*!<Select Timer5 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigTimer6 = 1u<<6, /*!<Select Timer6 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigUart0 = 1u<<7, /*!<Select Uart0 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigUart1 = 1u<<8, /*!<Select Uart1 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigLpuart0 = 1u<<9, /*!<Select Lpuart0 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigLpuart1 = 1u<<10, /*!<Select Lpuart1 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigVC0 = 1u<<11, /*!<Select VC0 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigVC1 = 1u<<12, /*!<Select VC1 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigRTC = 1u<<13, /*!<Select RTC interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPCA = 1u<<14, /*!<Select PCA interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigSPI0 = 1u<<15, /*!<Select SPI0 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigSPI1 = 1u<<16, /*!<Select SPI1 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigDMA = 1u<<17, /*!<Select DMA interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPA03 = 1u<<18, /*!<Select PA03 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPB03 = 1u<<19, /*!<Select PB03 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPC03 = 1u<<20, /*!<Select PC03 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPD03 = 1u<<21, /*!<Select PD03 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPA07 = 1u<<22, /*!<Select PA07 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPB07 = 1u<<23, /*!<Select PB07 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPC07 = 1u<<24, /*!<Select PC07 interrupt source, automatically trigger ADC sampling*/
    AdcMskTrigPD07 = 1u<<25, /*!<Select the PD07 interrupt source and automatically trigger ADC sampling*/
    AdcMskTrigPA11 = 1u<<26, /*!<Select the PA11 interrupt source and automatically trigger ADC sampling*/
    AdcMskTrigPB11 = 1u<<27, /*!<Select the PB11 interrupt source and automatically trigger ADC sampling*/
    AdcMskTrigPC11 = 1u<<28, /*!<Select the PC11 interrupt source and automatically trigger ADC sampling*/
    AdcMskTrigPA15 = 1u<<29, /*!<Select the PA15 interrupt source and automatically trigger ADC sampling*/
    AdcMskTrigPB15 = 1u<<30, /*!<Select the PB15 interrupt source and automatically trigger ADC sampling*/
    AdcMskTrigPC15 = 1u<<31, /*!<Select PC15 interrupt source to automatically trigger ADC sampling*/
}en_adc_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC external trigger source register selection
 *****************************************************************************/
typedef enum en_adc_ext_trig_sel
{
    AdcExtTrig0     =  0u,         /*!<Single and sequential scan conversion external trigger source selection register*/
    AdcExtTrig1     =  1u,         /*!<Queued scan conversion external trigger source selection register*/
}en_adc_ext_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC Sequential Conversion Channel
 *****************************************************************************/
typedef enum en_adc_sqr_chmux
{
    AdcSQRCH0MUX = 0u, /*!< Sequential scan mode conversion channel 0*/
    AdcSQRCH1MUX = 1u, /*!< Sequential scan mode conversion channel 1*/
    AdcSQRCH2MUX = 2u, /*!< Sequential scan mode conversion channel 2*/
    AdcSQRCH3MUX = 3u, /*!< Sequential scan mode conversion channel 3*/
    AdcSQRCH4MUX = 4u, /*!< Sequential scan mode conversion channel 4*/
    AdcSQRCH5MUX = 5u, /*!< Sequential scan mode conversion channel 5*/
    AdcSQRCH6MUX = 6u, /*!< Sequential scan mode conversion channel 6*/
    AdcSQRCH7MUX = 7u, /*!< Sequential scan mode conversion channel 7*/
    AdcSQRCH8MUX = 8u, /*!< Sequential scan mode conversion channel 8*/
    AdcSQRCH9MUX = 9u, /*!< Sequential scan mode conversion channel 9*/
    AdcSQRCH10MUX = 10u, /*!< Sequential scan mode conversion channel 10*/
    AdcSQRCH11MUX = 11u, /*!< Sequential scan mode conversion channel 11*/
    AdcSQRCH12MUX = 12u, /*!< Sequential scan mode conversion channel 12*/
    AdcSQRCH13MUX = 13u, /*!< Sequential scan mode conversion channel 13*/
    AdcSQRCH14MUX = 14u, /*!< Sequential scan mode conversion channel 14*/
    AdcSQRCH15MUX = 15u, /*!<Convert channel 15 in sequential scan mode*/
}en_adc_sqr_chmux_t;

/**
 ******************************************************************************
 ** \brief ADC queued conversion channel
 *****************************************************************************/
typedef enum en_adc_jqr_chmux
{
    AdcJQRCH0MUX = 0u, /*!<Convert channel 0*/
    AdcJQRCH1MUX = 1u, /*!<Convert channel 1*/
    AdcJQRCH2MUX = 2u, /*!<Convert channel 2*/
    AdcJQRCH3MUX = 3u, /*!<Convert channel 3*/
}en_adc_jqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC result alignment
 *****************************************************************************/
typedef enum en_adc_align
{
     AdcAlignRight  = 0u,
     AdcAlignLeft   = 1u,
}en_adc_align_t;

/**
 ******************************************************************************
 ** \brief ADC conversion result automatic accumulation function
 *****************************************************************************/
typedef enum en_adc_result_acc
{
     AdcResultAccEnable  = 1u,
     AdcResultAccDisable = 0u,
}en_adc_result_acc_t;

/**
 ******************************************************************************
 ** \brief ADC Interrupt Type Definition
 *****************************************************************************/
typedef enum en_adc_irq_type
{
    AdcMskIrqJqr = 1u<<5, /*!<ADC queued scan conversion completed*/
    AdcMskIrqSqr = 1u<<4, /*!<ADC sequential scan conversion completed*/
    AdcMskIrqReg = 1u<<3, /*!<ADC conversion result within comparison range*/
    AdcMskIrqHt = 1u<<2, /*!<ADC conversion result above HT*/
    AdcMskIrqLt = 1u<<1, /*!<ADC conversion result below LT*/
    AdcMskIrqSgl = 1u<<0, /*!<ADC single conversion completed*/

}en_adc_irq_type_t;

/**
 ******************************************************************************
 ** \brief OPA to ADC input mapping
 *****************************************************************************/
typedef enum en_adc_channel_remap_type
{
    AdcMskMuxMap = 0u, /*!<ADC port channel selected using SGLMUX*/
    AdcMskOpaMap = 1u, /*!<ADC partial channel mapped to OPA output*/
}en_adc_channel_remap_type_t;

/******************************************************************************
 ** Extern type definitions ('typedef')
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC initialization configuration structure
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    en_adc_mode_t enAdcMode; /*! ADC conversion mode*/
    en_adc_clk_div_t enAdcClkDiv; /*! ADC clock selection*/
    en_adc_samp_cycle_sel_t enAdcSampCycleSel; /*! ADC sampling cycle selection*/
    en_adc_ref_vol_sel_t enAdcRefVolSel; /*! ADC reference voltage selection*/
    en_adc_op_buf_t enAdcOpBuf; /*! ADC input signal amplifier control enable*/
    en_adc_in_ref_t enInRef; /*! ADC internal reference voltage enable*/
    en_adc_align_t enAdcAlign; /*! ADC conversion result alignment control*/
}stc_adc_cfg_t;


/**
 ******************************************************************************
 ** \brief  ADC sequential scan mode configuration structure
 *****************************************************************************/
typedef struct stc_adc_sqr_cfg
{
    uint8_t                 u8SqrCnt;                   /*! ADC sequential scan conversion count*/
    en_adc_result_acc_t     enResultAcc;                /*! ADC conversion result automatic accumulation function*/
    boolean_t               bSqrDmaTrig;                /*! ADC sequential scan conversion completion DMA trigger enable*/
}stc_adc_sqr_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC queue-jumping scan mode configuration structure
 *****************************************************************************/
typedef struct stc_adc_jqr_cfg
{
    uint8_t                 u8JqrCnt;                   /*! ADC sequential scan conversion count*/
    boolean_t               bJqrDmaTrig;                /*! ADC queued scan conversion completion DMA trigger enable*/   
}stc_adc_jqr_cfg_t;


/**
 ******************************************************************************
 ** \brief  ADC comparison function configuration structure
 *****************************************************************************/
typedef struct stc_adc_threshold_cfg
{
    boolean_t bAdcRegCmp; /*!ADC range enable*/
    boolean_t bAdcHtCmp; /*!ADC upper range out of range enable*/
    boolean_t bAdcLtCmp; /*!ADC lower range out of range enable*/
    uint32_t u32AdcHighThd; /*!ADC comparison upper threshold*/
    uint32_t u32AdcLowThd; /*!ADC comparison lower threshold*/
    en_adc_samp_ch_sel_t enSampChSel; /*!ADC sampling channel selection*/
}stc_adc_threshold_cfg_t;


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC initialization
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg);

//ADC interrupt enable
void Adc_EnableIrq(void);
//ADC interrupt disable
void Adc_DisableIrq(void);

//ADC interrupt/sampling completion status acquisition
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq);
//ADC interrupt/sampling completion status clear
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq);

//ADC enable
void Adc_Enable(void);
//ADC disable
void Adc_Disable(void);

//ADC sequential scan mode configuration
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg);
//ADC queue-jump scan mode configuration
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg);

//ADC Sgl single-shot conversion mode channel selection configuration
en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC SQR sequential scan conversion mode channel selection configuration
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC JQR queue scan conversion mode channel selection configuration
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);

///<ADC single conversion external trigger source configuration
void Adc_SglExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);
///<ADC sequential scan conversion external trigger source configuration
void Adc_SqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);
///ADC queue-interrupted scan conversion external trigger source configuration
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);

//ADC threshold comparison function configuration
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg);

//ADC single conversion mode start
void Adc_SGL_Start(void);
//ADC single conversion mode stop
void Adc_SGL_Stop(void);

//ADC single conversion mode always conversion mode start
void Adc_SGL_Always_Start(void);
//ADC Single-shot conversion mode, always-on conversion mode, stop
void Adc_SGL_Always_Stop(void);

//ADC sequential scan conversion mode starts
void Adc_SQR_Start(void);
//ADC sequential scan conversion mode stops
void Adc_SQR_Stop(void);

//ADC jump-in scan conversion mode starts
void Adc_JQR_Start(void);
//ADC jump-in scan conversion mode stops
void Adc_JQR_Stop(void);

//Get single-shot conversion sample value
uint32_t Adc_GetSglResult(void);
//Get sequential scan sample value
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux);
//Get jump-in scan sample value
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux);

//Get the accumulated sample value
uint32_t Adc_GetAccResult(void);
//Clear ADC accumulation register result
void Adc_ClrAccResult(void);

///< ADC channel remapping
void Adc_ChannelRemap(en_adc_channel_remap_type_t enChMap);

//@}
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

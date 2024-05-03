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
/** \file adc.h
 **
 ** Header file for AD Converter functions
 ** @link ADC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN mode uses ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN mode uses ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN mode uses ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN mode uses ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN mode uses ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN mode uses ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN mode uses ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN mode uses ADC CH7 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

 /**
 ******************************************************************************
 ** \brief ADC sampling mode
 *****************************************************************************/
typedef enum en_adc_op_mode
{
    AdcSglMode  = 0u,        /*!< Single input channel single sampling mode */
    AdcSCanMode     = 1u,        /*!< Multi-input channel sequential scan sampling mode, multi-input channel cut-in scanning sampling mode*/   
} en_adc_op_mode_t;

/**
 ******************************************************************************
 ** \brief ADC clock selection
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcClkSysTDiv1  = 0u,        /*!< PCLK */
    AdcClkSysTDiv2  = 1u,        /*!< 1/2 PCLK */
    AdcClkSysTDiv4  = 2u,        /*!< 1/4 PCLK */
    AdcClkSysTDiv8  = 3u,        /*!< 1/8 PCLK */

} en_adc_clk_div_t;

/**
 ******************************************************************************
 ** \brief ADC reference voltage
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    RefVolSelInBgr1p5 = 0u,        /*!<Internal reference voltage 1.5V (SPS<=200kHz)*/
    RefVolSelInBgr2p5 = 1u,        /*!<Internal reference voltage 2.5V (avdd>3V, SPS<=200kHz)*/
    RefVolSelExtern1  = 2u,        /*!<External input(max avdd)   PB01*/
    RefVolSelAVDD     = 3u,        /*!<AVDD*/

}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADC sampling channel selection
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{
    AdcExInputCH0    =  0u,        /*!<Use channel 0 - PA00*/
    AdcExInputCH1    =  1u,        /*!<Use channel 1 - PA01*/
    AdcExInputCH2    =  2u,        /*!<Use channel 2 - PA02*/
    AdcExInputCH3    =  3u,        /*!<Use channel 3 - PA02PA03*/
    AdcExInputCH4    =  4u,        /*!<Use channel 4 - PA02PA04*/
    AdcExInputCH5    =  5u,        /*!<Use channel 5 - PA02PA05*/
    AdcExInputCH6    =  6u,        /*!<Use channel 6 - PA02PA06*/
    AdcExInputCH7    =  7u,        /*!<Use channel 7 - PA02入PA07*/
    AdcExInputCH8    =  8u,        /*!<Use channel 8 - PB00*/
    AdcExInputCH9    =  9u,        /*!<Use channel 9 - PB01*/
    AdcExInputCH10   =  10u,       /*!<Use channel 10 - PC00*/
    AdcExInputCH11   =  11u,       /*!<Use channel 11 - PC01*/
    AdcExInputCH12   =  12u,       /*!<Use channel 12 - PC02*/
    AdcExInputCH13   =  13u,       /*!<Use channel 13 - PC03*/
    AdcExInputCH14   =  14u,       /*!<Use channel 14 - PC04*/
    AdcExInputCH15   =  15u,       /*!<Use channel 15 - PC05*/
    AdcExInputCH16   =  16u,       /*!<Use channel 16 - PB02*/
    AdcExInputCH17   =  17u,       /*!<Use channel 17 - PB10*/
    AdcExInputCH18   =  18u,       /*!<Use channel 18 - PB11*/
    AdcExInputCH19   =  19u,       /*!<Use channel 19 - PB12*/
    AdcExInputCH20   =  20u,       /*!<Use channel 20 - 入PB13*/
    AdcExInputCH21   =  21u,       /*!<Use channel 21 - 入PB14*/
    AdcExInputCH22   =  22u,       /*!<Use channel 22 - PB15*/
    AdcExInputCH23   =  23u,       /*!<Use channel 23 - PC06*/  
    AdcOPA0Input     =  24u,       /*!<Use channel 24 - OPA0*/
    AdcOPA1Input     =  25u,       /*!<Use channel 25 - OPA1*/
    AdcOPA2Input     =  26u,       /*!<Use channel 26 - OPA2*/                     
    AdcAVccDiV3Input =  27u,       /*!<Use 1/3 AVCC (input gain must be used)*/
    AdcAiTsInput     =  28u,       /*!<Use BGR_TS (input gain must be used)*/
    AdcVref1P2Input  =  29u,       /*!<Use Vref1P2 (input gain must be used)*/

}en_adc_samp_ch_sel_t;

/**
 ******************************************************************************
 ** \brief ADC sampling period selection
 *****************************************************************************/
typedef enum en_adc_samp_time_sel
{
    AdcSampTime4Clk  =  0u,        /*!<4 sample clocks*/
    AdcSampTime6Clk  =  1u,        /*!<6 sample clocks*/
    AdcSampTime8Clk  =  2u,        /*!<8 sample clocks*/
    AdcSampTime12Clk =  3u,        /*!<12 sample clocks*/

}en_adc_samp_time_sel_t;

/**
 ******************************************************************************
 ** \brief ADC peripheral module trigger source selection
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcTrigTimer0     =  0u,         /*!<Select timer0 interrupt*/
    AdcTrigTimer1     =  1u,         /*!<Select timer1 interrupt*/
    AdcTrigTimer2     =  2u,         /*!<Select timer2 interrupt*/
    AdcTrigTimer3     =  3u,         /*!<Select timer3 interrupt*/
    AdcTrigTimer4     =  4u,         /*!<Select timer4 interrupt*/
    AdcTrigTimer5     =  5u,         /*!<Select timer5 interrupt*/
    AdcTrigTimer6     =  6u,         /*!<Select timer6 interrupt*/
    AdcTrigUart0      =  7u,         /*!<Select uart0 interrupt*/
    AdcTrigUart1      =  8u,         /*!<Select uart1 interrupt*/
    AdcTrigLpuart0    =  9u,         /*!<Select lpuart0 interrupt*/
    AdcTrigLpuart1    =  10u,        /*!<Select lpuart1 interrupt*/
    AdcTrigVC0        =  11u,        /*!<VC0*/
    AdcTrigVC1        =  12u,        /*!<VC1*/
    AdcTrigRTC        =  13u,        /*!<RTC*/
    AdcTrigPCA        =  14u,        /*!<PCA*/
    AdcTrigSPI0       =  15u,        /*!<SPI0*/
    AdcTrigSPI1       =  16u,        /*!<SPI1*/
    AdcTrigDMA        =  17u,        /*!<DMA*/
    AdcTrigPA03       =  18u,        /*!<PA03*/
    AdcTrigPB03       =  19u,        /*!<PB03*/
    AdcTrigPC03       =  20u,        /*!<PC03 */
    AdcTrigPD03       =  21u,        /*!<PD03 */
    AdcTrigPA07       =  22u,        /*!<PA07 */
    AdcTrigPB07       =  23u,        /*!<PB07 */
    AdcTrigPC07       =  24u,        /*!<PC07 */
    AdcTrigPD07       =  25u,        /*!<PD07 */
    AdcTrigPA11       =  26u,        /*!<PA11 */
    AdcTrigPB11       =  27u,        /*!<PB11 */
    AdcTrigPC11       =  28u,        /*!<PC11 */
    AdcTrigPA15       =  29u,        /*!<A15 */
    AdcTrigPB15       =  30u,        /*!<PB15 */
    AdcTrigPC15       =  31u,        /*!<PC15 */
}en_adc_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC external trigger source  selection register
 *****************************************************************************/
typedef enum en_adc_ext_trig_sel
{
    AdcExtTrig0     =  0u,         /*!<Single and sequential scan conversion external trigger source select register*/
    AdcExtTrig1     =  1u,         /*!<Cut-in scan conversion external trigger source select register*/
}en_adc_ext_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC order Conversion channel
 *****************************************************************************/
typedef enum en_adc_sqr_chmux
{
    CH0MUX     =  0u,         /*!<Conversion channel 0*/
    CH1MUX     =  1u,         /*!< Conversion channel1*/
    CH2MUX     =  2u,         /*!< Conversion channel2*/
    CH3MUX     =  3u,         /*!< Conversion channel3*/
    CH4MUX     =  4u,         /*!< Conversion channel4*/
    CH5MUX     =  5u,         /*!< Conversion channel5*/
    CH6MUX     =  6u,         /*!< Conversion channel6*/
    CH7MUX     =  7u,         /*!< Conversion channel7*/
    CH8MUX     =  8u,         /*!< Conversion channel8*/
    CH9MUX     =  9u,         /*!< Conversion channel9*/
    CH10MUX    =  10u,        /*!< Conversion channel10*/
    CH11MUX    =  11u,        /*!< Conversion channel11*/
    CH12MUX    =  12u,        /*!< Conversion channel12*/
    CH13MUX    =  13u,        /*!< Conversion channel13*/
    CH14MUX    =  14u,        /*!< Conversion channel14*/
    CH15MUX    =  15u,        /*!< Conversion channel15*/
}en_adc_sqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC MUX Conversion channel
 *****************************************************************************/
typedef enum en_adc_jqr_chmux
{
    JQRCH0MUX     =  0u,         /*!< Conversion channel0*/
    JQRCH1MUX     =  1u,         /*!< Conversion channel1*/
    JQRCH2MUX     =  2u,         /*!< Conversion channel2*/
    JQRCH3MUX     =  3u,         /*!< Conversion channel3*/
}en_adc_jqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC result alignment
 *****************************************************************************/
typedef enum en_adc_align
{
     AlignRight  = 0u,
     AlignLeft = 1u,    
}en_adc_align_t;
/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC configuration
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    /*! ADC mode of operation*/
    en_adc_op_mode_t enAdcOpMode;

    /*! ADC clock divider selection*/
    en_adc_clk_div_t  enAdcClkDiv;

    /*! ADC sampling time*/
    en_adc_samp_time_sel_t  enAdcSampTimeSel;

    /*! ADC reference voltage*/
    en_adc_ref_vol_sel_t    enAdcRefVolSel;

    /*! ADC input gain enable*/
    boolean_t    bAdcInBufEn;
}stc_adc_cfg_t;

 /**
 ******************************************************************************
 ** \brief  ADC DMA trigger source register configuration
 *****************************************************************************/
typedef enum en_adc_dmatrig
{
   /*!Cut-in scan triggers DMA read control*/ 
  DmaJqr = 0, 
   /*!Sequential scan triggers DMA read control*/   
  DmaSqr = 1   
}en_adc_dmatrig_t;
 /**
 ******************************************************************************
 ** \brief  ADC external trigger source register configuration
 *****************************************************************************/
typedef struct stc_adc_ext_trig_cfg
{
    /*! External trigger source register selection*/
    en_adc_ext_trig_sel_t   enAdcExtTrigRegSel;
    
    /*! ADC single and sequential conversion trigger selection*/
    en_adc_trig_sel_t       enAdcTrig0Sel;

    /*! ADC cut-in conversion trigger selection*/
    en_adc_trig_sel_t       enAdcTrig1Sel;

}stc_adc_ext_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC interrupt configuration
 *****************************************************************************/
typedef struct stc_adc_irq
{
    /*!<ADC cut-in scan completion interrupt*/
    boolean_t  bAdcJQRIrq;   
    /*!<ADC sequential scan completion interrupt*/
    boolean_t  bAdcSQRIrq;  
    /*! ADC interval interrupt*/
    boolean_t  bAdcRegCmp;
    /*! Out of range interrupt on ADC*/
    boolean_t  bAdcHhtCmp;
    /*! Out of range interrupt under ADC*/
    boolean_t  bAdcLltCmp;    
    /*!<ADC single conversion complete interrupt*/
    boolean_t  bAdcIrq;
}stc_adc_irq_t;

typedef struct stc_adc_threshold_cfg
{
   
    boolean_t bAdcRegCmp ;      /*!ADC interval enable*/ 

    boolean_t bAdcHhtCmp ;     /*!Out of range enable on ADC*/ 

    boolean_t bAdcLltCmp ;     /*!ADC out of range enable*/
    
    uint32_t u32AdcRegHighThd; /*!Out of range over ADC*/
    
    uint32_t u32AdcRegLowThd; /*!Out of range under ADC*/ 
    
    en_adc_samp_ch_sel_t enThCh; /*!Threshold comparison channel selection*/
    
}stc_adc_threshold_cfg_t;
/**
 ******************************************************************************
 ** \brief  ADC interrupt callback function
 *****************************************************************************/
typedef struct stc_adc_irq_calbakfn_pt
{
    /*! ADC cut-in scan interrupt callback function pointer*/
    func_ptr_t  pfnAdcJQRIrq;
    /*! ADC sequential scan interrupt callback function pointer*/
    func_ptr_t  pfnAdcSQRIrq;    
    /*! ADC interval interrupt callback function pointer*/
    func_ptr_t  pfnAdcRegIrq;
    /*! Pointer to Interval Interrupt Callback Function on ADC*/
    func_ptr_t  pfnAdcHhtIrq;
    /*! Out of range interrupt callback function pointer under ADC*/
    func_ptr_t  pfnAdcLltIrq;
    /*! ADC single conversion interrupt callback function pointer*/
    func_ptr_t  pfnAdcIrq; 
}stc_adc_irq_calbakfn_pt_t;

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC initialization
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig);
//ADC ExtTrig Register config
en_result_t Adc_ExtTrigCfg(stc_adc_ext_trig_cfg_t* pstcExtTrigConfig);
//ADC de-init
void Adc_DeInit(void);

//ADC conversion start
void Adc_SGL_Start(void);
//ADC conversion stop
void Adc_SGL_Stop(void);

//ADC SQR conversion start
void Adc_SQR_Start(void);
//ADC SQR conversion stop
void Adc_SQR_Stop(void);

//ADC JQR conversion start
void Adc_JQR_Start(void);
//ADC JQR conversion stop
void Adc_JQR_Stop(void);

//ADC conversion enable
void Adc_Enable(void);
//ADC conversion disable
void Adc_Disable(void);

//ADC single covert mode configuration
en_result_t Adc_ConfigSglMode(stc_adc_cfg_t* pstcAdcConfig);
//ADC SQR mode configuration
en_result_t Adc_ConfigSqrMode(stc_adc_cfg_t* pstcAdcConfig, uint8_t u8AdcSampCnt,boolean_t  bAdcResultAccEn);
//ADC JQR mode configuration
en_result_t Adc_ConfigJqrMode(stc_adc_cfg_t* pstcAdcConfig, uint8_t u8AdcSampCnt,boolean_t  bAdcResultAccEn);

//ADC single covert mode channel configuraion 
en_result_t Adc_ConfigSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC SQR mode channel configuraion 
en_result_t Adc_ConfigSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC JQR mode channel configuraion 
en_result_t Adc_ConfigJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC DMA Trigger 
en_result_t Adc_ConfigDmaTrig(en_adc_dmatrig_t enAdcDmaTrig);
//ADC IRQ configuration
void Adc_ConfigIrq(stc_adc_irq_t* pstcAdcIrqCfg,
                   stc_adc_irq_calbakfn_pt_t* pstcAdcIrqCalbaks);
//ADC enable IRQ
void Adc_EnableIrq(void);
//ADC disable IRQ
void Adc_DisableIrq(void);
//ADC enable threshold compare
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* stcAdcThrCfg);
//ADC get IRQ state
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState);
//ADC clear IRQ states
void Adc_ClrSglIrqState(void);
void Adc_ClrJqrIrqState(void);
void Adc_ClrSqrIrqState(void);
void Adc_ClrRegIrqState(void);
void Adc_ClrHtIrqState(void);
void Adc_ClrLtIrqState(void);

//Query ADC single conversion status
boolean_t Adc_PollSglBusyState(void);
//Query ADC sequential scan conversion conversion status
boolean_t Adc_PollSqrBusyState(void);
//Query ADC cut scan conversion status
boolean_t Adc_PollJqrBusyState(void);
//Query ADC result comparison interval status
boolean_t Adc_PollRegBusyState(void);
//Query ADC results to compare upper threshold status
boolean_t Adc_PollHTBusyState(void);
//Query ADC results to compare lower threshold status
boolean_t Adc_PollLtBusyState(void);
//Get a single conversion sample value
en_result_t Adc_GetSglResult(uint16_t* pu16AdcResult);
//Get sequential scan sample values
en_result_t Adc_GetSqrResult(uint16_t* pu16AdcResult,uint8_t SQRChannelIndex);
//Get the cut scan sample value
en_result_t Adc_GetJqrResult(uint16_t* pu16AdcResult,uint8_t JQRChannelIndex);
//Get accumulated sample values
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult);
//clear ADC accumulated result
void Adc_ClrAccResult(void);
//Set reference voltage
en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel);
//Set the result alignment
en_result_t Adc_SetAlign(en_adc_align_t enAlign);
//@}
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

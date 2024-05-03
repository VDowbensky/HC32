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
/** \file adc.c
 **
 ** ADC driver API.
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "adc.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_adc_irq_calbakfn_pt_t stcAdcIrqCalbaks = {NULL, NULL, NULL, NULL,NULL,NULL};

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
 * \brief   
 *          ADC interrupt service routine
 *
 * \param   [in]  u8Param  Unused
 *
 * \retval  none
 */

void Adc_IRQHandler(uint8_t u8Param)
{
    if (TRUE == M0P_ADC->IFR_f.REGIF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcRegIrq)
        {
            stcAdcIrqCalbaks.pfnAdcRegIrq();
        }
        M0P_ADC->ICR_f.REGIC = 0u;
    }

    if (TRUE == M0P_ADC->IFR_f.HTIF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcHhtIrq)
        {
            stcAdcIrqCalbaks.pfnAdcHhtIrq();
        }
        M0P_ADC->ICR_f.HTIC = 0u;
    }

    if (TRUE == M0P_ADC->IFR_f.LTIF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcLltIrq)
        {
            stcAdcIrqCalbaks.pfnAdcLltIrq();
        }
        M0P_ADC->ICR_f.LTIC = 0u;
    }

    if (TRUE == M0P_ADC->IFR_f.SGLIF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcIrq)
        {
            stcAdcIrqCalbaks.pfnAdcIrq();
        }
        M0P_ADC->ICR_f.SGLIC = 0u;
    }
    if(TRUE == M0P_ADC->IFR_f.SQRIF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcSQRIrq)
        {
            stcAdcIrqCalbaks.pfnAdcSQRIrq();
        }
        M0P_ADC->ICR_f.SQRIC = 0u;
    }			
    if(TRUE == M0P_ADC->IFR_f.JQRIF)
    {
        if (NULL != stcAdcIrqCalbaks.pfnAdcJQRIrq)
        {
            stcAdcIrqCalbaks.pfnAdcJQRIrq();
        }
        M0P_ADC->ICR_f.JQRIC = 0u;
    }			
}

/**
 * \brief   
 *          Configuring the ADC interrupt function entry
 *
 * \param   [in]  pstcAdcIrqCfg  ADC interrupt configuration pointer
 * \param   [in]  pstcAdcIrqCalbaks  ADC interrupt callback function pointer
 *
 * \retval  none
 */
void Adc_ConfigIrq(stc_adc_irq_t* pstcAdcIrqCfg,
                   stc_adc_irq_calbakfn_pt_t* pstcAdcIrqCalbaks)
{
    if (TRUE == pstcAdcIrqCfg->bAdcIrq)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcIrq)
        {
            stcAdcIrqCalbaks.pfnAdcIrq = pstcAdcIrqCalbaks->pfnAdcIrq;
        }
    }
    if (TRUE == pstcAdcIrqCfg->bAdcJQRIrq)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcJQRIrq)
        {
            stcAdcIrqCalbaks.pfnAdcJQRIrq = pstcAdcIrqCalbaks->pfnAdcJQRIrq;
        }
    }
    if (TRUE == pstcAdcIrqCfg->bAdcSQRIrq)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcSQRIrq)
        {
            stcAdcIrqCalbaks.pfnAdcSQRIrq = pstcAdcIrqCalbaks->pfnAdcSQRIrq;
        }
    }    
    if (TRUE == pstcAdcIrqCfg->bAdcRegCmp)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcRegIrq)
        {
            stcAdcIrqCalbaks.pfnAdcRegIrq = pstcAdcIrqCalbaks->pfnAdcRegIrq;
        }
    }

    if (TRUE == pstcAdcIrqCfg->bAdcHhtCmp)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcHhtIrq)
        {
            stcAdcIrqCalbaks.pfnAdcHhtIrq = pstcAdcIrqCalbaks->pfnAdcHhtIrq;
        }
    }

    if (TRUE == pstcAdcIrqCfg->bAdcLltCmp)
    {
        if (NULL != pstcAdcIrqCalbaks->pfnAdcLltIrq)
        {
            stcAdcIrqCalbaks.pfnAdcLltIrq = pstcAdcIrqCalbaks->pfnAdcLltIrq;
        }
    }
    
}

/**
 * \brief   
 *          Get ADC interrupt status
 *
 * \param   [in]  pstcAdcIrqState  ADC interrupt status pointer
 *
 * \retval  none
 */
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState)
{
    pstcAdcIrqState->bAdcIrq = M0P_ADC->IFR_f.SGLIF;
    pstcAdcIrqState->bAdcRegCmp = M0P_ADC->IFR_f.REGIF;
    pstcAdcIrqState->bAdcHhtCmp = M0P_ADC->IFR_f.HTIF;
    pstcAdcIrqState->bAdcLltCmp = M0P_ADC->IFR_f.LTIF;
    pstcAdcIrqState->bAdcJQRIrq = M0P_ADC->IFR_f.JQRIF;
    pstcAdcIrqState->bAdcSQRIrq = M0P_ADC->IFR_f.SQRIF;
}
/**
 * \brief   
 *          Clear ADC SGL interrupt status
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrSglIrqState(void)
{
    M0P_ADC->ICR_f.SGLIC = 0;
}
/**
 * \brief   
 *          Clear ADC JQR interrupt status
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrJqrIrqState(void)
{
    M0P_ADC->ICR_f.JQRIC = 0;
}
/**
 * \brief   
 *          Clear ADC SQR interrupt status
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrSqrIrqState(void)
{
    M0P_ADC->ICR_f.SQRIC = 0;
}

/**
 * \brief   
 *          Clear ADC REG interrupt status
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrRegIrqState(void)
{
    M0P_ADC->ICR_f.REGIC = 0;
}

/**
 * \brief   
 *          Clear ADC HT interrupt status
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrHtIrqState(void)
{
    M0P_ADC->ICR_f.HTIC = 0;
}

/**
 * \brief   
 *          Clear ADC LT interrupt status
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrLtIrqState(void)
{
    M0P_ADC->ICR_f.LTIC = 0;
}


/**
 * \brief   
 *          ADC interrupt enable
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_EnableIrq(void)
{
    M0P_ADC->CR0_f.IE = 1u;
}

/**
 * \brief   
 *          ADC compare enable(Comparative interrupt)
 *
 * \param   [in]  pstcAdcIrqCfg  ADC comparison configuration
 *
 * \retval  none
 */

void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* stcAdcThrCfg)
{
  
    M0P_ADC->HT_f.HT = stcAdcThrCfg->u32AdcRegHighThd;               //Use comparison
    M0P_ADC->LT_f.LT = stcAdcThrCfg->u32AdcRegLowThd;               //Use comparison
    
    M0P_ADC->CR1_f.THCH = stcAdcThrCfg->enThCh;         //Threshold comparison channel selection
    
        if (TRUE == stcAdcThrCfg->bAdcRegCmp)
    {
        M0P_ADC->CR1_f.REGCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.REGCMP = 0u;
    }

    if (TRUE == stcAdcThrCfg->bAdcHhtCmp)
    {
        M0P_ADC->CR1_f.HTCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.HTCMP = 0u;
    }

    if (TRUE ==  stcAdcThrCfg->bAdcLltCmp)
    {
        M0P_ADC->CR1_f.LTCMP = 1u;
    }
    else
    {
        M0P_ADC->CR1_f.LTCMP = 0u;
    }

}

/**
 * \brief   
 *          ADC interrupt disable
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_DisableIrq(void)
{
    uint32_t u32Cr1;
    
    M0P_ADC->CR0_f.IE = 0u;
    
    u32Cr1 = M0P_ADC->CR1 | (1<<15);    // must write 1 to bit 15 to avoid clear ADC_result_acc
    u32Cr1 &= ~((1u<<12)|(1u<<13)|(1u<<14));
    M0P_ADC->CR1 = u32Cr1;
}

/**
 * \brief   
 *          ADC initialization
 *
 * \param   [in]  pstcAdcConfig  ADC configuration pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig)
{
    if (NULL == pstcAdcConfig)
    {
        return ErrorInvalidParameter;
    }
    M0P_ADC->CR0_f.CLKDIV = pstcAdcConfig->enAdcClkDiv;
    M0P_ADC->CR0_f.SAM = pstcAdcConfig->enAdcSampTimeSel;
    M0P_ADC->CR0_f.REF = pstcAdcConfig->enAdcRefVolSel;
    M0P_ADC->CR0_f.BUF = pstcAdcConfig->bAdcInBufEn;
    M0P_ADC->CR1_f.REGCMP = 0u;
    M0P_ADC->CR1_f.HTCMP = 0u;
    M0P_ADC->CR1_f.LTCMP = 0u;

    return Ok;
}

/**
 * \brief   
 *          ADC external interrupt trigger source configuration
 *
 * \param   [in]  pstcAdcConfig  ADC configuration pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ExtTrigCfg(stc_adc_ext_trig_cfg_t* pstcExtTrigConfig)
{
    if (NULL == pstcExtTrigConfig)
    {
        return ErrorInvalidParameter;
    }
    if(pstcExtTrigConfig->enAdcExtTrigRegSel == AdcExtTrig0)
    {
        M0P_ADC->EXTTRIGGER0  |= 1u << pstcExtTrigConfig->enAdcTrig0Sel;
    }
    else if(pstcExtTrigConfig->enAdcExtTrigRegSel == AdcExtTrig1)
    {
        M0P_ADC->EXTTRIGGER1  |= 1u << pstcExtTrigConfig->enAdcTrig1Sel;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    
    return Ok;
}

/**
 * \brief   
 *          ADC Deinit
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_DeInit(void)
{

    M0P_ADC->CR0_f.EN = 0u;

    M0P_ADC->CR0_f.IE = 0u;
    M0P_ADC->CR1_f.REGCMP = 0u;
    M0P_ADC->CR1_f.HTCMP = 0u;
    M0P_ADC->CR1_f.LTCMP = 0u;

    M0P_ADC->ICR_f.SGLIC = 0u;
    M0P_ADC->ICR_f.LTIC = 0u;
    M0P_ADC->ICR_f.HTIC = 0u; 
    M0P_ADC->ICR_f.REGIC = 0u;   
    M0P_ADC->ICR_f.SQRIC = 0u;  
    M0P_ADC->ICR_f.JQRIC = 0u;   

    M0P_ADC->CR0_f.CLKDIV = 0u;
    M0P_ADC->CR0_f.SAM = 0x2u;
    M0P_ADC->CR0_f.REF = 0x3u;
    M0P_ADC->CR0_f.SGLMUX = 0xFu;
    M0P_ADC->CR0_f.BUF = 0u;
    M0P_ADC->HT_f.HT = 0xFFFu;
    M0P_ADC->LT_f.LT = 0u;
}

/**
 * \brief   
 *          ADC Single conversion start
 *
 * \param   none
 *
 * \retval  none
 */

void Adc_SGL_Start(void)
{
    M0P_ADC->SGLSTART_f.START = 1u;
}

/**
 * \brief   
 *          ADC Single conversion stop
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_SGL_Stop(void)
{
    M0P_ADC->SGLSTART_f.START = 0u;
}
/**
 * \brief   
 *          ADC Sequential conversion start
 *
 * \param   none
 *
 * \retval  none
 */

void Adc_SQR_Start(void)
{
    M0P_ADC->SQRSTART_f.START = 1u;
}

/**
 * \brief   
 *          ADC Sequential conversion stop
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_SQR_Stop(void)
{
    M0P_ADC->SQRSTART_f.START = 0u;
}
/**
 * \brief   
 *          ADC Cut line conversion start
 *
 * \param   none
 *
 * \retval  none
 */

void Adc_JQR_Start(void)
{
    M0P_ADC->JQRSTART_f.START = 1u;
}

/**
 * \brief   
 *          ADC Cut line conversion stop
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_JQR_Stop(void)
{
    M0P_ADC->JQRSTART_f.START = 0u;
}
/**
 * \brief   
 *          ADC enable
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_Enable(void)
{
    M0P_ADC->CR0_f.EN = 1u;
}

/**
 * \brief   
 *          ADC disable
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_Disable(void)
{
    M0P_ADC->CR0_f.EN = 0u;
}

/**
 * \brief   
 *          Configure single conversion mode
 *
 * \param   [in]  pstcAdcConfig   ADC configuration pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigSglMode(stc_adc_cfg_t* pstcAdcConfig)
{
    if (NULL == pstcAdcConfig)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.MODE = pstcAdcConfig->enAdcOpMode;
    
    return Ok;
}

/**
 * \brief   
 *          Configuring sequential scan conversion mode
 *
 * \param   [in]  pstcAdcConfig   ADC configuration pointer
 * \param   [in]  pstcAdcNormCfg  Continuous conversion mode configuration pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigSqrMode(stc_adc_cfg_t* pstcAdcConfig, uint8_t u8AdcSampCnt,boolean_t  bAdcResultAccEn)
{
    if (NULL == pstcAdcConfig)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.MODE = pstcAdcConfig->enAdcOpMode;
    M0P_ADC->CR1_f.RACCCLR = 0;//ADC conversion result accumulation register (ADC_ResultAcc) is cleared
    M0P_ADC->CR1_f.RACCEN = bAdcResultAccEn;
    if (bAdcResultAccEn)
    {
        M0P_ADC->CR1_f.RACCCLR = 1u;
    }
    M0P_ADC->SQR2_f.CNT  = u8AdcSampCnt - 1;

    return Ok;
}

/**
 * \brief   
 *          Configure the cut scan conversion mode
 *
 * \param   [in]  pstcAdcConfig   ADC configuration pointer
 * \param   [in]  pstcAdcNormCfg  Scan conversion mode configuration pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigJqrMode(stc_adc_cfg_t* pstcAdcConfig, uint8_t u8AdcSampCnt,boolean_t  bAdcResultAccEn)
{
    if (NULL == pstcAdcConfig)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.MODE = pstcAdcConfig->enAdcOpMode;
    M0P_ADC->CR1_f.RACCEN = bAdcResultAccEn;
    M0P_ADC->JQR_f.CNT  = u8AdcSampCnt - 1;

    return Ok;
}
/**
 * \brief   
 *          Configuring a single conversion channel
 *
 * \param   [in]enstcAdcSampCh Conversion channel 
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh)
{
	M0P_ADC->CR0_f.SGLMUX = enstcAdcSampCh;	
	return Ok;
}

/**
 * \brief   
 *          Configuration sequence scan Conversion channel
 *
 * \param   [in]enstcAdcSqrChMux Sequential scanning Conversion channel order
 * \param   [in]enstcAdcSampCh   Conversion channel 
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    switch(enstcAdcSqrChMux)
    {
        case CH0MUX:
            M0P_ADC->SQR0_f.CH0MUX = enstcAdcSampCh;
        break;
        case CH1MUX:
            M0P_ADC->SQR0_f.CH1MUX = enstcAdcSampCh;
        break;
        case CH2MUX:
            M0P_ADC->SQR0_f.CH2MUX = enstcAdcSampCh;
        break;
        case CH3MUX:
            M0P_ADC->SQR0_f.CH3MUX = enstcAdcSampCh;
        break;
        case CH4MUX:
            M0P_ADC->SQR0_f.CH4MUX = enstcAdcSampCh;
        break;
        case CH5MUX:
            M0P_ADC->SQR0_f.CH5MUX = enstcAdcSampCh;
        break;
        case CH6MUX:
            M0P_ADC->SQR1_f.CH6MUX = enstcAdcSampCh;
        break;
        case CH7MUX:
            M0P_ADC->SQR1_f.CH7MUX = enstcAdcSampCh;
        break;
        case CH8MUX:
            M0P_ADC->SQR1_f.CH8MUX = enstcAdcSampCh;
        break;
        case CH9MUX:
            M0P_ADC->SQR1_f.CH9MUX = enstcAdcSampCh;
        break;
        case CH10MUX:
            M0P_ADC->SQR1_f.CH10MUX = enstcAdcSampCh;
        break;
        case CH11MUX:
            M0P_ADC->SQR1_f.CH11MUX = enstcAdcSampCh;
        break;
        case CH12MUX:
            M0P_ADC->SQR2_f.CH12MUX = enstcAdcSampCh;
        break;
        case CH13MUX:
            M0P_ADC->SQR2_f.CH13MUX = enstcAdcSampCh;
        break;
        case CH14MUX:
            M0P_ADC->SQR2_f.CH14MUX = enstcAdcSampCh;
        break;
        case CH15MUX:
            M0P_ADC->SQR2_f.CH15MUX = enstcAdcSampCh;			
        break;
        default:
        break;

    }
    return Ok;
}
/**
 * \brief   
 *          Configuring cut-in scanning Conversion channel
 *
 * \param   [in]enstcAdcSqrChMux Cut line scan Conversion channel order
 * \param   [in]enstcAdcSampCh   Conversion channel 
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    switch(enstcAdcJqrChMux)
    {
        case CH0MUX:
            M0P_ADC->JQR_f.CH0MUX = enstcAdcSampCh;
        break;
        case CH1MUX:
            M0P_ADC->JQR_f.CH1MUX = enstcAdcSampCh;
        break;
        case CH2MUX:
            M0P_ADC->JQR_f.CH2MUX = enstcAdcSampCh;
        break;
        case CH3MUX:
            M0P_ADC->JQR_f.CH3MUX = enstcAdcSampCh;
        break;
        default:
        break;
    }
    return Ok;
}
/**
 * \brief   
 *          Configuration trigger DMA read control
 *
 * \param   [in]enAdcDmaTrig Trigger DMA read control
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_ConfigDmaTrig(en_adc_dmatrig_t enAdcDmaTrig)
{
  if(enAdcDmaTrig == DmaJqr)
  {
      M0P_ADC->CR1_f.DMAJQR = 1;
  }else
  {
      M0P_ADC->CR1_f.DMASQR = 1;   
  }
  return Ok;
}

/**
 * \brief   
 *          Query ADC single conversion status
 *
 * \param   none
 *
 * \retval  boolean_t  TRUE:  ADC conversion completed
 * \retval  boolean_t  FALSE: ADC conversion
 */
boolean_t Adc_PollSglBusyState(void)
{
    return M0P_ADC->IFR_f.SGLIF;
}


/**
 * \brief   
 *          Query ADC sequential scan conversion status
 *
 * \retval  boolean_t  TRUE:  ADC conversion completed
 * \retval  boolean_t  FALSE: ADC conversion
 * \param   none
 *
 */
boolean_t Adc_PollSqrBusyState(void)
{
    return M0P_ADC->IFR_f.SQRIF;
}

/**
 * \brief   
 *          Query ADC cut scan conversion status
 *
 * \param   none
 *
 * \retval  boolean_t  TRUE:  ADC conversion completed
 * \retval  boolean_t  FALSE: ADC conversion
 */
boolean_t Adc_PollJqrBusyState(void)
{
    return M0P_ADC->IFR_f.JQRIF;
}

/**
 * \brief   
 *          Get sampled value
 *
 * \param   [out] pu16AdcResult  Sample value pointer
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_GetSglResult(uint16_t* pu16AdcResult)
{
    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

    *pu16AdcResult = M0P_ADC->RESULT_f.RESULT;

    return Ok;
}

/**
 * \brief   
 *          Query ADC result comparison interval status
 *
 * \retval  boolean_t  TRUE:  ADC conversion completed
 * \retval  boolean_t  FALSE: ADC conversion
 * \param   none
 *
 */
boolean_t Adc_PollRegBusyState(void)
{
    return M0P_ADC->IFR_f.REGIF;
}
/**
 * \brief   
 *          Query ADC results to compare upper threshold status
 *
 * \retval  boolean_t  TRUE:  ADC conversion completed
 * \retval  boolean_t  FALSE: ADC conversion
 * \param   none
 *
 */
boolean_t Adc_PollHTBusyState(void)
{
    return M0P_ADC->IFR_f.HTIF;
}
/**
 * \brief   
 *          Query ADC result comparison interval status
 *
 * \retval  boolean_t  TRUE:  ADC conversion completed
 * \retval  boolean_t  FALSE: ADC conversion
 * \param   none
 *
 */
boolean_t Adc_PollLtBusyState(void)
{
    return M0P_ADC->IFR_f.LTIF;
}
/**
 * \brief   
 *          Get sampled value
 *
 * \param   [out] pu16AdcResult  Sample value pointer
 * \param   [in] SQRChannelIndex  Sequential scan channel number
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_GetSqrResult(uint16_t* pu16AdcResult,uint8_t SQRChannelIndex)
{
    volatile uint32_t *BaseSqrResultAddress =(volatile uint32_t *) &(M0P_ADC->SQRRESULT0);

    if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

    if(SQRChannelIndex > 15)
    {
        return ErrorInvalidParameter;
    }
    
    *pu16AdcResult = (uint16_t)(*(BaseSqrResultAddress + SQRChannelIndex));

    return Ok;
}

/**
 * \brief   
 *          Get the cut scan sample value
 *
 * \param   [out] pu16AdcResult  Sample value pointer
 * \param   [in] JQRChannelIndex  Cut-in scan channel number
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_GetJqrResult(uint16_t* pu16AdcResult,uint8_t JQRChannelIndex)
{
	  volatile uint32_t *BaseJqrResultAddress =(volatile uint32_t *) &(M0P_ADC->JQRRESULT0);
	  if (NULL == pu16AdcResult)
    {
        return ErrorInvalidParameter;
    }

	  if(JQRChannelIndex > 3)
	  {
	  	return ErrorInvalidParameter;
	  }
	  *pu16AdcResult = (uint16_t)(*(BaseJqrResultAddress + JQRChannelIndex));
	  return Ok;
}
/**
 * \brief   
 *          Get accumulated sample values
 *
 * \param   [out] pu32AdcAccResult  Cumulative sample value pointer
 *
 * \retval  en_result_t  Ok:  success
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult)
{
    if (NULL == pu32AdcAccResult)
    {
        return ErrorInvalidParameter;
    }

    *pu32AdcAccResult = M0P_ADC->RESULTACC_f.RESULTACC;

    return Ok;
}

/**
 * \brief   
 *          Clear accumulated sampled value
 *
 * \param   none
 *
 * \retval  none
 */
void Adc_ClrAccResult(void)
{
    M0P_ADC->CR1_f.RACCCLR = 0u;
}


/**
 * \brief   
 *          Set the ADC reference voltage
 *
 * \param   [in]  enAdcRefVolSel  ADC reference voltage
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel)
{
    if (enAdcRefVolSel > RefVolSelAVDD)
    {
        return ErrorInvalidParameter;
    }
    if((RefVolSelInBgr1p5 == enAdcRefVolSel) || (RefVolSelInBgr2p5 == enAdcRefVolSel))
    {
        M0P_ADC->CR0_f.INREFEN = 1;
    }else
    {
        M0P_ADC->CR0_f.INREFEN = 0;
    }
    M0P_ADC->CR0_f.REF = enAdcRefVolSel;
    return Ok;
}
/**
 * \brief   
 *          Set ADC result alignment
 *
 * \param   [in]  enAlign  ADC result alignment
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: none Effect parameter
 */
en_result_t Adc_SetAlign(en_adc_align_t enAlign)
{
  M0P_ADC->CR1_f.ALIGN = enAlign;
  return Ok;
}
//@} // AdcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


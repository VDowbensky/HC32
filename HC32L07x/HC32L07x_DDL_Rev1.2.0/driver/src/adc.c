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
 * @file   adc.c
 *
 * @brief  Source file for ADC functions
 *
 * @author MADS Team 
 *
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

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
* \brief
* Get ADC interrupt status
*
* \param [in] enAdcIrq ADC interrupt type @ref en_adc_irq_type_t
*
* \retval Interrupt flag
*/
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    if(M0P_ADC->IFR&enAdcIrq)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
* \brief
* Clear ADC interrupt status
*
* \param [in] enAdcIrq ADC interrupt type @ref en_adc_irq_type_t
*
* \retval Null
*/
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    M0P_ADC->ICR &= ~(uint32_t)enAdcIrq;
}

/**
* \brief
* ADC interrupt enable
*
* \param None
*
* \retval None
*/
void Adc_EnableIrq(void)
{
    M0P_ADC->CR0_f.IE = 1u;
}

/**
* \brief
* ADC interrupt disable
*
* \param None
*
* \retval None
*/
void Adc_DisableIrq(void)
{
    M0P_ADC->CR0_f.IE = 0u;
}

/**
* \brief
* ADC initialization
*
* \param [in] pstcAdcCfg ADC configuration pointer
*
* \retval en_result_t Ok: Configuration successful
* \retval en_result_t ErrorInvalidParameter: Invalid parameter
*/
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg)
{
    if (NULL == pstcAdcCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0 = 0x1u;    ///< ADC enable
    delay10us(2);

    M0P_ADC->CR0 |= (uint32_t)pstcAdcCfg->enAdcClkDiv       |
                    (uint32_t)pstcAdcCfg->enAdcRefVolSel    |
                    (uint32_t)pstcAdcCfg->enAdcOpBuf        |
                    (uint32_t)pstcAdcCfg->enAdcSampCycleSel |
                    (uint32_t)pstcAdcCfg->enInRef;

    M0P_ADC->CR1_f.MODE  = pstcAdcCfg->enAdcMode;
    M0P_ADC->CR1_f.ALIGN = pstcAdcCfg->enAdcAlign;

    return Ok;
}


/**
* \brief
* ADC single conversion external interrupt trigger source configuration
*
* \param [in] enAdcTrigSel trigger source
*
* \retval en_result_t Null
*/
void Adc_SglExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue)
{
    if(TRUE == bValue)
    {
        M0P_ADC->EXTTRIGGER0 |= (uint32_t)enAdcTrigSel;
    }
    else
    {
        M0P_ADC->EXTTRIGGER0 &= ~(uint32_t)enAdcTrigSel;
    }

}

/**
* \brief
* ADC sequential scan conversion external interrupt trigger source configuration
*
* \param [in] enAdcTrigSel Trigger source
* \param [in] TRUE or FALSE
*
* \retval en_result_t Null
*/
void Adc_SqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue)
{
    if(TRUE == bValue)
    {
        M0P_ADC->EXTTRIGGER0 |= (uint32_t)enAdcTrigSel;
    }
    else
    {
        M0P_ADC->EXTTRIGGER0 &= ~(uint32_t)enAdcTrigSel;
    }

}

/**
* \brief
* ADC queue scan conversion external interrupt trigger source configuration
*
* \param [in] enAdcTrigSel trigger source
* \param [in] TRUE or FALSE
*
* \retval en_result_t Null
*/
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue)
{
    if(TRUE == bValue)
    {
        M0P_ADC->EXTTRIGGER1 |= (uint32_t)enAdcTrigSel;
    }
    else
    {
        M0P_ADC->EXTTRIGGER1 &= ~(uint32_t)enAdcTrigSel;
    }

}

/**
* \brief
* ADC single conversion start
*
* \param None
*
* \retval None
*/
void Adc_SGL_Start(void)
{
    M0P_ADC->SGLSTART = 1u;
}

/**
* \brief
* ADC single conversion stop
*
* \param None
*
* \retval None
*/
void Adc_SGL_Stop(void)
{
    M0P_ADC->SGLSTART = 0u;
}

/**
* \brief
* ADC single conversion always starts
*
* \param None
*
* \retval None
*/
void Adc_SGL_Always_Start(void)
{
    M0P_ADC->ALLSTART = 1u;
}

/**
* \brief
* ADC single conversion always stops
*
* \param None
*
* \retval None
*/
void Adc_SGL_Always_Stop(void)
{
    M0P_ADC->ALLSTART = 0u;
}

/**
* \brief
* ADC sequential scan conversion starts
*
* \param None
*
* \retval None
*/
void Adc_SQR_Start(void)
{
    M0P_ADC->SQRSTART = 1u;
}

/**
* \brief
* ADC sequential scan conversion stops
*
* \param None
*
* \retval None
*/
void Adc_SQR_Stop(void)
{
    M0P_ADC->SQRSTART = 0u;
}
/**
* \brief
* ADC queued scan conversion starts
*
* \param None
*
* \retval None
*/
void Adc_JQR_Start(void)
{
    M0P_ADC->JQRSTART = 1u;
}

/**
* \brief
* ADC queue scan conversion stops
*
* \param None
*
* \retval None
*/
void Adc_JQR_Stop(void)
{
    M0P_ADC->JQRSTART = 0u;
}

/**
* \brief
* ADC enable
*
* \param None
*
* \retval None
*/
void Adc_Enable(void)
{
    M0P_ADC->CR0_f.EN = 1u;
}

/**
* \brief
* ADC disable
*
* \param None
*
* \retval None
*/
void Adc_Disable(void)
{
    M0P_ADC->CR0_f.EN = 0u;
}

/**
* \brief
* Configure sequential scan conversion mode
*
* \param [in] pstcAdcCfg ADC configuration pointer
* \param [in] pstcAdcNormCfg Continuous conversion mode configuration pointer
*
* \retval en_result_t Ok: Configuration successful
* \retval en_result_t ErrorInvalidParameter: Invalid parameter
*/
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg)
{
    if ((NULL == pstcAdcSqrCfg) || (pstcAdcSqrCfg->u8SqrCnt > 16))
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.RACCCLR = 0; //ADC转换结果累加寄存器（ADC_ResultAcc）清零
    M0P_ADC->CR1_f.RACCEN  = pstcAdcSqrCfg->enResultAcc;
    M0P_ADC->CR1_f.DMASQR  = pstcAdcSqrCfg->bSqrDmaTrig;

    M0P_ADC->SQR2_f.CNT  = pstcAdcSqrCfg->u8SqrCnt - 1;

    return Ok;
}

/**
* \brief
* Configure the queue-jump scan conversion mode
*
* \param [in] pstcAdcCfg ADC configuration pointer
* \param [in] pstcAdcNormCfg Scan conversion mode configuration pointer
*
* \retval en_result_t Ok: Configuration successful
* \retval en_result_t ErrorInvalidParameter: Invalid parameter
*/
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg)
{
    if ((NULL == pstcAdcJqrCfg) || (pstcAdcJqrCfg->u8JqrCnt > 4))
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.DMASQR  = pstcAdcJqrCfg->bJqrDmaTrig;

    M0P_ADC->JQR_f.CNT  = pstcAdcJqrCfg->u8JqrCnt - 1;

    return Ok;
}

/**
* \brief
* Configure a single-shot conversion channel
*
* \param [in]enstcAdcSampCh Conversion channel
*
* \retval en_result_t OK: Success
* \retval en_result_t ErrorInvalidParameter: Invalid parameter
*/
en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    M0P_ADC->CR0_f.SGLMUX = enstcAdcSampCh;

    return Ok;
}

/**
* \brief
* Configure the sequential scan conversion channel
*
* \param [in]enstcAdcSqrChMux Sequential scan conversion channel sequence
* \param [in]enstcAdcSampCh Conversion channel
*
* \retval en_result_t OK: Success
* \retval en_result_t ErrorInvalidParameter: Invalid parameter
*/
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    
    switch(enstcAdcSqrChMux)
    {
        case AdcSQRCH0MUX:
            M0P_ADC->SQR0_f.CH0MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH1MUX:
            M0P_ADC->SQR0_f.CH1MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH2MUX:
            M0P_ADC->SQR0_f.CH2MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH3MUX:
            M0P_ADC->SQR0_f.CH3MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH4MUX:
            M0P_ADC->SQR0_f.CH4MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH5MUX:
            M0P_ADC->SQR0_f.CH5MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH6MUX:
            M0P_ADC->SQR1_f.CH6MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH7MUX:
            M0P_ADC->SQR1_f.CH7MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH8MUX:
            M0P_ADC->SQR1_f.CH8MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH9MUX:
            M0P_ADC->SQR1_f.CH9MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH10MUX:
            M0P_ADC->SQR1_f.CH10MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH11MUX:
            M0P_ADC->SQR1_f.CH11MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH12MUX:
            M0P_ADC->SQR2_f.CH12MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH13MUX:
            M0P_ADC->SQR2_f.CH13MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH14MUX:
            M0P_ADC->SQR2_f.CH14MUX = enstcAdcSampCh;
        break;
        case AdcSQRCH15MUX:
            M0P_ADC->SQR2_f.CH15MUX = enstcAdcSampCh;
        break;
        default:
            enResult = ErrorInvalidParameter;
        break;

    }
    
    return enResult;
}
/**
* \brief
* Configure the queued scan conversion channel
*
* \param [in]enstcAdcSqrChMux queued scan conversion channel order
* \param [in]enstcAdcSampCh conversion channel
*
* \retval en_result_t Ok: Success
* \retval en_result_t ErrorInvalidParameter: Invalid parameter
*/
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    
    switch(enstcAdcJqrChMux)
    {
        case AdcJQRCH0MUX:
            M0P_ADC->JQR_f.CH0MUX = enstcAdcSampCh;
        break;
        case AdcJQRCH1MUX:
            M0P_ADC->JQR_f.CH1MUX = enstcAdcSampCh;
        break;
        case AdcJQRCH2MUX:
            M0P_ADC->JQR_f.CH2MUX = enstcAdcSampCh;
        break;
        case AdcJQRCH3MUX:
            M0P_ADC->JQR_f.CH3MUX = enstcAdcSampCh;
        break;
        default:
            enResult = ErrorInvalidParameter;
        break;
    }
    
    return enResult;
}

/**
* \brief
* Get sample value
*
*
* \retval en_result_t Sample value
*/
uint32_t Adc_GetSglResult(void)
{
    return M0P_ADC->RESULT;
}

/**
* \brief
* Get sample value
*
* \param [in] enstcAdcSqrChMux Sequential Scan Channel Number @ref en_adc_sqr_chmux_t
*
* \retval en_result_t Sample Value
*/
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux)
{
    volatile uint32_t *BaseSqrResultAddress = &(M0P_ADC->SQRRESULT0);

    return *(BaseSqrResultAddress + enstcAdcSqrChMux);

}

/**
* \brief
* Get the queued scan sample value
*
* \param [in] enstcAdcJqrChMux Queued Scan Channel Number @ref en_adc_jqr_chmux_t
*
* \retval en_result_t Sample Value
*/
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux)
{
      volatile uint32_t *BaseJqrResultAddress = &(M0P_ADC->JQRRESULT0);

      return *(BaseJqrResultAddress + enstcAdcJqrChMux);

}

/**
* \brief
* Get the accumulated sampling value
*
*
* \retval en_result_t Accumulated sampling result
*/
uint32_t Adc_GetAccResult(void)
{
    return M0P_ADC->RESULTACC;

}

/**
* \brief
* Clear the accumulated sampling value
*
* \param None
*
* \retval None
*/
void Adc_ClrAccResult(void)
{
    M0P_ADC->CR1_f.RACCCLR = 0u;
}

/**
* \brief
* ADC compare enable (compare interrupt)
*
* \param [in] pstcAdcIrqCfg ADC compare configuration @ref stc_adc_threshold_cfg_t
*
* \retval None
*/
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg)
{
    M0P_ADC->HT = pstcAdcThrCfg->u32AdcHighThd;
    M0P_ADC->LT = pstcAdcThrCfg->u32AdcLowThd;

    M0P_ADC->CR1_f.THCH = pstcAdcThrCfg->enSampChSel;

    M0P_ADC->CR1_f.REGCMP = pstcAdcThrCfg->bAdcRegCmp;
    M0P_ADC->CR1_f.HTCMP  = pstcAdcThrCfg->bAdcHtCmp;
    M0P_ADC->CR1_f.LTCMP  = pstcAdcThrCfg->bAdcLtCmp;

}

/**
* \brief
* ADC channel remapping
*
* \param [in] enChMap ADC mapping channel type @ref en_adc_channel_remap_type_t
*
* \retval None
*/
void Adc_ChannelRemap(en_adc_channel_remap_type_t enChMap)
{
    M0P_ADC->CR0_f.CHMAP = enChMap;
}
//@} // AdcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


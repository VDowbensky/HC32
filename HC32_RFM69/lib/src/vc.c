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
/** \file vc.c
 **
 ** voltage comparator driver API.
 ** @link VC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "vc.h"

/**
 ******************************************************************************
 ** \addtogroup VcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_CHANNEL(x)     ( VcChannel0==(x) || VcChannel1 == (x))
#define IS_VALID_STAT(x)        ( VcCmpResult==(x) || VcIntrResult == (x))
#define IS_VALID_DIV(x)         ( (x) <= 64u )

#define IS_VALID_INPUT_P(x)     ( (x) <= VcInPCh15 )

#define IS_VALID_INPUT_N(x)     ( (x) <= AiLdo )

#define IS_VALID_DLY(x)         (   (VcDelay30mv == (x)) ||\
                                    (VcDelay20mv == (x)) ||\
                                    (VcDelay10mv == (x)) ||\
                                    (VcDelayoff == (x)) )

#define IS_VALID_BIAS(x)         (   (VcBias300na == (x)) ||\
                                    (VcBias1200na == (x)) ||\
                                    (VcBias10ua == (x)) ||\
                                    (VcBias20ua == (x)) )

#define IS_VALID_FILTER(x)         ( (x) <= VcFilter28800us )



/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static en_result_t VcEnableIrq(en_vc_channel_t enChannel, boolean_t bFlag);
static void VcEnableNvic(IRQn_Type enIrqn);
static void VcDisableNvic(IRQn_Type enIrqn);

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static func_ptr_t pfnVc0IrqCb = NULL;
static func_ptr_t pfnVc1IrqCb = NULL;

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
  * \brief
  * Specify VC channel interrupt enable/disable
  *
  * \param [in] enChannel VC channel number
  * \param [in] bFlag enable/disable flag
  *
  * \retval en_result_t Ok: Set successfully
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
static en_result_t VcEnableIrq(en_vc_channel_t enChannel, boolean_t bFlag)
{
    if (VcChannel0 == enChannel)
    {
        if (bFlag)
        {
            VcEnableNvic(VC0_IRQn);
            M0P_VC->VC0_CR_f.IE = 1u;
        }
        else
        {
            M0P_VC->VC0_CR_f.IE = 0u;
            VcDisableNvic(VC0_IRQn);
        }
    }
    else if (VcChannel1 == enChannel)
    {
        if (bFlag)
        {
            VcEnableNvic(VC1_IRQn);
            M0P_VC->VC1_CR_f.IE = 1u;
        }
        else
        {
            M0P_VC->VC1_CR_f.IE = 0u;
            VcDisableNvic(VC1_IRQn);
        }
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * Enable VC interrupt in NVIC
  *
  * \param [in] enIrqn interrupt number
  *
  * \retval none
  */
static void VcEnableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_EnableIRQ(enIrqn);
    NVIC_SetPriority(enIrqn, IrqLevel3);
}

/**
  * \brief
  * In addition to NVC interrupt in VC
  *
  * \param [in] enIrqn interrupt number
  *
  * \retval none
  */
static void VcDisableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_DisableIRQ(enIrqn);
    NVIC_SetPriority(enIrqn, IrqLevel3);
}

/**
  * \brief
  * VC interrupt service program
  *
  * \param [in] u8Param VC channel number
  *
  * \retval none
  */
void Vc_IRQHandler(uint8_t u8Param)
{
    if (0 == u8Param)
    {
        if (TRUE == M0P_VC->IFR_f.VC0_INTF)
        {
            if (NULL != pfnVc0IrqCb)
            {
                pfnVc0IrqCb();
            }
            M0P_VC->IFR_f.VC0_INTF = 0;
        }
    }
    else if (1 == u8Param)
    {
        if (TRUE == M0P_VC->IFR_f.VC1_INTF)
        {
            if (NULL != pfnVc1IrqCb)
            {
                pfnVc1IrqCb();
            }
            M0P_VC->IFR_f.VC1_INTF = 0;
        }
    }
    else
    {
        ;    // just return
    }    
}

/**
  * \brief
  * Configure VC interrupt trigger mode
  *
  * \param [in] enChannel VC channel number
  * \param [in] enSel interrupt trigger mode selection
  *
  * \retval en_result_t Ok: Set successfully
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_ConfigIrq(en_vc_channel_t enChannel, en_vc_irq_sel_t enSel)
{
    stc_vc_vc0_cr_field_t *stcVcnCr;
    en_result_t enRet = Ok;

    if (VcChannel0 == enChannel)
    {
        stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC0_CR_f;
    }
    else if (VcChannel1 == enChannel)
    {
        stcVcnCr = (stc_vc_vc0_cr_field_t*)&M0P_VC->VC1_CR_f;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    switch (enSel)
    {
        case VcIrqRise:
            stcVcnCr->RISING = 1u;
            break;
        case VcIrqFall:
            stcVcnCr->FALLING = 1u;
            break;
        case VcIrqHigh:
            stcVcnCr->LEVEL = 1u;
            break;

        default:
            enRet= ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
  * \brief
  * Get VC status
  *
  * \param [in] enChannel VC channel number
  * \param [in] enStat VC status type
  *
  * \retval boolean_t TRUE: Status is high
  * \retval boolean_t FALSE: Status is low
  */
boolean_t Vc_GetStat(en_vc_channel_t enChannel, en_vc_stat_t enStat)
{
    boolean_t bFlag = FALSE;

    ASSERT( IS_VALID_CHANNEL(enChannel) );
    ASSERT( IS_VALID_STAT(enStat) );

    if (VcChannel0 == enChannel)
    {
        switch (enStat)
        {
            case VcCmpResult:
                bFlag = M0P_VC->IFR_f.VC0_FILTER;
                break;
            case VcIntrResult:
                bFlag = M0P_VC->IFR_f.VC0_INTF;
                break;
            default:
                break;
        }
    }
    else
    {
        switch (enStat)
        {
            case VcCmpResult:
                bFlag = M0P_VC->IFR_f.VC1_FILTER;
                break;
            case VcIntrResult:
                bFlag = M0P_VC->IFR_f.VC1_INTF;
                break;
            default:
                break;
        }
    }

    return bFlag;
}

/**
  * \brief
  * Clear VC interrupt flag
  *
  * \param [in] enChannel VC channel number
  *
  * \retval none
  */
void Vc_ClearIrq(en_vc_channel_t enChannel)
{
    ASSERT( IS_VALID_CHANNEL(enChannel) );

    if (VcChannel0 == enChannel)
    {
        M0P_VC->IFR_f.VC0_INTF = 0u;
    }
    else
    {
        M0P_VC->IFR_f.VC1_INTF = 0u;
    }
}

/**
  * \brief
  * Specify VC channel interrupt enable
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Set successfully
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_EnableIrq(en_vc_channel_t enChannel)
{
    return VcEnableIrq(enChannel, TRUE);
}

/**
  * \brief
  * Specify VC channel interrupt disable
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Set successfully
  * ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_DisableIrq(en_vc_channel_t enChannel)
{
    return VcEnableIrq(enChannel, FALSE);
}

/**
  * \brief
  * VC module initialization
  *
  * \param [in] pstcGeneralConfig VC module configuration pointer
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_DACInit(stc_vc_dac_config_t *pstcDacConfig)
{
    if (NULL == pstcDacConfig)
    {
        return ErrorInvalidParameter;
    }

    M0P_VC->CR_f.DIV_EN = pstcDacConfig->bDivEn;
    M0P_VC->CR_f.REF2P5_SEL = pstcDacConfig->enDivVref;

    if (pstcDacConfig->u8DivVal < 0x40)
    {
        M0P_VC->CR_f.DIV = pstcDacConfig->u8DivVal;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * VC module deinit
  *
  * \param no
  *
  * \retval none
  */
void Vc_DACDeInit(void)
{
    M0P_VC->CR_f.DIV_EN = 0u;
    M0P_VC->CR_f.DIV = 0x20u;
    M0P_VC->CR_f.REF2P5_SEL = 0u;
}

/**
  * \brief
  * VC channel initialization
  *
  * \param [in] enChannel VC channel number
  * \param [in] pstcChannelConfig VC channel configuration pointer
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_ChannelInit(en_vc_channel_t enChannel,
                            stc_vc_channel_config_t *pstcChannelConfig)
{
    //en_result_t enRet = Ok;

    ASSERT(NULL != pstcChannelConfig);
    ASSERT(IS_VALID_INPUT_P(pstcChannelConfig->enVcInPin_P));
    ASSERT(IS_VALID_INPUT_N(pstcChannelConfig->enVcInPin_N));
    ASSERT(IS_VALID_DLY(pstcChannelConfig->enVcCmpDly));
    ASSERT(IS_VALID_BIAS(pstcChannelConfig->enVcBiasCurrent));
    ASSERT(IS_VALID_FILTER(pstcChannelConfig->enVcFilterTime));

    if (VcChannel0 == enChannel)
    {
        M0P_VC->CR_f.VC0_HYS_SEL = pstcChannelConfig->enVcCmpDly;
        M0P_VC->CR_f.VC0_BIAS_SEL = pstcChannelConfig->enVcBiasCurrent;
        M0P_VC->VC0_CR_f.DEBOUNCE_TIME = pstcChannelConfig->enVcFilterTime;
        M0P_VC->VC0_CR_f.P_SEL = pstcChannelConfig->enVcInPin_P;
        M0P_VC->VC0_CR_f.N_SEL = pstcChannelConfig->enVcInPin_N;
        M0P_VC->VC0_OUT_CFG = 1<<pstcChannelConfig->enVcOutConfig;

        switch(pstcChannelConfig->enVcIrqSel)
        {
            case VcIrqRise:
                M0P_VC->VC0_CR_f.RISING = 1u;
                break;
            case VcIrqFall:
                M0P_VC->VC0_CR_f.FALLING = 1u;
                break;
            case VcIrqHigh:
                M0P_VC->VC0_CR_f.LEVEL = 1u;
                break;
            default:
                M0P_VC->VC0_CR_f.LEVEL = 0u;
                M0P_VC->VC0_CR_f.RISING = 0u;
                M0P_VC->VC0_CR_f.FALLING = 0u;
                break;
        }

        pfnVc0IrqCb = pstcChannelConfig->pfnAnalogCmpCb;
    }
    else if (VcChannel1 == enChannel)
    {
        M0P_VC->CR_f.VC1_HYS_SEL = pstcChannelConfig->enVcCmpDly;
        M0P_VC->CR_f.VC1_BIAS_SEL = pstcChannelConfig->enVcBiasCurrent;
        M0P_VC->VC1_CR_f.DEBOUNCE_TIME = pstcChannelConfig->enVcFilterTime;
        M0P_VC->VC1_CR_f.P_SEL = pstcChannelConfig->enVcInPin_P;
        M0P_VC->VC1_CR_f.N_SEL = pstcChannelConfig->enVcInPin_N;
        M0P_VC->VC1_OUT_CFG = 1<<pstcChannelConfig->enVcOutConfig;

        switch(pstcChannelConfig->enVcIrqSel)
        {
            case VcIrqRise:
                M0P_VC->VC1_CR_f.RISING = 1u;
                break;
            case VcIrqFall:
                M0P_VC->VC1_CR_f.FALLING = 1u;
                break;
            case VcIrqHigh:
                M0P_VC->VC1_CR_f.LEVEL = 1u;
                break;
            default:
                M0P_VC->VC1_CR_f.LEVEL = 0u;
                M0P_VC->VC1_CR_f.RISING = 0u;
                M0P_VC->VC1_CR_f.FALLING = 0u;
                break;
        }

        pfnVc1IrqCb = pstcChannelConfig->pfnAnalogCmpCb;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * VC channel Deinit
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_ChannelDeInit(en_vc_channel_t enChannel)
{
    if (VcChannel0 == enChannel)
    {
        M0P_VC->VC0_CR_f.EN = 0u;
        M0P_VC->CR_f.VC0_HYS_SEL = 0;
        M0P_VC->CR_f.VC0_BIAS_SEL = 0;
        M0P_VC->VC0_CR_f.DEBOUNCE_TIME = 0;
        M0P_VC->VC0_CR_f.P_SEL = 0;
        M0P_VC->VC0_CR_f.N_SEL = 0;
        M0P_VC->VC0_OUT_CFG = 0;
        M0P_VC->VC0_CR_f.LEVEL = 0u;
        M0P_VC->VC0_CR_f.RISING = 0u;
        M0P_VC->VC0_CR_f.FALLING = 0u;
        pfnVc0IrqCb = NULL;
        M0P_VC->VC0_CR_f.IE = 0u;
        VcDisableNvic(VC0_IRQn);
    }
    else if (VcChannel1 == enChannel)
    {
        M0P_VC->VC1_CR_f.EN = 0u;
        M0P_VC->CR_f.VC1_HYS_SEL = 0;
        M0P_VC->CR_f.VC1_BIAS_SEL = 0;
        M0P_VC->VC1_CR_f.DEBOUNCE_TIME = 0;
        M0P_VC->VC1_CR_f.P_SEL = 0;
        M0P_VC->VC1_CR_f.N_SEL = 0;
        M0P_VC->VC1_OUT_CFG = 0;
        M0P_VC->VC1_CR_f.LEVEL = 0u;
        M0P_VC->VC1_CR_f.RISING = 0u;
        M0P_VC->VC1_CR_f.FALLING = 0u;
        pfnVc1IrqCb = NULL;
        M0P_VC->VC1_CR_f.IE = 0u;
        VcDisableNvic(VC1_IRQn);
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * VC channel enable
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_EnableChannel(en_vc_channel_t enChannel)
{
    if (VcChannel0 == enChannel)
    {
        M0P_VC->VC0_CR_f.EN = 1u;
    }
    else if (VcChannel1 == enChannel)
    {
        M0P_VC->VC1_CR_f.EN = 1u;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * VC channel disable
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_DisableChannel(en_vc_channel_t enChannel)
{
    if (VcChannel0 == enChannel)
    {
        M0P_VC->VC0_CR_f.EN = 0u;
    }
    else if (VcChannel1 == enChannel)
    {
        M0P_VC->VC1_CR_f.EN = 0u;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * VC output filter enable
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_EnableFilter(en_vc_channel_t enChannel)
{
    if (VcChannel0 == enChannel)
    {
        M0P_VC->VC0_CR_f.FLTEN = 1u;
    }
    else if (VcChannel1 == enChannel)
    {
        M0P_VC->VC1_CR_f.FLTEN = 1u;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
  * \brief
  * VC output filter disable
  *
  * \param [in] enChannel VC channel number
  *
  * \retval en_result_t Ok: Configuration is successful
  * \retval en_result_t ErrorInvalidParameter: invalid parameter
  */
en_result_t Vc_DisableFilter(en_vc_channel_t enChannel)
{
    if (VcChannel0 == enChannel)
    {
        M0P_VC->VC0_CR_f.FLTEN = 0u;
    }
    else if (VcChannel1 == enChannel)
    {
        M0P_VC->VC1_CR_f.FLTEN = 0u;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

//@} // VcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


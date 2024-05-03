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
/** \file adt.c
 **
 ** Low Voltage Detect driver API.
 ** @link Lvd Group Some description @endlink
 **
 **   - 2018-04-18 Husj    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "adt.h"

/**
 ******************************************************************************
 ** \addtogroup AdtGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
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
static func_ptr_t    pfnAdtIrqCbk[3][16] = {NULL};

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/*************************************************
 * \brief   
 *          Enable ADT interrupt in NVIC
 *
 * \param   [in]  enIrqn  Interrupt number
 *
 * \retval  none
 **************************************************/
static void AdtEnableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_EnableIRQ(enIrqn);
    NVIC_SetPriority(enIrqn, DDL_IRQ_LEVEL_DEFAULT);
}

/**************************************************
 * \brief   
 *          Disable ADT interrupt in NVIC
 *
 * \param   [in]  enIrqn  Interrupt number
 *
 * \retval  none
 **************************************************/
static void AdtDisableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_DisableIRQ(enIrqn);
    NVIC_SetPriority(enIrqn, DDL_IRQ_LEVEL_DEFAULT);
}

/***************************************************
 * \brief   
 *          ADT interrupt service routine
 *
 * \param   [in]  u8Param  Unused
 *
 * \retval  none
 ****************************************************/
void Adt_IRQHandler(uint8_t u8Param)
{
    uint8_t u8Adt = u8Param - 4;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*u8Adt);

    if (TRUE == pstcM0PAdt->IFR_f.CMAF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtCMAIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtCMAIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtCMAIrq);
    }

    if (TRUE == pstcM0PAdt->IFR_f.CMBF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtCMBIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtCMBIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtCMBIrq);
    }

    if (TRUE == pstcM0PAdt->IFR_f.CMCF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtCMCIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtCMCIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtCMCIrq);
    }

    if (TRUE == pstcM0PAdt->IFR_f.CMDF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtCMDIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtCMDIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtCMDIrq);
    }

    if (TRUE == pstcM0PAdt->IFR_f.OVFF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtOVFIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtOVFIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtOVFIrq);
    }

    if (TRUE == pstcM0PAdt->IFR_f.UDFF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtUDFIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtUDFIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtUDFIrq);
    }

    if (TRUE == pstcM0PAdt->IFR_f.DTEF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtDTEIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtDTEIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtDTEIrq);
    }
 
    if (TRUE == pstcM0PAdt->IFR_f.SAMLF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtSAMLIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtSAMLIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtSAMLIrq);
    }
 
    if (TRUE == pstcM0PAdt->IFR_f.SAMHF)
    {
        if (NULL != pfnAdtIrqCbk[u8Adt][AdtSAMHIrq])
        {
            pfnAdtIrqCbk[u8Adt][AdtSAMHIrq]();
        }
        pstcM0PAdt->ICLR = ~(1<<AdtSAMHIrq);
    }
}

/*****************************************************************
 * \brief   
 *          Interrupt configuration
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtIrq      Interrupt type
 * \param   [in]  bEn           Interrupt enable/disable
 * \param   [in]  pfnIrqCalbak  Callback function pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ****************************************************************/
en_result_t Adt_ConfigIrq(en_adt_unit_t enAdtUnit,
                          en_adt_irq_type_t enAdtIrq,
                          boolean_t bEn,
                          func_ptr_t pfnIrqCalbak)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pfnAdtIrqCbk[enAdtUnit][enAdtIrq] = pfnIrqCalbak;

    u32Val = pstcM0PAdt->ICONR;
    if (bEn)
    {
        u32Val |= 1u<<enAdtIrq;
    }
    else
    {
        u32Val &= ~(1u<<enAdtIrq);
    }
    pstcM0PAdt->ICONR = u32Val;
    return Ok;
}

/*******************************************************************
 * \brief   
 *          Get interrupt flag
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtIrq      Interrupt type
 * \param   [in]  pbFlag        Interrupt flag pointer
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *****************************************************************/
en_result_t Adt_GetIrqFlag(en_adt_unit_t enAdtUnit,
                           en_adt_irq_type_t enAdtIrq,
                           boolean_t* pbFlag)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->IFR;
    *pbFlag = (u32Val>>enAdtIrq) & 0x1;

    return Ok;
}

/****************************************************************
 * \brief   
 *          Clear interrupt flag
 *
 * \param   [in]  enAdtUnit    ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtIrq      Interrupt type
 *
 * \retval  en_result_t  Ok:  Successful configuration
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ****************************************************************/
en_result_t Adt_ClearIrqFlag(en_adt_unit_t enAdtUnit,
                             en_adt_irq_type_t enAdtIrq)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->ICLR = ~(1u<<enAdtIrq);
    return Ok;
}


/**************************************************************
 * \brief   
 *          Configuring hardware increment events
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwCntUp  Hardware recurring event
 *
 * \retval  en_result_t    Ok:  Successful configuration
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ****************************************************************/
en_result_t Adt_ConfigHwCntUp(en_adt_unit_t enAdtUnit, en_adt_hw_cnt_t enAdtHwCntUp)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwCntMax <= enAdtHwCntUp))
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HCUPR;
    pstcM0PAdt->HCUPR = u32Val | (1u<<enAdtHwCntUp);
    return Ok;
}

/**************************************************************
 * \brief   
 *          Clear hardware increment events
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Successful configuration
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ************************************************************/
en_result_t Adt_ClearHwCntUp(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }
    pstcM0PAdt->HCUPR = 0;
    return Ok;
}


/**
 * \brief   
 *          Configuring hardware decrement events
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwCntDwn Hardware decrement event
 *
 * \retval  en_result_t    Ok:  Successful configuration
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 */
en_result_t Adt_ConfigHwCntDwn(en_adt_unit_t enAdtUnit, en_adt_hw_cnt_t enAdtHwCntDwn)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwCntMax <= enAdtHwCntDwn))
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HCDOR;
    pstcM0PAdt->HCDOR = u32Val | (1u<<enAdtHwCntDwn);
    return Ok;
}

/******************************************************************
 * \brief   
 *          Clear hardware decrement events
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Successful configuration
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *****************************************************************/
en_result_t Adt_ClearHwCntDwn(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->HCDOR = 0;
    return Ok;
}

/******************************************************************
 * \brief   
 *          Configuring hardware startup events
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwStart      Hardware boot event
 *
 * \retval  en_result_t    Ok:  Successful configuration
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *******************************************************************/
en_result_t Adt_ConfigHwStart(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwStart)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwTrigEnd <= enAdtHwStart))
    {
        return ErrorInvalidParameter;
    }
    u32Val = pstcM0PAdt->HSTAR;
    pstcM0PAdt->HSTAR = u32Val | (1u<<enAdtHwStart);
    return Ok;
}

/************************************************************************
 * \brief   
 *          Clear hardware startup events
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***********************************************************************/
en_result_t Adt_ClearHwStart(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->HSTAR = 0;
    return Ok;
}

/*********************************************************************
 * \brief   
 *          Enable hardware boot
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *********************************************************************/
en_result_t Adt_EnableHwStart(en_adt_unit_t enAdtUnit)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HSTAR;
    pstcM0PAdt->HSTAR = u32Val | (1u<<31);
    return Ok;
}

/*************************************************************************
 * \brief   
 *          Disable hardware boot
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ************************************************************************/
en_result_t Adt_DisableHwStart(en_adt_unit_t enAdtUnit)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HSTAR;
    pstcM0PAdt->HSTAR = u32Val & 0x7FFFFFFF;
    return Ok;
}

/****************************************************************
 * \brief   
 *          Configuring hardware stop events
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwStop       Hardware stop event
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***************************************************************/
en_result_t Adt_ConfigHwStop(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwStop)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwTrigEnd <= enAdtHwStop))
    {
        return ErrorInvalidParameter;
    }
    u32Val = pstcM0PAdt->HSTPR;
    pstcM0PAdt->HSTPR = u32Val | (1u<<enAdtHwStop);
    return Ok;
}

/***************************************************************
 * \brief   
 *          Clear hardware stop event
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***************************************************************/
en_result_t Adt_ClearHwStop(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->HSTPR = 0;
    return Ok;
}

/*************************************************************
 * \brief   
 *          Enable hardware stop
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 **********************************************************/
en_result_t Adt_EnableHwStop(en_adt_unit_t enAdtUnit)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HSTPR;
    pstcM0PAdt->HSTPR = u32Val | (1u<<31);
    return Ok;
}

/*****************************************************************************
 * \brief   
 *          Disable hardware stop
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***************************************************************************/
en_result_t Adt_DisableHwStop(en_adt_unit_t enAdtUnit)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HSTPR;
    pstcM0PAdt->HSTPR = u32Val & 0x7FFFFFFF;
    return Ok;
}

/**************************************************************************
 * \brief   
 *          Configuring hardware clearing events
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwClear      Hardware clear event
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *************************************************************************/
en_result_t Adt_ConfigHwClear(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwClear)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwTrigEnd <= enAdtHwClear))
    {
        return ErrorInvalidParameter;
    }
    u32Val = pstcM0PAdt->HCELR & (1u<<31);
    pstcM0PAdt->HCELR = u32Val | (1u<<enAdtHwClear);
    return Ok;
}

/**************************************************************************
 * \brief   
 *          Clear hardware clear event
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 **************************************************************************/
en_result_t Adt_ClearHwClear(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->HCELR = 0;
    return Ok;
}

/***************************************************************************
 * \brief   
 *          Enable hardware clearing
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *************************************************************************/
en_result_t Adt_EnableHwClear(en_adt_unit_t enAdtUnit)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HCELR;
    pstcM0PAdt->HCELR = u32Val | (1u<<31);
    return Ok;
}

/************************************************************************
 * \brief   
 *          Disable hardware clearing
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 **********************************************************************/
en_result_t Adt_DisableHwClear(en_adt_unit_t enAdtUnit)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HCELR;
    pstcM0PAdt->HCELR = u32Val & 0x7FFFFFFF;
    return Ok;
}

/*******************************************************************
 * \brief   
 *          Configuring hardware capture A events
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwCaptureA   Hardware capture A event selection
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *******************************************************************/
en_result_t Adt_ConfigHwCaptureA(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwCaptureA)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwTrigEnd <= enAdtHwCaptureA))
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HCPAR;
    pstcM0PAdt->HCPAR = u32Val | (1u<<enAdtHwCaptureA);
    pstcM0PAdt->PCONR_f.CAPCA = 1;
    return Ok;
}

/************************************************************************
 * \brief   
 *         Clear hardware capture A event
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***********************************************************************/
en_result_t Adt_ClearHwCaptureA(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->HCPAR = 0;
    return Ok;
}

/*********************************************************************
 * \brief   
 *          Configuring hardware capture B events
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtHwCaptureB   Hardware capture B event selection
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ********************************************************************/
en_result_t Adt_ConfigHwCaptureB(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwCaptureB)
{
    uint32_t u32Val;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (AdtHwTrigEnd <= enAdtHwCaptureB))
    {
        return ErrorInvalidParameter;
    }

    u32Val = pstcM0PAdt->HCPBR;
    pstcM0PAdt->HCPBR =  u32Val | (1u<<enAdtHwCaptureB);
    pstcM0PAdt->PCONR_f.CAPCB = 1;
    return Ok;
}

/********************************************************************
 * \brief   
 *          Clear hardware capture B event
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *******************************************************************/
en_result_t Adt_ClearHwCaptureB(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->HCPBR = 0;
    return Ok;
}

/*****************************************************************
 * \brief   
 *          Start software synchronization 
 *
 * \param   [in]  pstcAdtSwSyncStart    Software synchronization start pointer
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***************************************************************/
en_result_t Adt_SwSyncStart(stc_adt_sw_sync_t* pstcAdtSwSyncStart)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncStart)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncStart->bAdTim4)
    {
        u32Val |= 0x1;
    }
    if (pstcAdtSwSyncStart->bAdTim5)
    {
        u32Val |= 0x2;
    }
    if (pstcAdtSwSyncStart->bAdTim6)
    {
        u32Val |= 0x4;
    }

    M0P_TIM4->SSTAR = u32Val;
    return Ok;
}

/***************************************************************
 * \brief   
 *          Stop software synchronization 
 *
 * \param   [in]  pstcAdtSwSyncStop     Software synchronization stop pointer
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 ***************************************************************/
en_result_t Adt_SwSyncStop(stc_adt_sw_sync_t* pstcAdtSwSyncStop)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncStop)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncStop->bAdTim4)
    {
        u32Val |= 0x1;
    }
    if (pstcAdtSwSyncStop->bAdTim5)
    {
        u32Val |= 0x2;
    }
    if (pstcAdtSwSyncStop->bAdTim6)
    {
        u32Val |= 0x4;
    }

    M0P_TIM4->SSTPR = u32Val;
    return Ok;
}

/*****************************************************************
 * \brief   
 *          Software synchronization clear
 *
 * \param   [in]  pstcAdtSwSyncClear    Software synchronization clear pointer
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *******************************************************************/
en_result_t Adt_SwSyncClear(stc_adt_sw_sync_t* pstcAdtSwSyncClear)
{
    uint32_t u32Val = 0;

    if (NULL == pstcAdtSwSyncClear)
    {
        return ErrorInvalidParameter;
    }

    if (pstcAdtSwSyncClear->bAdTim4)
    {
        u32Val |= 0x1;
    }
    if (pstcAdtSwSyncClear->bAdTim5)
    {
        u32Val |= 0x2;
    }
    if (pstcAdtSwSyncClear->bAdTim6)
    {
        u32Val |= 0x4;
    }

    M0P_TIM4->SCLRR = u32Val;
    return Ok;
}

/*******************************************************************
 * \brief   
 *          Get software synchronization running status
 *
 * \param   [in]  pstcAdtSwSyncState    ADV Timer software synchronization running status pointer
 *
 * \retval  en_result_t    Ok:  Success
 * \retval  en_result_t    ErrorInvalidParameter:  Invalid parameter
 *******************************************************************/
en_result_t Adt_GetSwSyncState(stc_adt_sw_sync_t* pstcAdtSwSyncState)
{
    if (NULL == pstcAdtSwSyncState)
    {
        return ErrorInvalidParameter;
    }

    if (M0P_TIM4->SSTAR & 0x1)
    {
        pstcAdtSwSyncState->bAdTim4 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim4 = FALSE;
    }
    if (M0P_TIM4->SSTAR & 0x2)
    {
        pstcAdtSwSyncState->bAdTim5 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim5 = FALSE;
    }
    if (M0P_TIM4->SSTAR & 0x4)
    {
        pstcAdtSwSyncState->bAdTim6 = TRUE;
    }
    else
    {
        pstcAdtSwSyncState->bAdTim6 = FALSE;
    }
    return Ok;
}

/************************************************************************
 * \brief   
 *          AOS trigger configuration
 *
 * \param   [in]  pstcAdtAosTrigCfg Trigger configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ************************************************************************/
en_result_t Adt_AosTrigConfig(stc_adt_aos_trig_cfg_t* pstcAdtAosTrigCfg)
{
    if (NULL == pstcAdtAosTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_TIM4->ITRIG_f.IAOS0S = pstcAdtAosTrigCfg->enAos0TrigSrc;
    M0P_TIM4->ITRIG_f.IAOS1S = pstcAdtAosTrigCfg->enAos1TrigSrc;
    M0P_TIM4->ITRIG_f.IAOS2S = pstcAdtAosTrigCfg->enAos2TrigSrc;
    M0P_TIM4->ITRIG_f.IAOS3S = pstcAdtAosTrigCfg->enAos3TrigSrc;
    return Ok;
}

/**********************************************************************
 * \brief   
 *          Interrupt trigger configuration
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  pstcAdtIrqTrigCfg Trigger configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_IrqTrigConfig(en_adt_unit_t enAdtUnit,
                              stc_adt_irq_trig_cfg_t* pstcAdtIrqTrigCfg)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (NULL == pstcAdtIrqTrigCfg))
    {
        return ErrorInvalidParameter;
    }
    
    pstcM0PAdt->CR_f.CMAE = pstcAdtIrqTrigCfg->bAdtCntMatchATrigEn;
    pstcM0PAdt->CR_f.CMBE = pstcAdtIrqTrigCfg->bAdtCntMatchBTrigEn;
    pstcM0PAdt->CR_f.CMCE = pstcAdtIrqTrigCfg->bAdtCntMatchCTrigEn;
    pstcM0PAdt->CR_f.CMDE = pstcAdtIrqTrigCfg->bAdtCntMatchDTrigEn;
    pstcM0PAdt->CR_f.OVFE = pstcAdtIrqTrigCfg->bAdtOverFlowTrigEn;
    pstcM0PAdt->CR_f.UDFE = pstcAdtIrqTrigCfg->bAdtUnderFlowTrigEn;
    pstcM0PAdt->CR_f.DMA_G_CMA = pstcAdtIrqTrigCfg->bAdtCntMatchATrigDmaEn;
    pstcM0PAdt->CR_f.DMA_G_CMB = pstcAdtIrqTrigCfg->bAdtCntMatchBTrigDmaEn;
    pstcM0PAdt->CR_f.DMA_G_CMC = pstcAdtIrqTrigCfg->bAdtCntMatchCTrigDmaEn;
    pstcM0PAdt->CR_f.DMA_G_CMD = pstcAdtIrqTrigCfg->bAdtCntMatchDTrigDmaEn;
    pstcM0PAdt->CR_f.DMA_G_OVF = pstcAdtIrqTrigCfg->bAdtOverFlowTrigDmaEn;
    pstcM0PAdt->CR_f.DMA_G_UDF = pstcAdtIrqTrigCfg->bAdtUnderFlowTrigDmaEn;
    pstcM0PAdt->CR_f.DMA_S_CMA = pstcAdtIrqTrigCfg->bAdtSpecilMatchATrigDmaEn;
    pstcM0PAdt->CR_f.DMA_S_CMB = pstcAdtIrqTrigCfg->bAdtSpecilMatchBTrigDmaEn;
    
    return Ok;
}

/*************************************************************************
 * \brief   
 *          Port trigger configuration
 *
 * \param   [in]  enAdtTrigPort         Trigger port
 * \param   [in]  pstcAdtPortTrigCfg    Trigger configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *************************************************************************/
en_result_t Adt_PortTrigConfig(en_adt_trig_port_t enAdtTrigPort,
                               stc_adt_port_trig_cfg_t* pstcAdtPortTrigCfg)
{
    if (NULL == pstcAdtPortTrigCfg)
    {
        return ErrorInvalidParameter;
    }

    switch (enAdtTrigPort)
    {
        case AdtTrigA:
            M0P_TIM4->TTRIG_f.TRIGAS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_TIM4->FCONR_f.NOFIENTA = pstcAdtPortTrigCfg->bFltEn;
            M0P_TIM4->FCONR_f.NOFICKTA = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigB:
            M0P_TIM4->TTRIG_f.TRIGBS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_TIM4->FCONR_f.NOFIENTB = pstcAdtPortTrigCfg->bFltEn;
            M0P_TIM4->FCONR_f.NOFICKTB = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigC:
            M0P_TIM4->TTRIG_f.TRIGCS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_TIM4->FCONR_f.NOFIENTC = pstcAdtPortTrigCfg->bFltEn;
            M0P_TIM4->FCONR_f.NOFICKTC = pstcAdtPortTrigCfg->enFltClk;
            break;

        case AdtTrigD:
            M0P_TIM4->TTRIG_f.TRIGDS = pstcAdtPortTrigCfg->enTrigSrc;
            M0P_TIM4->FCONR_f.NOFIENTD = pstcAdtPortTrigCfg->bFltEn;
            M0P_TIM4->FCONR_f.NOFICKTD = pstcAdtPortTrigCfg->enFltClk;
            break;

        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          CHxX port configuration
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtCHxXPort    CHxX port
 * \param   [in]  pstcAdtCHxXCfg   CHxX port configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *********************************************************************/
en_result_t Adt_CHxXPortConfig(en_adt_unit_t enAdtUnit,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                stc_adt_CHxX_port_cfg_t* pstcAdtCHxXCfg)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (NULL == pstcAdtCHxXCfg))
    {
        return ErrorInvalidParameter;
    }

    switch (enAdtCHxXPort)
    {
        case AdtCHxA:
            pstcM0PAdt->PCONR_f.CAPCA = pstcAdtCHxXCfg->enCap;
            pstcM0PAdt->PCONR_f.STACA = pstcAdtCHxXCfg->enStaOut;
            pstcM0PAdt->PCONR_f.STPCA = pstcAdtCHxXCfg->enStpOut;
            pstcM0PAdt->PCONR_f.STASTPSA = pstcAdtCHxXCfg->enStaStp;
            pstcM0PAdt->PCONR_f.CMPCA = pstcAdtCHxXCfg->enCmpc;
            pstcM0PAdt->PCONR_f.PERCA = pstcAdtCHxXCfg->enPerc;
            pstcM0PAdt->PCONR_f.OUTENA = pstcAdtCHxXCfg->bOutEn;
            pstcM0PAdt->PCONR_f.DISSELA = pstcAdtCHxXCfg->enDisSel;
            pstcM0PAdt->PCONR_f.DISVALA = pstcAdtCHxXCfg->enDisVal;
            pstcM0PAdt->FCONR_f.NOFIENGA = pstcAdtCHxXCfg->bFltEn;
            pstcM0PAdt->FCONR_f.NOFICKGA = pstcAdtCHxXCfg->enFltClk;
            break;

        case AdtCHxB:
            pstcM0PAdt->PCONR_f.CAPCB = pstcAdtCHxXCfg->enCap;
            pstcM0PAdt->PCONR_f.STACB = pstcAdtCHxXCfg->enStaOut;
            pstcM0PAdt->PCONR_f.STPCB = pstcAdtCHxXCfg->enStpOut;
            pstcM0PAdt->PCONR_f.STASTPSB = pstcAdtCHxXCfg->enStaStp;
            pstcM0PAdt->PCONR_f.CMPCB = pstcAdtCHxXCfg->enCmpc;
            pstcM0PAdt->PCONR_f.PERCB = pstcAdtCHxXCfg->enPerc;
            pstcM0PAdt->PCONR_f.OUTENB = pstcAdtCHxXCfg->bOutEn;
            pstcM0PAdt->PCONR_f.DISSELB = pstcAdtCHxXCfg->enDisSel;
            pstcM0PAdt->PCONR_f.DISVALB = pstcAdtCHxXCfg->enDisVal;
            pstcM0PAdt->FCONR_f.NOFIENGB = pstcAdtCHxXCfg->bFltEn;
            pstcM0PAdt->FCONR_f.NOFICKGB = pstcAdtCHxXCfg->enFltClk;
            break;

        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/************************************************************************
 * \brief   
 *          Enable port brake
 *
 * \param   [in]  port              port
 * \param   [in]  pstcAdtBrkPtCfg   Port brake configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ************************************************************************/
en_result_t Adt_EnableBrakePort(uint8_t port, stc_adt_break_port_cfg_t* pstcAdtBrkPtCfg)
{
    uint32_t u32Val;

    if (NULL == pstcAdtBrkPtCfg)
    {
        return ErrorInvalidParameter;
    }
    
    u32Val = M0P_TIM4->PTBKP;
    u32Val &= ~(1u<<port);
    M0P_TIM4->PTBKP = u32Val | (pstcAdtBrkPtCfg->enPol<<port);
    
    u32Val = M0P_TIM4->PTBKS;
    M0P_TIM4->PTBKS = u32Val | (1u<<port);

    return Ok;
}

/**********************************************************************
 * \brief   
 *          Clear port brake
 *
 * \param   none
 *
 * \retval  none
 **********************************************************************/
void Adt_ClearBrakePort(void)
{
    M0P_TIM4->PTBKS = 0;
}

/*********************************************************************
 * \brief   
 *          Invalid condition 3 configuration
 *
 * \param   [in]  pstcAdtDisable3   Invalid condition 3 configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ********************************************************************/
en_result_t Adt_Disable3Cfg(stc_adt_disable_3_cfg_t* pstcAdtDisable3)
{
    uint8_t i;

    if (NULL == pstcAdtDisable3)
    {
        return ErrorInvalidParameter;
    }

    Adt_ClearBrakePort();
    for (i = 0; i <= 15; i++)
    {
        if (TRUE == pstcAdtDisable3->stcBrkPtCfg[i].bPortEn)
        {
            Adt_EnableBrakePort(i, &pstcAdtDisable3->stcBrkPtCfg[i]);
        }
    }

    M0P_TIM4->AOSSR_f.BFILTEN = pstcAdtDisable3->bFltEn;
    M0P_TIM4->AOSSR_f.BFILTS = pstcAdtDisable3->enFltClk;
    M0P_TIM4->AOSSR_f.SOFTBK = pstcAdtDisable3->bSwBrk;

    return Ok;
}

/*******************************************************************
 * \brief   
 *          Get the port brake sign
 *
 * \param   none
 *
 * \retval  TRUE or FALSE
 ******************************************************************/
boolean_t Adt_GetPortBrakeFlag(void)
{
    return M0P_TIM4->AOSSR_f.FBRAKE;
}

/******************************************************************
 * \brief   
 *          Clear port brake flag clear port brake sign
 *
 * \param   none
 *
 * \retval  none
 ******************************************************************/
void Adt_ClearPortBrakeFlag(void)
{
    M0P_TIM4->AOSCL_f.FBRAKE = 0;
}

/********************************************************************
 * \brief   
 *          Invalid condition 1 configuration
 *
 * \param   [in]  pstcAdtDisable1   Invalid condition 1 configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ********************************************************************/
en_result_t Adt_Disable1Cfg(stc_adt_disable_1_cfg_t* pstcAdtDisable1)
{

    if (NULL == pstcAdtDisable1)
    {
        return ErrorInvalidParameter;
    }

    M0P_TIM4->AOSSR_f.SMH2 = pstcAdtDisable1->bTim6OutSH;
    M0P_TIM4->AOSSR_f.SMH1 = pstcAdtDisable1->bTim5OutSH;
    M0P_TIM4->AOSSR_f.SMH0 = pstcAdtDisable1->bTim4OutSH;
    M0P_TIM4->AOSSR_f.SML2 = pstcAdtDisable1->bTim6OutSL;
    M0P_TIM4->AOSSR_f.SML1 = pstcAdtDisable1->bTim5OutSL;
    M0P_TIM4->AOSSR_f.SML0 = pstcAdtDisable1->bTim4OutSL;

    return Ok;
}

/********************************************************************
 * \brief   
 *          Get the same high and low brake signs
 *
 * \param   none
 *
 * \retval  TRUE or FALSE
 ********************************************************************/
boolean_t Adt_GetSameBrakeFlag(void)
{
    return M0P_TIM4->AOSSR_f.FSAME;
}

/*********************************************************************
 * \brief   
 *          Clear the same high and low brake signs
 *
 * \param   none
 *
 * \retval  none
 *********************************************************************/
void Adt_ClearSameBrakeFlag(void)
{
    M0P_TIM4->AOSCL_f.FSAME = 0;
}

/********************************************************************
 * \brief   
 *          PWM spread spectrum configuration
 *
 * \param   [in]  pstcAdtPwmDitherCfg   PWM spread spectrum configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *********************************************************************/
en_result_t Adt_PwmDitherConfig(en_adt_unit_t enAdtUnit, stc_adt_pwm_dither_cfg_t* pstcAdtPwmDitherCfg)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);
    
    if (NULL == pstcAdtPwmDitherCfg)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->CR_f.DITENS = pstcAdtPwmDitherCfg->enAdtPDType;
    pstcM0PAdt->CR_f.DITENB = pstcAdtPwmDitherCfg->bTimxBPDEn;
    pstcM0PAdt->CR_f.DITENA = pstcAdtPwmDitherCfg->bTimxAPDEn;
    
    return Ok;
}

/**********************************************************************
 * \brief   
 *          ADT initialization
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  pstcAdtBaseCntCfg     Count configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 **********************************************************************/
en_result_t Adt_Init(en_adt_unit_t enAdtUnit, stc_adt_basecnt_cfg_t* pstcAdtBaseCntCfg)
{
    int32_t i;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (NULL == pstcAdtBaseCntCfg))
    {
        return ErrorInvalidParameter;
    }

    if (AdtTriangleModeB < pstcAdtBaseCntCfg->enCntMode)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->GCONR_f.MODE = pstcAdtBaseCntCfg->enCntMode;
    pstcM0PAdt->GCONR_f.DIR = pstcAdtBaseCntCfg->enCntDir;
    pstcM0PAdt->GCONR_f.CKDIV = pstcAdtBaseCntCfg->enCntClkDiv;

    for (i = 0; i < 16; i++)
    {
        pfnAdtIrqCbk[enAdtUnit][i] = NULL;
    }

    AdtEnableNvic((IRQn_Type)((int32_t)TIM4_IRQn + (int32_t)enAdtUnit));

    return Ok;
}

/************************************************************************
 * \brief   
 *          ADT Deinit
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_DeInit(en_adt_unit_t enAdtUnit)
{
    int32_t i;
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->GCONR_f.START = 0;

    AdtDisableNvic((IRQn_Type)((int32_t)TIM4_IRQn + (int32_t)enAdtUnit));

    for (i = 0; i < 16; i++)
    {
        pfnAdtIrqCbk[enAdtUnit][i] = NULL;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Start counting
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_StartCount(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->GCONR_f.START = 1;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Stop counting
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 **********************************************************************/
en_result_t Adt_StopCount(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->GCONR_f.START = 0;

    return Ok;
}

/********************************************************************
 * \brief   
 *          Set the count value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16Value          Count value
 *
 * \retval  en_result_t  Ok:  Success
 *                       ErrorInvalidParameter: Invalid parameter
 *******************************************************************/
en_result_t Adt_SetCount(en_adt_unit_t enAdtUnit, uint16_t u16Value)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->CNTER_f.CNT = u16Value;
    return Ok;
}

/********************************************************************
 * \brief   
 *          Get count value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16Value          Count value
 *
 * \retval  en_result_t  Ok:  Success
 *                       ErrorInvalidParameter: Invalid parameter
 *******************************************************************/
uint16_t Adt_GetCount(en_adt_unit_t enAdtUnit)
{
    uint16_t u16Value;
    
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    u16Value = pstcM0PAdt->CNTER_f.CNT;
    
    return u16Value;
}

/**************************************************************************
 * \brief   
 *          Clear count value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16Value          Count value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 **************************************************************************/
en_result_t Adt_ClearCount(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->CNTER_f.CNT = 0;
    return Ok;
}

/*************************************************************************
 * \brief   
 *          Get count status
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  pstcAdtCntState   Count status pointer 
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *************************************************************************/
en_result_t Adt_GetCntState(en_adt_unit_t enAdtUnit, stc_adt_cntstate_cfg_t* pstcAdtCntState)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (NULL == pstcAdtCntState))
    {
        return ErrorInvalidParameter;
    }

    pstcAdtCntState->u16Counter = pstcM0PAdt->CNTER_f.CNT;
    pstcAdtCntState->enCntDir = pstcM0PAdt->STFLR_f.DIRF;
    pstcAdtCntState->u8ValidPeriod = pstcM0PAdt->STFLR_f.VPERNUM;
    pstcAdtCntState->bCMSBDF = pstcM0PAdt->STFLR_f.CMSBDF;
    pstcAdtCntState->bCMSBUF = pstcM0PAdt->STFLR_f.CMSBUF;
    pstcAdtCntState->bCMSADF = pstcM0PAdt->STFLR_f.CMSADF;
    pstcAdtCntState->bCMSAUF = pstcM0PAdt->STFLR_f.CMSAUF;
    pstcAdtCntState->bDTEF = pstcM0PAdt->STFLR_f.DTEF;
    pstcAdtCntState->bUDFF = pstcM0PAdt->STFLR_f.UDFF;
    pstcAdtCntState->bOVFF = pstcM0PAdt->STFLR_f.OVFF;
    pstcAdtCntState->bCMDF = pstcM0PAdt->STFLR_f.CMDF;
    pstcAdtCntState->bCMCF = pstcM0PAdt->STFLR_f.CMCF;
    pstcAdtCntState->bCMBF = pstcM0PAdt->STFLR_f.CMBF;
    pstcAdtCntState->bCMAF = pstcM0PAdt->STFLR_f.CMAF;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Configuration count period
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16Period         Count period value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_SetPeriod(en_adt_unit_t enAdtUnit, uint16_t u16Period)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->PERAR = u16Period;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Configuration count period buffer
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16PeriodBuf          Count period buffer value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_SetPeriodBuf(en_adt_unit_t enAdtUnit, uint16_t u16PeriodBuf)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->PERBR = u16PeriodBuf;
    pstcM0PAdt->BCONR_f.BENP = 1u;

    return Ok;
}

/**********************************************************************
 * \brief   
 *          Clear count cycle buffer
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 **********************************************************************/
en_result_t Adt_ClearPeriodBuf(en_adt_unit_t enAdtUnit)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->BCONR_f.BENP = 0;
    pstcM0PAdt->PERBR = 0;

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Configure a valid count period
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  pstcAdtValidPerCfg            Valid count cycle configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_SetValidPeriod(en_adt_unit_t enAdtUnit,
                               stc_adt_validper_cfg_t* pstcAdtValidPerCfg)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (NULL == pstcAdtValidPerCfg))
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->VPERR_f.PCNTS = pstcAdtValidPerCfg->enValidCnt;
    pstcM0PAdt->VPERR_f.PCNTE = pstcAdtValidPerCfg->enValidCdt;
    pstcM0PAdt->VPERR_f.GEPERID = pstcAdtValidPerCfg->bPeriodD;
    pstcM0PAdt->VPERR_f.GEPERIC = pstcAdtValidPerCfg->bPeriodC;
    pstcM0PAdt->VPERR_f.GEPERIB = pstcAdtValidPerCfg->bPeriodB;
    pstcM0PAdt->VPERR_f.GEPERIA = pstcAdtValidPerCfg->bPeriodA;

    return Ok;
}

/************************************************************************
 * \brief   
 *          Configure comparison output count reference value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtCompare      比较基准  //Benchmark
 * \param   [in]  u16Compare        Comparison reference value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *************************************************************************/
en_result_t Adt_SetCompareValue(en_adt_unit_t enAdtUnit,
                                en_adt_compare_t enAdtCompare,
                                uint16_t u16Compare)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    if (AdtCompareA == enAdtCompare)
    {
        pstcM0PAdt->GCMAR = u16Compare;
    }
    else if (AdtCompareB == enAdtCompare)
    {
        pstcM0PAdt->GCMBR = u16Compare;
    }
    else if (AdtCompareC == enAdtCompare)
    {
        pstcM0PAdt->GCMCR = u16Compare;
    }
    else if (AdtCompareD == enAdtCompare)
    {
        pstcM0PAdt->GCMDR = u16Compare;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/************************************************************************
 * \brief   
 *          Configure a dedicated compare count reference value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtSpclCmp      Dedicated comparison reference register
 * \param   [in]  u16SpclCmp        Comparison reference value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *************************************************************************/
en_result_t Adt_SetSpecilCompareValue(en_adt_unit_t enAdtUnit,
                                      en_adt_special_compare_t enAdtSpclCmp,
                                      uint16_t u16SpclCmp)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    if (AdtSpclCompA == enAdtSpclCmp)
    {
        pstcM0PAdt->SCMAR_f.SCMA = u16SpclCmp;
    }
    else if (AdtSpclCompB == enAdtSpclCmp)
    {
        pstcM0PAdt->SCMBR_f.SCMB = u16SpclCmp;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**********************************************************************
 * \brief   
 *          Configuring general compare value / capture value cache transfer
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtCHxXPort    TIMxX port
 * \param   [in]  bCompareBufEn     General compare value cache transfer enable
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 **********************************************************************/
en_result_t Adt_EnableValueBuf(en_adt_unit_t enAdtUnit,
                                 en_adt_CHxX_port_t enAdtCHxXPort,
                                 boolean_t bCompareBufEn)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    if (AdtCHxA == enAdtCHxXPort)
    {
        pstcM0PAdt->BCONR_f.BENA = bCompareBufEn;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        pstcM0PAdt->BCONR_f.BENB = bCompareBufEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Clear compare output count value / capture value cache
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtCHxXPort    TIMxX port
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 **********************************************************************/
en_result_t Adt_ClearValueBuf(en_adt_unit_t enAdtUnit,
                                     en_adt_CHxX_port_t enAdtCHxXPort)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    if (AdtCHxA == enAdtCHxXPort)
    {
        pstcM0PAdt->GCMCR = 0;
        pstcM0PAdt->BCONR_f.BENA = 0;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        pstcM0PAdt->GCMDR = 0;
        pstcM0PAdt->BCONR_f.BENB = 0;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/***********************************************************************
 * \brief   
 *          Get the capture value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtCHxXPort    TIMxX port
 * \param   [in]  pu16Capture       Capture value pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_GetCaptureValue(en_adt_unit_t enAdtUnit,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16Capture)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    if (AdtCHxA == enAdtCHxXPort)
    {
        *pu16Capture = pstcM0PAdt->GCMAR_f.GCMA;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        *pu16Capture = pstcM0PAdt->GCMBR_f.GCMB;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}

/**********************************************************************
 * \brief   
 *          Get capture cache value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  enAdtCHxXPort    TIMxX port
 * \param   [in]  pu16CaptureBuf    Capture cache value pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_GetCaptureBuf(en_adt_unit_t enAdtUnit,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16CaptureBuf)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    if (AdtCHxA == enAdtCHxXPort)
    {
        *pu16CaptureBuf = pstcM0PAdt->GCMCR_f.GCMC;
    }
    else if (AdtCHxB == enAdtCHxXPort)
    {
        *pu16CaptureBuf = pstcM0PAdt->GCMDR_f.GCMD;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}

/***********************************************************************
 * \brief   
 *          Set the dead time time reference value
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16Value          Dead time time reference value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ************************************************************************/
en_result_t Adt_SetDTUA(en_adt_unit_t enAdtUnit,
                        uint16_t u16Value)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->DTUAR = u16Value;


    return Ok;
}

/***********************************************************************
 * \brief   
 *          Set the baseline value for dead time
 *
 * \param   [in]  enAdtUnit         ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  u16Value          Base time value
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 ***********************************************************************/
en_result_t Adt_SetDTDA(en_adt_unit_t enAdtUnit,
                        uint16_t u16Value)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->DTDAR = u16Value;


    return Ok;
}

/******************************************************************
 * \brief   
 *          Configure dead time function
 *
 * \param   [in]  enAdtUnit     ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  bDTEn         Dead zone function enable
 * \param   [in]  bEqual        The value of DTDAR and the value of DTUAR are automatically equal
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *****************************************************************/
en_result_t Adt_ConfigDT(en_adt_unit_t enAdtUnit,
                         boolean_t bDTEn,
                         boolean_t bEqual)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if (AdtTIM6 < enAdtUnit)
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->DCONR_f.DTCEN = bDTEn;
    pstcM0PAdt->DCONR_f.SEPA = bEqual;

    return Ok;
}

/*************************************************************************
 * \brief   
 *          Z phase input mask setting
 *
 * \param   [in]  enAdtUnit           ADV Timer channel selection (TIM4, TIM5, TIM6)
 * \param   [in]  pstcAdtZMaskCfg     Z phase input mask function configuration pointer
 *
 * \retval  en_result_t  Ok:  Success
 * \retval  en_result_t  ErrorInvalidParameter: Invalid parameter
 *************************************************************************/
en_result_t Adt_ConfigZMask(en_adt_unit_t enAdtUnit, stc_adt_zmask_cfg_t* pstcAdtZMaskCfg)
{
    volatile M0P_TIM4_TypeDef *pstcM0PAdt = (M0P_TIM4_TypeDef *)((uint32_t)M0P_TIM4+0x400*enAdtUnit);

    if ((AdtTIM6 < enAdtUnit) || (NULL == pstcAdtZMaskCfg))
    {
        return ErrorInvalidParameter;
    }

    pstcM0PAdt->GCONR_f.ZMSK = pstcAdtZMaskCfg->enZMaskCycle;
    pstcM0PAdt->GCONR_f.ZMSKPOS = pstcAdtZMaskCfg->bFltPosCntMaksEn;
    pstcM0PAdt->GCONR_f.ZMSKREV = pstcAdtZMaskCfg->bFltRevCntMaksEn;

    return Ok;
}

//@} // AdtGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


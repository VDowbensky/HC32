/******************************************************************************
*Copyright(C)2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
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

/** \file bt.c
 **
 ** Common API of base timer.
 ** @link btGroup Some description @endlink
 **
 **   - 2018-04-18    First Version
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "bt.h"
/**
 *******************************************************************************
 ** \addtogroup BtGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_TIM(x)         (TIM0 == (x) ||\
                                 TIM1 == (x) ||\
                                 TIM2 == (x))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static func_ptr_t pfnTim0Callback = NULL;
static func_ptr_t pfnTim1Callback = NULL;
static func_ptr_t pfnTim2Callback = NULL;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *****************************************************************************
 ** \brief Basic Timer Interrupt flag acquisition (mode 0/1/23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enTim3Irq        Interrupt type
 ** 
 ** \retval TRUE or FALSE                                      
 *****************************************************************************/
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    boolean_t bRetVal = FALSE;
    uint32_t u32Val;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    u32Val = pstcM0PBt->IFR;
    bRetVal = (u32Val>>enBtIrq) & 0x1;

    return bRetVal;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt flag clear (mode 0/1/23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enTim3Irq        Interrupt type
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ICLR = ~(1u<<enBtIrq);
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt all flag clear (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_ClearAllIntFlag(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ICLR_f.UIF  = 0;
    pstcM0PBt->ICLR_f.CA0F = 0;
    pstcM0PBt->ICLR_f.CB0F = 0;
    pstcM0PBt->ICLR_f.BIF  = 0;
    pstcM0PBt->ICLR_f.TIF  = 0;
    pstcM0PBt->ICLR_f.CA0E = 0;
    pstcM0PBt->ICLR_f.CB0E = 0;
    
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt enable (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode0_EnableIrq(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.UIE = TRUE;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt disable (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode0_DisableIrq(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.UIE = FALSE;

    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt enable (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enTim3Irq        Interrupt type
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode1_EnableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enBtIrq)
    {
        case BtUevIrq:
            pstcM0PBt->M1CR_f.UIE = TRUE;
            break;
        case BtCA0Irq:
            pstcM0PBt->CR0_f.CIEA = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt disable (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enTim3Irq        Interrupt type
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode1_DisableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
        
    switch (enBtIrq)
    {
        case BtUevIrq:
            pstcM0PBt->M1CR_f.UIE = FALSE;
            break;
        case BtCA0Irq:
            pstcM0PBt->CR0_f.CIEA = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt enable (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
  ** \param [in]  enTim3Irq       Interrupt type
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode23_EnableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    
    switch (enBtIrq)
    {
        case BtUevIrq:
            pstcM0PBt->M23CR_f.UIE = TRUE;
            break;
        case BtCA0Irq:
            pstcM0PBt->CRCH0_f.CIEA = TRUE;
            break;
        case BtCB0Irq:
            pstcM0PBt->CRCH0_f.CIEB = TRUE;
            break;
        case BtBkIrq:
            pstcM0PBt->M23CR_f.BIE = TRUE;
            break;
        case BtTrigIrq:
            pstcM0PBt->M23CR_f.TIE = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt disable (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enTim3Irq        Interrupt type
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode23_DisableIrq (en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
        
    switch (enBtIrq)
    {
        case BtUevIrq:
            pstcM0PBt->M23CR_f.UIE = FALSE;
            break;
        case BtCA0Irq:
            pstcM0PBt->CRCH0_f.CIEA = FALSE;
            break;
        case BtCB0Irq:
            pstcM0PBt->CRCH0_f.CIEB = FALSE;
            break;
        case BtBkIrq:
            pstcM0PBt->M23CR_f.BIE = FALSE;
            break;
        case BtTrigIrq:
            pstcM0PBt->M23CR_f.TIE = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Interrupt service function
 **
 **
 ** \param [in]  u8Param           Timer channel selection (0 - TIM0, 1 - TIM1, 2 - TIM2)
 ** 
 ** \retval NULL                                     
 *****************************************************************************/
void Tim_IRQHandler(uint8_t u8Param)
{
    switch (u8Param)
    {
        case 0:
            if(NULL != pfnTim0Callback)
            {
                pfnTim0Callback();
            }
            break;
        case 1:
            if(NULL != pfnTim1Callback)
            {
                pfnTim1Callback();
            }
            break;
        case 2:
            if(NULL != pfnTim2Callback)
            {
                pfnTim2Callback();
            }
            break;
        default:
            ;
            break;       
    }
}



/**
 *****************************************************************************
 ** \brief Base Timer Initial configuration (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization structure pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode0_Init(en_bt_unit_t enUnit, stc_bt_mode0_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            {
                M0P_TIM0_MODE0->M0CR_f.MODE   = pstcConfig->enWorkMode;
                M0P_TIM0_MODE0->M0CR_f.GATEP  = pstcConfig->enGateP;
                M0P_TIM0_MODE0->M0CR_f.GATE   = pstcConfig->bEnGate;
                M0P_TIM0_MODE0->M0CR_f.PRS    = pstcConfig->enPRS;
                M0P_TIM0_MODE0->M0CR_f.TOGEN  = pstcConfig->bEnTog;
                M0P_TIM0_MODE0->M0CR_f.CT     = pstcConfig->enCT;
                M0P_TIM0_MODE0->M0CR_f.MD     = pstcConfig->enCntMode; 
                
                pfnTim0Callback      = pstcConfig->pfnTim0Cb;
            }
            break;
        case TIM1:
            {
                M0P_TIM1_MODE0->M0CR_f.MODE   = pstcConfig->enWorkMode;
                M0P_TIM1_MODE0->M0CR_f.GATEP  = pstcConfig->enGateP;
                M0P_TIM1_MODE0->M0CR_f.GATE   = pstcConfig->bEnGate;
                M0P_TIM1_MODE0->M0CR_f.PRS    = pstcConfig->enPRS;
                M0P_TIM1_MODE0->M0CR_f.TOGEN  = pstcConfig->bEnTog;
                M0P_TIM1_MODE0->M0CR_f.CT     = pstcConfig->enCT;
                M0P_TIM1_MODE0->M0CR_f.MD     = pstcConfig->enCntMode;
                
                pfnTim1Callback      = pstcConfig->pfnTim1Cb;
            }
            break;
        case TIM2:
            {
                M0P_TIM2_MODE0->M0CR_f.MODE   = pstcConfig->enWorkMode;
                M0P_TIM2_MODE0->M0CR_f.GATEP  = pstcConfig->enGateP;
                M0P_TIM2_MODE0->M0CR_f.GATE   = pstcConfig->bEnGate;
                M0P_TIM2_MODE0->M0CR_f.PRS    = pstcConfig->enPRS;
                M0P_TIM2_MODE0->M0CR_f.TOGEN  = pstcConfig->bEnTog;
                M0P_TIM2_MODE0->M0CR_f.CT     = pstcConfig->enCT;
                M0P_TIM2_MODE0->M0CR_f.MD     = pstcConfig->enCntMode;
                
                pfnTim2Callback      = pstcConfig->pfnTim2Cb;

            }
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Start running (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M0_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Stop running (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M0_Stop(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief Base Timer Flip output enable/disable setting (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  bEnOutput        Flip output setting TRUE: enable, FALSE: disable
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M0_EnTOG_Output(en_bt_unit_t enUnit, boolean_t bEnOutput)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.MOE = bEnOutput;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer 16-bit counter initial value setting (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u16Data          16-bit initial value
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M0_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0_MODE0->CNT_f.CNT = u16Data;
            break;
        case TIM1:
            M0P_TIM1_MODE0->CNT_f.CNT = u16Data;
            break;
        case TIM2:
            M0P_TIM2_MODE0->CNT_f.CNT = u16Data;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer 16-bit count value acquisition (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval 16bits count value                                   
 *****************************************************************************/
uint16_t Bt_M0_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            u16CntData = M0P_TIM0_MODE0->CNT_f.CNT;
            break;
        case TIM1:
            u16CntData = M0P_TIM1_MODE0->CNT_f.CNT;
            break;
        case TIM2:
            u16CntData = M0P_TIM2_MODE0->CNT_f.CNT;
            break;
        default:
            u16CntData = 0;
            break;
    }
    
    return u16CntData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer reload value setting (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u16Data          16bits reload value
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M0_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0_MODE0->ARR_f.ARR = u16Data;
            break;
        case TIM1:
            M0P_TIM1_MODE0->ARR_f.ARR = u16Data;
            break;
        case TIM2:
            M0P_TIM2_MODE0->ARR_f.ARR = u16Data;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer 32-bit counter initial value setting (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u32Data          32-bit initial value
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M0_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data)
{
    en_result_t enResult = Ok;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0_MODE0->CNT32_f.CNT32 = u32Data;
            break;
        case TIM1:
            M0P_TIM1_MODE0->CNT32_f.CNT32 = u32Data;
            break;
        case TIM2:
            M0P_TIM2_MODE0->CNT32_f.CNT32 = u32Data;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer 32-bit count value acquisition (mode 0)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval 32bits count value                                    
 *****************************************************************************/
uint32_t Bt_M0_Cnt32Get(en_bt_unit_t enUnit)
{
    uint32_t    u32CntData = 0;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            u32CntData = M0P_TIM0_MODE0->CNT32_f.CNT32;
            break;
        case TIM1:
            u32CntData = M0P_TIM1_MODE0->CNT32_f.CNT32;
            break;
        case TIM2:
            u32CntData = M0P_TIM2_MODE0->CNT32_f.CNT32;
            break;
        default:
            u32CntData = 0;
            break;
    }
    
    return u32CntData;
}

/**
 *****************************************************************************
 ** \brief Base Timer Initial configuration (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode1_Init(en_bt_unit_t enUnit, stc_bt_mode1_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            {
                M0P_TIM0_MODE1->M1CR_f.MODE    = pstcConfig->enWorkMode;
                M0P_TIM0_MODE1->M1CR_f.PRS     = pstcConfig->enPRS;
                M0P_TIM0_MODE1->M1CR_f.CT      = pstcConfig->enCT;
                M0P_TIM0_MODE1->M1CR_f.ONESHOT = pstcConfig->enOneShot;
                
                pfnTim0Callback      = pstcConfig->pfnTim0Cb;
            }
            break;
        case TIM1:
            {
                M0P_TIM1_MODE1->M1CR_f.MODE    = pstcConfig->enWorkMode;
                M0P_TIM1_MODE1->M1CR_f.PRS     = pstcConfig->enPRS;
                M0P_TIM1_MODE1->M1CR_f.CT      = pstcConfig->enCT;
                M0P_TIM1_MODE1->M1CR_f.ONESHOT = pstcConfig->enOneShot;
                
                pfnTim1Callback      = pstcConfig->pfnTim1Cb;
            }
            break;
        case TIM2:
            {
                M0P_TIM2_MODE1->M1CR_f.MODE    = pstcConfig->enWorkMode;
                M0P_TIM2_MODE1->M1CR_f.PRS     = pstcConfig->enPRS;
                M0P_TIM2_MODE1->M1CR_f.CT      = pstcConfig->enCT;
                M0P_TIM2_MODE1->M1CR_f.ONESHOT = pstcConfig->enOneShot;
                
                pfnTim2Callback      = pstcConfig->pfnTim2Cb;
            }
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer PWC input configuration (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M1_Input_Config(en_bt_unit_t enUnit, stc_bt_pwc_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->MSCR_f.TS    = pstcConfig->enTsSel;
    pstcM0PBt->MSCR_f.IA0S  = pstcConfig->enIA0Sel;
    pstcM0PBt->MSCR_f.IB0S  = pstcConfig->enIB0Sel;
    pstcM0PBt->FLTR_f.ETP   = pstcConfig->enETRPhase;
    pstcM0PBt->FLTR_f.FLTET = pstcConfig->enFltETR;
    pstcM0PBt->FLTR_f.FLTA0 = pstcConfig->enFltIA0;
    pstcM0PBt->FLTR_f.FLTB0 = pstcConfig->enFltIB0;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer PWC measurement edge start end selection (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enEdgeSel        Pwc measurement start termination level
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M1_PWC_Edge_Sel(en_bt_unit_t enUnit,en_bt_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enEdgeSel)
    {
        case 0:                            ///< rising edge to rising edge (period)
            pstcM0PBt->M1CR_f.EDG1ST = 0;  //Rising edge
            pstcM0PBt->M1CR_f.EDG2ND = 0;  //Rising edge
            break;
        case 1:                            ///< Falling edge to Rising edge(Low level)
            pstcM0PBt->M1CR_f.EDG1ST = 1;  //Falling edge
            pstcM0PBt->M1CR_f.EDG2ND = 0;  //Rising edge
            break;
        case 2:                            ///< Rising edge to Falling edge(High level)
            pstcM0PBt->M1CR_f.EDG1ST = 0;  //Rising edge
            pstcM0PBt->M1CR_f.EDG2ND = 1;  //Falling edge
            break;
        case 3:                            ///< Falling edge to Falling edge(cycle)
            pstcM0PBt->M1CR_f.EDG1ST = 1;  //Falling edge
            pstcM0PBt->M1CR_f.EDG2ND = 1;  //Falling edge
            break;
        default:
            ;
            break;       
    }
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Start running (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M1_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M1CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Stop running (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M1_Stop(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M1CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief Base Timer 16-bit counter initial value setting (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u16Data          16-bit initial value
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M1_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            M0P_TIM0_MODE1->CNT_f.CNT = u16Data;
            break;
        case TIM1:
            M0P_TIM1_MODE1->CNT_f.CNT = u16Data;
            break;
        case TIM2:
            M0P_TIM2_MODE1->CNT_f.CNT = u16Data;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer 16-bit count value acquisition (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval 16bits count value                                    
 *****************************************************************************/
uint16_t Bt_M1_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            u16CntData = M0P_TIM0_MODE1->CNT_f.CNT;
            break;
        case TIM1:
            u16CntData = M0P_TIM1_MODE1->CNT_f.CNT;
            break;
        case TIM2:
            u16CntData = M0P_TIM2_MODE1->CNT_f.CNT;
            break;
        default:
            u16CntData = 0;
            break;
    }
    
    return u16CntData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer Pulse width measurement result value acquisition (mode 1)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval 16bits pulse width measurement result                                     
 *****************************************************************************/
uint16_t Bt_M1_PWC_CapValueGet(en_bt_unit_t enUnit)
{
    uint16_t    u16CapData = 0;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            u16CapData = M0P_TIM0_MODE1->CCR0A_f.CCR0A;
            break;
        case TIM1:
            u16CapData = M0P_TIM1_MODE1->CCR0A_f.CCR0A;
            break;
        case TIM2:
            u16CapData = M0P_TIM2_MODE1->CCR0A_f.CCR0A;
            break;
        default:
            u16CapData = 0;
            break;
    }
    
    return u16CapData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer Initial configuration (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_Mode23_Init(en_bt_unit_t enUnit, stc_bt_mode23_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enUnit)
    {
        case TIM0:
            {
                M0P_TIM0_MODE23->M23CR_f.MODE    = pstcConfig->enWorkMode;
                
                M0P_TIM0_MODE23->M23CR_f.PRS     = pstcConfig->enPRS;
                M0P_TIM0_MODE23->M23CR_f.CT      = pstcConfig->enCT;
                M0P_TIM0_MODE23->M23CR_f.COMP    = pstcConfig->enPWMTypeSel;
                M0P_TIM0_MODE23->M23CR_f.PWM2S   = pstcConfig->enPWM2sSel;
                M0P_TIM0_MODE23->M23CR_f.ONESHOT = pstcConfig->bOneShot;
                M0P_TIM0_MODE23->M23CR_f.URS     = pstcConfig->bURSSel;
                M0P_TIM0_MODE23->M23CR_f.DIR     = pstcConfig->enCntDir;
                
                pfnTim0Callback      = pstcConfig->pfnTim0Cb;
            }
            break;
        case TIM1:
            {
                M0P_TIM1_MODE23->M23CR_f.MODE    = pstcConfig->enWorkMode;
                
                M0P_TIM1_MODE23->M23CR_f.PRS     = pstcConfig->enPRS;
                M0P_TIM1_MODE23->M23CR_f.CT      = pstcConfig->enCT;
                M0P_TIM1_MODE23->M23CR_f.COMP    = pstcConfig->enPWMTypeSel;
                M0P_TIM1_MODE23->M23CR_f.PWM2S   = pstcConfig->enPWM2sSel;
                M0P_TIM1_MODE23->M23CR_f.ONESHOT = pstcConfig->bOneShot;
                M0P_TIM1_MODE23->M23CR_f.URS     = pstcConfig->bURSSel;
                M0P_TIM1_MODE23->M23CR_f.DIR     = pstcConfig->enCntDir;
                
                pfnTim1Callback      = pstcConfig->pfnTim1Cb;
            }
            break;
        case TIM2:
            {
                M0P_TIM2_MODE23->M23CR_f.MODE    = pstcConfig->enWorkMode;
                
                M0P_TIM2_MODE23->M23CR_f.PRS     = pstcConfig->enPRS;
                M0P_TIM2_MODE23->M23CR_f.CT      = pstcConfig->enCT;
                M0P_TIM2_MODE23->M23CR_f.COMP    = pstcConfig->enPWMTypeSel;
                M0P_TIM2_MODE23->M23CR_f.PWM2S   = pstcConfig->enPWM2sSel;
                M0P_TIM2_MODE23->M23CR_f.ONESHOT = pstcConfig->bOneShot;
                M0P_TIM2_MODE23->M23CR_f.URS     = pstcConfig->bURSSel;
                M0P_TIM2_MODE23->M23CR_f.DIR     = pstcConfig->enCntDir;
                
                pfnTim2Callback      = pstcConfig->pfnTim2Cb;
            }
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer PWM output enable/disable (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  bEnOutput        PWM output enable/disable setting
 ** \param [in]  bEnAutoOutput    PWM automatic output enable/disable setting
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnPWM_Output(en_bt_unit_t enUnit, boolean_t bEnOutput, boolean_t bEnAutoOutput)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.MOE = bEnOutput;
    pstcM0PBt->DTR_f.AOE = bEnAutoOutput;
    
    return enResult;
}


/**
 *****************************************************************************
 ** \brief Base Timer Start running (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.CTEN = TRUE;
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Stop running (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_Stop(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
 *****************************************************************************
 ** \brief Base Timer reload value setting (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u16Data          16bits reload value
 ** \param [in]  bArrBufEn        ARR reload cache enable TRUE / disable FALSE
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data, boolean_t bArrBufEn)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
     pstcM0PBt->ARR_f.ARR = u16Data;
     pstcM0PBt->M23CR_f.BUFPEN  = bArrBufEn;

    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer 16-bit counter initial value setting (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u16Data          16-bit initial value
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CNT_f.CNT       = u16Data;

    return enResult; 
}

/**
 *****************************************************************************
 ** \brief Base Timer 16-bit count value acquisition (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval 16bits count value                                    
 *****************************************************************************/
uint16_t Bt_M23_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    u16CntData = pstcM0PBt->CNT_f.CNT;
    
    return u16CntData; 
}

/**
 *****************************************************************************
 ** \brief Base Timer Compare Capture Register CCR0A/CCR0B Settings (Mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enCCRSel         CCR0A/CCR0B setting
 ** \param [in]  u16Data          CCR0A/CCR0B 16-bit initial value
 ** 
 ** \retval Ok or Error                                     
 *****************************************************************************/
en_result_t Bt_M23_CCR_Set(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    if(BtCCR0A == enCCRSel)
    {
        pstcM0PBt->CCR0A_f.CCR0A = u16Data;
    }
    else if(BtCCR0B == enCCRSel)
    {
        pstcM0PBt->CCR0B_f.CCR0B = u16Data;
    }
    else
    {
        enResult = Error;
    }
    
    return enResult;
}

/**
 *****************************************************************************
 ** \brief Base Timer Compare capture register CCR0A/CCR0B read (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  enCCRSel         CCR0A/CCR0B setting
 ** 
 ** \retval 16bitsCCR0A capture value                                   
 *****************************************************************************/
uint16_t Bt_M23_CCR_Get(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel)
{
    uint16_t    u16Data = 0;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));

    if(BtCCR0A == enCCRSel)
    {
        u16Data = pstcM0PBt->CCR0A_f.CCR0A;
    }
    else if(BtCCR0B == enCCRSel)
    {
        u16Data = pstcM0PBt->CCR0B_f.CCR0B;
    }
    else
    {
        u16Data = 0;
    }
    
    return u16Data; 
}

/**
 *****************************************************************************
 ** \brief Base Timer GATE function selection in PWM complementary output mode (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_GateFuncSel(en_bt_unit_t enUnit,stc_bt_m23_gate_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.CSG = pstcConfig->enGateFuncSel;
    pstcM0PBt->M23CR_f.CRG = pstcConfig->bGateRiseCap;
    pstcM0PBt->M23CR_f.CFG = pstcConfig->bGateFallCap;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Master-slave mode configuration (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_MasterSlave_Set(en_bt_unit_t enUnit, stc_bt_m23_master_slave_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->MSCR_f.MSM = pstcConfig->enMasterSlaveSel;
    pstcM0PBt->MSCR_f.MMS = pstcConfig->enMasterSrc;
    pstcM0PBt->MSCR_f.SMS = pstcConfig->enSlaveModeSel;
    pstcM0PBt->MSCR_f.TS  = pstcConfig->enTsSel;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer CH0A/CH0B comparison channel output control (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_PortOutput_Config(en_bt_unit_t enUnit, stc_bt_m23_compare_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CSA         = 0;
    pstcM0PBt->FLTR_f.OCMA0_FLTA0  = pstcConfig->enCH0ACmpCtrl;
    pstcM0PBt->FLTR_f.CCPA0        = pstcConfig->enCH0APolarity;
    pstcM0PBt->CRCH0_f.BUFEA       = pstcConfig->bCh0ACmpBufEn;
    pstcM0PBt->M23CR_f.CIS         = pstcConfig->enCh0ACmpIntSel;
    
    pstcM0PBt->CRCH0_f.CSB         = 0;
    pstcM0PBt->FLTR_f.OCMB0_FLTB0  = pstcConfig->enCH0BCmpCtrl;
    pstcM0PBt->FLTR_f.CCPB0        = pstcConfig->enCH0BPolarity;
    pstcM0PBt->CRCH0_f.BUFEB       = pstcConfig->bCH0BCmpBufEn;
    pstcM0PBt->CRCH0_f.CISB        = pstcConfig->enCH0BCmpIntSel;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer CH0A/CH0B input control (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_PortInput_Config(en_bt_unit_t enUnit, stc_bt_m23_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CSA           = 1;
    pstcM0PBt->CRCH0_f.CFA_CRA_BKSA  = pstcConfig->enCH0ACapSel;
    pstcM0PBt->FLTR_f.OCMA0_FLTA0    = pstcConfig->enCH0AInFlt;
    pstcM0PBt->FLTR_f.CCPA0          = pstcConfig->enCH0APolarity;
    
    pstcM0PBt->CRCH0_f.CSB           = 1;
    pstcM0PBt->CRCH0_f.CFB_CRB_BKSB  = pstcConfig->enCH0BCapSel;
    pstcM0PBt->FLTR_f.OCMB0_FLTB0    = pstcConfig->enCH0BInFlt;
    pstcM0PBt->FLTR_f.CCPB0          = pstcConfig->enCH0BPolarity;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer ERT input control (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_ETRInput_Config(en_bt_unit_t enUnit, stc_bt_m23_etr_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->FLTR_f.ETP    = pstcConfig->enETRPolarity;
    pstcM0PBt->FLTR_f.FLTET  = pstcConfig->enETRFlt;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Brake BK input control (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_BrakeInput_Config(en_bt_unit_t enUnit, stc_bt_m23_bk_input_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.BKE             = pstcConfig->bEnBrake;
    pstcM0PBt->DTR_f.VC0E            = pstcConfig->bEnVC0Brake;
    pstcM0PBt->DTR_f.VC1E            = pstcConfig->bEnVC1Brake;
    pstcM0PBt->DTR_f.SAFEEN          = pstcConfig->bEnSafetyBk;
    pstcM0PBt->DTR_f.BKSEL           = pstcConfig->bEnBKSync;
    pstcM0PBt->CRCH0_f.CFA_CRA_BKSA  = pstcConfig->enBkCH0AStat;
    pstcM0PBt->CRCH0_f.CFB_CRB_BKSB  = pstcConfig->enBkCH0BStat;
    pstcM0PBt->FLTR_f.BKP            = pstcConfig->enBrakePolarity;
    pstcM0PBt->FLTR_f.FLTBK          = pstcConfig->enBrakeFlt;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Trigger ADC Control (Mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_TrigADC_Config(en_bt_unit_t enUnit, stc_bt_m23_adc_trig_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ADTR_f.ADTE   = pstcConfig->bEnTrigADC;
    pstcM0PBt->ADTR_f.UEVE   = pstcConfig->bEnUevTrigADC;
    pstcM0PBt->ADTR_f.CMA0E  = pstcConfig->bEnCH0ACmpTrigADC;
    pstcM0PBt->ADTR_f.CMB0E  = pstcConfig->bEnCH0BCmpTrigADC;
    
    return enResult;    
}

/**
 *****************************************************************************
** \brief Base Timer Dead zone function (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_DT_Config(en_bt_unit_t enUnit, stc_bt_m23_dt_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.DTEN = pstcConfig->bEnDeadTime;
    pstcM0PBt->DTR_f.DTR  = pstcConfig->u8DeadTimeValue;
    
    return enResult;    
}

/**
 *****************************************************************************
** \brief Base Timer Repeat cycle setting (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  u8ValidPeriod    Repeat period value
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_SetValidPeriod(en_bt_unit_t enUnit, uint8_t u8ValidPeriod)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->RCR_f.RCR = u8ValidPeriod;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer OCREF clear function (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_OCRefClr(en_bt_unit_t enUnit, stc_bt_m23_OCREF_Clr_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.OCCS = pstcConfig->enOCRefClrSrcSel;
    pstcM0PBt->M23CR_f.OCCE = pstcConfig->bVCClrEn;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Enable DMA transfer (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** \param [in]  pstcConfig       Initialization struture pointer
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnDMA(en_bt_unit_t enUnit, stc_bt_m23_trig_dma_config_t* pstcConfig)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.UDE  = pstcConfig->bUevTrigDMA;
    pstcM0PBt->M23CR_f.TDE  = pstcConfig->bTITrigDMA;
    pstcM0PBt->CRCH0_f.CDEA = pstcConfig->bCmpATrigDMA;
    pstcM0PBt->CRCH0_f.CDEB = pstcConfig->bCmpBTrigDMA;
    pstcM0PBt->MSCR_f.CCDS  = pstcConfig->enCmpUevTrigDMA;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Capture Compare A Software Trigger (Mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnSwTrigCapCmpA(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CCGA = TRUE;

    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Capture Compare B Software Trigger (Mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnSwTrigCapCmpB(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CCGB = TRUE;

    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Software update enable (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnSwUev(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.UG = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Software Trigger Enable (Mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnSwTrig(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.TG = TRUE;
    
    return enResult;    
}

/**
 *****************************************************************************
 ** \brief Base Timer Software brake enable (mode 23)
 **
 **
 ** \param [in]  enUnit           Timer channel selection (TIM0, TIM1, TIM2)
 ** 
 ** \retval Ok or Error                                      
 *****************************************************************************/
en_result_t Bt_M23_EnSwBk(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.BG = TRUE;
    
    return enResult;    
}

//@} // BtGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

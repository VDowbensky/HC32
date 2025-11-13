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
 * @file   timer3.c
 *
 * @brief  Source file for TIMER3 functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "timer3.h"
/**
 *******************************************************************************
 ** \addtogroup Tim3Group
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/


/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
*****************************************************************************
** \brief Timer3 Interrupt Flag Get (Mode 0/1/23)
**
**
** \param [in] enTim3Irq Interrupt Type
**
** \retval TRUE or FALSE
*****************************************************************************/
boolean_t Tim3_GetIntFlag(en_tim3_irq_type_t enTim3Irq)
{
    boolean_t bRetVal = FALSE;
    uint32_t u32Val;
        
    u32Val = M0P_TIM3_MODE23->IFR;
    bRetVal = (u32Val>>enTim3Irq) & 0x1;

    return bRetVal;
}

/**
***********************************************************************
** \brief Timer3 interrupt flag clear (mode 0/1/23)
**
** \param [in] enTim3Irq interrupt type
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_ClearIntFlag(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->ICLR = ~(1u<<enTim3Irq);
    
    return enResult;
}

/**
***************************************************************************
** \brief Timer3 interrupt all flags clear (mode 23)
** 
** 
** 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_ClearAllIntFlag(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE23->ICLR = 0;
    
    return enResult;
}

/** 
******************************************************************************* 
** \brief Timer3 interrupt enable (mode 0) 
** 
** 
** \param [in] none 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_Mode0_EnableIrq(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE0->M0CR_f.UIE = TRUE;

    return enResult;
}

/**
*************************************************************************
** \brief Timer3 interrupt disable (mode 0)
**
**
** \param [in] none
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_Mode0_DisableIrq(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE0->M0CR_f.UIE = FALSE;

    return enResult;
}

/**
*************************************************************************
** \brief Timer3 interrupt enable (mode 1)
**
**
** \param [in] enTim3Irq interrupt type
**
** \retval Ok or Error
******************************************************************************/
en_result_t Tim3_Mode1_EnableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE1->M1CR_f.UIE = TRUE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE1->CR0_f.CIEA = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/** 
******************************************************************************* 
** \brief Timer3 interrupt disable (mode 1) 
** 
** 
** \param [in] enTim3Irq interrupt type 
** 
** \retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_Mode1_DisableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE1->M1CR_f.UIE = FALSE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE1->CR0_f.CIEA = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/** 
******************************************************************************* 
** \brief Timer3 interrupt enable (mode 23) 
** 
** 
** \param [in] enTim3Irq interrupt type 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_Mode23_EnableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE23->M23CR_f.UIE = TRUE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEA = TRUE;
            break;
        case Tim3CB0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEB = TRUE;
            break;
        case Tim3CA1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEA = TRUE;
            break;
        case Tim3CB1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEB = TRUE;
            break;
        case Tim3CA2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEA = TRUE;
            break;
        case Tim3CB2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEB = TRUE;
            break;
        case Tim3BkIrq:
            M0P_TIM3_MODE23->M23CR_f.BIE = TRUE;
            break;
        case Tim3TrigIrq:
            M0P_TIM3_MODE23->M23CR_f.TIE = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/** 
******************************************************************************* 
** \brief Timer3 interrupt disable (mode 23) 
** 
** 
** \param [in] enTim3Irq interrupt type 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_Mode23_DisableIrq (en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;
    
        
    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE23->M23CR_f.UIE = FALSE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEA = FALSE;
            break;
        case Tim3CB0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEB = FALSE;
            break;
        case Tim3CA1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEA = FALSE;
            break;
        case Tim3CB1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEB = FALSE;
            break;
        case Tim3CA2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEA = FALSE;
            break;
        case Tim3CB2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEB = FALSE;
            break;
        case Tim3BkIrq:
            M0P_TIM3_MODE23->M23CR_f.BIE = FALSE;
            break;
        case Tim3TrigIrq:
            M0P_TIM3_MODE23->M23CR_f.TIE = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }
    
    return enResult;
}

/**
***********************************************************************
** \brief Timer3 initialization configuration (mode 0)
**
**
** \param [in] pstcCfg initialization configuration structure pointer
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_Mode0_Init(stc_tim3_mode0_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    M0P_TIM3_MODE0->M0CR_f.MODE   = pstcCfg->enWorkMode;
    M0P_TIM3_MODE0->M0CR_f.GATEP  = pstcCfg->enGateP;
    M0P_TIM3_MODE0->M0CR_f.GATE   = pstcCfg->bEnGate;
    M0P_TIM3_MODE0->M0CR_f.PRS    = pstcCfg->enPRS;
    M0P_TIM3_MODE0->M0CR_f.TOGEN  = pstcCfg->bEnTog;
    M0P_TIM3_MODE0->M0CR_f.CT     = pstcCfg->enCT;
    M0P_TIM3_MODE0->M0CR_f.MD     = pstcCfg->enCntMode; 
    
    return enResult;
}

/** 
******************************************************************************* 
** \brief Timer3 starts running (mode 0) 
** ** 
** \param [in] none 
** 
**\retval Ok or Error
*******************************************************************************/
en_result_t Tim3_M0_Run(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE0->M0CR_f.CTEN = TRUE;
    
    return enResult;    
}

/** 
******************************************************************************* 
** \brief Timer3 stop running (mode 0) 
** 
** 
** \param [in] none 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M0_Stop(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE0->M0CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
***********************************************************************
** \brief Timer3 port output enable/disable setting (mode 0)
**
** \param [in] bEnOutput Toggle output setting TRUE: Enable, FALSE: Disable
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M0_Enable_Output(boolean_t bEnOutput)
{
    en_result_t enResult = Ok;
    

    M0P_TIM3_MODE0->DTR_f.MOE = bEnOutput;
    
    return enResult;    
}

/**
***********************************************************************************
** \brief Timer3 toggle enable/disable (low level) setting (mode 0)
**
**
** \param [in] bEnTOG Toggle output setting. TRUE: Enable, FALSE: Disable.
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M0_EnTOG(boolean_t bEnTOG)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE0->M0CR_f.TOGEN = bEnTOG;
    
    return enResult;  
}

/**
*************************************************************************
** \brief Timer3 16-bit counter initial value setting (mode 0)
**
**
** \param [in] u16Data CNT 16-bit initial value
**
** \retval Ok or Error
*****************************************************************************/
en_result_t Tim3_M0_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE0->CNT_f.CNT = u16Data;
 
    return enResult; 
}

/**
*************************************************************************
** \brief Timer3 16-bit counter value acquisition (mode 0)
**
**
** \param [in] none
**
** \retval 16-bit counter value
*************************************************************************/
uint16_t Tim3_M0_Cnt16Get(void)
{
    uint16_t    u16CntData = 0;
      
    u16CntData = M0P_TIM3_MODE0->CNT_f.CNT;
    
    return u16CntData; 
}

/**
************************************************************************
** \brief Timer3 reload value setting (mode 0)
**
**
** \param [in] u16Data 16-bit reload value
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M0_ARRSet(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE0->ARR_f.ARR = u16Data;

    return enResult; 
}

/**
***************************************************************************
** \brief Timer3 Set 32-bit counter initial value (mode 0)
**
** \param [in] u32Data 32-bit initial value
**
** \retval Ok or Error
********************************************************************/
en_result_t Tim3_M0_Cnt32Set(uint32_t u32Data)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE0->CNT32_f.CNT32 = u32Data;
    
    return enResult; 
}

/**
***********************************************************************
** \brief Timer3 32-bit counter value (mode 0)
**
** \param [in] none
**
** \retval 32-bit counter value
*****************************************************************************/
uint32_t Tim3_M0_Cnt32Get(void)
{
    uint32_t    u32CntData = 0;
    
    u32CntData = M0P_TIM3_MODE0->CNT32_f.CNT32;
    
    return u32CntData;
}

/**
*****************************************************************************
** \brief Timer3 initialization configuration (mode 1)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
*******************************************************************/
en_result_t Tim3_Mode1_Init(stc_tim3_mode1_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    M0P_TIM3_MODE1->M1CR_f.MODE    = pstcCfg->enWorkMode;
    M0P_TIM3_MODE1->M1CR_f.PRS     = pstcCfg->enPRS;
    M0P_TIM3_MODE1->M1CR_f.CT      = pstcCfg->enCT;
    M0P_TIM3_MODE1->M1CR_f.ONESHOT = pstcCfg->enOneShot;
    
    return enResult;
}

/**
***********************************************************************
** \brief Timer3 PWC input configuration (mode 1)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M1_Input_Cfg(stc_tim3_pwc_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE1->MSCR_f.TS    = pstcCfg->enTsSel;
    M0P_TIM3_MODE1->MSCR_f.IA0S  = pstcCfg->enIA0Sel;
    M0P_TIM3_MODE1->MSCR_f.IB0S  = pstcCfg->enIB0Sel;
    M0P_TIM3_MODE1->FLTR_f.ETP   = pstcCfg->enETRPhase;
    M0P_TIM3_MODE1->FLTR_f.FLTET = pstcCfg->enFltETR;
    M0P_TIM3_MODE1->FLTR_f.FLTA0 = pstcCfg->enFltIA0;
    M0P_TIM3_MODE1->FLTR_f.FLTB0 = pstcCfg->enFltIB0;
    
    return enResult;
}

/**
****************************************************************************
** \brief Timer3 PWC measurement edge start and end selection (mode 1)
**
** \param [in] enEdgeSel PWC measurement start and end levels
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M1_PWC_Edge_Sel(en_tim3_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;
        
    switch (enEdgeSel)
    {
        case 0:                                 ///< Rising edge to rising edge (period)
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 0;  //Rising edge
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 0;  //Rising edge
            break;
        case 1:                                 ///< Falling edge to rising edge (low level)
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 1;  //Falling edge
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 0;  //Rising edge
            break;
        case 2:                                 ///< Rising edge to falling edge (high level)
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 0;  //Rising edge
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 1;  //Falling edge
            break;
        case 3:                                 ///< Falling edge to falling edge (period)
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 1;  //Falling edge
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 1;  // Falling edge
            break;
        default:
            ;
            break;       
    }
    
    return enResult;    
}

/**
*************************************************************************
** \brief Timer3 start running (mode 1)
**
**
** \param [in] none
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M1_Run(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE1->M1CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
*****************************************************************************
** \brief Timer3 stop running (mode 1)
**
**
** \param [in] none
**
** \retval Ok or Error
*********************************************************************/
en_result_t Tim3_M1_Stop(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE1->M1CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
*************************************************************************
** \brief Timer3 16-bit counter initial value set (mode 1)
**
**
** \param [in] u16Data 16-bit initial value
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M1_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    M0P_TIM3_MODE1->CNT_f.CNT = u16Data;
    
    return enResult; 
}

/**
********************************************************************************
** \brief Timer3 16-bit count value acquisition (mode 1)
**
**
** \param [in] none
**
** \retval 16-bit count value
***********************************************************************/
uint16_t Tim3_M1_Cnt16Get(void)
{
    uint16_t    u16CntData = 0;
  
    u16CntData = M0P_TIM3_MODE1->CNT_f.CNT;
        
    return u16CntData; 
}

/**
*****************************************************************************
** \brief Timer3 pulse width measurement result acquisition (mode 1)
**
** \param [in] none
**
** \retval 16-bit pulse width measurement result
*************************************************************************/
uint16_t Tim3_M1_PWC_CapValueGet(void)
{
    uint16_t    u16CapData = 0;
  
    u16CapData = M0P_TIM3_MODE1->CCR0A_f.CCR0A;
        
    return u16CapData; 
}

/**
*****************************************************************************
** \brief Timer3 initialization configuration (mode 23)
**
**
** \param [in] pstcCfg initialization configuration structure pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_Mode23_Init(stc_tim3_mode23_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    M0P_TIM3_MODE23->M23CR_f.MODE    = pstcCfg->enWorkMode;
    
    M0P_TIM3_MODE23->M23CR_f.PRS     = pstcCfg->enPRS;
    M0P_TIM3_MODE23->M23CR_f.CT      = pstcCfg->enCT;
    M0P_TIM3_MODE23->M23CR_f.COMP    = pstcCfg->enPWMTypeSel;
    M0P_TIM3_MODE23->M23CR_f.PWM2S   = pstcCfg->enPWM2sSel;
    M0P_TIM3_MODE23->M23CR_f.ONESHOT = pstcCfg->bOneShot;
    M0P_TIM3_MODE23->M23CR_f.URS     = pstcCfg->bURSSel;
    M0P_TIM3_MODE23->M23CR_f.DIR     = pstcCfg->enCntDir;
        
    return enResult;
}

/** 
******************************************************************************* 
** \brief Timer3 PWM output enable (mode 23)
**
** \param [in] bEnOutput PWM output enable/disable setting
** \param [in] bEnAutoOutput PWM automatic output enable/disable setting
**
** \retval Ok or Error
********************************************************************/
en_result_t Tim3_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->DTR_f.MOE = bEnOutput;
    M0P_TIM3_MODE23->DTR_f.AOE = bEnAutoOutput;
    
    return enResult;
}

/**
***************************************************************************
** \brief Timer3 Start running (mode 23)
**
** \param [in] none
**
** \retval Ok or Error
********************************************************************/
en_result_t Tim3_M23_Run(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.CTEN = TRUE;
    
    return enResult;
}

/**
***************************************************************************
** \brief Timer3 stop running (mode 23)
**
** \param [in] none
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M23_Stop(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
****************************************************************************
** \brief Timer3 reload value setting (mode 23)
**
**
** \param [in] u16Data 16-bit reload value
** \param [in] bArrBufEn ARR reload buffer enable TRUE/disable FALSE
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn)
{
    en_result_t enResult = Ok;
        
     M0P_TIM3_MODE23->ARR_f.ARR       = u16Data;
     M0P_TIM3_MODE23->M23CR_f.BUFPEN  = bArrBufEn;

    return enResult; 
}

/**
********************************************************************************
** \brief Timer3 16-bit counter initial value set (mode 23)
**
** \param [in] u16Data 16-bit initial value
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M23_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->CNT_f.CNT = u16Data;

    return enResult; 
}

/**
*****************************************************************************
** \brief Timer3 16-bit count value acquisition (mode 23)
**
** \param [in] none
**
** \retval 16-bit count value
*************************************************************************/
uint16_t Tim3_M23_Cnt16Get(void)
{
    uint16_t    u16CntData = 0;
        
    u16CntData = M0P_TIM3_MODE23->CNT_f.CNT;
    
    return u16CntData; 
}

/**
*************************************************************************
** \brief Timer3 compare capture register CCRxA/CCRxB settings (mode 23)
**
**
** \param [in] enCCRSel CCRxA/CCRxB settings 
** \param [in] u16Data CCRxA/CCRxB 16-bit initial value 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M23_CCR_Set(en_tim3_m23_ccrx_t enCCRSel, uint16_t u16Data)
{
    en_result_t enResult = Ok;
        
    if(Tim3CCR0A == enCCRSel)
    {
        M0P_TIM3_MODE23->CCR0A_f.CCR0A = u16Data;
    }
    else if(Tim3CCR0B == enCCRSel)
    {
        M0P_TIM3_MODE23->CCR0B_f.CCR0B = u16Data;
    }
    else if(Tim3CCR1A == enCCRSel)
    {
        M0P_TIM3_MODE23->CCR1A_f.CCR1A = u16Data;
    }
    else if(Tim3CCR1B == enCCRSel)
    {
        M0P_TIM3_MODE23->CCR1B_f.CCR1B = u16Data;
    }
    else if(Tim3CCR2A == enCCRSel)
    {
        M0P_TIM3_MODE23->CCR2A_f.CCR2A = u16Data;
    }
    else if(Tim3CCR2B == enCCRSel)
    {
        M0P_TIM3_MODE23->CCR2B_f.CCR2B = u16Data;
    }
    else
    {
        enResult = Error;
    }
    
    return enResult;
}

/** *****************************************************************************
** \brief Timer3 compare capture register CCRxA/CCRxB read (mode 23)
**
**
** \param [in] enCCRSel CCRxA/CCRxB setting
**
** \retval 16-bit CCRxA/CCRxB capture value
***********************************************************************/
uint16_t Tim3_M23_CCR_Get(en_tim3_m23_ccrx_t enCCRSel)
{
    uint16_t    u16Data = 0;
    
    if(Tim3CCR0A == enCCRSel)
    {
        u16Data = M0P_TIM3_MODE23->CCR0A_f.CCR0A;
    }
    else if(Tim3CCR0B == enCCRSel)
    {
        u16Data = M0P_TIM3_MODE23->CCR0B_f.CCR0B;
    }
    else if(Tim3CCR1A == enCCRSel)
    {
        u16Data = M0P_TIM3_MODE23->CCR1A_f.CCR1A;
    }
    else if(Tim3CCR1B == enCCRSel)
    {
        u16Data = M0P_TIM3_MODE23->CCR1B_f.CCR1B;
    }
    else if(Tim3CCR2A == enCCRSel)
    {
        u16Data = M0P_TIM3_MODE23->CCR2A_f.CCR2A;
    }
    else if(Tim3CCR2B == enCCRSel)
    {
        u16Data = M0P_TIM3_MODE23->CCR2B_f.CCR2B;
    }
    else
    {
        u16Data = 0;
    }
    
    return u16Data; 
}

/**
************************************************************************************
** \brief Timer3 PWM complementary output mode, GATE function selection (mode 23)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M23_GateFuncSel(stc_tim3_m23_gate_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.CSG = pstcCfg->enGateFuncSel;
    M0P_TIM3_MODE23->M23CR_f.CRG = pstcCfg->bGateRiseCap;
    M0P_TIM3_MODE23->M23CR_f.CFG = pstcCfg->bGateFallCap;
    
    return enResult;    
}

/**
*************************************************************************
** \brief Timer3 Master/Slave Mode Configuration (Mode 23)
**
**
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M23_MasterSlave_Set(stc_tim3_m23_master_slave_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE23->MSCR_f.MSM = pstcCfg->enMasterSlaveSel;
    M0P_TIM3_MODE23->MSCR_f.MMS = pstcCfg->enMasterSrc;
    M0P_TIM3_MODE23->MSCR_f.SMS = pstcCfg->enSlaveModeSel;
    M0P_TIM3_MODE23->MSCR_f.TS  = pstcCfg->enTsSel;
    
    return enResult;    
}

/** 
******************************************************************************* 
** \brief Timer3 CHxA/CHxB comparison channel control (mode 23)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
** \param [in] enTim3Chx Timer3 channel (Tim3CH0, Tim3CH1, Tim3CH2)
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M23_PortOutput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_compare_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    switch (enTim3Chx)
    {
        case Tim3CH0:
            M0P_TIM3_MODE23->CRCH0_f.CSA         = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMA0_FLTA0  = pstcCfg->enCHxACmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPA0        = pstcCfg->enCHxAPolarity;
            M0P_TIM3_MODE23->CRCH0_f.BUFEA       = pstcCfg->bCHxACmpBufEn;
            M0P_TIM3_MODE23->M23CR_f.CIS         = pstcCfg->enCHxACmpIntSel;
    
            M0P_TIM3_MODE23->CRCH0_f.CSB         = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMB0_FLTB0  = pstcCfg->enCHxBCmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPB0        = pstcCfg->enCHxBPolarity;
            M0P_TIM3_MODE23->CRCH0_f.BUFEB       = pstcCfg->bCHxBCmpBufEn;
            M0P_TIM3_MODE23->CRCH0_f.CISB        = pstcCfg->enCHxBCmpIntSel;
          break;
        case Tim3CH1:
            M0P_TIM3_MODE23->CRCH1_f.CSA         = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMA1_FLTA1  = pstcCfg->enCHxACmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPA1        = pstcCfg->enCHxAPolarity;
            M0P_TIM3_MODE23->CRCH1_f.BUFEA       = pstcCfg->bCHxACmpBufEn;
            M0P_TIM3_MODE23->M23CR_f.CIS         = pstcCfg->enCHxACmpIntSel;
    
            M0P_TIM3_MODE23->CRCH1_f.CSB         = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMB1_FLTB1  = pstcCfg->enCHxBCmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPB1        = pstcCfg->enCHxBPolarity;
            M0P_TIM3_MODE23->CRCH1_f.BUFEB       = pstcCfg->bCHxBCmpBufEn;
            M0P_TIM3_MODE23->CRCH1_f.CISB        = pstcCfg->enCHxBCmpIntSel;
          break;
        case Tim3CH2:
            M0P_TIM3_MODE23->CRCH2_f.CSA         = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMA2_FLTA2  = pstcCfg->enCHxACmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPA2        = pstcCfg->enCHxAPolarity;
            M0P_TIM3_MODE23->CRCH2_f.BUFEA       = pstcCfg->bCHxACmpBufEn;
            M0P_TIM3_MODE23->M23CR_f.CIS         = pstcCfg->enCHxACmpIntSel;
    
            M0P_TIM3_MODE23->CRCH2_f.CSB         = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMB2_FLTB2  = pstcCfg->enCHxBCmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPB2        = pstcCfg->enCHxBPolarity;
            M0P_TIM3_MODE23->CRCH2_f.BUFEB       = pstcCfg->bCHxBCmpBufEn;
            M0P_TIM3_MODE23->CRCH2_f.CISB        = pstcCfg->enCHxBCmpIntSel;
          break;
        default:
            enResult = Error;
          break;
    }
    
    return enResult;    
}

/**
***********************************************************************
** \brief Timer3 CHxA/CHxB input control (mode 23)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
** \param [in] enTim3Chx Timer3 channel (Tim3CH0, Tim3CH1, Tim3CH2) 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M23_PortInput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;

    switch (enTim3Chx)
    {
        case Tim3CH0:
            M0P_TIM3_MODE23->CRCH0_f.CSA           = 1;
            M0P_TIM3_MODE23->CRCH0_f.CFA_CRA_BKSA  = pstcCfg->enCHxACapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMA0_FLTA0    = pstcCfg->enCHxAInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPA0          = pstcCfg->enCHxAPolarity;
    
            M0P_TIM3_MODE23->CRCH0_f.CSB           = 1;
            M0P_TIM3_MODE23->CRCH0_f.CFB_CRB_BKSB  = pstcCfg->enCHxBCapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMB0_FLTB0    = pstcCfg->enCHxBInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPB0          = pstcCfg->enCHxBPolarity;
          break;
        case Tim3CH1:
            M0P_TIM3_MODE23->CRCH1_f.CSA           = 1;
            M0P_TIM3_MODE23->CRCH1_f.CFA_CRA_BKSA  = pstcCfg->enCHxACapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMA1_FLTA1    = pstcCfg->enCHxAInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPA1          = pstcCfg->enCHxAPolarity;
    
            M0P_TIM3_MODE23->CRCH1_f.CSB           = 1;
            M0P_TIM3_MODE23->CRCH1_f.CFB_CRB_BKSB  = pstcCfg->enCHxBCapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMB1_FLTB1    = pstcCfg->enCHxBInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPB1          = pstcCfg->enCHxBPolarity;
          break;
        case Tim3CH2:
            M0P_TIM3_MODE23->CRCH2_f.CSA           = 1;
            M0P_TIM3_MODE23->CRCH2_f.CFA_CRA_BKSA  = pstcCfg->enCHxACapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMA2_FLTA2    = pstcCfg->enCHxAInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPA2          = pstcCfg->enCHxAPolarity;
    
            M0P_TIM3_MODE23->CRCH2_f.CSB           = 1;
            M0P_TIM3_MODE23->CRCH2_f.CFB_CRB_BKSB  = pstcCfg->enCHxBCapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMB2_FLTB2    = pstcCfg->enCHxBInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPB2          = pstcCfg->enCHxBPolarity;
          break;
        default:
            enResult = Error;
          break;
    }
    return enResult;    
}

/** 
******************************************************************************* 
** \brief Timer3 ERT Input Control (Mode 23)
**
**
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error
********************************************************************/
en_result_t Tim3_M23_ETRInput_Cfg(stc_tim3_m23_etr_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->FLTR_f.ETP    = pstcCfg->enETRPolarity;
    M0P_TIM3_MODE23->FLTR_f.FLTET  = pstcCfg->enETRFlt;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Timer3 Brake BK input control (Mode 23)
**
**
** \param [in] pstcBkCfg Initialization configuration structure pointer
**
** \retval Ok or Error
********************************************************************/
en_result_t Tim3_M23_BrakeInput_Cfg(stc_tim3_m23_bk_input_cfg_t* pstcBkCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->DTR_f.BKE             = pstcBkCfg->bEnBrake;
    M0P_TIM3_MODE23->DTR_f.VCE             = pstcBkCfg->bEnVCBrake;
    M0P_TIM3_MODE23->DTR_f.SAFEEN          = pstcBkCfg->bEnSafetyBk;
    M0P_TIM3_MODE23->DTR_f.BKSEL           = pstcBkCfg->bEnBKSync;
    M0P_TIM3_MODE23->CRCH0_f.CFA_CRA_BKSA  = pstcBkCfg->enBkCH0AStat;
    M0P_TIM3_MODE23->CRCH0_f.CFB_CRB_BKSB  = pstcBkCfg->enBkCH0BStat;
    M0P_TIM3_MODE23->CRCH1_f.CFA_CRA_BKSA  = pstcBkCfg->enBkCH1AStat;
    M0P_TIM3_MODE23->CRCH1_f.CFB_CRB_BKSB  = pstcBkCfg->enBkCH1BStat;
    M0P_TIM3_MODE23->CRCH2_f.CFA_CRA_BKSA  = pstcBkCfg->enBkCH2AStat;
    M0P_TIM3_MODE23->CRCH2_f.CFB_CRB_BKSB  = pstcBkCfg->enBkCH2BStat;
    M0P_TIM3_MODE23->FLTR_f.BKP            = pstcBkCfg->enBrakePolarity;
    M0P_TIM3_MODE23->FLTR_f.FLTBK          = pstcBkCfg->enBrakeFlt;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer3 trigger ADC control (mode 23)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M23_TrigADC_Cfg(stc_tim3_m23_adc_trig_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->ADTR_f.ADTE   = pstcCfg->bEnTrigADC;
    M0P_TIM3_MODE23->ADTR_f.UEVE   = pstcCfg->bEnUevTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMA0E  = pstcCfg->bEnCH0ACmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMB0E  = pstcCfg->bEnCH0BCmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMA1E  = pstcCfg->bEnCH1ACmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMB1E  = pstcCfg->bEnCH1BCmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMA2E  = pstcCfg->bEnCH2ACmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMB2E  = pstcCfg->bEnCH2BCmpTrigADC;
    return enResult;    
}

/** 
*******************************************************************************
** \brief Timer3 dead zone function (mode 23) 
** 
** 
** \param [in] pstcCfg Initializes the configuration structure pointer
**
** \retval Ok or Error
*****************************************************************************/
en_result_t Tim3_M23_DT_Cfg(stc_tim3_m23_dt_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->DTR_f.DTEN = pstcCfg->bEnDeadTime;
    M0P_TIM3_MODE23->DTR_f.DTR  = pstcCfg->u8DeadTimeValue;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Timer3 repeat period setting (mode 23)
**
**
** \param [in] u8ValidPeriod repeat period value
**
** \retval Ok or Error
*****************************************************************************/
en_result_t Tim3_M23_SetValidPeriod(uint8_t u8ValidPeriod)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->RCR_f.RCR = u8ValidPeriod;
    
    return enResult;    
}

/**
*************************************************************************
** \brief Timer3 OCREF clear function (mode 23)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M23_OCRefClr(stc_tim3_m23_OCREF_Clr_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.OCCS = pstcCfg->enOCRefClrSrcSel;
    M0P_TIM3_MODE23->M23CR_f.OCCE = pstcCfg->bVCClrEn;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Timer3 Enable DMA transfer (Mode 23)
**
**
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M23_EnDMA(stc_tim3_m23_trig_dma_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.UDE  = pstcCfg->bUevTrigDMA;
    M0P_TIM3_MODE23->M23CR_f.TDE  = pstcCfg->bTITrigDMA;
    M0P_TIM3_MODE23->CRCH0_f.CDEA = pstcCfg->bCmpA0TrigDMA;
    M0P_TIM3_MODE23->CRCH0_f.CDEB = pstcCfg->bCmpB0TrigDMA;
    M0P_TIM3_MODE23->CRCH1_f.CDEA = pstcCfg->bCmpA1TrigDMA;
    M0P_TIM3_MODE23->CRCH1_f.CDEB = pstcCfg->bCmpB1TrigDMA;
    M0P_TIM3_MODE23->CRCH2_f.CDEA = pstcCfg->bCmpA2TrigDMA;
    M0P_TIM3_MODE23->CRCH2_f.CDEB = pstcCfg->bCmpB2TrigDMA;
    M0P_TIM3_MODE23->MSCR_f.CCDS  = pstcCfg->enCmpUevTrigDMA;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Timer3 Capture Compare A Software Trigger (Mode 23)
**
**
** \param [in] enTim3Chx Timer3 channel (Tim3CH0, Tim3CH1, Tim3CH2) 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Tim3_M23_EnSwTrigCapCmpA(en_tim3_channel_t enTim3Chx)
{
    en_result_t enResult = Ok;
    if(Tim3CH0 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH0_f.CCGA = TRUE;
    }
    else if(Tim3CH1 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH1_f.CCGA = TRUE;
    }
    else if(Tim3CH2 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH2_f.CCGA = TRUE;
    }
    else
    {
        enResult = Error;
    }
    return enResult;    
}

/**
*****************************************************************************
** \brief Timer3 Capture Compare B Software Trigger (Mode 23)
**
**
** \param [in] enTim3Chx Timer3 Channel (Tim3CH0, Tim3CH1, Tim3CH2)
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M23_EnSwTrigCapCmpB(en_tim3_channel_t enTim3Chx)
{
    en_result_t enResult = Ok;
    if(Tim3CH0 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH0_f.CCGB = TRUE;
    }
    else if(Tim3CH1 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH1_f.CCGB = TRUE;
    }
    else if(Tim3CH2 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH2_f.CCGB = TRUE;
    }
    else
    {
        enResult = Error;
    }
    return enResult;    
}

/**
*************************************************************************
** \brief Timer3 software update enable (mode 23)
**
**
** \param [in] none
**
** \retval Ok or Error
*************************************************************************/
en_result_t Tim3_M23_EnSwUev(void)
{
    en_result_t enResult = Ok;
    
    M0P_TIM3_MODE23->M23CR_f.UG = TRUE;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Timer3 software trigger enable (mode 23)
**
**
** \param [in] none
**
** \retval Ok or Error
***********************************************************************/
en_result_t Tim3_M23_EnSwTrig(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.TG = TRUE;
    
    return enResult;    
}

/**
*****************************************************************************
** \brief Timer3 software brake enable (mode 23)
**
**
** \param [in] none
**
** \retval OK or Error
*******************************************************************************/
en_result_t Tim3_M23_EnSwBk(void)
{
    en_result_t enResult = Ok;
        
    M0P_TIM3_MODE23->M23CR_f.BG = TRUE;
    
    return enResult;    
}

//@} // Tim3Group

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

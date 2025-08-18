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
 * @file   bt.c
 *
 * @brief  Source file for BT functions
 *
 * @author MADS Team 
 *
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


/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
*****************************************************************************
** \brief Get Base Timer Interrupt Flag (Mode 0/1/23)
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] enBtIrq Interrupt type
**
** \retval TRUE or FALSE
*************************************************************************/
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
***********************************************************************
** \brief Base Timer Interrupt Flag Clear (Mode 0/1/23)
** 
** 
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2) 
** \param [in] enBtIrq interrupt type 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ICLR = ~(1u<<enBtIrq);
    
    return enResult;
}

/**
*************************************************************************
** \brief Base Timer Interrupt Clear All Flags (Mode 23)
**
**
** \param [in] enUnit Timer Channel Select (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_ClearAllIntFlag(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ICLR  = 0;
    
    return enResult;
}

/**
*******************************************************************
** \brief Base Timer Interrupt Enable (Mode 0)
**
**
** \param [in] enUnit Timer Channel Select (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
***************************************************************************/
en_result_t Bt_Mode0_EnableIrq(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.UIE = TRUE;
    
    return enResult;
}

/**
***********************************************************************
** \brief Base Timer Interrupt Disable (Mode 0)
**
**
** \param [in] enUnit Timer Channel Select (TIM0, TIM1, TIM2)
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Bt_Mode0_DisableIrq(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.UIE = FALSE;

    return enResult;
}

/** 
******************************************************************************* 
** \brief Base Timer interrupt enable (mode 1) 
** 
** 
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2) 
** \param [in] enBtIrq interrupt type 
** 
**\retval Ok or Error 
*******************************************************************************/
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
***********************************************************************
** \brief Base Timer Interrupt Disable (Mode 1)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] enBtIrq interrupt type
**
** \retval Ok or Error
*******************************************************************/
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
******************************************************************************* 
** \brief Base Timer Interrupt enable (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] enBtIrq interrupt type
**
** \retval Ok or Error
********************************************************************/
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

/** *****************************************************************************
** \brief Base Timer Interrupt Disable (Mode 23)
**
**
** \param [in] enUnit Timer channel select (TIM0, TIM1, TIM2)
** \param [in] enBtIrq interrupt type
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
***********************************************************************
** \brief Base Timer initialization configuration (Mode 0)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_Mode0_Init(en_bt_unit_t enUnit, stc_bt_mode0_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.MODE   = pstcCfg->enWorkMode;
    pstcM0PBt->M0CR_f.GATEP  = pstcCfg->enGateP;
    pstcM0PBt->M0CR_f.GATE   = pstcCfg->bEnGate;
    pstcM0PBt->M0CR_f.PRS    = pstcCfg->enPRS;
    pstcM0PBt->M0CR_f.TOGEN  = pstcCfg->bEnTog;
    pstcM0PBt->M0CR_f.CT     = pstcCfg->enCT;
    pstcM0PBt->M0CR_f.MD     = pstcCfg->enCntMode; 
    
    return enResult;
}

/**
***********************************************************************
** \brief Base Timer Starts Running (Mode 0)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M0_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer Stop (Mode 0)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
*******************************************************************/
en_result_t Bt_M0_Stop(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
***********************************************************************
** \brief Base Timer toggle output enable/disable (low level) setting (mode 0)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] bEnTOG toggle output setting TRUE: Enable, FALSE: Disable
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M0_EnTOG_Output(en_bt_unit_t enUnit, boolean_t bEnTOG)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M0CR_f.TOGEN = bEnTOG;
    
    return enResult;    
}
    
/** 
******************************************************************************* 
** \brief Base Timer Port output enable/disable setting (mode 0)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] bEnOutput Port output setting TRUE: Enable, FALSE: Disable
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_M0_Enable_Output(en_bt_unit_t enUnit, boolean_t bEnOutput)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.MOE = bEnOutput;
    
    return enResult;    
}

/**
************************************************************************
** \brief Base Timer 16-bit counter initial value set (mode 0)
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] u16Data 16-bit initial value
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M0_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CNT_f.CNT = u16Data;
    
    return enResult; 
}

/**
*******************************************************************
** \brief Get Base Timer 16-bit count value (Mode 0)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
**
** \retval 16-bit count value
******************************************************************************/
uint16_t Bt_M0_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;
  
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    u16CntData = pstcM0PBt->CNT_f.CNT;
    
    return u16CntData; 
}

/**
***********************************************************************
** \brief Base Timer Reload Value Setting (Mode 0)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2) 
** \param [in] u16Data 16bits overload value 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M0_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ARR_f.ARR = u16Data;

    return enResult; 
}

/**
***********************************************************************
** \brief Base Timer 32-bit counter initial value set (mode 0)
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] u32Data 32-bit initial value
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M0_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data)
{
    en_result_t enResult = Ok;
  
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CNT32_f.CNT32 = u32Data;
    
    return enResult;
}

/**
***********************************************************************
** \brief Get Base Timer 32-bit count value (Mode 0)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
**
** \retval 32-bit count value
*******************************************************************/
uint32_t Bt_M0_Cnt32Get(en_bt_unit_t enUnit)
{
    uint32_t    u32CntData = 0;
    
    volatile M0P_TIM0_MODE0_TypeDef *pstcM0PBt = (M0P_TIM0_MODE0_TypeDef *)((uint32_t)M0P_TIM0_MODE0+0x100*enUnit);
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    u32CntData = pstcM0PBt->CNT32_f.CNT32;
    
    return u32CntData;
}

/**
***********************************************************************
** \brief Base Timer initialization configuration (mode 1)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Bt_Mode1_Init(en_bt_unit_t enUnit, stc_bt_mode1_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M1CR_f.MODE    = pstcCfg->enWorkMode;
    pstcM0PBt->M1CR_f.PRS     = pstcCfg->enPRS;
    pstcM0PBt->M1CR_f.CT      = pstcCfg->enCT;
    pstcM0PBt->M1CR_f.ONESHOT = pstcCfg->enOneShot;

    
    return enResult;
}

/**
****************************************************************************
** \brief Base Timer PWC Input Configuration (Mode 1)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M1_Input_Cfg(en_bt_unit_t enUnit, stc_bt_pwc_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->MSCR_f.TS    = pstcCfg->enTsSel;
    pstcM0PBt->MSCR_f.IA0S  = pstcCfg->enIA0Sel;
    pstcM0PBt->MSCR_f.IB0S  = pstcCfg->enIB0Sel;
    pstcM0PBt->FLTR_f.ETP   = pstcCfg->enETRPhase;
    pstcM0PBt->FLTR_f.FLTET = pstcCfg->enFltETR;
    pstcM0PBt->FLTR_f.FLTA0 = pstcCfg->enFltIA0;
    pstcM0PBt->FLTR_f.FLTB0 = pstcCfg->enFltIB0;
    
    return enResult;
}

/**
****************************************************************************
** \brief Base Timer PWC Measurement Edge Start and End Selection (Mode 1)
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] enEdgeSel PWC Measurement Start and End Levels
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M1_PWC_Edge_Sel(en_bt_unit_t enUnit,en_bt_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    switch (enEdgeSel)
    {
        case 0:                            ///< Rising edge to rising edge (period)
            pstcM0PBt->M1CR_f.EDG1ST = 0;  //Rising edge
            pstcM0PBt->M1CR_f.EDG2ND = 0;  //Rising edge
            break;
        case 1:                            ///< Falling edge to rising edge (low level)
            pstcM0PBt->M1CR_f.EDG1ST = 1;  //Falling edge
            pstcM0PBt->M1CR_f.EDG2ND = 0;  //Rising edge
            break;
        case 2:                            ///< Rising edge to falling edge (high level)
            pstcM0PBt->M1CR_f.EDG1ST = 0;  //Rising edge
            pstcM0PBt->M1CR_f.EDG2ND = 1;  //Falling edge
            break;
        case 3:                            ///< Falling edge to falling edge (period)
            pstcM0PBt->M1CR_f.EDG1ST = 1;  // Falling edge
            pstcM0PBt->M1CR_f.EDG2ND = 1;  // Falling edge
            break;
        default:
            ;
            break;       
    }
    
    return enResult;    
}

/**
*************************************************************************
** \brief Base Timer Starts Running (Mode 1)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_M1_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M1CR_f.CTEN = TRUE;
    
    return enResult;    
}

/**
*************************************************************************
** \brief Base Timer Stop (Mode 1)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_M1_Stop(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M1CR_f.CTEN = FALSE;
    
    return enResult;  
}

/**
***********************************************************************
** \brief Base Timer 16-bit Counter Initial Value Setting (Mode 1)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] u16Data 16-bit Initial Value
**
** \retval Ok or Error
*****************************************************************************/
en_result_t Bt_M1_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
  
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CNT_f.CNT = u16Data;
    
    return enResult;
}

/**
***********************************************************************
** \brief Base Timer 16-bit counter value acquisition (mode 1)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
**
** \retval 16-bit count value
**********************************************************************/
uint16_t Bt_M1_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;
  
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    u16CntData = pstcM0PBt->CNT_f.CNT;
    
    return u16CntData;
}

/**
*****************************************************************************
** \brief Base Timer Pulse Width Measurement Result Get (Mode 1)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
**
** \retval 16-bit pulse width measurement result
*****************************************************************************/
uint16_t Bt_M1_PWC_CapValueGet(en_bt_unit_t enUnit)
{
    uint16_t    u16CapData = 0;
    
    volatile M0P_TIM0_MODE1_TypeDef *pstcM0PBt = (M0P_TIM0_MODE1_TypeDef *)((uint32_t)M0P_TIM0_MODE1+0x100*enUnit);
  
    ASSERT(IS_VALID_TIM(enUnit));
    
    u16CapData = pstcM0PBt->CCR0A_f.CCR0A;
    
    return u16CapData;
}

/**
*************************************************************************
** \brief Base Timer initialization configuration (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg initialization configuration structure pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_Mode23_Init(en_bt_unit_t enUnit, stc_bt_mode23_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
  
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.MODE    = pstcCfg->enWorkMode;
    
    pstcM0PBt->M23CR_f.PRS     = pstcCfg->enPRS;
    pstcM0PBt->M23CR_f.CT      = pstcCfg->enCT;
    pstcM0PBt->M23CR_f.COMP    = pstcCfg->enPWMTypeSel;
    pstcM0PBt->M23CR_f.PWM2S   = pstcCfg->enPWM2sSel;
    pstcM0PBt->M23CR_f.ONESHOT = pstcCfg->bOneShot;
    pstcM0PBt->M23CR_f.URS     = pstcCfg->bURSSel;
    pstcM0PBt->M23CR_f.DIR     = pstcCfg->enCntDir;

    
    return enResult;
}

/**
***********************************************************************
** \brief Base Timer PWM output enable/disable (mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] bEnOutput PWM output enable/disable setting
** \param [in] bEnAutoOutput PWM automatic output enable/disable setting
**
** \retval Ok or Error
***********************************************************************/
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
******************************************************************************* 
** \brief Base Timer starts running (mode 23) ** 
** 
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2) 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M23_Run(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.CTEN = TRUE;
    
    return enResult;
}

/** *****************************************************************************
** \brief Base Timer Stop (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
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
****************************************************************************
** \brief Base Timer Reload Value Setting (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] u16Data 16-bit Reload Value
** \param [in] bArrBufEn ARR Reload Buffer Enable TRUE/Disable FALSE
**
** \retval Ok or Error
***********************************************************************/
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
***********************************************************************
** \brief Base Timer 16-bit Counter Initial Value Setup (Mode 23)
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] u16Data 16-bit initial value 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M23_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CNT_f.CNT       = u16Data;

    return enResult; 
}

/** *****************************************************************************
** \brief Get Base Timer 16-bit count value (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
**
** \retval 16-bit count value
*************************************************************************/
uint16_t Bt_M23_Cnt16Get(en_bt_unit_t enUnit)
{
    uint16_t    u16CntData = 0;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    u16CntData = pstcM0PBt->CNT_f.CNT;
    
    return u16CntData; 
}

/**
*************************************************************************
** \brief Base Timer Compare Capture Register CCR0A/CCR0B Settings (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] enCCRSel CCR0A/CCR0B Settings
** \param [in] u16Data CCR0A/CCR0B 16-bit Initial Value
**
** \retval Ok or Error
*************************************************************************/
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
*************************************************************************
** \brief Base Timer Compare Capture Registers CCR0A/CCR0B Read (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] enCCRSel CCR0A/CCR0B setting
**
** \retval 16-bit CCR0A capture value
*************************************************************************/
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
***********************************************************************
** \brief Base Timer PWM complementary output mode, GATE function selection (mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg initialization configuration structure pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M23_GateFuncSel(en_bt_unit_t enUnit,stc_bt_m23_gate_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.CSG = pstcCfg->enGateFuncSel;
    pstcM0PBt->M23CR_f.CRG = pstcCfg->bGateRiseCap;
    pstcM0PBt->M23CR_f.CFG = pstcCfg->bGateFallCap;
    
    return enResult;    
}

/**
****************************************************************************
** \brief Base Timer Master-Slave Mode Configuration (Mode 23)
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M23_MasterSlave_Set(en_bt_unit_t enUnit, stc_bt_m23_master_slave_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->MSCR_f.MSM = pstcCfg->enMasterSlaveSel;
    pstcM0PBt->MSCR_f.MMS = pstcCfg->enMasterSrc;
    pstcM0PBt->MSCR_f.SMS = pstcCfg->enSlaveModeSel;
    pstcM0PBt->MSCR_f.TS  = pstcCfg->enTsSel;
    
    return enResult;    
}

/** *****************************************************************************
** \brief Base Timer CH0A/CH0B Compare Channel Output Control (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error
*****************************************************************************/
en_result_t Bt_M23_PortOutput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_compare_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CSA         = 0;
    pstcM0PBt->FLTR_f.OCMA0_FLTA0  = pstcCfg->enCH0ACmpCtrl;
    pstcM0PBt->FLTR_f.CCPA0        = pstcCfg->enCH0APolarity;
    pstcM0PBt->CRCH0_f.BUFEA       = pstcCfg->bCh0ACmpBufEn;
    pstcM0PBt->M23CR_f.CIS         = pstcCfg->enCh0ACmpIntSel;
    
    pstcM0PBt->CRCH0_f.CSB         = 0;
    pstcM0PBt->FLTR_f.OCMB0_FLTB0  = pstcCfg->enCH0BCmpCtrl;
    pstcM0PBt->FLTR_f.CCPB0        = pstcCfg->enCH0BPolarity;
    pstcM0PBt->CRCH0_f.BUFEB       = pstcCfg->bCH0BCmpBufEn;
    pstcM0PBt->CRCH0_f.CISB        = pstcCfg->enCH0BCmpIntSel;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer CH0A/CH0B Input Control (Mode 23)
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization Configuration Structure Pointer
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M23_PortInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CSA           = 1;
    pstcM0PBt->CRCH0_f.CFA_CRA_BKSA  = pstcCfg->enCH0ACapSel;
    pstcM0PBt->FLTR_f.OCMA0_FLTA0    = pstcCfg->enCH0AInFlt;
    pstcM0PBt->FLTR_f.CCPA0          = pstcCfg->enCH0APolarity;
    
    pstcM0PBt->CRCH0_f.CSB           = 1;
    pstcM0PBt->CRCH0_f.CFB_CRB_BKSB  = pstcCfg->enCH0BCapSel;
    pstcM0PBt->FLTR_f.OCMB0_FLTB0    = pstcCfg->enCH0BInFlt;
    pstcM0PBt->FLTR_f.CCPB0          = pstcCfg->enCH0BPolarity;
    
    return enResult;    
}

/**
********************************************************************
** \brief Base Timer ERT Input Control (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M23_ETRInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_etr_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->FLTR_f.ETP    = pstcCfg->enETRPolarity;
    pstcM0PBt->FLTR_f.FLTET  = pstcCfg->enETRFlt;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer Brake BK Input Control (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M23_BrakeInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_bk_input_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.BKE             = pstcCfg->bEnBrake;
    pstcM0PBt->DTR_f.VCE             = pstcCfg->bEnVCBrake;
    pstcM0PBt->DTR_f.SAFEEN          = pstcCfg->bEnSafetyBk;
    pstcM0PBt->DTR_f.BKSEL           = pstcCfg->bEnBKSync;
    pstcM0PBt->CRCH0_f.CFA_CRA_BKSA  = pstcCfg->enBkCH0AStat;
    pstcM0PBt->CRCH0_f.CFB_CRB_BKSB  = pstcCfg->enBkCH0BStat;
    pstcM0PBt->FLTR_f.BKP            = pstcCfg->enBrakePolarity;
    pstcM0PBt->FLTR_f.FLTBK          = pstcCfg->enBrakeFlt;
    
    return enResult;
}

/** *****************************************************************************
** \brief Base Timer Trigger ADC Control (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error
*****************************************************************************/
en_result_t Bt_M23_TrigADC_Cfg(en_bt_unit_t enUnit, stc_bt_m23_adc_trig_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->ADTR_f.ADTE   = pstcCfg->bEnTrigADC;
    pstcM0PBt->ADTR_f.UEVE   = pstcCfg->bEnUevTrigADC;
    pstcM0PBt->ADTR_f.CMA0E  = pstcCfg->bEnCH0ACmpTrigADC;
    pstcM0PBt->ADTR_f.CMB0E  = pstcCfg->bEnCH0BCmpTrigADC;
    
    return enResult;    
}

/** 
*******************************************************************************
** \brief Base Timer dead zone function (mode 23) 
** 
** 
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_M23_DT_Cfg(en_bt_unit_t enUnit, stc_bt_m23_dt_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->DTR_f.DTEN = pstcCfg->bEnDeadTime;
    pstcM0PBt->DTR_f.DTR  = pstcCfg->u8DeadTimeValue;
    
    return enResult;    
}

/**
********************************************************************************
** \brief Base Timer repeat period setting (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] u8ValidPeriod repeat period value
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M23_SetValidPeriod(en_bt_unit_t enUnit, uint8_t u8ValidPeriod)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->RCR_f.RCR = u8ValidPeriod;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer OCREF Clear Function (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization configuration structure pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_M23_OCRefClr(en_bt_unit_t enUnit, stc_bt_m23_OCREF_Clr_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.OCCS = pstcCfg->enOCRefClrSrcSel;
    pstcM0PBt->M23CR_f.OCCE = pstcCfg->bVCClrEn;
    
    return enResult;    
}

/**
*************************************************************************
** \brief Base Timer Enable DMA Transfer (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
** \param [in] pstcCfg Initialization Configuration Structure Pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Bt_M23_EnDMA(en_bt_unit_t enUnit, stc_bt_m23_trig_dma_cfg_t* pstcCfg)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.UDE  = pstcCfg->bUevTrigDMA;
    pstcM0PBt->M23CR_f.TDE  = pstcCfg->bTITrigDMA;
    pstcM0PBt->CRCH0_f.CDEA = pstcCfg->bCmpATrigDMA;
    pstcM0PBt->CRCH0_f.CDEB = pstcCfg->bCmpBTrigDMA;
    pstcM0PBt->MSCR_f.CCDS  = pstcCfg->enCmpUevTrigDMA;
    
    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer Capture Compare A Software Trigger (Mode 23)
**
**
** \param [in] enUnit Timer Channel Select (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M23_EnSwTrigCapCmpA(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CCGA = TRUE;

    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer Capture Compare B Software Trigger (Mode 23)
**
**
** \param [in] enUnit Timer Channel Selection (TIM0, TIM1, TIM2)
**
** \retval Ok or Error
***********************************************************************/
en_result_t Bt_M23_EnSwTrigCapCmpB(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->CRCH0_f.CCGB = TRUE;

    return enResult;    
}

/**
***********************************************************************
** \brief Base Timer Software Update Enable (Mode 23)
**
**
** \param [in] enUnit Timer Channel Select (TIM0, TIM1, TIM2)
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
***********************************************************************
** \brief Base Timer Software Trigger Enable (Mode 23)
**
**
** \param [in] enUnit Timer channel selection (TIM0, TIM1, TIM2) 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Bt_M23_EnSwTrig(en_bt_unit_t enUnit)
{
    en_result_t enResult = Ok;
    volatile M0P_TIM0_MODE23_TypeDef *pstcM0PBt = (M0P_TIM0_MODE23_TypeDef *)((uint32_t)M0P_TIM0_MODE23+0x100*enUnit);
    ASSERT(IS_VALID_TIM(enUnit));
    
    pstcM0PBt->M23CR_f.TG = TRUE;
    
    return enResult;    
}

/** *****************************************************************************
** \brief Base Timer Software Brake Enable (Mode 23)
**
**
** \param [in] enUnit Timer Channel Select (TIM0, TIM1, TIM2)
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

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
 * @file   trim.c
 *
 * @brief  Source file for TRIM functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "trim.h"
/**
 *******************************************************************************
 ** \addtogroup TrimGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#define IS_VALID_TRIMINT(x)             (TrimStop     == (x) ||\
                                         TrimCalCntOf == (x) ||\
                                         TrimXTLFault == (x) ||\
                                         TrimXTHFault == (x) ||\
                                         TrimPLLFault == (x))


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
** \brief Trim interrupt flag get
**
**
** \param [in] enIntType Interrupt type (RefStop, CalCntOf, XTAL32KFault, XTAL32MFault)
**
** \retval TRUE or FALSE
*****************************************************************************/
boolean_t Trim_GetIntFlag(en_trim_inttype_t enIntType)
{  
    ASSERT(IS_VALID_TRIMINT(enIntType));
    
    if(M0P_CLK_TRIM->IFR&enIntType)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
     
}

/** 
******************************************************************************* 
** \brief Trim interrupt flag cleared 
** 
** 
** \param [in] enIntType interrupt type (RefStop, CalCntOf, XTAL32KFault, XTAL32MFault) 
** 
**\retval Ok or Error 
*******************************************************************************/
en_result_t Trim_ClearIntFlag(en_trim_inttype_t enIntType)
{
    en_result_t enResult = Error;
  
    ASSERT(IS_VALID_TRIMINT(enIntType));
    
    M0P_CLK_TRIM->ICLR &= ~(uint32_t)enIntType;
    
    return enResult;
}



/**
*****************************************************************************
** \brief Trim interrupt enable
**
**
**
** \retval Null
*************************************************************************/
void Trim_EnableIrq (void)
{
    M0P_CLK_TRIM->CR_f.IE = TRUE;
}

/**
*****************************************************************************
** \brief Trim interrupt disable
**
**
**
** \retval Ok or Error
*****************************************************************************/
void Trim_DisableIrq(void)
{
    M0P_CLK_TRIM->CR_f.IE = FALSE;
}

/**
*****************************************************************************
** \brief Trim initialization configuration
**
**
** \param [in] pstcCfg Trim configuration structure pointer
**
** \retval Ok or Error
*************************************************************************/
en_result_t Trim_Init(stc_trim_cfg_t* pstcCfg)
{
    en_result_t enResult = Error;

    M0P_CLK_TRIM->CR = 0;
    
    M0P_CLK_TRIM->CR = (uint32_t)pstcCfg->enCALCLK |
                       (uint32_t)pstcCfg->enREFCLK |
                       (uint32_t)pstcCfg->enMON;  
    
    M0P_CLK_TRIM->REFCON = pstcCfg->u32RefCon;
    M0P_CLK_TRIM->CALCON = pstcCfg->u32CalCon;
    
    enResult = Ok;
    
    return enResult;
}

/**
***********************************************************************
** \brief Trim calibration/monitoring start run
**
**
**
** \retval Null
***********************************************************************/
void Trim_Run(void)
{
    M0P_CLK_TRIM->CR_f.TRIM_START = TRUE;
}

/**
********************************************************************
** \brief Trim calibration/monitoring stop
**
**
**
**
** \retval Null
***************************************************************************/
void Trim_Stop(void)
{
    M0P_CLK_TRIM->CR_f.TRIM_START = FALSE;
}

/**
***********************************************************************************
** \brief Trim reference counter count value acquisition
**
**
** \retval u32Data reference counter count value
***********************************************************************/
uint32_t Trim_RefCntGet(void)
{
    return (uint32_t)M0P_CLK_TRIM->REFCNT;
}

/**
*****************************************************************************
** \brief Get Trim calibration counter value
**
**
**
**
** \retval u32Data Calibration counter value
*********************************************************************/
uint32_t Trim_CalCntGet(void)
{
    return (uint32_t)M0P_CLK_TRIM->CALCNT;
}

//@} // TrimGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

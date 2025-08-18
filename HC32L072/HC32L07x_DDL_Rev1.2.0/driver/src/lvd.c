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
 * @file   lvd.c
 *
 * @brief  Source file for LVD functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lvd.h"

/**
 ******************************************************************************
 ** \addtogroup LvdGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_INPUT(x)       ( (x) <= LvdInputPB07 )

#define IS_VALID_THRESHOLD(x)   ( (x) <= LvdTH3p3V )

#define IS_VALID_FILTER(x)      ( (x) <= LvdFilter29ms )

#define IS_VALID_IRQTYPE(x)     ( (x) <= LvdIrqFall )


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
// static void LvdEnableNvic(void);
// static void LvdDisableNvic(void);
// static en_result_t LvdEnable(en_lvd_type_t enType, boolean_t bFlag);

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/** 
* \brief 
* Enable LVD interrupt 
* 
* \param [in] enType LVD interrupt type *
* \retval en_result_t Ok: Setup successful
* \retval en_result_t ErrorInvalidParameter: Invalid type
*/
void Lvd_EnableIrq(void)
{
    M0P_LVD->CR_f.IE = TRUE;
}

/**
* \brief
* Disable LVD interrupt
*
* \param None
*
* \retval None
*/
void Lvd_DisableIrq(void)
{
    M0P_LVD->CR_f.IE = FALSE;
}

/**
* \brief
* LVD initialization
*
* \param [in] pstcCfg LVD configuration pointer
*
* \retval None
*/
void Lvd_Init(stc_lvd_cfg_t *pstcCfg)
{
    M0P_LVD->CR = 0;

    M0P_LVD->CR = (uint32_t)pstcCfg->enAct        |
                  (uint32_t)pstcCfg->enFilter     |
                  (uint32_t)pstcCfg->enFilterTime |
                  (uint32_t)pstcCfg->enInputSrc   |
                  (uint32_t)pstcCfg->enIrqType    |
                  (uint32_t)pstcCfg->enThreshold;
}

/** 
* \brief 
* Enable LVD 
* 
* \param None 
* 
* \retval None 
* 
*/
void Lvd_Enable(void)
{
    M0P_LVD->CR_f.LVDEN = 1u;
}

/** 
* \brief 
* Deactivate LVD 
* 
* \param None 
* 
* \retval None
*/
void Lvd_Disable(void)
{
    M0P_LVD->CR_f.LVDEN = 0u;
}

/**
* \brief
* Get LVD interrupt flag
*
* \param None
*
* \retval boolean_t interrupt flag
*/
boolean_t Lvd_GetIrqStat(void)
{
    return M0P_LVD->IFR_f.INTF;

}

/**
* \brief
* Clear LVD interrupt flag
*
* \param None
*
* \retval None
*/
void Lvd_ClearIrq(void)
{
    M0P_LVD->IFR_f.INTF = 0u;
}

/**
* \brief
* Get filter result
*
* \param None
*
* \retval boolean_t Filter result 
*/
boolean_t Lvd_GetFilterResult(void)
{
    return (boolean_t)M0P_LVD->IFR_f.FILTER;
}
//@} // LvdGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


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
 * @file   pca.c
 *
 * @brief  Source file for PCA functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "pca.h"

/**
 ******************************************************************************
 ** \addtogroup PCNTGroup
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

/**
******************************************************************************
** \brief Get interrupt source flags
** @param IT_Src : Interrupt source flags
** \retval FALSE or TRUE
**
************************************************************************/
boolean_t Pca_GetItStatus(en_pca_ccficlr_t It_Src)
{
    return (((M0P_PCA->CCON)>>It_Src) & 1) > 0? TRUE : FALSE;
}

/**
**********************************************************************************
** \brief Clears the interrupt source flag
** @param IT_Src: Interrupt source flag
** \retval None
**
**********************************************************************************/
void Pca_ClrItStatus(en_pca_ccficlr_t It_Src)
{
    M0P_PCA->ICLR &= ~(uint32_t)(1<<It_Src);
}

/**
**************************************************************************
** \brief PCA counter operation control PCA_CCON CR control bit
** @param NewStatus : TRUE or FALSE
** \retval None
**
******************************************************************************/
void Pca_StartPca(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CCON)), 6, NewStatus);
}

/**
**********************************************************************************
** \brief PCA idle mode: Sets whether to stop the PCA operation.
** @param NewStatus : TRUE or FALSE
** \retval None
**
******************************************************************************/
void Pca_SetCidl(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CMOD)), 7, NewStatus);
}

/**
**********************************************************************************
** \brief PCA module 4 watchdog enable control
** @param NewStatus: TRUE or FALSE
** \retval None
**
******************************************************************************/
void Pca_Set4Wdte(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CMOD)), 6, NewStatus);
}

/**
**************************************************************************
** \brief PCA counter interrupt control CFIE in PCA_CMOD, corresponding to the control interrupt bits CF in PCA_CCON and CF in PCA_ICLR
** @param NewStatus: TRUE or FALSE
** \retval None
**
******************************************************************************/
void Pca_ConfPcaIt(boolean_t NewStatus)
{
    SetBit((uint32_t)(&(M0P_PCA->CMOD)), 0, NewStatus);
}

/**
**********************************************************************************
** \brief PCA compare capture interrupt enable control CCIE in PCA_CCAPMx
** @param Modulex: pca_module0~4
** @param NewStatus: TRUE or FALSE 
** \retval None 
**
******************************************************************************/
void Pca_ConfModulexIt(en_pca_module_t Modulex, boolean_t NewStatus)
{
    switch(Modulex)
    {
        case PcaModule0:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM0)), 0, NewStatus);
            break;
        case PcaModule1:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM1)), 0, NewStatus);
            break;        
        case PcaModule2:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM2)), 0, NewStatus);
            break;
        case PcaModule3:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM3)), 0, NewStatus);
            break;
        case PcaModule4:
            SetBit((uint32_t)(&(M0P_PCA->CCAPM4)), 0, NewStatus);
            break;
        default:
            break;
    }
}

/**
******************************************************************************
** \brief Initialization of PCA module 0
** @param InitStruct : PCA initialization configuration structure
** \retval None 
**
******************************************************************************/
void Pca_M0Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM0_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM0_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM0_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM0_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM0_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM0_f.PWM  = InitStruct->pca_pwm;
    M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP0L_f.CCAP0 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP0H_f.CCAP0 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP0_f.CCAP0 = InitStruct->pca_ccap;        
    }
    M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
***************************************************************************
** \brief PCA module 1 initialization
** @param InitStruct: PCA initialization configuration structure
** \retval None
**
**********************************************************************************/
void Pca_M1Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM1_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM1_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM1_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM1_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM1_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM1_f.PWM  = InitStruct->pca_pwm;
    M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP1L_f.CCAP1 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP1H_f.CCAP1 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP1_f.CCAP1 = InitStruct->pca_ccap;        
    }
    M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
** \brief PCA module 2 initialization
** @param InitStruct: PCA initialization configuration structure
** \retval None
**
**********************************************************************************/
void Pca_M2Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM2_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM2_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM2_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM2_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM2_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM2_f.PWM  = InitStruct->pca_pwm;
    M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP2L_f.CCAP2 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP2H_f.CCAP2 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP2_f.CCAP2 = InitStruct->pca_ccap;        
    }
    M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
** \brief Initialization of PCA module 3
** @param InitStruct: PCA initialization configuration structure
** \retval None
**
**********************************************************************************/
void Pca_M3Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM3_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM3_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM3_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM3_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM3_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM3_f.PWM  = InitStruct->pca_pwm;
    M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP3L_f.CCAP3 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP3H_f.CCAP3 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP3_f.CCAP3 = InitStruct->pca_ccap;        
    }
    M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
****************************************************************************** 
** \brief PCA Module 4 Initialization
** @param InitStruct: PCA initialization configuration structure
** \retval None
**
**************************************************************************/
void Pca_M4Init(stc_pcacfg_t* InitStruct)
{
    M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
    M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
    M0P_PCA->CCAPM4_f.ECOM = InitStruct->pca_ecom;
    M0P_PCA->CCAPM4_f.CAPP = InitStruct->pca_capp;
    M0P_PCA->CCAPM4_f.CAPN = InitStruct->pca_capn;
    M0P_PCA->CCAPM4_f.MAT  = InitStruct->pca_mat;
    M0P_PCA->CCAPM4_f.TOG  = InitStruct->pca_tog;
    M0P_PCA->CCAPM4_f.PWM  = InitStruct->pca_pwm;
    M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
    if(InitStruct->pca_pwm == PcaPwm8bitEnable)
    {
        M0P_PCA->CCAP4L_f.CCAP4 = InitStruct->pca_ccapl;
        M0P_PCA->CCAP4H_f.CCAP4 = InitStruct->pca_ccaph;
    }
    else
    {
        M0P_PCA->CCAP4_f.CCAP4 = InitStruct->pca_ccap;        
    }
    M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
** \brief PCA Reads the value of the CNT register
** @param None
** \retval The lower halfword value of CNT
**
*****************************************************************************/
uint16_t Pca_GetCnt(void)
{
    return (uint16_t)(M0P_PCA->CNT);
}

/**
**********************************************************************************
** \brief PCA writes a value to the CNT register
** @param cnt: The value to be written
** \retval None
**
**********************************************************************************/
void Pca_SetCnt(uint16_t cnt)
{
    if(GetBit((uint32_t)(&(M0P_PCA->CCON)), 6)==TRUE)
    {
        Pca_StartPca(FALSE);
        M0P_PCA->CNT_f.CNT = cnt;        
        Pca_StartPca(TRUE);        
    }
    else
    {
        M0P_PCA->CNT_f.CNT = cnt;
    }

}

/**
**************************************************************************
** \brief PCA Returns the value of the specified channel's compare high-speed output flag register.
** @param Modulex: Channel number x = 0, 1, 2, 3, 4
** \retval TRUE or FALSE
**
******************************************************************************/
boolean_t Pca_GetOut(en_pca_module_t Modulex)
{
    return GetBit((uint32_t)(&(M0P_PCA->CCAPO)), Modulex);
}

/**
**********************************************************************************
** \brief PCA Set the value of the compare capture 16-bit register CCAPx.
** @param Modulex: Channel number x = 0, 1, 2, 3, 4
** @param Value: Value to set
** \retval None
**
**************************************************************************/
void Pca_SetCcap(en_pca_module_t Modulex, uint16_t Value)
{
    switch(Modulex)
    {
        case 0:
            M0P_PCA->CCAP0_f.CCAP0 = Value;
        break;
        case 1:
            M0P_PCA->CCAP1_f.CCAP1 = Value;
            break;
        case 2:
            M0P_PCA->CCAP2_f.CCAP2 = Value;
            break;
        case 3:
            M0P_PCA->CCAP3_f.CCAP3 = Value;
            break;
        case 4:
            M0P_PCA->CCAP4_f.CCAP4 = Value;
            break;
        default:
            break;
    }    
}

/**
**************************************************************************
** \brief PCA reads the value of the compare capture 16-bit register CCAPx
** @param Modulex: channel number x = 0, 1, 2, 3, 4
** \retval CCAPx value, x = 0, 1, 2, 3, 4
**
******************************************************************************/
uint16_t Pca_GetCcap(en_pca_module_t Modulex)
{
    uint16_t tmp;
    switch(Modulex)
    {
        case 0:
            tmp = M0P_PCA->CCAP0_f.CCAP0;
        break;
        case 1:
            tmp = M0P_PCA->CCAP1_f.CCAP1;
            break;
        case 2:
            tmp = M0P_PCA->CCAP2_f.CCAP2;
            break;
        case 3:
            tmp = M0P_PCA->CCAP3_f.CCAP3;
            break;
        case 4:
            tmp = M0P_PCA->CCAP4_f.CCAP4;
            break;
        default:
            break;
    }
    return tmp;
}

/**
******************************************************************************
** \brief PCA sets auto-reload register value
** @param None
** \retval None
**
******************************************************************************/
void Pca_SetCarr(uint16_t Value)
{
    M0P_PCA->CARR_f.CARR = Value;
}

/**
******************************************************************************
** \brief PCA Gets the value of the auto-reload register
** @param None
** \retval None
**
******************************************************************************/
uint16_t Pca_GetCarr(void)
{
    return M0P_PCA->CARR_f.CARR;
}

/**
**********************************************************************************
** \brief PCA Sets the upper and lower 8 bits of the compare capture register
** @param Modulex: Channel number x = 0, 1, 2, 3, 4
** @param ValueH: Value to be written to the upper 8 bits
** @param ValueL: Value to be written to the lower 8 bits
** \retval None 
**
******************************************************************************/
void Pca_SetCcapHL(en_pca_module_t Modulex, uint8_t ValueH, uint8_t ValueL)
{
    switch(Modulex)
    {
        case 0:
            M0P_PCA->CCAP0H_f.CCAP0 = ValueH;
            M0P_PCA->CCAP0L_f.CCAP0 = ValueL;
            break;
        case 1:
            M0P_PCA->CCAP1H_f.CCAP1 = ValueH;
            M0P_PCA->CCAP1L_f.CCAP1 = ValueL;
            break;
        case 2:
            M0P_PCA->CCAP2H_f.CCAP2 = ValueH;
            M0P_PCA->CCAP2L_f.CCAP2 = ValueL;
            break;
        case 3:
            M0P_PCA->CCAP3H_f.CCAP3 = ValueH;
            M0P_PCA->CCAP3L_f.CCAP3 = ValueL;
            break;
        case 4:
            M0P_PCA->CCAP4H_f.CCAP4 = ValueH;
            M0P_PCA->CCAP4L_f.CCAP4 = ValueL;
            break;
        default:
            break;
    }
}

/**
******************************************************************************
** \brief PCA Reads the upper and lower 8 bits of the compare capture register
** @param Modulex: Channel number x = 0, 1, 2, 3, 4
** @param ValueH: Value of the upper 8 bits of CCAPx
** @param ValueL: Value of the lower 8 bits of CCAPx
** \retval None 
**
******************************************************************************/
void Pca_GetCcapHL(en_pca_module_t Modulex, uint8_t *ValueH, uint8_t *ValueL)
{
    switch(Modulex)
    {
        case 0:
            *ValueH = M0P_PCA->CCAP0H_f.CCAP0;
            *ValueL = M0P_PCA->CCAP0L_f.CCAP0;
            break;
        case 1:
            *ValueH = M0P_PCA->CCAP1H_f.CCAP1;
            *ValueL = M0P_PCA->CCAP1L_f.CCAP1;
            break;
        case 2:
            *ValueH = M0P_PCA->CCAP2H_f.CCAP2;
            *ValueL = M0P_PCA->CCAP2L_f.CCAP2;
            break;
        case 3:
            *ValueH = M0P_PCA->CCAP3H_f.CCAP3;
            *ValueL = M0P_PCA->CCAP3L_f.CCAP3;
            break;
        case 4:
            *ValueH = M0P_PCA->CCAP4H_f.CCAP4;
            *ValueL = M0P_PCA->CCAP4L_f.CCAP4;
            break;
        default:
            break;
    }    
}
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/






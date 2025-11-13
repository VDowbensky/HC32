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
 * @file   opa.c
 *
 * @brief  Source file for OPA functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "opa.h"

/**
 ******************************************************************************
 ** \addtogroup OPAGroup
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
**************************************************************************
** \brief OPA output channel configuration
**
** \param Opax: Specifies which OPA to use. There are three OPAs, with values: Opa0, Opa1, and Opa2
** OutChs: OPA output channel configuration. Multiple channels can be enabled.
** \retval None
**
**************************************************************************/
void Opa_OutChannelConfig(en_opa_t Opax, stc_opa_oenx_config_t OutChs)
{
	if ((Opax==Opa0)||(Opax==Opa1)||(Opax==Opa2))
	{
		SetBit((uint32_t)(&(M0P_OPA->CR0)), OPA_CHANNEL_OUT_Pos(Opax, Opa_Ch_Oen1), OutChs.opa_ch1);
		SetBit((uint32_t)(&(M0P_OPA->CR0)), OPA_CHANNEL_OUT_Pos(Opax, Opa_Ch_Oen2), OutChs.opa_ch2);
		SetBit((uint32_t)(&(M0P_OPA->CR0)), OPA_CHANNEL_OUT_Pos(Opax, Opa_Ch_Oen3), OutChs.opa_ch3);
		SetBit((uint32_t)(&(M0P_OPA->CR0)), OPA_CHANNEL_OUT_Pos(Opax, Opa_Ch_Oen4), OutChs.opa_ch4);
	}
}

/**
******************************************************************************
** \brief OPAx enable or disable
**
** \param Opax: 5 OPAs in total, values: Opa0, Opa1, Opa2, Opa3, Opa4
** NewStatus: Configure Opax to be enabled or disabled, TRUE or FALSE
** \retval None
**
**********************************************************************************/
void Opa_Cmd(en_opa_t Opax, boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_OPA->CR1)), Opax, NewStatus);
	if(Opax == Opa3)       /*When OPA3 is enabled, DAC0 cannot use OPA3 as an output buffer*/
	{
		M0P_OPA->CR1 &= (uint32_t)~(1<<Opa_Dac0Buff);
	}else if(Opax == Opa4) /*When OPA4 is enabled, DAC1 cannot use OPA4 as an output buffer*/
	{
		M0P_OPA->CR1 &= (uint32_t)~(1<<Opa_Dac1Buff);
	}else
    {
    
    }
}

/**
******************************************************************************
** \brief DAC buffer enable or disable
**
** \param Buffx: Opa_Adc0Buff or Opa_Adc1Buff
** NewStatus: Configure Buffx to enable or disable, TRUE or FALSE
** \retval None
**
**********************************************************************************/
void Opa_DacBufCmd(en_opa_dac_buff_t Buffx, boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_OPA->CR1)), Buffx, NewStatus);
	if (Buffx == Opa_Dac0Buff)
    {
		M0P_OPA->CR1 &= (uint32_t)~(1<<Opa3);  /*DAC0 uses OP3 units to increase cache enable, so OPA3 is disabled*/
	}else
	{
		M0P_OPA->CR1 &= (uint32_t)~(1<<Opa4);  /*DAC1 uses OP4 units to increase cache enable, so OPA4 is disabled*/
	}
}

/**
**************************************************************************
** \brief Configure OPA teach-to-zero enable
**
** \param Opax: Specifies which OPA to use. There are five OPAs, with possible values: Opa0, Opa1, Opa2, Opa3, and Opa4.
** NewStatus: Enables or disables the Opax zero setting. TRUE or FALSE.
** \retval: None
**
**************************************************************************/
void Opa_CalCmd(en_opa_t Opax, boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_OPA->CR1)), OPA_AZEN_Pos(Opax), NewStatus);
}

/**
****************************************************************************** 
** \brief automatically teaches zero parameter configuration 
** 
** \param InitZero: 
** \retval None 
**
******************************************************************************/
void Opa_CalConfig(stc_opa_zconfig_t* InitZero)
{
	M0P_OPA->CR_f.CLK_SEL = InitZero->enClksrc;
	M0P_OPA->CR_f.CLK_SW_SET = InitZero->bClk_sw_set;
	M0P_OPA->CR_f.AZ_PULSE = InitZero->bAz_pulse;
	M0P_OPA->CR_f.ADCTR_EN   = InitZero->bAdctr_en; 
}

/**
******************************************************************************
** \brief Software triggers automatic zero teach
**
** \param InitZero:
** \retval None
**
**************************************************************************/
void Opa_CalSwTrig(void)
{
	M0P_OPA->CR_f.TRIGGER = TRUE;
}


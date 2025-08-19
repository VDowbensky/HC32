/****************************************************************************** 
* Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved. 
* 
* This software component is licensed by XHSC under BSD 3-Clause license 
* (the "License"); You may not use this file except in compliance with the 
* License. You may obtain a copy of the License at: 
* opensource.org/licenses/BSD-3-Clause 
* 
******************************************************************************/

/****************************************************************************** 
* @file dac.h 
* 
* @brief Header file for DAC functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __DAC_H__
#define __DAC_H__

/******************************************************************************/
/* Include files */
/**************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with a C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
******************************************************************************
** \brief Enable or disable instruction
**************************************************************************/
typedef enum
{
    DacDisable = 0u, //Disable
    DacEnable = 1u //Enable
}en_en_state_t;

/**
**********************************************************************************
** \brief Enable or disable the DAC0 channel output buffer DAC_CR0: BOFF0
**************************************************************************/
typedef enum
{
    DacBoffDisable = 1u,
    DacBoffEnable = 0u
}en_dac_boff_t;

/**
******************************************************************************
** \brief Enable or disable DAC0 channel trigger enable DAC_CR0: TEN0
**************************************************************************/
typedef enum
{
    DacTenDisable = 0u,
    DacTenEnable = 1u
}en_dac_ten_t;

/**
******************************************************************************
** \brief DAC0 channel trigger select DAC_CR0: TSEL0
******************************************************************************/
typedef enum
{
    DacTim0Tradc = 0u, //TIM0_TRADC trigger
    DacTim1Tradc = 1u, //TIM1_TRADC trigger
    DacTim2Tradc = 2u, //TIM2_TRADC trigger
    DacTim3Tradc = 3u, //TIM3_TRADC trigger
    DacTim4Tradc = 4u, //TIM4_TRADC trigger
    DacTim5Tradc = 5u, //TIM5_TRADC trigger
    DacSwTriger = 6u, //Software trigger
    DacExPortTriger = 7u //External port trigger
}en_dac_tsel_t;

/**
********************************************************************************
** \brief DAC0 channel noise/triangle wave generation enabled or disabled DAC_CR0: WAVE0
********************************************************************/
typedef enum
{
    DacWaveDisable = 0u, //Disable wave generation
    DacNoiseEnable = 1u, //Enable noise wave generation
    DacTrWaveEnable = 2u //Enable triangle wave generation
}en_dac_wave_t;

/**
********************************************************************************
** \brief DACx channel mask/amplitude selector DAC_CR0: MAMP0 & MAMP1
************************************************************************/
typedef enum
{
    DacMemp01 = 0u,
    DacMenp03 = 1u,
    DacMenp07 = 2u,
    DacMenp15 = 3u,
    DacMenp31 = 4u,
    DacMenp63 = 5u,
    DacMenp127 = 6u,
    DacMenp255 = 7u,
    DacMenp511 = 8u,
    DacMenp1023 = 9u,
    DacMenp2047 = 10u,
    DacMenp4095 = 11u
}en_dac_mamp_t;

/**
********************************************************************************
** \brief DACx channel DMA enable or disable DAC_CR0: DMAEN0 & DMAEN1
****************************************************************************/

/**
************************************************************************************
** \brief DACx channel DMA underflow interrupt enable or disable DAC_CR0: DMAUDRIE0 & DMAUDRIE1
******************************************************************************/

/**
******************************************************************************
** \brief DACx reference voltage selection DAC_CR0: SREF0 & SREF1
**************************************************************************/
typedef enum
{
    DacVoltage1V5 = 0u, //Internal 1.5V
    DacVoltage2V5 = 1u, //Internal 2.5V
    DacVoltageExRef = 2u, //External reference voltage ExRef (PB01)
    DacVoltageAvcc = 3u //AVCC voltage
}en_dac_sref_t;

/**
******************************************************************************
** \brief DACx trigger selection register DAC_ETRS
******************************************************************************/
typedef enum
{
    DacPortTrigPA9 = 0u, //Trigger port PA9
    DacPortTrigPB9 = 1u, //Trigger port PB9
    DacPortTrigPC9 = 2u, //Trigger port PC9
    DacPortTrigPD9 = 3u, //Trigger port PD9
    DacPortTrigPE9 = 4u, //Trigger port PE9
    DacPortTrigPF9 = 5u //Trigger port PF9
}en_port_trig_t;

/**
****************************************************************************
** \brief Alignment
**************************************************************************/
typedef enum
{
    DacRightAlign = 0u, //Right alignment
    DacLeftAlign = 1u //Left alignment
}en_align_t;

/**
******************************************************************************
** \brief Number of data bits
**************************************************************************/
typedef enum
{
    DacBit8 = 0u, //8 bits
    DacBit12 = 1u //12 bits
}en_bitno_t;

/**
**********************************************************************************
** \brief Initialization configuration structure
******************************************************************************/
typedef struct
{
    en_dac_boff_t boff_t; 
    en_dac_ten_t ten_t; 
    en_dac_tsel_t tsel_t; 
    en_dac_wave_t wave_t; 
    en_dac_mamp_t mamp_t; 
    en_dac_sref_t sref_t; 
    en_port_trig_t port_trig_t; 
    en_align_t align; 
    uint16_t dhr12; 
    uint8_t dhr8;
}stc_dac_cfg_t;

///< DAC0 operation API
extern void Dac0_Init(stc_dac_cfg_t* DAC_InitStruct);
extern void Dac0_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data);
extern uint16_t Dac0_GetDataOutputValue(void);
extern void Dac0_DmaCmd(boolean_t NewState);
extern void Dac0_DmaITCfg(boolean_t NewState);
extern boolean_t Dac0_GetITStatus(void);
extern void Dac0_Cmd(boolean_t NewState);
extern void Dac0_SoftwareTriggerCmd(void);


///< DAC1 operation API
extern void Dac1_Init(stc_dac_cfg_t* DAC_InitStruct);
extern void Dac1_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data);
extern uint16_t Dac1_GetDataOutputValue(void);
extern void Dac1_DmaCmd(boolean_t NewState);
extern void Dac1_DmaITCfg(boolean_t NewState);
extern boolean_t Dac1_GetITStatus(void);
extern void Dac1_Cmd(boolean_t NewState);
extern void Dac1_SoftwareTriggerCmd(void);

#ifdef __cplusplus
}
#endif
#endif //__DAC_H__

/******************************************************************************/
/* EOF (not truncated) */
/******************************************************************************/
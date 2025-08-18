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
 * @file   dac.c
 *
 * @brief  Source file for DAC functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "dac.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
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
** \brief Enable DMA for the associated channel (DMAEN0 in DMA_CR0)
**
** @param NewState: TRUE or FALSE
** \retval None
**
**************************************************************************/
void Dac0_DmaCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 12, NewState);
}

/**
**********************************************************************************
** \brief Enable DMA for the associated channel (DMAEN1 in DMA_CR0)
**
** @param NewState: TRUE or FALSE
** \retval None
**
******************************************************************************/
void Dac1_DmaCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 28, NewState);
}

/**
**********************************************************************************
** \brief Configure DAC DMA underflow interrupt, DMAUDRIE0 in DMA_CR0
**
** @param NewState: TRUE or FALSE
** \retval None
**
******************************************************************************/
void Dac0_DmaITCfg(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 13, NewState);
}

/**
**************************************************************************
** \brief Configure the DAC's DMA underflow interrupt, DMAUDRIE1 in DMA_CR0
**
** @param NewState: TRUE or FALSE
** \retval None
**
**************************************************************************/
void Dac1_DmaITCfg(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 29, NewState);
}

/**
**********************************************************************************
** \brief Get the DAC's DMA underflow interrupt flag status, DMAUDR0 in DMA_SR
**
** @param None
** \retval TRUE or FALSE
**
*****************************************************************************/
boolean_t Dac0_GetITStatus(void)
{
    return GetBit((uint32_t)(&(M0P_DAC->SR)), 13);
}

/**
******************************************************************************
** \brief Gets the DAC DMA underflow interrupt flag status, DMAUDR1 in DMA_SR
**
** @param None
** \retval TRUE or FALSE
**
******************************************************************************/
boolean_t Dac1_GetITStatus(void)
{
    return GetBit((uint32_t)(&(M0P_DAC->SR)), 29);
}

/**
**********************************************************************************
** \brief Configures DAC enable/disable, EN0 in DMA_CR0
**
** @param NewState: TRUE or FALSE
** \retval None
**
**************************************************************************/
void Dac0_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 0, NewState);
}

/**
**************************************************************************
** \brief Configures DAC enable/disable, EN1 in DMA_CR0
**
** @param NewState: TRUE or FALSE
** \retval None
**
**************************************************************************/
void Dac1_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_DAC->CR0)), 16, NewState);
}

/**
**********************************************************************************
** \brief Software trigger register, triggers DAC conversion, SWTRIG0 in DMA_SWTRIGR
**
** @param None
** \retval None
**
******************************************************************************/
void Dac0_SoftwareTriggerCmd(void)
{
    SetBit((uint32_t)(&(M0P_DAC->SWTRIGR)), 0, TRUE);
}

/**
**********************************************************************************
** \brief Software trigger register, triggers DAC conversion SWTRIG1 in DMA_SWTRIGR
**
** @param None
** \retval None
**
**********************************************************************************/
void Dac1_SoftwareTriggerCmd(void)
{
    SetBit((uint32_t)(&(M0P_DAC->SWTRIGR)), 1, TRUE);
}
    
/**
**************************************************************************
** \brief Initialize DAC0
**
** @param DAC_InitStruct: Structure used to initialize DAC0
** \retval None
**
******************************************************************************/
void Dac0_Init(stc_dac_cfg_t* DAC_InitStruct)
{
    M0P_DAC->CR0_f.BOFF0 = DAC_InitStruct->boff_t;
    M0P_DAC->CR0_f.TEN0  = DAC_InitStruct->ten_t;
    M0P_DAC->CR0_f.TSEL0 = DAC_InitStruct->tsel_t;
    M0P_DAC->CR0_f.WAVE0 = DAC_InitStruct->wave_t;
    M0P_DAC->CR0_f.MAMP0 = DAC_InitStruct->mamp_t;
    M0P_DAC->CR0_f.SREF0 = DAC_InitStruct->sref_t;
    
    if(DAC_InitStruct->align == DacLeftAlign)
    {
        M0P_DAC->DHR12L0_f.DHR0 = DAC_InitStruct->dhr12;
    }
    else if(DAC_InitStruct->align == DacRightAlign)
    {
        M0P_DAC->DHR12R0_f.DHR0 = DAC_InitStruct->dhr12;
    }
    else
    {
        M0P_DAC->DHR8R0_f.DHR0 = DAC_InitStruct->dhr8;
    }
}

/**
******************************************************************************
** \brief Initialize DAC1
**
** @param DAC_InitStruct: Structure used to initialize DAC1
** \retval None
**
**********************************************************************************/
void Dac1_Init(stc_dac_cfg_t* DAC_InitStruct)
{
    M0P_DAC->CR0_f.BOFF1 = DAC_InitStruct->boff_t;
    M0P_DAC->CR0_f.TEN1  = DAC_InitStruct->ten_t;
    M0P_DAC->CR0_f.TSEL1 = DAC_InitStruct->tsel_t;
    M0P_DAC->CR0_f.WAVE1 = DAC_InitStruct->wave_t;
    M0P_DAC->CR0_f.MAMP1 = DAC_InitStruct->mamp_t;
    M0P_DAC->CR0_f.SREF1 = DAC_InitStruct->sref_t;
    
    if(DAC_InitStruct->align == DacLeftAlign)
    {
        M0P_DAC->DHR12L1_f.DHR1 = DAC_InitStruct->dhr12;
    }
    else if(DAC_InitStruct->align == DacRightAlign)
    {
        M0P_DAC->DHR12R1_f.DHR1 = DAC_InitStruct->dhr12;
    }
    else
    {
        M0P_DAC->DHR8R1_f.DHR1 = DAC_InitStruct->dhr8;
    }
}

/**
******************************************************************************
** \brief Writes data to the DAC0 data holding register
**
** @param DAC_Channel: Dac_0
** @param DAC_Align: Right_Align and Left_Align
** @param DAC_Bit: Bit8 and Bit12
** @param Data: Data to be sent
** \retval None
**
******************************************************************************/
void Dac0_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data)
{
        if(DAC_Align == DacRightAlign)
        {
            if(DAC_Bit == DacBit8)
            {
                M0P_DAC->DHR8R0_f.DHR0 = (uint8_t)Data;
            }
            else if(DAC_Bit == DacBit12)
            {
                M0P_DAC->DHR12R0_f.DHR0 = Data;
            }
            else
            {
              return;
            }
        }
        else if(DAC_Align == DacLeftAlign)
        {
            if(DAC_Bit == DacBit8)
            {
                return;
            }
            else if(DAC_Bit == DacBit12)
            {
                M0P_DAC->DHR12L0_f.DHR0 = Data;
            }
            else
            {
              return;
            }
        }
        else
        {
            return;
        }
}

/**
**************************************************************************
** \brief Write data to the data holding register of DAC1
**
** @param DAC_Channel: Dac_1
** @param DAC_Align: Right_Align Left_Align
** @param DAC_Bit: Bit8 and Bit12
** @param Data: Data to be sent
** \retval None
**
**************************************************************************/
void Dac1_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data)
{
        if(DAC_Align == DacRightAlign)
        {
            if(DAC_Bit == DacBit8)
            {
                M0P_DAC->DHR8R1_f.DHR1 = (uint8_t)Data;
            }
            else if(DAC_Bit == DacBit12)
            {
                M0P_DAC->DHR12R1_f.DHR1 = Data;
            }
            else
            {
              return;
            }
        }
        else if(DAC_Align == DacLeftAlign)
        {
            if(DAC_Bit == DacBit8)
            {
                return;
            }
            else if(DAC_Bit == DacBit12)
            {
                M0P_DAC->DHR12L1_f.DHR1 = Data;
            }
            else
            {
              return;
            }
        }
        else
        {
            return;
        }
}

/**
**********************************************************************************
** \brief Get DAC data output register DAC_DOR0
**
** @param None
** \retval DAC_DOR0 value
**
******************************************************************************/
uint16_t Dac0_GetDataOutputValue(void)
{
    uint16_t tmp;
    tmp = M0P_DAC->DOR0_f.DOR0;
    return tmp&0x0fff;
}

/**
**************************************************************************
** \brief Get DAC data output register DAC_DOR1
**
** @param None
** \retval Value of DAC_DOR1
**
**************************************************************************/
uint16_t Dac1_GetDataOutputValue(void)
{
    uint16_t tmp;
    tmp = M0P_DAC->DOR1_f.DOR1;
    return tmp&0x0fff;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



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
* @file i2s.h 
* 
* @brief Header file for I2S functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __I2S_H__
#define __I2S_H__
/******************************************************************************/
/* Include files */
/**************************************************************************/
#include "ddl.h"

/**
******************************************************************************
** \brief The following macros define the corresponding register bits.
**************************************************************************/
#define I2S_IT_TXE ((uint8_t)7) // the TXEIE of I2Sx_CR
#define I2S_IT_RXNEIE ((uint8_t)6) // the RXNEI of I2Sx_CR
#define I2S_IT_ERRIE ((uint8_t)5) // the ERRIE of I2Sx_CR
#define I2S_RDMA_EN ((uint8_t)1) // the RDMA of I2Sx_CR
#define I2S_LDMA_EN ((uint8_t)0) // the LDMA of I2Sx_CR

#define I2S_RXNE_L ((uint8_t)0) // the RXNE_L of I2Sx_SR
#define I2S_TXE_L ((uint8_t)1) // the TXE_L of I2Sx_SR
#define I2S_UDR_L ((uint8_t)2) // the UDR_L of I2Sx_SR
#define I2S_UDR_R ((uint8_t)3) // the UDR_R of I2Sx_SR
#define I2S_OVR_L ((uint8_t)6) // the OVR_L of I2Sx_SR
#define I2S_BSY ((uint8_t)7) // the BSY of I2Sx_SR
#define I2S_FRE ((uint8_t)8) // the FRE of I2Sx_SR
#define I2S_OVR_R ((uint8_t)13)// the OVR_R of I2Sx_SR
#define I2S_RXNE_R ((uint8_t)14)// the RXNE_R of I2Sx_SR
#define I2S_TXE_R ((uint8_t)15)// the TXE_R of I2Sx_SR

#define I2S_FLAG_UDF ((uint8_t)3) // the UDF of I2Sx_ICR
#define I2S_FLAG_OVR ((uint8_t)6) // the OVR of I2Sx_ICR
#define I2S_FLAG_FRE ((uint8_t)8) // the FRE of I2Sx_ICR

/** 
****************************************************************************** 
** \brief Audio sample rate 
******************************************************************************/
#define I2S_AudioFreq_192k (uint32_t)192000u // 192khz
#define I2S_AudioFreq_96k (uint32_t)96000u // 96khz
#define I2S_AudioFreq_48k (uint32_t)48000u // 48khz
#define I2S_AudioFreq_44k (uint32_t)44100u // 44.1kHz
#define I2S_AudioFreq_32k (uint32_t)32000u // 32kHz
#define I2S_AudioFreq_22k (uint32_t)22050u // 22kHz
#define I2S_AudioFreq_16k (uint32_t)16000u // 16kHz
#define I2S_AudioFreq_11k (uint32_t)11025u // 11.025kHz
#define I2S_AudioFreq_8k (uint32_t)8000u // 8kHz

/**
********************************************************************************
** \brief Enable or disable command
******************************************************************************/
typedef enum
{
    DISABLE = 0, //Disable
    ENABLE = 1 //Enable
}en_en_state_t;

/**
************************************************************************************
** \brief Status flags
************************************************************************/
typedef enum
{
    RESET = 0,
    SET = !RESET
}en_flag_status_t;

/**
********************************************************************************************
** \brief I2S function channel selection settings
************************************************************************/
typedef enum
{
    I2S0 = 0u, //I2S channel 0
    I2S1 = 1u, // I2S channel 1
}en_i2s_channel_t;

/**
******************************************************************************
** \brief I2S function enable setting
**************************************************************************/
typedef enum
{
    I2sEnable = 1u, // I2S module enable
    I2sDisable = 0u, // I2S module disable
}en_i2s_en_t;

/**
******************************************************************************
** \brief I2S mode configuration
**************************************************************************/
typedef enum
{
    I2sSlaveSend = 0u, // Slave mode send
    I2sSlaveRec = 1u, // Slave mode receive
    I2sMasterSend = 2u, //Master mode transmit
    I2sMasterRec = 3u, //Master mode receive
}en_spi_mode_t;

/**
**************************************************************************
** \brief I2S PCMSYNC synchronization frame flag
**************************************************************************/
typedef enum
{
    I2sPcmsyncShort = 0u, //Short frame synchronization
    I2sPcmsyncLong = 1u //Long frame synchronization
}en_i2s_pcmsync_t;

/**
******************************************************************************
** \brief I2S input clock selection
******************************************************************************/
typedef enum
{
    I2sPclk = 0u, //I2S clock in master mode: PCLLK
    I2sHclk = 1u //I2S clock in master mode: HCLLK
}en_i2s_cksel_t;

/**
******************************************************************************
** \brief I2S standard selection
**************************************************************************/
typedef enum
{
    i2sstdPhilips = 0u, //I2S Philips standard
    i2sstdMSBL = 1u, //MSB alignment standard (left justification)
    i2sstdLSBR = 2u, //LSB alignment standard (right justification)
    i2sstdPCM = 3u //PCM standard
}en_i2s_i3sstd_t;

/**
************************************************************************
** \brief I2S data length to be transmitted
********************************************************************/
typedef enum
{
    i2sDatlen16Bit = 0u, //16-bit data length
    i2sDatlen24Bit = 1u, //24-bit data length
    i2sDatlen32Bit = 2u //32-bit data length
}en_i2s_datlen_t;

/**
********************************************************************************
** \brief I2S channel data length
********************************************************************/
typedef enum
{
    i2sChlen16Bit = 0u, //16-bit data length
    i2sDatlen24Bit = 1u, //24-bit data length
    i2sDatlen32Bit = 2u, //32-bit data length
}en_i2s_datlen_t;

/**
************************************************************************************
** \brief I2S channel data length
************************************************************************/
typedef enum
{
    i2sChlen16Bit = 0u, //24-bit data length //Channel data length: 16 bits
    i2sChlen32Bit = 1u //Channel data length: 32 bits
}en_i2s_chlen_t;

/**
********************************************************************************
** \brief I2S configuration structure
************************************************************************/
typedef struct
{
    en_spi_mode_t i2s_Mode; //I2S mode configuration bits
    en_i2s_pcmsync_t i2s_PcmSync; //I2S frame synchronization
    en_i2s_cksel_t i2s_Cksel; //I2S master mode always selects: 0: PCLK 1: HCLK
    en_i2s_i3sstd_t i2s_Std; //I2S standard selection: 0: I2S Philips 1: MAS left-aligned 2: LSB right-aligned 3: PCM standard
    en_i2s_datlen_t i2s_Datalen; //I2S data length to be transmitted
    en_i2s_chlen_t i2s_Chlen; //Number of bits per I2S audio channel, 0: 16 bits, 1: 32 bits
    en_en_state_t i2s_Mckoe; //I2S master clock MCK output enable
    uint32_t i2s_AudioFreq; //I2S audio frequency
    uint8_t i2s_Div; //I2S PR register DIV, 8 bits: linear prescaler
    uint8_t i2s_Odd; //I2S PR register ODD, 1 bit: odd factor of the prescaler
    uint8_t i2s_Fract; //I2S PR register FRACT fractional divider, 6 bits
}stc_i2s_config_t;

/***************************************************************************
** \brief I2Sx-related function declarations
**************************************************************************/
extern void I2S_ConfIt(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it, en_en_state_t NewState);
extern void I2s_ConfDma(M0P_I2S_TypeDef *i2sx, uint8_t rl_dma_en, en_en_state_t NewState);
extern en_flag_status_t I2s_GetStatus(M0P_I2S_TypeDef *i2sx, uint8_t i2s_status);
extern void I2s_ClearITPendingBit(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it_flag);
extern void I2s_SendDataL(M0P_I2S_TypeDef *i2sx, uint16_t Data);
extern void I2s_SendDataR(M0P_I2S_TypeDef *i2sx, uint16_t Data);
extern uint16_t I2s_ReceiveDataL(M0P_I2S_TypeDef *i2sx);
extern uint16_t I2s_ReceiveDataR(M0P_I2S_TypeDef *i2sx);
extern void I2s_Init(M0P_I2S_TypeDef *i2sx, stc_i2s_config_t *i2s_conf);
extern void I2S_Cmd(M0P_I2S_TypeDef *i2sx, en_en_state_t NewState);

#endif //__I2S_H__

/******************************************************************************/
/* EOF (not truncated) */
/******************************************************************************/
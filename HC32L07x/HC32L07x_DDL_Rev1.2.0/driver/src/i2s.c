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
 * @file   i2s.c
 *
 * @brief  Source file for I2S functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "i2s.h"

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
******************************************************************************
* @brief Enable I2Sx-related interrupts
* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param i2s_it: The following value
* @arg I2S_IT_TXE: Transmit buffer empty interrupt enable bit
* @arg I2S_IT_RXNEIE: Receive buffer empty interrupt enable bit
* @arg I2S_IT_ERRIE: Error interrupt enable bit
* @param NewState: =ENALE or DISABLE
* @retval None
**
**************************************************************************/
void I2S_ConfIt(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it, en_en_state_t NewState)
{
	uint32_t itmark=0;
	itmark=1<<i2s_it;
	if(NewState == ENABLE)               //Enable interrupts
	{
		i2sx->CR |= itmark;
	}
	else if(NewState == DISABLE)         //Disable interrupts
	{
		i2sx->CR &= ~itmark;
	}
        else
        {
          ;
        }
}

/**
************************************************************************************
** \brief I2S left and right channel buffer DMA data transmission enable configuration
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param i2s_it: The following value
* @arg I2S_RDMA_EN: Right channel buffer DMA data transmission enable bit
* @arg I2S_LDMA_EN: Left channel buffer DMA data transmission enable bit
* @param NewState: =ENALE or DISABLE
** \retval none
**
************************************************************************/
void I2s_ConfDma(M0P_I2S_TypeDef *i2sx, uint8_t rl_dma_en, en_en_state_t NewState)
{
	uint32_t itmark=0;
	itmark = 1<<rl_dma_en;
	if(NewState == ENABLE)            //Enable left or right channel DMA
	{
		i2sx->CR |= itmark;
	}
	else if(NewState == DISABLE)      //Disable left or right channel DMA
	{
		i2sx->CR &= ~itmark;
	}	
        else
        {
          ;
        }
}

/**
******************************************************************************
** \brief I2S status flag status acquisition
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param i2s_status: The following value
* @arg I2S_RXNE_L: Left channel receive buffer not empty flag
* @arg I2S_TXE_L: Left channel transmit buffer empty flag
* @arg I2S_UDR_L: Left channel underflow flag
* @arg I2S_UDR_R: Right channel underflow flag
* @arg I2S_OVR_L: Left channel overflow flag
* @arg I2S_BSY: Busy flag
* @arg I2S_FRE: Framing error flag
* @arg I2S_OVR_R: Right channel overflow flag
* @arg I2S_RXNE_R: Right channel receive buffer not empty flag
* @arg I2S_TXE_R: Right channel transmit buffer empty flag
** \retval Status flag bit status RESET and SET
**
**************************************************************************/
en_flag_status_t I2s_GetStatus(M0P_I2S_TypeDef *i2sx, uint8_t i2s_status)
{
	uint16_t itmark=0;
	en_flag_status_t bitstatus;
	itmark=(uint16_t)1<<i2s_status;	
	if(!(i2sx->SR & itmark))
	{
		bitstatus = RESET;
	}
	else
	{
		bitstatus = SET;
	}
	return bitstatus;
}

/**
******************************************************************************
** Brief I2S interrupt status flag clears **

* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param i2s_status: The following value
* @arg I2S_FLAG_UDF: Underflow interrupt flag
* @arg I2S_FLAG_OVR: Overflow interrupt flag
* @arg I2S_FLAG_FRE: Framing error flag
** \retval none
**
**************************************************************************/
void I2s_ClearITPendingBit(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it_flag)
{
	uint32_t bitstatus;
	bitstatus = 1<<i2s_it_flag;
	i2sx->ICR &= ~bitstatus;
}

/**
******************************************************************************
** \brief Writes the data to be transmitted to the left channel data register DRL
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param Data: 16-bit data to be sent
** \retval none
**
**********************************************************************/
void I2s_SendDataL(M0P_I2S_TypeDef *i2sx, uint16_t Data)
{	
	i2sx->DRL_f.DRL = Data;
}

/**
**************************************************************************
** \brief Writes the data to be sent to the right channel data register DRR.
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param Data: 16-bit data to be sent
** \retval none
**
**********************************************************************/
void I2s_SendDataR(M0P_I2S_TypeDef *i2sx, uint16_t Data)
{
	i2sx->DRR_f.DRR = Data;
}

/**
**************************************************************************
** \brief Reads received data from the left channel data register DRL
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
** \retval Read data
**
**************************************************************************/
uint16_t I2s_ReceiveDataL(M0P_I2S_TypeDef *i2sx)
{	
	uint16_t data;
	data = (uint16_t)i2sx->DRL;
	return data;
}

/**
******************************************************************************
** \brief Reads received data from the right channel data register DRR
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
** \retval The data read
**
**********************************************************************/
uint16_t I2s_ReceiveDataR(M0P_I2S_TypeDef *i2sx)
{	
	uint16_t data;
	data = (uint16_t)i2sx->DRR;
	return data;
}

/**
**************************************************************************
** \brief Initialize I2Sx configuration
** (I) Fractional division FRACT=0:
** (1) Output master clock (MCKOE=1)
** Channel frame width is 16 bits, sampling rate = master frequency I2SxCLK/[(16*2)*(2*I2SDIV+ODD)*8]
** Channel frame width is 32 bits, sampling rate = main frequency I2SxCLK/[(32*2)*(2*I2SDIV+ODD)*4]
** (2) Disable main clock (MCKOE=0)
** Channel frame width is 16 bits, sampling rate = main frequency I2SxCLK/[(16*2)*(2*I2SDIV+ODD)]
** Channel frame width is 32 bits, sampling rate = main frequency I2SxCLK/[(32*2)*(2*I2SDIV+ODD)]
** (II) Fractional division FRACT=0:
** (1) Output main clock (MCKOE=1)
** Channel frame width is 16 bits, sampling rate = main frequency I2SxCLK/[(16*2)*(2*(I2SDIV+FRACT/64))*8]
** Channel frame width is 32 bits, sampling rate = main frequency I2SxCLK/[(32*2)*(2*(I2SDIV+FRACT/64))*4]
** (2) Output main clock (MCKOE=0)
** Channel frame width is 16 bits, sampling rate = main frequency I2SxCLK/[(16*2)*(2*(I2SDIV+FRACT/64))]
** Channel frame width is 32 bits, sampling rate = main frequency I2SxCLK/[(32*2)*(2*(I2SDIV+FRACT/64))]
** I2SDIV, FRACT and I2SODD are set according to the above calculation formula according to the actual situation
* @param i2sx: M0P_I2S0 or M0P_I2S1
* @param i2s_conf: configuration parameters
** \retval None
** ******************************************************************************/
void I2s_Init(M0P_I2S_TypeDef *i2sx, stc_i2s_config_t *i2s_conf)
{
	i2sx->CFGR_f.CFG     = i2s_conf->i2s_Mode;       //Set mode
	i2sx->CFGR_f.PCMSYNC = i2s_conf->i2s_PcmSync;    //PCM frame synchronization bit. This bit is only meaningful when I2SSTD=3.
	i2sx->CFGR_f.CKSEL   = i2s_conf->i2s_Cksel;      //In master mode, I2S always selects: 0: PCLK 1: HCLK
	i2sx->CFGR_f.STD     = i2s_conf->i2s_Std;        //Standard selection: 0: I2S Philips 1: MAS left-aligned 2: LSB right-aligned 3: PCM standard
	i2sx->CFGR_f.DATLEN  = i2s_conf->i2s_Datalen;    //Data length to be transmitted
	i2sx->CFGR_f.CHIEN   = i2s_conf->i2s_Chlen;      //Number of bits per audio channel, 0: 16 bits, 1: 32 bits
	i2sx->PR_f.MCKOE     = i2s_conf->i2s_Mckoe;      //Master clock MCK output enable
	i2sx->PR_f.I2SDIV    = i2s_conf->i2s_Div;
	i2sx->PR_f.FRACT     = i2s_conf->i2s_Fract;
	i2sx->PR_f.ODD       = i2s_conf->i2s_Odd;
}

/**
****************************************************************************
** \brief Enable or disable I2Sx
**
* @param i2sx: M0P_I2S0 or M0P_I2S1
**
* @param NewState: EANBLE or DISABLE
** \retval None
**
************************************************************************/
void I2S_Cmd(M0P_I2S_TypeDef *i2sx, en_en_state_t NewState)
{
	i2sx->CFGR_f.E = NewState;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/










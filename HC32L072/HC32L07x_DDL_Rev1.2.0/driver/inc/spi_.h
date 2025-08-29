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
* @file spi.h 
* 
* @brief Header file for SPI functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __SPI_H__
#define __SPI_H__

/******************************************************************************
* Include files
*************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with a C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

//@{

/******************************************************************************
* Global type definitions
*************************************************************************/
/**
******************************************************************************
** \brief SPI function channel selection settings
**************************************************************************/

/**
**********************************************************************************
** \brief SPI Function Enable Setting
******************************************************************************/
typedef enum en_spi_en
{
    SpiMskEnable = 0x4u, ///< SPI module enable
    SpiMskDisable = 0u, ///< SPI module disable
}en_spi_en_t;
/**
******************************************************************************
** \brief SPI Mode Configuration
******************************************************************************/
typedef enum en_spi_mode
{
    SpiMskMaster = 0x10u, ///< Master
    SpiMskSlave = 0x00u, ///< Slave
}en_spi_mode_t;
/**
**********************************************************************************
** \brief SPI Clock Polarity Setting
******************************************************************************/
typedef enum en_spi_cpol
{
    SpiMskcpollow = 0u, ///<Polarity is low
    SpiMskcpolhigh = 0x08u, ///<Polarity is high
}en_spi_cpol_t;
/**
******************************************************************************
** \brief SPI clock phase configuration
******************************************************************************/
typedef enum en_spi_cpha
{
    SpiMskCphafirst = 0u, ///<First edge sampling
    SpiMskCphasecond = 0x4u, ///<Second edge sampling
}en_spi_cpha_t;
/**
**********************************************************************************
** \brief SPI clock divider configuration
*****************************************************************************/
typedef enum en_spi_clk_div
{
    SpiClkMskDiv2 = 0x00u, ///<PCLK divided by 2
    SpiClkMskDiv4 = 0x01u, ///<PCLK divided by 4
    SpiClkMskDiv8 = 0x02u, ///<PCLK divided by 8
    SpiClkMskDiv16 = 0x03u, ///<PCLK divided by 16
    SpiClkMskDiv32 = 0x80u, ///<PCLK divided by 32
    SpiClkMskDiv64 = 0x81u, ///<PCLK divided by 64
    SpiClkMskDiv128 = 0x82u, ///<PCLK divided by 128
}en_spi_clk_div_t;

/**
**************************************************************************
** \brief SPI chip select pin level selection
*************************************************************************/
typedef enum en_spi_cspin
{
    SpiCsLow = 0u, ///<Chip select low level
    SpiCsHigh = 1u, ///<Chip select high level
}en_spi_cspin_t;

/**
******************************************************************************
** \brief SPI status
*************************************************************************/
typedef enum en_spi_status
{
    SpiIf = 0x80u, ///<Transmission end interrupt flag
    SpiSserr = 0x20u, ///<Slave mode error flag SpiMdf = 0x10u, ///< Host mode error flag
    SpiBusy = 0x08u, ///< SPI bus busy flag
    SpiTxe = 0x04u, ///< Transmit buffer empty flag
    SpiRxne = 0x02u, ///< Receive buffer not empty flag
}en_spi_status_t;
/**
******************************************************************************
** \brief SPI function enable function
*************************************************************************/
typedef enum en_spi_func
{
    SpiMskRxNeIe = 0x40u, ///< Receive buffer not empty interrupt enable
    SpiMskTxEIe = 0x20u, ///< Transmit buffer empty interrupt enable
    SpiMskDmaTxEn = 0x10u, ///< DMA hardware access transmit enable
    SpiMskDmaRxEn = 0x08u, ///<DMA hardware access receive enable
}en_spi_func_t;
/**
****************************************************************************
** \brief SPI overall configuration structure
***********************************************************************/
typedef struct stc_spi_cfg
{
    en_spi_mode_t enSpiMode; ///< Master/slave mode selection
    en_spi_clk_div_t enPclkDiv; ///< PCLK division coefficient (baud rate division)
    en_spi_cpol_t enCPOL; ///< Clock polarity selection
    en_spi_cpha_t enCPHA; ///< Clock phase selection
}stc_spi_cfg_t;

//SPI status acquisition
boolean_t Spi_GetStatus(M0P_SPI_TypeDef* SPIx,en_spi_status_t enStatus);

///< SPI interrupt enable/disable
en_result_t Spi_IrqEnable(M0P_SPI_TypeDef* SPIx);
en_result_t Spi_IrqDisable(M0P_SPI_TypeDef* SPIx);
//SPI clear interrupt flag
en_result_t Spi_ClearStatus(M0P_SPI_TypeDef* SPIx);
//SPI initialization function
en_result_t Spi_Init(M0P_SPI_TypeDef* SPIx,stc_spi_cfg_t* pstcSpiCfg);
//SPI function enable/disable function
en_result_t Spi_FuncEnable(M0P_SPI_TypeDef* SPIx, en_spi_func_t enFunc);
en_result_t Spi_FuncDisable(M0P_SPI_TypeDef* SPIx, en_spi_func_t enFunc);
//SPI shutdown function
en_result_t Spi_DeInit(M0P_SPI_TypeDef* SPIx);

//SPI master transmit level configuration
void Spi_SetCS(M0P_SPI_TypeDef* SPIx, boolean_t bFlag);

//SPI data byte transmission/reception
uint8_t Spi_RWByte(M0P_SPI_TypeDef* SPIx, uint8_t u8Data);
//SPI data transmission
en_result_t Spi_SendData(M0P_SPI_TypeDef* SPIx, uint8_t u8Data);
void Spi_Slave_DummyWriteData(M0P_SPI_TypeDef* SPIx, uint8_t u8Data);
en_result_t Spi_SendBuf(M0P_SPI_TypeDef* SPIx, uint8_t* pu8Buf, uint32_t u32Len);
//SPI data reception
uint8_t Spi_ReceiveData(M0P_SPI_TypeDef* SPIx);
en_result_t Spi_ReceiveBuf(M0P_SPI_TypeDef* SPIx, uint8_t* pu8Buf, uint32_t u32Len);
//@} // Spi Group

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */
/****************************************************************************** 
* EOF (not truncated) 
*******************************************************************************/


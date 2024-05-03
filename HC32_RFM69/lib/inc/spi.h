/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED   , ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file spi.h
 **
 ** Headerfile for SPI functions
 **  
 **
 ** History:
 **   - 2017-05-17  1.0  Devi     First Version
 **
 *****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

//@{

/******************************************************************************
 * Global type definitions
 *****************************************************************************/
 /**
************************************************** ****************************
  ** \brief SPI function channel selection setting
  ************************************************** ****************************/ 
typedef enum en_spi_channel
{
    Spi0     = 0u,  ///< SPI channel 0
    Spi1     = 1u,  ///< SPI channel 1
}en_spi_channel_t;
/**
************************************************** ****************************
  ** \brief SPI function enable setting
  ************************************************** ****************************/ 
typedef enum en_spi_en
{
    SpiEnable     = 1u,  ///< SPI module enable
    SpiDisable    = 0u,  ///< SPI module disable
}en_spi_en_t;
/**
 ******************************************************************************
 ** \brief SPI Mode configuration
 ******************************************************************************/ 
typedef enum en_spi_mode
{
    SpiMaster = 1u,  ///<master
    SpiSlave  = 0u,  ///<slave
}en_spi_mode_t;
/**
 ******************************************************************************
 ** \brief SPI Clock polarity setting
 ******************************************************************************/ 
typedef enum en_spi_cpol
{
    Spicpollow   = 0u,  ///<Low polarity
    Spicpolhigh  = 1u,  ///<High polarity
}en_spi_cpol_t;
/**
 ******************************************************************************
 ** \brief SPI Clock phase setting
 ******************************************************************************/ 
typedef enum en_spi_cpha
{
    Spicphafirst   = 0u,  ///<First edge sampling
    Spicphasecond  = 1u,  ///<Second edge sampling
}en_spi_cpha_t;
/**
 ******************************************************************************
 ** \brief SPI Clock prescaler configuration
 *****************************************************************************/
typedef enum en_spi_clk_div
{
    SpiClkDiv2   = 0u,   ///<2Frequency division       
    SpiClkDiv4   = 1u,   ///<4Frequency division            
    SpiClkDiv8   = 2u,   ///<8Frequency division            
    SpiClkDiv16  = 3u,   ///<16Frequency division            
    SpiClkDiv32  = 4u,   ///<32Frequency division            
    SpiClkDiv64  = 5u,   ///<64Frequency division            
    SpiClkDiv128 = 6u,   ///<128Frequency division            
}en_spi_clk_div_t;

/**
 ******************************************************************************
 ** \brief SPI Chip select level selection
 *****************************************************************************/
typedef enum en_spi_cspin
{
    SpiCsLow  = 0u,      ///<Chip select low         
    SpiCsHigh = 1u,      ///<Chip select high            
}en_spi_cspin_t;

/**
 ******************************************************************************
 ** \brief SPI status
 *****************************************************************************/
typedef enum en_spi_status
{
    SpiIf              = 0x80,   ///<Transmission end interrupt flag       
    SpiSserr           = 0x20,   ///<Slave mode error flag    
    SpiMdf             = 0x10,   ///<Master mode error flag 
    SpiBusy            = 0x08,   ///<SPI bus busy flag
    SpiTxe             = 0x04,   ///<Transmit buffer empty flag
    SpiRxne            = 0x02,   ///<Receive buffer non-empty flag
}en_spi_status_t;
/**
 ******************************************************************************
 ** \brief SPI enable function
 *****************************************************************************/
typedef enum en_spi_func
{
    SpiRxNeIe          = 0x40,   ///<Receive buffer non-empty interrupt enable       
    SpiTxEIe           = 0x20,   ///<Transmit buffer empty interrupt enable    
    SpiDmaTxEn         = 0x10,   ///<DMA hardware access send enable
    SpiDmaRxEn         = 0x08,   ///<DMA hardware access receive enable
}en_spi_func_t;
/**
 ******************************************************************************
 ** \brief SPI Overall configuration structure
 *****************************************************************************/
typedef struct stc_spi_config
{
    boolean_t           bMasterMode;     ///< Master-slave mode selection
    uint8_t             u8BaudRate;      ///< Baud rate setting
    boolean_t           bCPOL;           ///< Clock polarity selection
    boolean_t           bCPHA;           ///< Clock phase selection
    boolean_t           bIrqEn;          ///< Interrupt enable
    func_ptr_t          pfnSpi0IrqCb;    ///< Interrupt callback function
    func_ptr_t          pfnSpi1IrqCb;    ///< Interrupt callback function
}stc_spi_config_t;

//SPI Interrupt
void Spi_IRQHandler(en_spi_channel_t enCh);

//SPI get status  
uint8_t Spi_GetState(en_spi_channel_t enCh);
boolean_t Spi_GetStatus(en_spi_channel_t enCh,en_spi_status_t enStatus);
//SPI Clear interrupt flag
en_result_t Spi_ClearStatus(en_spi_channel_t enCh);
//SPI initialization function
en_result_t Spi_Init(en_spi_channel_t enCh,stc_spi_config_t* pstcSpiConfig);
//SPI Function enable disable function
en_result_t Spi_FuncEn(en_spi_channel_t enCh,en_spi_func_t enFunc,boolean_t bFlag);
//SPI shutdown function
en_result_t Spi_DeInit(en_spi_channel_t enCh);
//SPI Configure the level of the main send
void Spi_SetCS(en_spi_channel_t enCh,boolean_t bFlag);
//SPI send data
en_result_t Spi_SendData(en_spi_channel_t enCh,uint8_t u8Data);
//SPI master receive data
uint8_t Spi_ReceiveData(en_spi_channel_t enCh,boolean_t bMasterOrSlave);
uint8_t Spi_MasterTransfer(en_spi_channel_t enCh, uint8_t data);

//@} // Spi Group

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


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
* @file dmac.h 
* 
* @brief Header file for DMAC functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __DMAC_H__
#define __DMAC_H__

/************************************************************************************
* Include files
******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif 

/** 
******************************************************************************* 
** \defgroup DmacGroup Direct Memory Access Control(DMAC) 
** 
******************************************************************************/ 
//@{ 

/************************************************************************************ 
* Global type definitions ('typedef') 
******************************************************************************/ 
/** **********************************************************************************
** \brief DMA channel
**
**************************************************************************/
typedef enum en_dma_channel
{
    DmaCh0 = 0x00, ///< DMA channel 0
    DmaCh1 = 0x04, ///< DMA channel 1
} en_dma_channel_t;
/**
*******************************************************************************
** \brief DMA priority
**
******************************************************************************/
typedef enum en_dma_priority
{
    DmaMskPriorityFix = 0x00000000, ///< Fixed DMA channel priority (CH0 > CH1)
    DmaMskPriorityLoop = 0x10000000, ///< DMA channel priority uses round-robin mode
} en_dma_priority_t;

/**
****************************************************************************
** \brief DMA transfer data width
**
************************************************************************/
typedef enum en_dma_transfer_width
{
    DmaMsk8Bit = 0x00000000, ///< 8-bit byte transfer
    DmaMsk16Bit = 0x04000000, ///< 16-bit half-word transfer
    DmaMsk32Bit = 0x08000000 ///< 32-bit word transfer
} en_dma_transfer_width_t;

/**
****************************************************************************************************
** \brief DMA transfer mode: Block or Burst
**
************************************************************************/
typedef enum en_dma_transfer_mode
{
    DmaMskBlock = 0x00000000, ///< Block transfer
    DmaMskBurst = 0x10000000, ///< Burst transfer
} en_dma_transfer_mode_t;

/**
************************************************************************************
** \brief DMA transfer current status
**
****************************************************************************/
typedef enum en_dma_stat
{
    DmaDefault = 0U, ///< Initial value
    DmaAddOverflow = 1U, ///< Abort caused by a transfer error (address overflow)
    DmaHALT = 2U, ///< Abort caused by a transfer halt request (stop caused by a peripheral halt request or transfer disabled by the EB/DE bit)
    DmaAccSCRErr = 3U, ///< Abort caused by a transfer error (source address access error)
    DmaAccDestErr = 4U, ///< Abort caused by a transfer error (destination address access error)
    DmaTransferComplete = 5U, ///< Successful transfer completion
    DmaTransferPause = 7U, ///< Pause transfer
} en_dma_stat_t;

/**
********************************************************************************
** \brief DMA source address control mode: auto-increment or fixed
**
****************************************************************************/
typedef enum en_src_address_mode
{
    DmaMskSrcAddrInc = 0x00000000, ///< Address auto-increment
    DmaMskSrcAddrFix = 0x02000000, ///< Address fixed
} en_src_address_mode_t;

/**
************************************************************************************
** \brief DMA destination address control mode: auto-increment or fixed
**
****************************************************************************/
typedef enum en_dst_address_mode
{
    DmaMskDstAddrInc = 0x00000000, ///< Address auto-increment
    DmaMskDstAddrFix = 0x01000000, ///< Address fixed
} en_dst_address_mode_t;

/**
******************************************************************************
** \brief DMA CONFA:BC[3:0] and CONFA:TC[15:0] reload function
**
******************************************************************************/
typedef enum en_bc_tc_reload_mode
{
    DmaMskBcTcReloadDisable = 0x00000000, ///< Disable reload
    DmaMskBcTcReloadEnable = 0x00800000, ///< Enable reload
} en_bc_tc_reload_mode_t;

/**
************************************************************************************
** \brief DMA source address reload function: enable or disable
**
********************************************************************************/
typedef enum en_src_address_reload_mode
{
    DmaMskSrcAddrReloadDisable = 0x00000000, ///< Disable DMA source address reload
    DmaMskSrcAddrReloadEnable = 0x00400000, ///< Enable DMA source address reload
} en_src_address_reload_mode_t;

/**
********************************************************************************
** \brief DMA destination address reload function: enable or disable
**
****************************************************************************/
typedef enum en_dst_address_reload_mode
{
    DmaMskDstAddrReloadDisable = 0x00000000, ///< Disable DMA destination address reload
    DmaMskDstAddrReloadEnable = 0x00200000, ///< Enable DMA destination address reload
} en_dst_address_reload_mode_t;

/**
*******************************************************************************
** \brief DMA continuous transfer settings
**
**************************************************************************/
typedef enum en_dma_msk
{
    DmaMskOneTransfer = 0x00000000, ///< Transfer once. Clear CONFA:ENS bits when DMAC transfer completes.
    DmaMskContinuousTransfer = 0x00000001, ///< Continuous transfer. Do not clear CONFA:ENS bits when DMAC transfer completes.
} en_dma_msk_t;
/**
*******************************************************************************
** \brief DMA trigger source selection
**
**************************************************************************/
typedef enum stc_dma_trig_sel
{
    DmaSWTrig = 0U, ///< Select DMA software trig 
    DmaSPI0RXTrig = 64U, ///< Select DMA hardware trig 0 
    DmaSPI0TXTrig = 65U, ///< Select DMA hardware trig 1 
    DmaSPI1RXTrig = 66U, ///< Select DMA hardware trig 2 
    DmaSPI1TXTrig = 67U, ///< Select DMA hardware trig 3 
    DmaADCJQRTrig = 68U, ///< Select DMA hardware trig 4 
    DmaADCSQRTrig = 69U, ///< Select DMA hardware trig 5 
    DmaLCDTxTrig = 70U, ///< Select DMA hardware trig 6 
    DmaUart0RxTrig = 72U, ///< Select DMA hardware trig 8 
    DmaUart0TxTrig = 73U, ///< Select DMA hardware trig 9 DmaUart1RxTrig = 74U, ///< Select DMA hardware trig 10 
    DmaUart1TxTrig = 75U, ///< Select DMA hardware trig 11 
    DmaLpUart0RxTrig = 76U, ///< Select DMA hardware trig 12 
    DmaLpUart0TxTrig = 77U, ///< Select DMA hardware trig 13 
    DmaLpUart1RxTrig = 78U, ///< Select DMA hardware trig 14 
    DmaLpUart1TxTrig = 79U, ///< Select DMA hardware trig 15 
    DmaDAC0Trig = 80U, ///< Select DMA hardware trig 16 
    DmaDAC1Trig = 81U, ///< Select DMA hardware trig 17 
    DmaTIM0ATrig = 82U, ///< Select DMA hardware trig 18 
    DmaTIM0BTrig = 83U, ///< Select DMA hardware trig 19 
    DmaTIM1ATrig = 84U, ///< Select DMA hardware trig 20 
    DmaTIM1BTrig = 85U, ///< Select DMA hardware trig 21 
    DmaTIM2ATrig = 86U, ///< Select DMA hardware trig 22 
    DmaTIM2BTrig = 87U, ///< Select DMA hardware trig 23 
    DmaTIM3ATrig = 88U, ///< Select DMA hardware trig 24 
    DmaTIM3BTrig = 89U, ///< Select DMA hardware trig 25 
    DmaTIM4ATrig = 90U, ///< Select DMA hardware trig 26 
    DmaTIM4BTrig = 91U, ///< Select DMA hardware trig 27 DmaTIM5ATrig = 92U, ///< Select DMA hardware trig 28 
    DmaTIM5BTrig = 93U, ///< Select DMA hardware trig 29 
    DmaTIM6ATrig = 94U, ///< Select DMA hardware trig 30 
    DmaTIM6BTrig = 95U, ///< Select DMA hardware trig 31 
    DmaUart2RxTrig = 96U, ///< Select DMA hardware trig 32 
    DmaUart2TxTrig = 97U, ///< Select DMA hardware trig 33 
    DmaUart3RxTrig = 98U, ///< Select DMA hardware trig 34 
    DmaUart3TxTrig = 99U, ///< Select DMA hardware trig 35 
    DmaI2S0LeftTrig = 100U, ///< Select DMA hardware trig 36 DmaI2S0RightRrig = 101U, ///< Select DMA hardware trig 37 
    DmaI2S1LeftTrig = 102U, ///< Select DMA hardware trig 36 
    DmaI2S1RightRrig = 103U,//< Select DMA hardware trig 37
}en_dma_trig_sel_t;

/**
****************************************************************************
** \brief DMA channel initialization configuration structure
**
****************************************************************************/
typedef struct stc_dma_cfg
{
    en_dma_transfer_mode_t enMode;

    uint16_t u16BlockSize; ///< Number of block transfers
    uint16_t u16TransferCnt; ///< Number of block transfers
    en_dma_transfer_width_t enTransferWidth; ///< Width of transferred data bytes. For details, refer to the enumeration definition: en_dma_transfer_width_t

    en_src_address_mode_t enSrcAddrMode; ///< DMA source address control mode: auto-increment or fixed
    en_dst_address_mode_t enDstAddrMode; ///< DMA destination address control mode: auto-increment or fixed

    en_src_address_reload_mode_t enSrcAddrReloadCtl; ///< Source address reload. For details, refer to the enumeration definition: en_src_address_reload_mode_t
    en_dst_address_reload_mode_t enDestAddrReloadCtl; ///< Destination address reload. For details, refer to the enumeration definition: en_dst_address_reload_mode_t
    en_bc_tc_reload_mode_t enSrcBcTcReloadCtl; ///< Bc/Tc value reload function. For details, refer to the enumeration definition: en_bc_tc_reload_mode_t

    uint32_t u32SrcAddress; ///< Source address>
    uint32_t u32DstAddress; ///< Destination address>

    en_dma_msk_t enTransferMode; ///DMA continuous transfer setting. For details, refer to the enumeration definition: en_dma_msk_t
    en_dma_priority_t enPriority; ///DMA priority setting. For details, refer to the enumeration definition: en_dma_priority_t
    en_dma_trig_sel_t enRequestNum; ///<DMA trigger source selection. For details, refer to the enumeration definition: en_dma_trig_sel_t
} stc_dma_cfg_t;

/*******************************************************************************
* Global pre-processor symbols/macros ('#define')
****************************************************************************/

/***********************************************************************************
* Global variable definitions ('extern')
**********************************************************************************/

/*******************************************************************************
* Global function prototypes (definition in C source)
**************************************************************************/
///< Initialize the DMAC channel
en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg);

///< DMA module enable function, enabling all channels. Each channel operates according to its own settings.
void Dma_Enable(void);
///< DMA module disable function, disabling all channels.
void Dma_Disable(void);

///< Trigger the software transfer function of the specified DMA channel.
void Dma_SwStart(en_dma_channel_t enCh);
///< Stop the software transfer function of the specified DMA channel.
void Dma_SwStop(en_dma_channel_t enCh);

///< Enable the specified DMA channel's (transfer completion) interrupt.

void Dma_EnableChannelIrq(en_dma_channel_t enCh);

///< Disable the specified DMA channel's (transfer completion) interrupt.

void Dma_DisableChannelIrq(en_dma_channel_t enCh);

///< Enable the specified DMA channel's (transfer error) interrupt.

void Dma_EnableChannelErrIrq(en_dma_channel_t enCh);

///< Disable the specified DMA channel's (transfer error) interrupt.

void Dma_DisableChannelErrIrq(en_dma_channel_t enCh);

///< Enable the specified DMA channel.

void Dma_EnableChannel(en_dma_channel_t enCh);

///< Disable the specified DMA channel.

void Dma_DisableChannel(en_dma_channel_t enCh);

///< Set the block size for the specified channel.

void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize);

///< Set the number of block transfers for the specified channel.

void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt);

///< Enable continuous transfers on the specified channel. That is, the DMAC does not clear the CONFA:ENS bit when a transfer is complete.

void Dma_EnableContinusTranfer(en_dma_channel_t enCh);

///< Disable continuous transfers on the specified channel. That is, the DMAC clears the CONFA:ENS bit when a transfer is complete.

void Dma_DisableContinusTranfer(en_dma_channel_t enCh);

///< Pause all DMA channels.

void Dma_HaltTranfer(void);
///< Resume all previously paused DMA channels.
void Dma_RecoverTranfer(void);
///< Pause the specified DMA channel.
void Dma_PauseChannelTranfer(en_dma_channel_t enCh);
///< Resume the specified DMA channel.
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh);

///< Set the transfer data width of the specified channel.
void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth);
///< Set the DMA channel priority.
void Dma_SetChPriority(en_dma_priority_t enPrio);

///< Get the status of the specified DMA channel.
en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh); enCh);

///< Clear the status of the specified DMA channel.
void Dma_ClrStat(en_dma_channel_t enCh);

///< Set the source address of the specified channel.
void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address);
///< Set the destination address of the specified channel.
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address);
//@} // DmacGroup

#ifdef __cplusplus
}
#endif

#endif /* __DMAC_H__ */

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/

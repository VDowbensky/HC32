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
* @file can.h 
* 
* @brief Header file for CAN functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __CAN_H__
#define __CAN_H__

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
** \defgroup CanGroup Controller Area Network(CAN) 
** 
******************************************************************************/
//@{

/************************************************************************************ 
* Global type definitions ('typedef') 
******************************************************************************/

/** *******************************************************************************
** \brief CAN error types.
************************************************************************/
typedef enum
{
    NO_ERROR = 0U, ///< No error
    BIT_ERROR = 1U, ///< Bit error
    FORM_ERROR = 2U, ///< Form error
    STUFF_ERROR = 3U, ///< Stuff error
    ACK_ERROR = 4U, ///< Acknowledge error
    CRC_ERROR = 5U, ///< CRC error
    UNKOWN_ERROR = 6U, ///< Unknown error
}en_can_error_t;

/**
********************************************************************************
** \brief CAN transmit buffer selection. (TCMD)
******************************************************************************/
typedef enum
{
    CanPTBSel = 0U, ///< Primary buffer select
    CanSTBSel = 1U, ///< Secondary buffer select
}en_can_buffer_sel_t;

/**
********************************************************************************
** \brief CAN Warning Limit (AFWL)
****************************************************************************/
typedef struct stc_can_warning_limit
{
    uint8_t CanWarningLimitVal; ///< Receive buffer almost full limit
    uint8_t CanErrorWarningLimitVal; ///< Error warning limit
}stc_can_warning_limit_t;

/**
****************************************************************************************
** \brief Filter Type (ACF)
**************************************************************************/
typedef enum en_can_acf_format_en
{
    CanStdFrames = 0x02u, ///< Accept only standard frames
    CanExtFrames = 0x03u, ///< Accept only extended frames
    CanAllFrames = 0x00u, ///< Receive both standard and extended frames
}en_can_acf_format_en_t;

/**
*******************************************************************************
** \brief Filter Group Enable (ACFEN)
******************************************************************************/
typedef enum en_can_filter_sel
{
    CanFilterSel1 = 0u, ///< Enable filter group 1
    CanFilterSel2 = 1u, ///< Filter group 2 enabled
    CanFilterSel3 = 2u, ///< Filter group 3 enabled
    CanFilterSel4 = 3u, ///< Filter group 4 enabled
    CanFilterSel5 = 4u, ///< Filter group 5 enabled
    CanFilterSel6 = 5u, ///< Filter group 6 enabled
    CanFilterSel7 = 6u, ///< Filter group 7 enabled
    CanFilterSel8 = 7u, ///< Filter group 8 enabled
}en_can_filter_sel_t;

/**
********************************************************************************
** \brief CAN transmit and receive interrupt enable (IE)
****************************************************************************/
typedef enum
{
    //<<Can Rx or Tx Irq En
    CanRxIrqEn = 0x00000080, ///< Receive interrupt enable
    CanRxOverIrqEn = 0x00000040, ///< Receive overflow interrupt enable
    CanRxBufFullIrqEn = 0x00000020, ///< Receive buffer full interrupt enable
    CanRxBufAlmostFullIrqEn = 0x00000010, ///< Receive buffer almost full interrupt enable
    CanTxPrimaryIrqEn = 0x00000008, ///< PTB transmit interrupt enable
    CanTxSecondaryIrqEn = 0x00000004, ///< STB transmit interrupt enable
    CanErrorIrqEn = 0x00000002, ///< Error interrupt enable
    CanErrorIrqEn = 0x00000002, ///< Error interrupt enable
    CanErrorIrqEn = 0x00000002 0x00200000, ///< Error passive interrupt enable
    CanArbiLostIrqEn = 0x00080000, ///< Arbitration loss interrupt enable
    CanBusErrorIrqEn = 0x00020000, ///< Bus error interrupt enable
}en_can_irq_type_t;

/**
********************************************************************************
** \brief CAN interrupt flag (IF)
********************************************************************************/
typedef enum
{
    CanTxBufFullIrqFlg = 0x00000001, ///< Transmit buffer full flag
    CanRxIrqFlg = 0x00008000, ///< Receive interrupt flag
    CanRxOverIrqFlg = 0x00004000, ///< Receive overflow interrupt flag
    CanRxBufFullIrqFlg = 0x00002000, ///< Receive buffer full interrupt flag
    CanRxBufAlmostFullIrqFlg = 0x00001000, ///< Receive buffer almost full interrupt flag
    CanTxPrimaryIrqFlg = 0x00000800, ///< PTB transmit interrupt flag
    CanTxSecondaryIrqFlg = 0x00000400, ///< STB transmit interrupt flag
    CanErrorIrqFlg = 0x00000200, ///< Error interrupt flag
    CanAbortIrqFlg = 0x00000100, ///< Abort transmit interrupt flag
    CanErrorWarningIrqFlg = 0x00800000, ///< Error limit reached warning flag
    CanErrorPassivenodeIrqFlg = 0x00400000, ///< Error passive node flag
    CanErrorPassiveIrqFlg = 0x00100000, ///< Error passive interrupt flag
    CanArbiLostIrqFlg = 0x00040000, ///< Arbitration loss interrupt flag
    CanBusErrorIrqFlg = 0x00010000, ///< Bus error interrupt flag
}en_can_irq_flag_type_t;

/**
********************************************************************************
** \brief CAN mode.(CFG_STAT)
****************************************************************************/
typedef enum
{
    CanExternalLoopBackMode = 0x40u, ///< External loopback mode
    CanInternalLoopBackMode = 0x20u, ///< Internal loopback mode
    CanTxSignalPrimaryMode = 0x10u, ///< PTB single-shot transmission mode
    CanTxSignalSecondaryMode = 0x08u, ///< STB single-shot transmission mode
    CanListenOnlyMode = 0xFFu, ///< Silent mode
}en_can_mode_t;

/**
************************************************************************************
** \brief CAN status (STAT)
****************************************************************************/
typedef enum
{
    CanRxActive = 0x04, ///< Receiving status
    CanTxActive = 0x02, ///< Transmitting status
    CanBusoff = 0x01, ///< Bus off status
}en_can_status_t;

/**
*******************************************************************************
** \brief CAN Transmit Command (TCMD)
************************************************************************/
typedef enum
{
    CanPTBTxCmd = 0x10, ///< PTB Transmit Command
    CanPTBTxAbortCmd = 0x08, ///< PTB Transmit Cancel Command
    CanSTBTxOneCmd = 0x04, ///< STB Single Frame Transmit Command
    CanSTBTxAllCmd = 0x02, ///< STB All Frames Command
    CanSTBTxAbortCmd = 0x01, ///< STB Transmit Cancel Command
}en_can_tx_cmd_t;

/**
********************************************************************************
** \brief CAN Sub-Buffer Transmit Mode Select (TCTRL)
******************************************************************************/
typedef enum
{
    CanSTBFifoMode = 0, ///< FIFO mode
    CanSTBPrimaryMode = 1, ///< Priority mode
}en_can_stb_mode_t;

/**
********************************************************************************
** \brief CAN self-acknowledgement (RCTRL)
****************************************************************************/
typedef enum
{
    CanSelfAckDisable = 0, ///< Disable self-acknowledgement
    CanSelfAckEnable = 1, ///< Enable self-acknowledgement (LBME=1)
}en_can_self_ack_en_t;

/**
************************************************************************************
** \brief Receive buffer overflow mode (RCTRL)
******************************************************************************/
typedef enum
{
    CanRxBufOverwritten = 0, ///< The oldest received data is overwritten
    CanRxBufNotStored = 1, ///< The most recently received data is not stored
}en_can_rx_buf_mode_en_t;

/**
********************************************************************************
** \brief Receive buffer data storage mode (RCTRL)
****************************************************************************/
typedef enum
{
    CanRxNormal = 0, ///< Normal mode
    CanRxAll = 1, ///< Store all data (including errors)
}en_can_rx_buf_all_t;

/**
************************************************************************************
** \brief CAN Receive Buffer Status (RSTAT)
**************************************************************************/
typedef enum
{
    CanRxBufEmpty = 0, ///< Empty
    CanRxBufnotAlmostFull = 1, ///< Not empty but less than the warning limit
    CanRxBufAlmostFull = 2, ///< Greater than the warning limit but not full
    CanRxBufFull = 3, ///< Full (overflow)
}en_can_rx_buf_status_t;

/**
*******************************************************************************
** \brief CAN Transmit Buffer Status (TSSTAT)
**************************************************************************/
typedef enum
{
    CanTxBufEmpty = 0, ///< Empty
    CanTxBufnotHalfFull = 1, ///< Less than or equal to half full
    CanTxBufHalfFull = 2, ///< More than half full
    CanTxBufFull = 3, ///< Full
}en_can_tx_buf_status_t;

/**
********************************************************************************
** \brief CAN filter.
****************************************************************************/
typedef struct stc_can_filter
{
    uint32_t u32CODE; ///< CODE
    uint32_t u32MASK; ///< MASK
    en_can_filter_sel_t enFilterSel; ///< Filter group selection
    en_can_acf_format_en_t enAcfFormat; ///< Filter frame format.
}stc_can_filter_t;

/**
*******************************************************************************
** \brief CAN timing.
**************************************************************************/
typedef struct stc_can_bt
{
    uint8_t SEG_1; ///< Segment 1 time (Tseg_1 = (SEG_1 + 2) * TQ)
    uint8_t SEG_2; ///< Segment 2 time (Tseg_2 = (SEG_2 + 1)*TQ)
    uint8_t SJW; ///< Resynchronization compensation width time (Tsjw = (SJW + 1)*TQ)
    uint8_t PRESC; ///< CAN clock prescaler (TQ)
}stc_can_bt_t;

/**
********************************************************************************
** \brief CAN data frame control.
************************************************************************/
typedef struct
{
    uint32_t DLC: 4; ///< Data length code
    uint32_t RESERVED0: 2; ///< Ignore
    uint32_t RTR: 1; ///< Remote transmission request
    uint32_t IDE: 1; ///< IDentifier extension 
    uint32_t RESERVED1 : 24; ///< Ignore
}stc_can_txcontrol_t;

/** 
******************************************************************************* 
** \brief CAN sends data frame. 
******************************************************************************/
typedef struct stc_can_txframe
{ 
  union 
  { 
    uint32_t TBUF32_0; ///< Ignore 
    uint32_t StdID; ///< Standard ID 
    uint32_t ExtID; ///< Extended ID 
  }; 
  union 
  { 
    uint32_t TBUF32_1; ///< Ignore 
    stc_can_txcontrol_t Control_f; ///< CAN Tx Control 
  }; 
  union 
  { 
    uint32_t TBUF32_2[2]; ///< Ignore 
    uint8_t Data[8]; ///< CAN data 
  }; 
  en_can_buffer_sel_t enBufferSel; ///< CAN Tx buffer select
}stc_can_txframe_t;

/** 
******************************************************************************* 
** \brief CAN receive data frame control. 
******************************************************************************/
typedef struct
{ 
    uint8_t DLC : 4; ///< Data length code 
    uint8_t RESERVED0 : 2; ///< Ignore 
    uint8_t RTR : 1; ///< Remote transmission request 
    uint8_t IDE : 1; ///< IDentifier extension
}stc_can_rxcontrol_t;

/** *******************************************************************************
** \brief CAN receive data frame status.
********************************************************************/
typedef struct
{
    uint8_t RESERVED0: 4; ///< Ignore
    uint8_t TX: 1; ///< TX is set to 1 if the loopback mode is activated
    uint8_t KOER: 3; ///< Kind of error
}stc_can_status_t;

/**
********************************************************************************
** \brief CAN data control, status, CYCTIM.
************************************************************************/
typedef struct
{
    stc_can_rxcontrol_t Control_f; ///< @ref stc_can_rxcontrol_t 
    stc_can_status_t Status_f; ///< @ref stc_can_status_t 
    uint16_t CycleTime; ///< TTCAN cycletime
}stc_can_cst_t;

/** 
******************************************************************************* 
** \brief CAN receive data frame. 
******************************************************************************/
typedef struct stc_can_rxframe
{ 
  union 
  { 
    uint32_t RBUF32_0; ///< Ignore 
    uint32_t StdID; ///< Standard ID 
    uint32_t ExtID; ///< Extended ID 
  }; 
  union 
  { 
    uint32_t RBUF32_1; ///< Ignore 
    stc_can_cst_t Cst; ///< @ref stc_can_cst_t 
  }; 
  union 
  { 
    uint32_t RBUF32_2[2]; ///< Ignore 
    uint8_t Data[8]; ///< CAN data 
  };
}stc_can_rxframe_t;

/** 
******************************************************************************* 
** \brief CAN initialization configuration. 
******************************************************************************/
typedef struct stc_can_init_config
{ 
    en_can_rx_buf_all_t enCanRxBufAll; ///< @ref en_can_rx_buf_all_t 
    en_can_rx_buf_mode_en_t enCanRxBufMode; ///< @ref en_can_rx_buf_mode_en_t 
    en_can_stb_mode_t enCanSTBMode; ///< @ref en_can_stb_mode_t 
    stc_can_bt_t stcCanBt; ///< @ref stc_can_bt_t 
    stc_can_warning_limit_t stcWarningLimit; ///< @ref stc_can_warning_limit_t
}stc_can_init_config_t;


/** 
******************************************************************************* 
** \brief CAN TTCAN 
******************************************************************************/
/** 
******************************************************************************* 
** \brief TTCAN buffer selection 
******************************************************************************/
typedef enum
{ 
    CanTTcanPTBSel = 0x00u, ///< PTB 
    CanTTcanSTB1Sel = 0x01u, ///< STB1
    CanTTcanSTB2Sel = 0x02u, ///< STB2
    CanTTcanSTB3Sel = 0x03u, ///< STB3
    CanTTcanSTB4Sel = 0x04u, ///< STB4
}en_can_ttcan_tbslot_t;

/**
********************************************************************************
** \brief TTCAN counter prescaler Frequency
**************************************************************************/
typedef enum
{
    CanTTcanTprescDiv1 = 0x00u, ///< Div1
    CanTTcanTprescDiv2 = 0x01u, ///< Div2
    CanTTcanTprescDiv3 = 0x02u, ///< Div3
    CanTTcanTprescDiv4 = 0x03u, ///< Div4
}en_can_ttcan_Tpresc_t;

/**
*******************************************************************************
** \brief TTCAN trigger type
**************************************************************************/
typedef enum
{
    CanTTcanImmediate = 0x00, ///< Immediate trigger
    CanTTcanTime = 0x01, ///< Time trigger
    CanTTcanSingle = 0x02, ///< Single transmit trigger
    CanTTcanTransStart = 0x03, ///< Transmit start trigger
    CanTTcanTransStop = 0x04, ///< Transmit stop trigger
}en_can_ttcan_trigger_type_t;

/**
********************************************************************************
** \brief TTCAN trigger interrupt flag
****************************************************************************/
typedef enum
{
    CanTTcanWdtTriggerIrq = 0x80, ///< Watchdog interrupt trigger flag
    CanTTcanErrorTriggerIrq = 0x10, ///< Error interrupt trigger flag
    CanTTcanTimTriggerIrq = 0x10, ///< time triggered interrupt flag
}en_can_ttcan_irq_type_t;


typedef struct stc_can_ttcan_ref_msg
{ 
  uint8_t u8IDE; ///< Reference message IDE:1-Extended; 0-Standard; 
  union ///< Reference message ID 
  { 
    uint32_t RefStdID; ///< Reference standard ID 
    uint32_t RefExtID; ///< Reference Extended ID 
  };
}stc_can_ttcan_ref_msg_t;

typedef struct stc_can_ttcan_trigger_config
{ 
    en_can_ttcan_tbslot_t enTbSlot; ///< Transmit trigger TB slot pointer 
    en_can_ttcan_trigger_type_t enTrigType; ///< Trigger type 
    en_can_ttcan_Tpresc_t enTpresc; ///< Timer prescaler 
    uint8_t u8Tew; ///< Transmit enable window 
    uint16_t u16TrigTime; ///< TTCAN trigger time 
    uint16_t u16WatchTrigTime; ///< TTCAN watch trigger time register
}stc_can_ttcan_trigger_config_t;


/************************************************************************************ 
* Global pre-processor symbols/macros ('#define') 
******************************************************************************/


/************************************************************************************ 
* Global variable definitions ('extern') 
******************************************************************************/

/************************************************************************************ 
* Global function prototypes (definition in C source)
************************************************************************/
///< CAN initialization configuration
void CAN_Init(stc_can_init_config_t *pstcCanInitCfg);
///< CAN deinitialization
void CAN_DeInit(void);
///< CAN interrupt control
void CAN_IrqCmd(en_can_irq_type_t enCanIrqType, boolean_t enNewState);
///< CAN interrupt flag get
boolean_t CAN_IrqFlgGet(en_can_irq_flag_type_t enCanIrqFlgType);
///< CAN interrupt flag clear
void CAN_IrqFlgClr(en_can_irq_flag_type_t enCanIrqFlgType);
///< CAN mode configuration
void CAN_ModeConfig(en_can_mode_t enMode, en_can_self_ack_en_t enCanSAck, boolean_t enNewState);
///< Get CAN error type
en_can_error_t CAN_ErrorStatusGet(void);
///< Get CAN status
boolean_t CAN_StatusGet(en_can_status_t enCanStatus);
///< CAN filter configuration
void CAN_FilterConfig(stc_can_filter_t *pstcFilter, boolean_t enNewState);
///< CAN transmit data frame configuration
void CAN_SetFrame(stc_can_txframe_t *pstcTxFrame);
///< CAN data frame transmission command
void CAN_TransmitCmd(en_can_tx_cmd_t enTxCmd);
///< CAN Get transmit buffer status
en_can_tx_buf_status_t CAN_TxBufStatusGet(void);
///< CAN data frame reception
void CAN_Receive(stc_can_rxframe_t *pstcRxFrame);
///< Get CAN receive buffer status
en_can_rx_buf_status_t CAN_RxBufStatusGet(stc_can_rxframe_t *pstcRxFrame);

///< CAN arbitration capture
uint8_t CAN_ArbitrationLostCap(void);
///< Get CAN receive error count
uint8_t CAN_RxErrorCntGet(void);
///< Get CAN transmit error count
uint8_t CAN_TxErrorCntGet(void);

//<< void CAN_TTCAN_Enable(void);
//<< void CAN_TTCAN_Disable(void);
//<< void CAN_TTCAN_IrqCmd(void);
//<< void CAN_TTCAN_ReferenceMsgSet(stc_can_ttcan_ref_msg_t *pstcRefMsg);
//<< void CAN_TTCAN_TriggerConfig(stc_can_ttcan_trigger_config_t *pstcTriggerCfg);

//@} // CanGroup

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

/************************************************************************************ 
* EOF (not truncated) 
******************************************************************************/
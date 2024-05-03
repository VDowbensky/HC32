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
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
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
/** \file uart.h
 **
 ** Headerfile for UART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __UART_H__
#define __UART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
 /**
 ******************************************************************************
 **\brief Uart channel selection
 ******************************************************************************/

typedef enum en_uart_channel
{
    UARTCH0 = 0u, ///<Serial port 0
    UARTCH1 = 1u, ///<Serial port 1
}en_uart_channel_t;
/**
 ******************************************************************************
 ** \brief Uart multi-master mode address frame/data frame or parity
 ******************************************************************************/
typedef enum en_uart_mmdorck
{
    UartDataOrAddr = 0u, ///<In multi-master mode, the frame is determined to be a data frame or an address frame by reading and writing SBUF[8].
    UartEven       = 1u, ///<Non-multi-master mode even parity   
    UartOdd        = 2u, ///<Non-multi-master mode odd parity    
}en_uart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief Uart multi-master mode configuration
 ******************************************************************************/
typedef enum en_uart_multimode
{
    UartNormal = 0u, ///<Normal working mode
    UartMulti  = 1u, ///<Multi-master working mode
}en_uart_multimode_t;
/**
 ******************************************************************************
 ** \brief Uart multi-master mode and slave address and address mask configuration
 ******************************************************************************/

typedef struct stc_uart_multimode
{
    en_uart_multimode_t enMulti_mode; ///<Multi-master mode configuration
    uint8_t             u8SlaveAddr;  ///<Slave address
    uint8_t                u8SaddEn;  ///<Slave address mask
}stc_uart_multimode_t;

/**
 ******************************************************************************
 ** \brief uart Four working mode options
 ******************************************************************************/

typedef enum en_uart_mode
{
    UartMode0 = 0u, ///<mode 0    
    UartMode1 = 1u, ///<mode 1
    UartMode2 = 2u, ///<mode 2
    UartMode3 = 3u, ///<mode 3
} en_uart_mode_t;
/**
 ******************************************************************************
 ** \brief uart Stop length selection
 ******************************************************************************/

typedef enum en_uart_stop
{
    Uart1bit  = 0u, ///<1 stop bit(s) 
    Uart15bit = 1u, ///<1.5 stop bit(s)
    Uart2bit  = 2u, ///<2 stop bit(s)
} en_uart_stop_t;
/**
 ******************************************************************************
 ** \brief uart Function enable
 ******************************************************************************/
typedef enum en_uart_func
{
    UartTx     = 0u, ///<Mode0mode represents TX   
    UartRx     = 1u, ///<Non-mode0mode stands for RX and TX, and mode0mode stands for RX
    UartDmaTx  = 3u, ///<DMA send enable
    UartDmaRx  = 4u, ///<DMA receive enable
    UartCtsRts = 5u, ///<Hardware flow control enable
}en_uart_func_t;
/**
 ******************************************************************************
 ** \brief Uart interrupt enable control
 ******************************************************************************/
typedef enum en_uart_irq_sel
{
    UartTxIrq  = 0u,  ///<Transmit interrupt enable        
    UartRxIrq  = 1u,  ///<Receive interrupt enable
    UartFEIrq  = 3u,  ///<Frame error interrupt enable
    UartCtsIrq = 4u,  ///<CTS signal toggle interrupt enable
    UartPEIrq  = 5u,  ///<Parity interrupt enable
    UartTxEIrq = 6u,  ///<TX empty interrupt enable   
}en_uart_irq_sel_t;
/**
 ******************************************************************************
 ** \brief Uart send and receive interrupt handler interface
 ******************************************************************************/

typedef struct stc_uart_irq_cb
{
    func_ptr_t pfnTxIrqCb;    ///<Send interrupt service function     
    func_ptr_t pfnRxFEIrqCb;  ///<Receive frame error interrupt service function
    func_ptr_t pfnRxIrqCb;    ///<Receive interrupt service function 
    func_ptr_t pfnCtsIrqCb;   ///<CTS signal toggle interrupt service function 
    func_ptr_t pfnPEIrqCb;    ///<Parity error interrupt service function 
}stc_uart_irq_cb_t;
/**
 ******************************************************************************
 ** \brief uart Status flags
 ******************************************************************************/
typedef enum en_uart_status
{
    UartCts   = 0u,  ///<CTS signal flag
    UartRC    = 1u,  ///<Receive data completion tag
    UartTC    = 2u,  ///<Send data completion flag
    UartPE    = 3u,  ///<Parity error flag
    UartFE    = 4u,  ///<Frame error flag  
    UartCtsIf = 5u,  ///<CTS interrupt flag
    UartTxe   = 6u,  ///<TXbuff empty tag
}en_uart_status_t;
/**
 ******************************************************************************
 ** \brief uart Channel address and interrupt function address structure
 ******************************************************************************/
typedef struct stc_uart_instance_data
{   
    uint32_t               u32Idx;               ///< Channel number
    M0P_UART_TypeDef       *pstcInstance;        ///< Channel register address
    stc_uart_irq_cb_t      stcUartInternIrqCb;   ///< Channel interrupt service function
} stc_uart_instance_data_t;
/**
 ******************************************************************************
 ** \brief uart Channel baud rate configuration
 ******************************************************************************/
typedef enum en_uart_clkdiv
{
    Uart16Or32Div = 0u,///<Mode 0 is invalid, mode 1/3 is divided by 16 and mode 2 is divided by 32.
    Uart8Or16Div  = 1u,///<Mode 0 is invalid, mode 1/3 is divided by 8 and mode 2 is divided by 16
}en_uart_clkdiv_t;
/**
 ******************************************************************************
 ** \brief uart Channel baud rate calculation parameter
 ******************************************************************************/
typedef struct stc_uart_baud
{
    uint32_t             u32Pclk;        ///<pclk
    en_uart_mode_t       enRunMode;      ///< Four mode configurations
    uint32_t             u32Baud;        ///< Baud rate
} stc_uart_baud_t;
/**
 ******************************************************************************
 ** \uart Overall configuration
 ******************************************************************************/

typedef struct stc_uart_config
{
    en_uart_mode_t       enRunMode;      ///< Four mode configurations
    en_uart_stop_t       enStopBit;      ///<Stop bit length
    stc_uart_multimode_t* pstcMultiMode; ///<Multi-master mode configuration
    stc_uart_irq_cb_t*  pstcIrqCb;       ///<Interrupt service function          
    boolean_t           bTouchNvic;      ///<NVIC interrupt enable    
} stc_uart_config_t;
//Interrupt related setting function
en_result_t Uart_EnableIrq(uint8_t u8Idx,
                           en_uart_irq_sel_t enIrqSel);
en_result_t Uart_DisableIrq(uint8_t u8Idx,
                            en_uart_irq_sel_t enIrqSel);
//void Uart_IrqHandler(uint8_t u8Idx);
// Total initialization processing
en_result_t Uart_Init(uint8_t u8Idx, 
                      stc_uart_config_t* pstcConfig);
en_result_t Uart_DeInit(uint8_t u8Idx, boolean_t bTouchNvic);
//UART module working mode setting function
en_result_t Uart_SetMode(uint8_t u8Idx,en_uart_mode_t enMode);
//UART module multi-master mode setting function
en_result_t Uart_SetMultiMode(uint8_t u8Idx,stc_uart_multimode_t* pstcMultiConfig);
//UART channel multi-master mode send data / address frame or parity configuration TB8
en_result_t Uart_SetMMDOrCk(uint8_t u8Idx,en_uart_mmdorck_t enTb8);
//Slave address configuration
en_result_t Uart_SetSaddr(uint8_t u8Idx,uint8_t u8Addr);
//Slave address mask configuration
en_result_t Uart_SetSaddrEn(uint8_t u8Idx,uint8_t u8Addren);
//Stop bit length setting
en_result_t Uart_SetStopBit(uint8_t u8Idx,uint8_t u8Len);
//RB8 data acquisition
boolean_t Uart_GetRb8(uint8_t u8Idx);

//Sampling prescaler setting
en_result_t Uart_SetClkDiv(uint8_t u8Idx,en_uart_clkdiv_t enClkDiv);
//Baud rate setting calculation
uint16_t Uart_CalScnt(uint8_t u8Idx,stc_uart_baud_t *pstcBaud);
//Baud rate setting
en_result_t Uart_SetBaud(uint8_t u8Idx,uint16_t u16Scnt);
//Get baud rate
uint32_t Uart_GetBaud(uint8_t u8Idx,uint8_t u8Mode,uint32_t u32Pclk);
                             
// Function enable and disable
en_result_t Uart_EnableFunc(uint8_t u8Idx, en_uart_func_t enFunc);
en_result_t Uart_DisableFunc(uint8_t u8Idx, en_uart_func_t enFunc);
//Status bit acquisition and clear 
uint8_t Uart_GetIsr(uint8_t u8Idx);
boolean_t Uart_GetStatus(uint8_t u8Idx,en_uart_status_t enStatus);
en_result_t Uart_ClrIsr(uint8_t u8Idx);
en_result_t Uart_ClrStatus(uint8_t u8Idx,en_uart_status_t enStatus);
//Data transfer
//en_result_t  Uart_MultiSendFirstData(uint8_t U8Addr);
en_result_t Uart_SendData(uint8_t u8Idx, uint8_t u8Data);
uint8_t Uart_ReceiveData(uint8_t u8Idx);

//@} // UartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/




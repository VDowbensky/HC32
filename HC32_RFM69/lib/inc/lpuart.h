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
 ** Headerfile for LPUART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __LPUART_H__
#define __LPUART_H__
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
 ** \defgroup LPUartGroup Universal Asynchronous Receiver/Transmitter (LPUART)
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
 **\brief LPuart channel selection
 ******************************************************************************/

typedef enum en_lpuart_channel
{
    LPUART0 = 0u, ///<Serial port 2
    LPUART1 = 1u, ///<Serial port 3
}en_lpuart_channel_t;
/**
 ******************************************************************************
 ** \brief lpuart 的sclk时钟源选择
 ******************************************************************************/

typedef enum en_lpuart_sclk_sel
{
    LPUart_Pclk   = 0u, ///<pclk
    LPUart_Pclk_1 = 1u, ///<pclk
    LPUart_Xtl    = 2u, ///<External low speed crystal
    LPUart_Rcl    = 3u, ///<Internal low speed crystal
} en_lpuart_sclksel_t;

/**
 ******************************************************************************
 ** \brief Lpuart multi-master mode address frame/data frame or parity
 ******************************************************************************/
typedef enum en_lpuart_mmdorck
{
    LPUartDataOrAddr = 0u, ///<In multi-master mode, the frame is determined to be a data frame or an address frame by reading and writing SBUF[8].
    LPUartEven       = 1u, ///<Non-multi-master mode even parity   
    LPUartOdd        = 2u, ///<Non-multi-master mode odd parity    
}en_lpuart_mmdorck_t;

/**
 ******************************************************************************
 ** \brief Lpuart multi-host mode configuration
 ******************************************************************************/
typedef enum en_lpuart_multimode
{
    LPUartNormal = 0u, ///<Normal working mode
    LPUartMulti  = 1u, ///<Multi-master working mode
}en_lpuart_multimode_t;
/**
 ******************************************************************************
 ** \brief Lpuart multi-master mode and slave address and address mask configuration
 ******************************************************************************/

typedef struct stc_lpuart_multimode
{
    en_lpuart_multimode_t enMulti_mode; ///<Multi-host mode configuration
    uint8_t             u8SlaveAddr;  ///<Slave address
    uint8_t                u8SaddEn;  ///<Slave address mask
}stc_lpuart_multimode_t;

/**
 ******************************************************************************
 ** \brief lpuart Four working mode options
 ******************************************************************************/

typedef enum en_lpuart_mode
{
    LPUartMode0 = 0u, ///<Mode 0    
    LPUartMode1 = 1u, ///<Mode 1
    LPUartMode2 = 2u, ///<Mode 2
    LPUartMode3 = 3u, ///<Mode 3
} en_lpuart_mode_t;
/**
 ******************************************************************************
 ** \brief lpuart Stop length selection
 ******************************************************************************/

typedef enum en_lpuart_stop
{
    LPUart1bit  = 0u, ///<1 stop bit 
    LPUart15bit = 1u, ///<1.5 stop bit 
    LPUart2bit  = 2u, ///<2 stop bit 
} en_lpuart_stop_t;
/**
 ******************************************************************************
 ** \brief lpuart Function enable
 ******************************************************************************/
typedef enum en_lpuart_func
{
    LPUartTx     = 0u, ///<Mode0 mode represents TX    
    LPUartRx     = 1u, ///<Non-mode0 mode stands for RX and TX, mode0 mode stands for RX
    LPUartDmaTx  = 3u, ///<DMA send enable
    LPUartDmaRx  = 4u, ///<DMA receive enable
    LPUartCtsRts = 5u, ///<Hardware control enable
}en_lpuart_func_t;
/**
 ******************************************************************************
 ** \brief Lpuart interrupt enable control
 ******************************************************************************/
typedef enum en_lpuart_irq_sel
{
    LPUartTxIrq  = 0u,  ///<Transmit interrupt enable        
    LPUartRxIrq  = 1u,  ///<Receive interrupt enable
    LPUartFEIrq  = 3u,  ///<Frame error interrupt enable
    LPUartCtsIrq = 4u,  ///<CTS signal toggle interrupt enable
    LPUartPEIrq  = 5u,  ///<Parity interrupt enable
    LPUartTxEIrq = 6u,  ///<TX empty interrupt enable   
}en_lpuart_irq_sel_t;
/**
 ******************************************************************************
 ** \brief Lpuart send and receive interrupt handler interface
 ******************************************************************************/

typedef struct stc_lpuart_irq_cb
{
    func_ptr_t pfnTxIrqCb;    ///<Send interrupt service function     
    func_ptr_t pfnRxFEIrqCb;  ///<Receive frame error interrupt service function
    func_ptr_t pfnRxIrqCb;    ///<Receive interrupt service function 
    func_ptr_t pfnCtsIrqCb;   ///<CTS signal toggle interrupt service function 
    func_ptr_t pfnPEIrqCb;    ///<Parity error interrupt service function 
}stc_lpuart_irq_cb_t;
/**
 ******************************************************************************
 ** \brief lpuart Status flags
 ******************************************************************************/
typedef enum en_lpuart_status
{
    LPUartCts   = 0u,  ///<CTS signal marking
    LPUartRC    = 1u,  ///<Receive data completion tag
    LPUartTC    = 2u,  ///<Send data completion tag
    LPUartPE    = 3u,  ///<Parity error flag
    LPUartFE    = 4u,  ///<Frame error flag  
    LPUartCtsIf = 5u,  ///CTS interrupt flag
    LPUartTxe   = 6u,  ///TXbuff empty tag
}en_lpuart_status_t;
/**
 ******************************************************************************
 ** \brief lpuart Channel address and interrupt function address structure
 ******************************************************************************/
typedef struct stc_lpuart_instance_data
{   
    uint32_t               u32Idx;               ///< Channel number
    M0P_LPUART_TypeDef     *pstcInstance;        ///< Channel register address
    stc_lpuart_irq_cb_t    stcLPUartInternIrqCb;   ///< Channel interrupt service function
} stc_lpuart_instance_data_t;
/**
 ******************************************************************************
 ** \brief lpuart Channel baud rate configuration
 ******************************************************************************/
typedef enum en_lpuart_clkdiv
{
    LPUart16Or32Div = 0u,///<Mode 0 is invalid, mode 1/3 is divided by 16 and mode 2 is divided by 32.
    LPUart8Or16Div  = 1u,///<Mode 0 is invalid, mode 1/3 is divided by 8 and mode 2 is divided by 16.
    LPUart4Or8Div   = 2u,///<Mode 0 is invalid, mode 1/3 is divided by 4, and mode 2 is divided by 8.
}en_lpuart_clkdiv_t;
/**
 ******************************************************************************
 ** \brief lpuart Clock related configuration
 ******************************************************************************/
typedef struct stc_lpuart_sclk_sel
{
    en_lpuart_clkdiv_t  enSclk_Prs; ///<Frequency division selection
    en_lpuart_sclksel_t enSclk_sel; ///<Transmission clock selection
}stc_lpuart_sclk_sel_t;
/**
 ******************************************************************************
 ** \brief lpuart Channel baud rate calculation parameter
 ******************************************************************************/
typedef struct stc_lpuart_baud
{
    uint32_t             u32Sclk;        ///<sclk
    en_lpuart_mode_t     enRunMode;      ///< Four mode configurations
    uint32_t             u32Baud;        ///< Baud rate
} stc_lpuart_baud_t;
/**
 ******************************************************************************
 ** \lpuart Overall configuration
 ******************************************************************************/

typedef struct stc_lpuart_config
{
    en_lpuart_mode_t       enRunMode;      ///< Four mode configurations
    stc_lpuart_sclk_sel_t* pstcLpuart_clk; ///<Clock source configuration
    en_lpuart_stop_t       enStopBit;      ///<Stop bit length
    stc_lpuart_multimode_t* pstcMultiMode; ///<Multi-host mode configuration
    stc_lpuart_irq_cb_t*  pstcIrqCb;       ///<Interrupt service function          
    boolean_t           bTouchNvic;      ///<NVIC interrupt enable    
} stc_lpuart_config_t;
//Interrupt related setting function
en_result_t LPUart_EnableIrq(uint8_t u8Idx,
                           en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(uint8_t u8Idx,
                            en_lpuart_irq_sel_t enIrqSel);
// Total initialization processing
en_result_t LPUart_Init(uint8_t u8Idx, 
                      stc_lpuart_config_t* pstcConfig);
//LPUART module working mode setting function
en_result_t LPUart_SetMode(uint8_t u8Idx,en_lpuart_mode_t enMode);
//LPUART module working mode setting function
en_result_t LPUart_SetMultiMode(uint8_t u8Idx,stc_lpuart_multimode_t* pstcMultiConfig);
//LPUART channel multi-master mode transmit data / address frame or parity configuration TB8
en_result_t LPUart_SetMMDOrCk(uint8_t u8Idx,en_lpuart_mmdorck_t enTb8);
//Slave address configuration
en_result_t LPUart_SetSaddr(uint8_t u8Idx,uint8_t u8Addr);
//Slave address mask configuration
en_result_t LPUart_SetSaddrEn(uint8_t u8Idx,uint8_t u8Addren);
//Stop bit configuration
en_result_t LPUart_SetStopBit(uint8_t u8Idx,uint8_t u8Len);
//Data register bit 8 bit acquisition
boolean_t LPUart_GetRb8(uint8_t u8Idx);
//Clock source selection
en_result_t LPUart_SelSclk(uint8_t u8Idx,en_lpuart_sclksel_t enClk);
//Clock source clock acquisition
uint32_t LPUart_GetSclk(uint8_t u8Idx);
//Sampling crossover setting
en_result_t LPUart_SetClkDiv(uint8_t u8Idx,en_lpuart_clkdiv_t enClkDiv);
//Baud rate setting calculation
uint16_t LPUart_CalScnt(uint8_t u8Idx,stc_lpuart_baud_t *pstcBaud);
//Baud rate setting
en_result_t LPUart_SetBaud(uint8_t u8Idx,uint16_t u16Scnt);
//Get baud rate
uint32_t LPUart_GetBaud(uint8_t u8Idx,uint8_t u8Mode,uint32_t u32Pclk);
                             
//Function enable and disable
en_result_t LPUart_EnableFunc(uint8_t u8Idx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(uint8_t u8Idx, en_lpuart_func_t enFunc);
//a state bit get function
boolean_t LPUart_GetStatus(uint8_t u8Idx,en_lpuart_status_t enStatus);
//Clearing status bit 
en_result_t LPUart_ClrStatus(uint8_t u8Idx,en_lpuart_status_t enStatus);
//Entire status register acquisition
uint8_t LPUart_GetIsr(uint8_t u8Idx);
//Entire status register clear
en_result_t LPUart_ClrIsr(uint8_t u8Idx);
//Data query mode sending operation
en_result_t LPUart_SendData(uint8_t u8Idx, uint8_t u8Data);
//Data query mode receiving operation
uint8_t LPUart_ReceiveData(uint8_t u8Idx);

//@} // LPUartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/




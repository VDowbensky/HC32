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
 * @file   uart.c
 *
 * @brief  Source file for UART functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "uart.h"
/**
 ******************************************************************************
 ** \addtogroup UartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/**
**********************************************************************************
** \brief UART communication interrupt enable function settings
**
** \param [in] UARTx channel number, enIrqSel transmit or receive interrupt enable
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
**************************************************************************/
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, TRUE);

    return Ok;
}

/**
****************************************************************************
** \brief UART communication interrupt disable function setting
**
** \param [in] UARTx channel number, enIrqSel transmit or receive interrupt disable
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, FALSE);
    
    return Ok;
}


auto_awesome
Перекласти з такої мови: англійська
5 000 / 5 000
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
* @file uart.c 
* 
* @brief Source file for UART functions 
* 
* @author MADS Team 
* ******************************************************************************/

/******************************************************************************/
/* Include files */
/******************************************************************************/
#include "uart.h"
/** 
****************************************************************************** 
** \addtogroup UartGroup 
******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define') */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static') */
/**********************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static') */
/******************************************************************************/

/**
**********************************************************************************
** \brief UART communication interrupt enable function settings
**
** \param [in] UARTx channel number, enIrqSel transmit or receive interrupt enable
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
**************************************************************************/
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, TRUE);

return Ok;
}
/**
****************************************************************************
** \brief UART communication interrupt disable function setting
**
** \param [in] UARTx channel number, enIrqSel transmit or receive interrupt disable
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, FALSE);

return Ok;
}

/**
******************************************************************************
** \brief UART channel multi-master mode configuration
**
** \param [in] UARTx channel number, stcMultiCfg multi-master mode structure
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx, stc_uart_multimode_t* pstcMultiCfg)
{
    if(NULL != pstcMultiCfg)
    {
        UARTx->SCON_f.ADRDET = TRUE;   
        UARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        UARTx->SADEN = pstcMultiCfg->u8SaddEn;

    }
    else
    {
        return ErrorInvalidParameter;
    }
    
    return Ok;
}

/**
************************************************************************
** \brief UART single-line half-duplex mode enabled
**
** \param [in] UARTx channel number
**
** \retval Null
************************************************************************/
void Uart_HdModeEnable(M0P_UART_TypeDef* UARTx)
{
    UARTx->SCON_f.HDSEL = TRUE;
}

/**
************************************************************************************
** \brief UART single-line half-duplex mode disabled
**
** \param [in] UARTx channel number
**
** \retval Null
************************************************************************/
void Uart_HdModeDisable(M0P_UART_TypeDef* UARTx)
{
    UARTx->SCON_f.HDSEL = FALSE;
}

/**
****************************************************************************
** \brief UART channel multi-processor mode transmit data/address frame configuration TB8
**
** \param [in] UARTx channel number
** \param [in] TRUE - TB8 is the address frame flag; FALSE - TB8 is the data frame flag;
**
** \retval Null
************************************************************************/
void Uart_SetTb8(M0P_UART_TypeDef* UARTx, boolean_t bTB8Value)
{
    UARTx->SCON_f.B8CONT = bTB8Value;
    
}

/**
******************************************************************************
** \brief Get RB8 value
**
** \param [in] UARTx channel number
**
** \retval RB8
**************************************************************************/
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.DATA8);
}

/**
******************************************************************************
** \brief UART channel multi-master mode slave address configuration function
**
** \param [in] UARTx channel number, address
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
********************************************************************/
en_result_t Uart_SetSaddr(M0P_UART_TypeDef* UARTx,uint8_t u8Addr)
{
    UARTx->SADDR = u8Addr;
    
    return Ok;
}

/**
************************************************************************************
** \brief UART channel transmit or receive function enable setting
**
** \param [in] UARTx channel number, enFunc function
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{    
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, TRUE);
    
    return Ok;
}

/**
********************************************************************************
** \brief UART channel transmit or receive function disable settings
**
** \param [in] UARTx channel number, enFunc function
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, FALSE);
    
    return Ok;
}

/**
************************************************************************
** \brief UART channel communication status acquisition
**
** \param [in] UARTx channel number
**
** \retval status value
********************************************************************/
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->ISR);
}

/**
********************************************************************************
** \brief UART channel communication status acquisition
**
** \param [in] UARTx channel number, enStatus obtains the status
**
** \retval status value
********************************************************************/
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

     
    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(UARTx->ISR)), enStatus);
    
    return bStatus;
}

/**
********************************************************************************
** \brief UART channel communication status clear
**
** \param [in] UARTx channel number
**
** \retval OK
** \retval ErrorInvalidParameter clear failed
********************************************************************/
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx)
{
    UARTx->ICR = 0u;
    return Ok;
}

/**
******************************************************************************
** \brief UART channel communication status clear
**
** \param [in] UARTx channel number, enStatus clears which status
**
** \retval OK
** \retval ErrorInvalidParameter clear failed
********************************************************************/
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(UARTx->ICR)), enStatus, FALSE);
    
    return Ok;
}

/**
********************************************************************************
** \brief UART channel data sending function. Call this function in query mode; interrupt mode is not applicable.
**
** \param [in] UARTx channel number, Data to send data
**
** \retval Ok Send successfully
** \retval ErrorInvalidParameter Send failed
************************************************************************/
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
    while(FALSE == Uart_GetStatus(UARTx,UartTxe))
    {}
    UARTx->SBUF_f.DATA = u8Data;
    while(FALSE == Uart_GetStatus(UARTx,UartTC))
    {}
    Uart_ClrStatus(UARTx,UartTC);       
    return Ok;
}

/**
********************************************************************************
** \brief UART channel data sending function. Call this function in query mode; interrupt mode is not applicable.
**
** \param [in] UARTx channel number, Data sends data 
** 
** \retval @ref en_result_t 
******************************************************************************/
en_result_t Uart_SendDataPollTimeOut(M0P_UART_TypeDef* UARTx, uint8_t u8Data, uint32_t u32TimeOut)
{
    uint32_t u32Cnt = 0;
    
    while(FALSE == Uart_GetStatus(UARTx,UartTxe))
    {
        if(u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;
    }
    UARTx->SBUF_f.DATA = u8Data;
    
    u32Cnt = 0;
    while(FALSE == Uart_GetStatus(UARTx,UartTC))
    {
        if(u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;
    }
    Uart_ClrStatus(UARTx,UartTC);       
    return Ok;
}

/**
********************************************************************************
** \brief UART channel data sending function, called via interrupt
**
** \param [in] UARTx channel number, Data to send data
**
** \retval Ok Send successful
** \retval ErrorInvalidParameter Send failed
************************************************************************/
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{ 
    UARTx->SBUF_f.DATA = u8Data; 
    
    return Ok;
}


Rief UART tōngdào duō zhǔjī móshì cóng jī dìzhǐ pèizhì hánshù ** ** \param [in] UARTx tōngdào hào,addr dìzhǐ ** ** \retval OK pèizhì chénggōng ** \retval ErrorInvalidParameter pèizhì shībài ******************************************************************************/ en_result_t Uart_SetSaddr(M0P_UART_TypeDef* UARTx,uint8_t u8Addr) { UARTx->SADDR = u8Addr; return Ok; } /** ****************************************************************************** ** \brief UART tōngdào fāsòng huò jiēshōu děng gōngnéng shǐ néng shèzhì ** ** \param [in] UARTx tōngdào hào,enFunc gōngnéng ** ** \retval OK pèizhì chénggōng ** \retval ErrorInvalidParameter pèizhì shībài ******************************************************************************/ en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc) { SetBit((uint32_t)(&(UARTx->SCON)), enFunc, TRUE); return Ok; } /** ****************************************************************************** ** \brief UART tōngdào fāsòng huò jiēshōu děng gōngnéng jìnzhǐ shèzhì ** ** \param [in] UARTx tōngdào hào,enFunc gōngnéng ** ** \retval OK pèizhì chénggōng ** \retval ErrorInvalidParameter pèizhì shībài ******************************************************************************/ en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc) { SetBit((uint32_t)(&(UARTx->SCON)), enFunc, FALSE); return Ok; } /** ****************************************************************************** ** \brief UART tōngdào tōngxìn zhuàngtài huòqǔ ** ** \param [in] UARTx tōngdào hào ** ** \retval zhuàngtài zhí ******************************************************************************/ uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx) { return (UARTx->ISR); } /** ****************************************************************************** ** \brief UART tōngdào tōngxìn zhuàngtài huòqǔ ** ** \param [in] UARTx tōngdào hào,enStatus huòqǔ nǎge zhuàngtài ** ** \retval zhuàngtài zhí ******************************************************************************/ boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus) { boolean_t bStatus = FALSE; ASSERT(IS_VALID_STATUS(enStatus)); bStatus = GetBit((uint32_t)(&(UARTx->ISR)), enStatus); return bStatus; } /** ****************************************************************************** ** \brief UART tōngdào tōngxìn zhuàngtài qīngchú ** ** \param [in] UARTx tōngdào hào ** ** \retval OK ** \retval ErrorInvalidParameter qīngchú shībài ******************************************************************************/ en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx) { UARTx->ICR = 0u; return Ok; } /** ****************************************************************************** ** \brief UART tōngdào tōngxìn zhuàngtài qīngchú ** ** \param [in] UARTx tōngdào hào,enStatus qīngchú nǎge zhuàngtài ** ** \retval OK ** \retval ErrorInvalidParameter qīngchú shībài ******************************************************************************/ en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus) { ASSERT(IS_VALID_STATUS(enStatus)); SetBit((uint32_t)(&(UARTx->ICR)), enStatus, FALSE); return Ok; } /** ****************************************************************************** ** \brief UART tōngdào fāsòng shùjù hánshù, cháxún fāngshì diàoyòng cǐ hánshù, zhōngduàn fāngshì fǎ sòng bù shìyòng ** ** \param [in] UARTx tōngdào hào,Data fāsòng shùjù ** ** \retval Ok fāsòng chénggōng ** \retval ErrorInvalidParameter fāsòng shībài ******************************************************************************/ en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data) { while(FALSE == Uart_GetStatus(UARTx,UartTxe)) {} UARTx->SBUF_f.DATA = u8Data; while(FALSE == Uart_GetStatus(UARTx,UartTC)) {} Uart_ClrStatus(UARTx,UartTC); return Ok; } /** ****************************************************************************** ** \brief UART tōngdào fāsòng shùjù hánshù, cháxún fāngshì diàoyòng cǐ hánshù, zhōngduàn fāngshì fǎ sòng bù shìyòng ** ** \param [in] UARTx tōngdào hào,Data fāsòng shùjù ** ** \retval@ref en_result_t ******************************************************************************/ en_result_t Uart_SendDataPollTimeOut(M0P_UART_TypeDef* UARTx, uint8_t u8Data, uint32_t u32TimeOut) { uint32_t u32Cnt = 0; while(FALSE == Uart_GetStatus(UARTx,UartTxe)) { if(u32Cnt > u32TimeOut) { return ErrorTimeout; } u32Cnt++; } UARTx->SBUF_f.DATA = u8Data; u32Cnt = 0; while(FALSE == Uart_GetStatus(UARTx,UartTC)) { if(u32Cnt > u32TimeOut) { return ErrorTimeout; } u32Cnt++; } Uart_ClrStatus(UARTx,UartTC); return Ok; } /** ****************************************************************************** ** \brief UART tōngdào fāsòng shùjù hánshù, zhōngduàn fāngshì diàoyòng cǐ hánshù ** ** \param [in] UARTx tōngdào hào,Data fāsòng shùjù ** ** \retval Ok fāsòng chénggōng ** \retval ErrorInvalidParameter fāsòng shībài ******************************************************************************/ en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data) { UARTx->SBUF_f.DATA = u8Data; return Ok; } /** ****************************************************************************** ** \brief UART tōngdào jiēshōu shùjù hánshù ** ** \param [in] UARTx tōngdào hào ** ** \retval jiēshōu shùjù ******************************************************************************/
Показати більше
5 000 / 5 000
Brief UART channel multi-master mode slave address configuration function
**
** \param [in] UARTx channel number, address
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
********************************************************************/
en_result_t Uart_SetSaddr(M0P_UART_TypeDef* UARTx, uint8_t u8Addr)
{
UARTx->SADDR = u8Addr;

return Ok;
}

/**
************************************************************************************
** \brief UART channel transmit or receive function enable setting
**
** \param [in] UARTx channel number, enFunc function
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
SetBit((uint32_t)(&(UARTx->SCON)), enFunc, TRUE);

return Ok;
}
/**
********************************************************************************
** \brief UART channel transmit or receive function disable settings
**
** \param [in] UARTx channel number, enFunc function
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
SetBit((uint32_t)(&(UARTx->SCON)), enFunc, FALSE);

return Ok;
}
/**
************************************************************************
** \brief UART channel communication status acquisition
**
** \param [in] UARTx channel number
**
** \retval status value
********************************************************************/
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx)
{
return (UARTx->ISR);
}

/**
********************************************************************************
** \brief UART channel communication status acquisition
**
** \param [in] UARTx channel number, enStatus obtains the status
**
** \retval status value
********************************************************************/
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus)
{
boolean_t bStatus = FALSE;

ASSERT(IS_VALID_STATUS(enStatus));

bStatus = GetBit((uint32_t)(&(UARTx->ISR)), enStatus);

return bStatus;
}
/**
********************************************************************************
** \brief UART channel communication status clear
**
** \param [in] UARTx channel number
**
** \retval OK
** \retval ErrorInvalidParameter clear failed
********************************************************************/
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx)
{
UARTx->ICR = 0u;
return Ok;
}
/**
******************************************************************************
** \brief UART channel communication status clear
**
** \param [in] UARTx channel number, enStatus clears which status
**
** \retval OK
** \retval ErrorInvalidParameter clear failed
********************************************************************/
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus)
{
ASSERT(IS_VALID_STATUS(enStatus));

SetBit((uint32_t)(&(UARTx->ICR)), enStatus, FALSE);

return Ok;
}
/**
********************************************************************************
** \brief UART channel data sending function. Call this function in query mode; interrupt mode is not applicable.
**
** \param [in] UARTx channel number, Data to send data
**
** \retval Ok Send successfully
** \retval ErrorInvalidParameter Send failed
************************************************************************/
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
while(FALSE == Uart_GetStatus(UARTx,UartTxe))
{}
UARTx->SBUF_f.DATA = u8Data;
while(FALSE == Uart_GetStatus(UARTx,UartTC))
{}
Uart_ClrStatus(UARTx,UartTC);
return Ok;
}

/**
********************************************************************************
** \brief UART channel data sending function. Call this function in query mode; interrupt mode is not applicable.
**
** \param [in] UARTx channel number, Data sends data 
** 
** \retval @ref en_result_t 
******************************************************************************/
en_result_t Uart_SendDataPollTimeOut(M0P_UART_TypeDef* UARTx, uint8_t u8Data, uint32_t u32TimeOut)
{ 
uint32_t u32Cnt = 0; 

while(FALSE == Uart_GetStatus(UARTx,UartTxe)) 
{ 
if(u32Cnt > u32TimeOut) 
{ 
return ErrorTimeout; 
} 
u32Cnt++; 
} 
UARTx->SBUF_f.DATA = u8Data; 

u32Cnt = 0; 
while(FALSE == Uart_GetStatus(UARTx,UartTC)) 
{ if(u32Cnt > u32TimeOut)
{
return ErrorTimeout;
}
u32Cnt++;
}
Uart_ClrStatus(UARTx,UartTC);
return Ok;
}

/**
********************************************************************************
** \brief UART channel data sending function, called via interrupt
**
** \param [in] UARTx channel number, Data to send data
**
** \retval Ok Send successful
** \retval ErrorInvalidParameter Send failed
************************************************************************/
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
UARTx->SBUF_f.DATA = u8Data;

return Ok;
}

/**
******************************************************************************
** \brief UART channel receive data function
**
** \param [in] UARTx channel number
**
** \retval Receive data
**************************************************************************/
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.DATA);
}

/**
**************************************************************************
** \brief UART channel initialization function
**
** \param [in] UARTx channel number, pstcCfg initialization structure @ref stc_uart_cfg_t
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
**************************************************************************/
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    uint32_t u32Over[2] = {0x4, 0x3};
    uint16_t u16OverShift;
    float32_t f32Scnt=0;
    
    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }
    
    UARTx->SCON = 0;
    
    UARTx->SCON = (uint32_t)pstcCfg->enStopBit |
                  (uint32_t)pstcCfg->enMmdorCk |
                  (uint32_t)pstcCfg->stcBaud.enClkDiv |
                  (uint32_t)pstcCfg->enRunMode;
    
    if((UartMskMode1 == pstcCfg->enRunMode) || (UartMskMode3 == pstcCfg->enRunMode))
    {
        u16OverShift = u32Over[pstcCfg->stcBaud.enClkDiv/UartMsk8Or16Div];
        f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Pclk)/(float32_t)(pstcCfg->stcBaud.u32Baud<<u16OverShift);        
        UARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
        Uart_EnableFunc(UARTx,UartRenFunc);       ///<Enable transceiver
    }
    
    
 
    enRet = Ok;
    return enRet;
}
//@} // UartGroup      

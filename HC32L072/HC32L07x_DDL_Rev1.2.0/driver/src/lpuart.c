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
 * @file   lpuart.c
 *
 * @brief  Source file for LPUART functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "lpuart.h"
/**
 ******************************************************************************
 ** \addtogroup LPUartGroup
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
** \brief LPUART communication interrupt enable function setup
**
** \param [in] LPUARTx channel number, enIrqSel transmit or receive interrupt enable
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
**************************************************************************/
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), enIrqSel, TRUE);

    return Ok;
}

/**
********************************************************************************
** \brief LPUART communication interrupt disable function setting
**
** \param [in] LPUARTx channel number, enIrqSel transmit or receive interrupt disable
**
** \retval OK Configuration successful
**\retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{

    SetBit((uint32_t)(&(LPUARTx->SCON)), enIrqSel, FALSE);

    return Ok;
}

/**
************************************************************************
** \brief lpuart communication clock source selection
**
** \param [in] LPUARTx channel number, enClk clock source option
**
** \retval Ok Setting successful
**\retval ErrorInvalidParameter Setting failed
************************************************************************/
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk)
{
    ASSERT(IS_VALID_CLK(enSclk));

    LPUARTx->SCON_f.SCLKSEL = enSclk;

    return Ok;
}

/**
************************************************************************************
** \brief LPUART channel multi-master mode configuration
**
** \param [in] LPUARTx channel number, stcMultiCfg multi-master mode structure
**
** \retval OK Configuration successful
**\retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg)
{

    if(NULL != pstcMultiCfg)
    {
        LPUARTx->SCON_f.ADRDET = TRUE;
        LPUARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        LPUARTx->SADEN = pstcMultiCfg->u8SaddEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
******************************************************************************
** \brief LPUART single-line half-duplex mode enable
**
** \param [in] LPUARTx channel number
**
** \retval Null
************************************************************************/
void LPUart_HdModeEnable(M0P_LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = TRUE;
}


/**
********************************************************************************
** \brief LPUART single-line half-duplex mode disable
**
** \param [in] LPUARTx channel number
**
** \retval Null
************************************************************************/
void LPUart_HdModeDisable(M0P_LPUART_TypeDef* LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = FALSE;
}

/**
****************************************************************************
** \brief LPUART channel multi-device mode sends data/address frame configuration TB8
**
** \param [in] LPUARTx channel number
** \param [in] TRUE - TB8 is the address frame flag; FALSE - TB8 is the data frame flag;
**
** \retval Null
****************************************************************************/
void LPUart_SetTb8(M0P_LPUART_TypeDef* LPUARTx, boolean_t bTB8Value)
{
    LPUARTx->SCON_f.B8CONT = bTB8Value;

}

/**
****************************************************************************
** \brief Get RB8 value
**
** \param [in] LPUARTx channel number
**
** \retval RB8
**\retval ErrorInvalidParameter Configuration failed
********************************************************************/
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->SBUF_f.DATA8);
}

/**
************************************************************************************
** \brief LPUART channel multi-master mode slave address configuration function
**
** \param [in] LPUARTx channel number, addr address
**
** \retval OK Configuration successful
**\retval ErrorInvalidParameter Configuration failed
************************************************************************/
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef* LPUARTx,uint8_t u8Addr)
{
    LPUARTx->SADDR = u8Addr;

    return Ok;
}

/**
************************************************************************************
** \brief LPUART channel transmit or receive function enable settings
**
** \param [in] u8Idx channel number, enFunc function
**
** \retval OK Configuration successful
**\retval ErrorInvalidParameter Configuration failed
******************************************************************************/
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enFunc, TRUE);

    return Ok;
}

/**
******************************************************************************
** \brief Setting the LPUART channel transmit or receive function disable
**
** \param [in] u8Idx channel number, enFunc function
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
**************************************************************************/
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enFunc, FALSE);

    return Ok;
}

/**
****************************************************************************
** \brief Get LPUART channel communication status
**
** \param [in] u8Idx channel number
**
** \retval Status value
************************************************************************/
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->ISR);
}

/**
********************************************************************************
** \brief Get LPUART channel communication status
**
** \param [in] u8Idx channel number, enStatus gets the status
**
** \retval Status value
**\retval ErrorInvalidParameter Get failed
**************************************************************************/
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

    ASSERT(IS_VALID_STATUS(enStatus));

    bStatus =  GetBit((uint32_t)(&(LPUARTx->ISR)), enStatus);

    return bStatus;
}

/**
******************************************************************************
** \brief Clears all LPUART channel communication statuses
**
** \param [in] u8Idx channel number
**
** \retval OK
******************************************************************************/
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef* LPUARTx)
{
    LPUARTx->ICR = 0u;
    return Ok;
}

/**
************************************************************************************
** \brief LPUART channel communication status clear
**
** \param [in] u8Idx channel number, enStatus which status to clear
**
** \retval status value
**\retval ErrorInvalidParameter clear failed
********************************************************************/
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef* LPUARTx,en_lpuart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));

    SetBit((uint32_t)(&(LPUARTx->ICR)), enStatus, FALSE);

    return Ok;
}

/**
****************************************************************************
** \brief LPUART channel data sending function. Call this function in query mode; interrupt mode is not applicable.
**
** \param [in] u8Idx channel number, Data to send data
**
** \retval Ok Send successful
**\retval ErrorInvalidParameter Send failed
************************************************************************/
en_result_t LPUart_SendData(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data)
{
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {}
    LPUARTx->SBUF_f.DATA = u8Data;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {}
    LPUart_ClrStatus(LPUARTx,LPUartTC);
    return Ok;
}

/**
******************************************************************************
** \brief LPUART channel data sending function. Call this function in query mode; interrupt mode is not applicable.
**
** \param [in] u8Idx channel number, Data to send data
**
** \retval @ref en_result_t
******************************************************************************/
en_result_t LPUart_SendDataTimeOut(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data, uint32_t u32TimeOut)
{
    uint32_t u32Cnt = 0;
    
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTxe))
    {
        if(u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;    
    }
    LPUARTx->SBUF_f.DATA = u8Data;
    while(FALSE == LPUart_GetStatus(LPUARTx,LPUartTC))
    {        
        if(u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;
    }
    LPUart_ClrStatus(LPUARTx,LPUartTC);
    return Ok;
}

/**
************************************************************************
** \brief LPUART channel data sending function, called via interrupt
**
** \param [in] u8Idx channel number, Data sending data
**
** \retval Ok Sending success
**\retval ErrorInvalidParameter Sending failure
************************************************************************/
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data)
{
    LPUARTx->SBUF_f.DATA = u8Data;

    return Ok;
}

/**
************************************************************************************
** \brief LPUART channel data receiving function
**
** \param [in] u8Idx channel number
**
** \retval Received data
**\retval ErrorInvalidParameter Receive failed
**************************************************************************/
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef* LPUARTx)
{
    return (LPUARTx->SBUF_f.DATA);
}

/**
******************************************************************************
** \brief LPUART channel initialization function
**
** \param [in] u8Idx channel number, pstcCfg initialization structure @ref stc_lpuart_cfg_t
**
** \retval OK Configuration successful
** \retval ErrorInvalidParameter Configuration failed
**********************************************************************/
en_result_t LPUart_Init(M0P_LPUART_TypeDef* LPUARTx,stc_lpuart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    const uint32_t u32Over[3] = {0x4, 0x3, 0x2};
    uint16_t u16OverShift;
    float32_t f32Scnt=0;

    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    LPUARTx->SCON = 0;

    LPUARTx->SCON = (uint32_t)pstcCfg->enStopBit          |
                    (uint32_t)pstcCfg->enMmdorCk          |
                    (uint32_t)pstcCfg->stcBaud.enSclkDiv  |
                    (uint32_t)pstcCfg->stcBaud.enSclkSel  |
                    (uint32_t)pstcCfg->enRunMode;

    if((LPUartMskMode1 == pstcCfg->enRunMode) || (LPUartMskMode3 == pstcCfg->enRunMode))
    {
        u16OverShift = u32Over[pstcCfg->stcBaud.enSclkDiv/LPUartMsk8Or16Div];
        f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Sclk)/(float32_t)(pstcCfg->stcBaud.u32Baud<<u16OverShift);
        LPUARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
        LPUart_EnableFunc(LPUARTx,LPUartRenFunc);       ///<使能收发
    }



    enRet = Ok;
    return enRet;
}
//@} // LPUartGroup

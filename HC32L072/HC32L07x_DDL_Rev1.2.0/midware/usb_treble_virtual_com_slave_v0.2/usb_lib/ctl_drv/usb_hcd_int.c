/******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd. All rights reserved.
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
/******************************************************************************/
/** \file usbd_desc.c
 **
 ** A detailed description is available at
 ** @link
		Host driver interrupt subroutines.
	@endlink
 **
 **   - 2018-12-26  1.0  wangmin First version for USB demo.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_core.h"
#include "usb_defines.h"
#include "usb_hcd_int.h"


/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#if defined   (__CC_ARM) /*!< ARM Compiler */
#pragma O0
#elif defined (__GNUC__) /*!< GNU Compiler */
#pragma GCC optimize ("O0")
#elif defined  (__TASKING__) /*!< TASKING Compiler */
#pragma optimize=0
#endif /* __CC_ARM */
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static uint32_t USB_OTG_USBH_handle_sof_ISR(USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_port_ISR(USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_hc_ISR (USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_hc_n_In_ISR (USB_OTG_CORE_HANDLE *pdev ,
                                                 uint32_t num);
static uint32_t USB_OTG_USBH_handle_hc_n_Out_ISR (USB_OTG_CORE_HANDLE *pdev ,
                                                  uint32_t num);
static uint32_t USB_OTG_USBH_handle_rx_qlvl_ISR (USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_nptxfempty_ISR (USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_ptxfempty_ISR (USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_Disconnect_ISR (USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_IncompletePeriodicXfer_ISR (USB_OTG_CORE_HANDLE *pdev);
static uint32_t USB_OTG_USBH_handle_RemoteWakeUp_ISR (USB_OTG_CORE_HANDLE *pdev);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief  HOST_Handle_ISR
 **         This function handles all USB Host Interrupts
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
uint32_t USBH_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GINTSTS_TypeDef  gintsts;
    uint32_t retval = 0;

    gintsts.d32 = 0;

    /* Check if HOST Mode */
    if (USB_OTG_IsHostMode(pdev))
    {
        gintsts.d32 = USB_OTG_ReadCoreItr(pdev);
        if (!gintsts.d32)
        {
            return 0;
        }

        if (gintsts.b.sofintr)
        {
            retval |= USB_OTG_USBH_handle_sof_ISR (pdev);
        }

        if (gintsts.b.rxstsqlvl)
        {
            retval |= USB_OTG_USBH_handle_rx_qlvl_ISR (pdev);
        }

        if (gintsts.b.nptxfempty)
        {
        retval |= USB_OTG_USBH_handle_nptxfempty_ISR (pdev);
        }

        if (gintsts.b.ptxfempty)
        {
            retval |= USB_OTG_USBH_handle_ptxfempty_ISR (pdev);
        }

        if (gintsts.b.hcintr)
        {
            retval |= USB_OTG_USBH_handle_hc_ISR (pdev);
        }

        if (gintsts.b.portintr)
        {
            retval |= USB_OTG_USBH_handle_port_ISR (pdev);
        }

        if (gintsts.b.disconnect)
        {
            retval |= USB_OTG_USBH_handle_Disconnect_ISR (pdev);
        }

        if (gintsts.b.incomplisoout)
        {
            retval |= USB_OTG_USBH_handle_IncompletePeriodicXfer_ISR (pdev);
        }
        if (gintsts.b.wkupintr)
        {
            retval |= USB_OTG_USBH_handle_RemoteWakeUp_ISR (pdev);
        }
    }
    return retval;
}

/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_hc_ISR
 **         This function indicates that one or more host channels has a pending
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
static uint32_t USB_OTG_USBH_handle_hc_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_HAINT_TypeDef        haint;
    USB_OTG_HCCHAR_TypeDef       hcchar;
    uint32_t i = 0;
    uint32_t retval = 0;

    /* Clear appropriate bits in HCINTn to clear the interrupt bit in GINTSTS */
    haint.d32 = USB_OTG_ReadHostAllChannels_intr(pdev);

    for (i = 0; i < pdev->cfg.host_channels ; i++)
    {
        if (haint.b.chint & (1 << i))
        {
            hcchar.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[i]->HCCHAR);

            if (hcchar.b.epdir)
            {
                retval |= USB_OTG_USBH_handle_hc_n_In_ISR (pdev, i);
            }
            else
            {
                retval |=  USB_OTG_USBH_handle_hc_n_Out_ISR (pdev, i);
            }
        }
    }
    return retval;
}

/**
 *******************************************************************************
 ** \brief  USB_OTG_otg_hcd_handle_sof_intr
 **         Handles the start-of-frame interrupt in host mode.
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
static uint32_t USB_OTG_USBH_handle_sof_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GINTSTS_TypeDef      gintsts;
    gintsts.d32 = 0;

    USBH_HCD_INT_fops->SOF(pdev);

    /* Clear interrupt */
    gintsts.b.sofintr = 1;
    USB_OTG_WRITE_REG32(&pdev->regs.GREGS->GINTSTS, gintsts.d32);

    return 1;
}

/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_Disconnect_ISR
 **         Handles disconnect event.
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
static uint32_t USB_OTG_USBH_handle_Disconnect_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GINTSTS_TypeDef      gintsts;

    gintsts.d32 = 0;

    USBH_HCD_INT_fops->DevDisconnected(pdev);

    /* Clear interrupt */
    gintsts.b.disconnect = 1;
    USB_OTG_WRITE_REG32(&pdev->regs.GREGS->GINTSTS, gintsts.d32);

    return 1;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_nptxfempty_ISR
 **         Handles non periodic tx fifo empty.
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
static uint32_t USB_OTG_USBH_handle_nptxfempty_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GINTMSK_TypeDef      intmsk;
    USB_OTG_HNPTXSTS_TypeDef     hnptxsts;
    uint16_t                     len_words , len;

    hnptxsts.d32 = USB_OTG_READ_REG32(&pdev->regs.GREGS->GNPTXSTS);

    len_words = (pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_len + 3) / 4;

    while ((hnptxsts.b.nptxfspcavail > len_words)&& (pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_len != 0))
    {
        len = hnptxsts.b.nptxfspcavail * 4;

        if (len > pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_len)
        {
            /* Last packet */
            len = pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_len;

            intmsk.d32 = 0;
            intmsk.b.nptxfempty = 1;
            USB_OTG_MODIFY_REG32( &pdev->regs.GREGS->GINTMSK, intmsk.d32, 0);
        }

        len_words = (pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_len + 3) / 4;

        USB_OTG_WritePacket (pdev , pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_buff, hnptxsts.b.nptxqtop_chnep, len);

        pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_buff  += len;
        pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_len   -= len;
        pdev->host.hc[hnptxsts.b.nptxqtop_chnep].xfer_count  += len;

        hnptxsts.d32 = USB_OTG_READ_REG32(&pdev->regs.GREGS->GNPTXSTS);
    }

    return 1;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_ptxfempty_ISR
 **         Handles periodic tx fifo empty
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
static uint32_t USB_OTG_USBH_handle_ptxfempty_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GINTMSK_TypeDef      intmsk;
    USB_OTG_HPTXSTS_TypeDef      hptxsts;
    uint16_t                     len_words , len;

    hptxsts.d32 = USB_OTG_READ_REG32(&pdev->regs.HREGS->HPTXSTS);

    len_words = (pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_len + 3) / 4;

    while ((hptxsts.b.ptxfspcavail > len_words)&&(pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_len != 0))
    {
        len = hptxsts.b.ptxfspcavail * 4;

        if (len > pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_len)
        {
            len = pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_len;
            /* Last packet */
            intmsk.d32 = 0;
            intmsk.b.ptxfempty = 1;
            USB_OTG_MODIFY_REG32( &pdev->regs.GREGS->GINTMSK, intmsk.d32, 0);
        }

        len_words = (pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_len + 3) / 4;
        USB_OTG_WritePacket (pdev , pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_buff, hptxsts.b.ptxqtop.chnum, len);

        pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_buff  += len;
        pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_len   -= len;
        pdev->host.hc[hptxsts.b.ptxqtop.chnum].xfer_count  += len;

        hptxsts.d32 = USB_OTG_READ_REG32(&pdev->regs.HREGS->HPTXSTS);
    }
    return 1;
}

/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_port_ISR
 **         This function determines which interrupt conditions have occurred
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
static uint32_t USB_OTG_USBH_handle_port_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_HPRT0_TypeDef  hprt0;
    USB_OTG_HPRT0_TypeDef  hprt0_dup;
    USB_OTG_HCFG_TypeDef   hcfg;
    uint32_t do_reset = 0;
    uint32_t retval = 0;

    hcfg.d32 = 0;
    hprt0.d32 = 0;
    hprt0_dup.d32 = 0;

    hprt0.d32 = USB_OTG_READ_REG32(pdev->regs.HPRT0);
    hprt0_dup.d32 = USB_OTG_READ_REG32(pdev->regs.HPRT0);

    /* Clear the interrupt bits in GINTSTS */
    hprt0_dup.b.prtena = 0;
    hprt0_dup.b.prtconndet = 0;
    hprt0_dup.b.prtenchng = 0;
    hprt0_dup.b.prtovrcurrchng = 0;

    /* Port Connect Detected */
    if (hprt0.b.prtconndet)
    {
        hprt0_dup.b.prtconndet = 1;
        USBH_HCD_INT_fops->DevConnected(pdev);
        retval |= 1;
    }

    /* Port Enable Changed */
    if (hprt0.b.prtenchng)
    {
        hprt0_dup.b.prtenchng = 1;

        if (hprt0.b.prtena == 1)
        {
            USBH_HCD_INT_fops->DevConnected(pdev);

            if ((hprt0.b.prtspd == HPRT0_PRTSPD_LOW_SPEED) ||
            (hprt0.b.prtspd == HPRT0_PRTSPD_FULL_SPEED))
            {
                hcfg.d32 = USB_OTG_READ_REG32(&pdev->regs.HREGS->HCFG);

                if (hprt0.b.prtspd == HPRT0_PRTSPD_LOW_SPEED)
                {
                    //USB_OTG_WRITE_REG32(&pdev->regs.HREGS->HFIR, 6000 );
                    if (hcfg.b.fslspclksel != HCFG_6_MHZ)
                    {
                        if(pdev->cfg.phy_itface  == USB_OTG_EMBEDDED_PHY)
                        {
                            //USB_OTG_InitFSLSPClkSel(pdev ,HCFG_6_MHZ );
                        }
                        do_reset = 1;
                    }
                }
                else
                {
                    USB_OTG_WRITE_REG32(&pdev->regs.HREGS->HFIR, 48000 );
                    if (hcfg.b.fslspclksel != HCFG_48_MHZ)
                    {
                        USB_OTG_InitFSLSPClkSel(pdev ,HCFG_48_MHZ );
                        do_reset = 1;
                    }
                }
            }
            else
            {
                do_reset = 1;
            }
        }
    }
    /* Overcurrent Change Interrupt */
    if (hprt0.b.prtovrcurrchng)
    {
        hprt0_dup.b.prtovrcurrchng = 1;
        retval |= 1;
    }
    if (do_reset)
    {
        //USB_OTG_ResetPort(pdev);
    }
    /* Clear Port Interrupts */
    USB_OTG_WRITE_REG32(pdev->regs.HPRT0, hprt0_dup.d32);

    return retval;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_hc_n_Out_ISR
 **         Handles interrupt for a specific Host Channel
 ** \param  pdev: Selected device
 ** \param  hc_num: Channel number
 ** \retval status
 ******************************************************************************/
uint32_t USB_OTG_USBH_handle_hc_n_Out_ISR (USB_OTG_CORE_HANDLE *pdev , uint32_t num)
{
    USB_OTG_HCINTn_TypeDef     hcint;
    USB_OTG_HCINTMSK_TypeDef  hcintmsk;
    USB_OTG_HC_REGS *hcreg;
    USB_OTG_HCCHAR_TypeDef     hcchar;

    hcreg = pdev->regs.HC_REGS[num];
    hcint.d32 = USB_OTG_READ_REG32(&hcreg->HCINT);
    hcintmsk.d32 = USB_OTG_READ_REG32(&hcreg->HCINTMSK);
    hcint.d32 = hcint.d32 & hcintmsk.d32;

    hcchar.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[num]->HCCHAR);

    if (hcint.b.ahberr)
    {
        CLEAR_HC_INT(hcreg ,ahberr);
        UNMASK_HOST_INT_CHH (num);
    }
    else if (hcint.b.ack)
    {
        CLEAR_HC_INT(hcreg , ack);
    }
    else if (hcint.b.frmovrun)
    {
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg ,frmovrun);
    }
    else if (hcint.b.xfercompl)
    {
        pdev->host.ErrCnt[num] = 0;
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg , xfercompl);
        pdev->host.HC_Status[num] = HC_XFRC;
    }

    else if (hcint.b.stall)
    {
        CLEAR_HC_INT(hcreg , stall);
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        pdev->host.HC_Status[num] = HC_STALL;
    }

    else if (hcint.b.nak)
    {
        pdev->host.ErrCnt[num] = 0;
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg , nak);
        pdev->host.HC_Status[num] = HC_NAK;
    }

    else if (hcint.b.xacterr)
    {
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        pdev->host.ErrCnt[num] ++;
        pdev->host.HC_Status[num] = HC_XACTERR;
        CLEAR_HC_INT(hcreg , xacterr);
    }
    else if (hcint.b.nyet)
    {
        pdev->host.ErrCnt[num] = 0;
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg , nyet);
        pdev->host.HC_Status[num] = HC_NYET;
    }
    else if (hcint.b.datatglerr)
    {
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg , nak);
        pdev->host.HC_Status[num] = HC_DATATGLERR;

        CLEAR_HC_INT(hcreg , datatglerr);
    }
    else if (hcint.b.chhltd)
    {
        MASK_HOST_INT_CHH (num);

        if(pdev->host.HC_Status[num] == HC_XFRC)
        {
            pdev->host.URB_State[num] = URB_DONE;

            if (hcchar.b.eptype == EP_TYPE_BULK)
            {
                pdev->host.hc[num].toggle_out ^= 1;
            }
        }
        else if(pdev->host.HC_Status[num] == HC_NAK)
        {
            pdev->host.URB_State[num] = URB_NOTREADY;
        }
        else if(pdev->host.HC_Status[num] == HC_NYET)
        {
            if(pdev->host.hc[num].do_ping == 1)
            {
            USB_OTG_HC_DoPing(pdev, num);
            }
            pdev->host.URB_State[num] = URB_NOTREADY;
        }
        else if(pdev->host.HC_Status[num] == HC_STALL)
        {
            pdev->host.URB_State[num] = URB_STALL;
        }
        else if(pdev->host.HC_Status[num] == HC_XACTERR)
        {
            if (pdev->host.ErrCnt[num] == 3)
            {
            pdev->host.URB_State[num] = URB_ERROR;
            pdev->host.ErrCnt[num] = 0;
            }
        }
        CLEAR_HC_INT(hcreg , chhltd);
    }
    return 1;
}
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_hc_n_In_ISR
 **         Handles interrupt for a specific Host Channel
 ** \param  pdev: Selected device
 ** \param  hc_num: Channel number
 ** \retval status
 ******************************************************************************/
uint32_t USB_OTG_USBH_handle_hc_n_In_ISR (USB_OTG_CORE_HANDLE *pdev , uint32_t num)
{
    USB_OTG_HCINTn_TypeDef     hcint;
    USB_OTG_HCINTMSK_TypeDef  hcintmsk;
    USB_OTG_HCCHAR_TypeDef     hcchar;
    USB_OTG_HCTSIZn_TypeDef  hctsiz;
    USB_OTG_HC_REGS *hcreg;

    hcreg = pdev->regs.HC_REGS[num];
    hcint.d32 = USB_OTG_READ_REG32(&hcreg->HCINT);
    hcintmsk.d32 = USB_OTG_READ_REG32(&hcreg->HCINTMSK);
    hcint.d32 = hcint.d32 & hcintmsk.d32;
    hcchar.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[num]->HCCHAR);
    hcintmsk.d32 = 0;

    if (hcint.b.ahberr)
    {
        CLEAR_HC_INT(hcreg ,ahberr);
        UNMASK_HOST_INT_CHH (num);
    }
    else if (hcint.b.ack)
    {
        CLEAR_HC_INT(hcreg ,ack);
    }
    else if (hcint.b.stall)
    {
        UNMASK_HOST_INT_CHH (num);
        pdev->host.HC_Status[num] = HC_STALL;
        CLEAR_HC_INT(hcreg , nak);   /* Clear the NAK Condition */
        CLEAR_HC_INT(hcreg , stall); /* Clear the STALL Condition */
        hcint.b.nak = 0;           /* NOTE: When there is a 'stall', reset also nak,
                      else, the pdev->host.HC_Status = HC_STALL will be overwritten by 'nak' in code below */
        USB_OTG_HC_Halt(pdev, num);
    }
    else if (hcint.b.datatglerr)
    {
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg , nak);
        pdev->host.HC_Status[num] = HC_DATATGLERR;
        CLEAR_HC_INT(hcreg , datatglerr);
    }

    if (hcint.b.frmovrun)
    {
        UNMASK_HOST_INT_CHH (num);
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg ,frmovrun);
    }
    else if (hcint.b.xfercompl)
    {
        if (pdev->cfg.dma_enable == 1)
        {
            hctsiz.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[num]->HCTSIZ);
            pdev->host.XferCnt[num] =  pdev->host.hc[num].xfer_len - hctsiz.b.xfersize;
        }

        pdev->host.HC_Status[num] = HC_XFRC;
        pdev->host.ErrCnt [num]= 0;
        CLEAR_HC_INT(hcreg , xfercompl);

        if ((hcchar.b.eptype == EP_TYPE_CTRL)||(hcchar.b.eptype == EP_TYPE_BULK))
        {
            UNMASK_HOST_INT_CHH (num);
            USB_OTG_HC_Halt(pdev, num);
            CLEAR_HC_INT(hcreg , nak);
            pdev->host.hc[num].toggle_in ^= 1;
        }
        else if(hcchar.b.eptype == EP_TYPE_INTR)
        {
            hcchar.b.oddfrm  = 1;
            USB_OTG_WRITE_REG32(&pdev->regs.HC_REGS[num]->HCCHAR, hcchar.d32);
            pdev->host.URB_State[num] = URB_DONE;
        }
        else if(hcchar.b.eptype == EP_TYPE_ISOC)
        {
            if(pdev->host.HC_Status[num] == HC_XFRC)
            {
                pdev->host.URB_State[num] = URB_DONE;
            }
        }
    }
    else if (hcint.b.chhltd)
    {
        MASK_HOST_INT_CHH (num);

        if(pdev->host.HC_Status[num] == HC_XFRC)
        {
            pdev->host.URB_State[num] = URB_DONE;
        }

        else if (pdev->host.HC_Status[num] == HC_STALL)
        {
            pdev->host.URB_State[num] = URB_STALL;
        }

        else if((pdev->host.HC_Status[num] == HC_XACTERR) ||
            (pdev->host.HC_Status[num] == HC_DATATGLERR))
        {
            pdev->host.ErrCnt[num] = 0;
            pdev->host.URB_State[num] = URB_ERROR;
        }
        else if(hcchar.b.eptype == EP_TYPE_INTR)
        {
            pdev->host.hc[num].toggle_in ^= 1;
        }
        CLEAR_HC_INT(hcreg , chhltd);
    }
    else if (hcint.b.xacterr)
    {
        UNMASK_HOST_INT_CHH (num);
        pdev->host.ErrCnt[num] ++;
        pdev->host.HC_Status[num] = HC_XACTERR;
        USB_OTG_HC_Halt(pdev, num);
        CLEAR_HC_INT(hcreg , xacterr);
    }
    else if (hcint.b.nak)
    {
        if(hcchar.b.eptype == EP_TYPE_INTR)
        {
            UNMASK_HOST_INT_CHH (num);
            USB_OTG_HC_Halt(pdev, num);
        }
        else if  ((hcchar.b.eptype == EP_TYPE_CTRL)||(hcchar.b.eptype == EP_TYPE_BULK))
        {
            /* re-activate the channel  */
            hcchar.b.chen = 1;
            hcchar.b.chdis = 0;
            USB_OTG_WRITE_REG32(&pdev->regs.HC_REGS[num]->HCCHAR, hcchar.d32);
        }
        pdev->host.HC_Status[num] = HC_NAK;
        CLEAR_HC_INT(hcreg , nak);
    }
    return 1;
}

/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_rx_qlvl_ISR
 **         Handles the Rx Status Queue Level Interrupt
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
static uint32_t USB_OTG_USBH_handle_rx_qlvl_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GRXFSTS_TypeDef       grxsts;
    USB_OTG_GINTMSK_TypeDef       intmsk;
    USB_OTG_HCTSIZn_TypeDef       hctsiz;
    USB_OTG_HCCHAR_TypeDef        hcchar;
    __IO uint8_t                  channelnum =0;
    uint32_t                      count;

    /* Disable the Rx Status Queue Level interrupt */
    intmsk.d32 = 0;
    intmsk.b.rxstsqlvl = 1;
    USB_OTG_MODIFY_REG32( &pdev->regs.GREGS->GINTMSK, intmsk.d32, 0);

    grxsts.d32 = USB_OTG_READ_REG32(&pdev->regs.GREGS->GRXSTSP);
    channelnum = grxsts.b.chnum;
    hcchar.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[channelnum]->HCCHAR);

    switch (grxsts.b.pktsts)
    {
        case GRXSTS_PKTSTS_IN:
            /* Read the data into the host buffer. */
            if ((grxsts.b.bcnt > 0) && (pdev->host.hc[channelnum].xfer_buff != (void  *)0))
            {
                USB_OTG_ReadPacket(pdev, pdev->host.hc[channelnum].xfer_buff, grxsts.b.bcnt);
                /*manage multiple Xfer */
                pdev->host.hc[grxsts.b.chnum].xfer_buff += grxsts.b.bcnt;
                pdev->host.hc[grxsts.b.chnum].xfer_count  += grxsts.b.bcnt;

                count = pdev->host.hc[channelnum].xfer_count;
                pdev->host.XferCnt[channelnum]  = count;

                hctsiz.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[channelnum]->HCTSIZ);
                if(hctsiz.b.pktcnt > 0)
                {
                    /* re-activate the channel when more packets are expected */
                    hcchar.b.chen = 1;
                    hcchar.b.chdis = 0;
                    USB_OTG_WRITE_REG32(&pdev->regs.HC_REGS[channelnum]->HCCHAR, hcchar.d32);
                }
            }
            break;

        case GRXSTS_PKTSTS_IN_XFER_COMP:
        case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
        case GRXSTS_PKTSTS_CH_HALTED:
            default:
        break;
    }

    /* Enable the Rx Status Queue Level interrupt */
    intmsk.b.rxstsqlvl = 1;
    USB_OTG_MODIFY_REG32(&pdev->regs.GREGS->GINTMSK, 0, intmsk.d32);
    return 1;
}

/**
 *******************************************************************************
 ** \brief  USB_OTG_USBH_handle_IncompletePeriodicXfer_ISR
 **         Handles the incomplete Periodic transfer Interrupt
 ** \param  pdev: Selected device
 ** \retval status
 ******************************************************************************/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma optimize = none
#endif /* __CC_ARM */
static uint32_t USB_OTG_USBH_handle_IncompletePeriodicXfer_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_GINTSTS_TypeDef       gintsts;
    USB_OTG_HCCHAR_TypeDef        hcchar;

    hcchar.d32 = USB_OTG_READ_REG32(&pdev->regs.HC_REGS[0]->HCCHAR);
    hcchar.b.chen = 1;
    hcchar.b.chdis = 1;
    USB_OTG_WRITE_REG32(&pdev->regs.HC_REGS[0]->HCCHAR, hcchar.d32);

    gintsts.d32 = 0;
    /* Clear interrupt */
    gintsts.b.incomplisoout = 1;
    USB_OTG_WRITE_REG32(&pdev->regs.GREGS->GINTSTS, gintsts.d32);

    return 1;
}
static uint32_t USB_OTG_USBH_handle_RemoteWakeUp_ISR (USB_OTG_CORE_HANDLE *pdev)
{
    USB_OTG_HPRT0_TypeDef     port0;

    port0.d32 = USB_OTG_ReadHPRT0(pdev);
    port0.b.prtres = 0;
    USB_OTG_WRITE_REG32(pdev->regs.HPRT0, port0.d32);
    return 1;
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


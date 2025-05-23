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
/** \file usb_dcd.c
 **
 ** A detailed description is available at
 ** @link
		Peripheral Device Interface Layer
	@endlink
 **
 **   - 2019-06-28  1.0   First version for USB demo.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dcd.h"
#include "usb_bsp.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Device intialize
 ** \param pdev : Device instance
 ** \param coreID : Core ID
 ** \retval : None
 ******************************************************************************/
void DCD_Init(USB_OTG_CORE_HANDLE *pdev ,
              USB_OTG_CORE_ID_TypeDef coreID)
{
    uint32_t i;
    USB_OTG_EP *ep;

    USB_OTG_SelectCore (pdev , coreID);  //初始化寄存器地址,端点数等也在该函数初始化

    pdev->dev.device_status = USB_OTG_DEFAULT; //设备初始状态
    pdev->dev.device_address = 0;              //设备地址为0

    /* Init ep structure */
    for (i = 0; i < pdev->cfg.dev_endpoints ; i++)
    {
        ep = &pdev->dev.in_ep[i];         //获取输入端点结构体的地址
        /* Init ep structure */
        ep->is_in = 1;                    //数据为从设备到主机
        ep->num = i;                      //输入端点序号
        ep->tx_fifo_num = i;              //发送FIFO序号
        /* Control until ep is actvated */
        ep->type = EP_TYPE_CTRL;                 //初始的类型为控制节点
        ep->maxpacket =  USB_OTG_MAX_EP0_SIZE;   //初始最大数据包
        ep->xfer_buff = 0;                       //发送缓存空
        ep->xfer_len = 0;                        //发送数据空
    }

    for (i = 0; i < pdev->cfg.dev_endpoints; i++)
    {
        ep = &pdev->dev.out_ep[i];
        /* Init ep structure */
        ep->is_in = 0;                    //数据为从主机到设备
        ep->num = i;
        ep->tx_fifo_num = i;
        /* Control until ep is activated */
        ep->type = EP_TYPE_CTRL;
        ep->maxpacket = USB_OTG_MAX_EP0_SIZE;
        ep->xfer_buff = 0;
        ep->xfer_len = 0;
    }

    USB_OTG_DisableGlobalInt(pdev);              //使能全局中断GlblIntrMsk->操作位置：usb_core.c

    /*Init the Core (common init.) */
    USB_OTG_CoreInit(pdev);                      //内核初始化，内核软复位和相关寄存器的配置

    /* Force Device Mode*/
#ifndef USE_OTG_MODE
    USB_OTG_SetCurrentMode(pdev, DEVICE_MODE);   //强制工作在设备模式
#endif

    /* Init Device */
    USB_OTG_CoreInitDev(pdev);                   //设备初始化：内部含中断的设置

    /* Enable USB Global interrupt */
    USB_OTG_EnableGlobalInt(pdev);               //使能全局中断GlblIntrMsk->操作位置：usb_core.c
}

/**
 *******************************************************************************
 ** \brief  Configure an EP
 ** \param pdev : Device instance
 ** \param epdesc : Endpoint Descriptor
 ** \retval : status
 ******************************************************************************/
uint32_t DCD_EP_Open(USB_OTG_CORE_HANDLE *pdev ,
                     uint8_t ep_addr,
                     uint16_t ep_mps,
                     uint8_t ep_type)
{
    USB_OTG_EP *ep;

    if ((ep_addr & 0x80) == 0x80)
    {
        ep = &pdev->dev.in_ep[ep_addr & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[ep_addr & 0x7F];
    }
    ep->num   = ep_addr & 0x7F;

    ep->is_in = (0x80 & ep_addr) != 0;
    ep->maxpacket = ep_mps;
    ep->type = ep_type;
    if (ep->is_in)
    {
        /* Assign a Tx FIFO */
        ep->tx_fifo_num = ep->num;
//										if(ep->tx_fifo_num != 0)
//					ep->tx_fifo_num = 1;
    }
    /* Set initial data PID. */
    if (ep_type == USB_OTG_EP_BULK )
    {
        ep->data_pid_start = 0;
				ep->tx_fifo_num = 0;
    }
    USB_OTG_EPActivate(pdev , ep );
    return 0;
}

/**
 *******************************************************************************
* \brief  called when an EP is disabled
 ** \param pdev: device instance
 ** \param ep_addr: endpoint address
 ** \retval : status
 ******************************************************************************/
uint32_t DCD_EP_Close(USB_OTG_CORE_HANDLE *pdev , uint8_t  ep_addr)
{
    USB_OTG_EP *ep;

    if ((ep_addr&0x80) == 0x80)
    {
        ep = &pdev->dev.in_ep[ep_addr & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[ep_addr & 0x7F];
    }
    ep->num   = ep_addr & 0x7F;
    ep->is_in = (0x80 & ep_addr) != 0;
    USB_OTG_EPDeactivate(pdev , ep );
    return 0;
}

/**
 *******************************************************************************
 ** \brief  DCD_EP_PrepareRx
 ** \param pdev: device instance
 ** \param ep_addr: endpoint address
 ** \param pbuf: pointer to Rx buffer
 ** \param buf_len: data length
 ** \retval : status
 ******************************************************************************/
uint32_t   DCD_EP_PrepareRx( USB_OTG_CORE_HANDLE *pdev,
                            uint8_t   ep_addr,
                            uint8_t *pbuf,
                            uint16_t  buf_len)
{
    USB_OTG_EP *ep;

    ep = &pdev->dev.out_ep[ep_addr & 0x7F];

    /*setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;
    ep->xfer_count = 0;
    ep->is_in = 0;
    ep->num = ep_addr & 0x7F;

    if (pdev->cfg.dma_enable == 1)
    {
        ep->dma_addr = (uint32_t)pbuf;
    }

    if ( ep->num == 0 )
    {
        USB_OTG_EP0StartXfer(pdev , ep);
    }
    else
    {
        USB_OTG_EPStartXfer(pdev, ep );
    }
    return 0;
}

/**
 *******************************************************************************
 ** \brief  Transmit data over USB
 ** \param pdev: device instance
 ** \param ep_addr: endpoint address
 ** \param pbuf: pointer to Tx buffer
 ** \param buf_len: data length
 ** \retval : status
 ******************************************************************************/
uint32_t  DCD_EP_Tx ( USB_OTG_CORE_HANDLE *pdev,
                     uint8_t   ep_addr,
                     uint8_t   *pbuf,
                     uint32_t   buf_len)
{
    USB_OTG_EP *ep;

    ep = &pdev->dev.in_ep[ep_addr & 0x7F];

    /* Setup and start the Transfer */
    ep->is_in = 1;
    ep->num = ep_addr & 0x7F;
    ep->xfer_buff = pbuf;
    ep->dma_addr = (uint32_t)pbuf;
    ep->xfer_count = 0;
    ep->xfer_len  = buf_len;

    if ( ep->num == 0 )
    {
        USB_OTG_EP0StartXfer(pdev , ep);
    }
    else
    {
        USB_OTG_EPStartXfer(pdev, ep );
    }
    return 0;
}

/**
 *******************************************************************************
 ** \brief  Stall an endpoint.
 ** \param pdev: device instance
 ** \param epnum: endpoint address
 ** \retval : status
 ******************************************************************************/
uint32_t  DCD_EP_Stall (USB_OTG_CORE_HANDLE *pdev, uint8_t   epnum)
{
    USB_OTG_EP *ep;
    if ((0x80 & epnum) == 0x80)
    {
        ep = &pdev->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[epnum];
    }

    ep->is_stall = 1;
    ep->num   = epnum & 0x7F;
    ep->is_in = ((epnum & 0x80) == 0x80);

    USB_OTG_EPSetStall(pdev , ep);
    return (0);
}

/**
 *******************************************************************************
 ** \brief  Clear stall condition on endpoints.
 ** \param pdev: device instance
 ** \param epnum: endpoint address
 ** \retval : status
 ******************************************************************************/
uint32_t  DCD_EP_ClrStall (USB_OTG_CORE_HANDLE *pdev, uint8_t epnum)
{
    USB_OTG_EP *ep;
    if ((0x80 & epnum) == 0x80)
    {
        ep = &pdev->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[epnum];
    }

    ep->is_stall = 0;
    ep->num   = epnum & 0x7F;
    ep->is_in = ((epnum & 0x80) == 0x80);

    USB_OTG_EPClearStall(pdev , ep);
    return (0);
}

/**
 *******************************************************************************
 ** \brief  This Function flushes the FIFOs.
 ** \param pdev: device instance
 ** \param epnum: endpoint address
 ** \retval : status
 ******************************************************************************/
uint32_t  DCD_EP_Flush (USB_OTG_CORE_HANDLE *pdev , uint8_t epnum)
{
    if ((epnum & 0x80) == 0x80)
    {
        USB_OTG_FlushTxFifo(pdev, epnum & 0x7F);
    }
    else
    {
        USB_OTG_FlushRxFifo(pdev);
    }
    return (0);
}

/**
 *******************************************************************************
 ** \brief  This Function set USB device address
 ** \param pdev: device instance
 ** \param address: new device address
 ** \retval : status
 ******************************************************************************/
void  DCD_EP_SetAddress (USB_OTG_CORE_HANDLE *pdev, uint8_t address)
{
    USB_OTG_DCFG_TypeDef  dcfg;
    dcfg.d32 = 0;
    dcfg.b.devaddr = address;
    USB_OTG_MODIFY_REG32( &pdev->regs.DREGS->DCFG, 0, dcfg.d32);
}

/**
 *******************************************************************************
 ** \brief  Connect device (enable internal pull-up)
 ** \param pdev: device instance
 ** \retval : None
 ******************************************************************************/
void  DCD_DevConnect (USB_OTG_CORE_HANDLE *pdev)
{
#ifndef USE_OTG_MODE
    USB_OTG_DCTL_TypeDef  dctl;
    dctl.d32 = USB_OTG_READ_REG32(&pdev->regs.DREGS->DCTL);
    /* Connect device */
    dctl.b.sftdiscon  = 0;
    USB_OTG_WRITE_REG32(&pdev->regs.DREGS->DCTL, dctl.d32);
    USB_OTG_BSP_mDelay(3);
#endif
}

/**
 *******************************************************************************
 ** \brief  Disconnect device (disable internal pull-up)
 ** \param pdev: device instance
 ** \retval : None
 ******************************************************************************/
void  DCD_DevDisconnect (USB_OTG_CORE_HANDLE *pdev)
{
#ifndef USE_OTG_MODE
    USB_OTG_DCTL_TypeDef  dctl;
    dctl.d32 = USB_OTG_READ_REG32(&pdev->regs.DREGS->DCTL);
    /* Disconnect device for 3ms */
    dctl.b.sftdiscon  = 1;
    USB_OTG_WRITE_REG32(&pdev->regs.DREGS->DCTL, dctl.d32);
    USB_OTG_BSP_mDelay(3);
#endif
}

/**
 *******************************************************************************
 ** \brief  returns the EP Status
 ** \param  pdev : Selected device
 **         epnum : endpoint address
 ** \retval : EP status
 ******************************************************************************/
uint32_t DCD_GetEPStatus(USB_OTG_CORE_HANDLE *pdev ,uint8_t epnum)
{
    USB_OTG_EP *ep;
    uint32_t Status = 0;

    if ((0x80 & epnum) == 0x80)
    {
        ep = &pdev->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[epnum];
    }

    Status = USB_OTG_GetEPStatus(pdev ,ep);
    /* Return the current status */
    return Status;
}

/**
 *******************************************************************************
 ** \brief  Set the EP Status
 ** \param  pdev : Selected device
 **         Status : new Status
 **         epnum : EP address
 ** \retval : None
 ******************************************************************************/
void DCD_SetEPStatus (USB_OTG_CORE_HANDLE *pdev , uint8_t epnum , uint32_t Status)
{
    USB_OTG_EP *ep;

    if ((0x80 & epnum) == 0x80)
    {
        ep = &pdev->dev.in_ep[epnum & 0x7F];
    }
    else
    {
        ep = &pdev->dev.out_ep[epnum];
    }

    USB_OTG_SetEPStatus(pdev ,ep , Status);
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

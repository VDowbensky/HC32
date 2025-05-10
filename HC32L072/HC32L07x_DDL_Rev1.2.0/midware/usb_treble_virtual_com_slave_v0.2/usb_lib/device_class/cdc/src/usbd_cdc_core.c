/******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file usbd_cdc_core.c
 **
 ** A detailed description is available at
 ** @link 
		This file provides the USBD descriptors and string formating method.  
	@endlink
 **
 **   - 2019-07-03  lsq  First version for USB demo.
 **
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"


#define USB_CDC_IDLE         0
#define USB_CDC_BUSY         1
#define USB_CDC_ZLP          2


/*********************************************
   CDC Device library callbacks
 *********************************************/
uint8_t  usbd_cdc_Init         (void  *pdev, uint8_t cfgidx);
uint8_t  usbd_cdc_DeInit       (void  *pdev, uint8_t cfgidx);
uint8_t  usbd_cdc_Setup        (void  *pdev, USB_SETUP_REQ *req);
uint8_t  usbd_cdc_EP0_RxReady  (void *pdev);
uint8_t  usbd_cdc_DataIn       (void *pdev, uint8_t epnum);
uint8_t  usbd_cdc_DataOut      (void *pdev, uint8_t epnum);
uint8_t  usbd_cdc_SOF          (void *pdev);

/*********************************************
   CDC specific management functions
 *********************************************/
static void Handle_USBAsynchXfer  (void *pdev);
static uint8_t  *USBD_cdc_GetCfgDesc (uint8_t speed, uint16_t *length);


extern uint8_t USBD_DeviceDesc   [USB_SIZ_DEVICE_DESC];

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN uint8_t usbd_cdc_CfgDesc  [USB_CDC_CONFIG_DESC_SIZ] __USB_ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN uint8_t usbd_cdc_OtherCfgDesc  [USB_CDC_CONFIG_DESC_SIZ] __USB_ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN static __IO uint32_t  usbd_cdc_AltSet  __USB_ALIGN_END = 0;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN uint8_t USB_Rx_Buffer   [CDC_DATA_MAX_PACKET_SIZE] __USB_ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN uint8_t APP_Rx_Buffer   [APP_RX_DATA_SIZE] __USB_ALIGN_END ; 


#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__USB_ALIGN_BEGIN uint8_t CmdBuff[CDC_CMD_PACKET_SZE] __USB_ALIGN_END ;

uint32_t APP_Rx_ptr_in  = 0;
uint32_t APP_Rx_ptr_out = 0;
uint32_t APP_Rx_length  = 0;

uint8_t  USB_Tx_State = USB_CDC_IDLE;

static uint32_t cdcCmd[NUM_OF_CDC_UARTS] = {0xFF, 0xFF, 0xFF};
static uint32_t cdcLen[NUM_OF_CDC_UARTS]= {0, 0, 0};
/* CDC interface class callbacks structure */
USBD_Class_cb_TypeDef  USBD_CDC_cb = 
{
  usbd_cdc_Init,
  usbd_cdc_DeInit,
  usbd_cdc_Setup,
  NULL,                 /* EP0_TxSent, */
  usbd_cdc_EP0_RxReady,
  usbd_cdc_DataIn,
  usbd_cdc_DataOut,
  usbd_cdc_SOF,
  NULL,
  NULL,     
  USBD_cdc_GetCfgDesc,
};

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
/* USB CDC device Configuration Descriptor */
__USB_ALIGN_BEGIN uint8_t usbd_cdc_CfgDesc[USB_CDC_CONFIG_DESC_SIZ]  __USB_ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */
  USB_CDC_CONFIG_DESC_SIZ,                /* wTotalLength:no of returned bytes */
  0x00,
  0x06,   /* bNumInterfaces: 6 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */
  
  /*---------------------------------------------------------------------------*/
  // IAD  Interface Association Descriptor
  0x08,	// bLength: Interface Descriptor size
  0x0B,		// bDescriptorType: IAD
  0x00,	// bFirstInterface
  0x02,	// bInterfaceCount
  0x02,	// bFunctionClass: CDC
  0x02,	// bFunctionSubClass
  0x01,	// bFunctionProtocol 
  0x02,	// iFunction
  
  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */
  
  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,
  
  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */
  
  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */
  
  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  0x00,   /* bMasterInterface: Communication class interface */
  0x01,   /* bSlaveInterface0: Data Class Interface */
  
  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SZE),
#ifdef USE_USB_OTG_HS
  0x10,                           /* bInterval: */
#else
  0xFF,                           /* bInterval: */
#endif /* USE_USB_OTG_HS */
  
  /*---------------------------------------------------------------------------*/
  
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
  CDC_IN_EP,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
  0x00,   
  
  /*---------------------------------------------------------------------------*/  
  // IAD  Interface Association Descriptor
  0x08,	// bLength: Interface Descriptor size
  0x0B,		// bDescriptorType: IAD
  0x02,	// bFirstInterface
  0x02,	// bInterfaceCount
  0x02,	// bFunctionClass: CDC
  0x02,	// bFunctionSubClass
  0x01,	// bFunctionProtocol 
  0x02,	// iFunction

/*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x02,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */
  
  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,
  
  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */
  
  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */
  
  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  0x00,   /* bMasterInterface: Communication class interface */
  0x01,   /* bSlaveInterface0: Data Class Interface */
  
  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP1,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SZE),
  0xFF,                           /* bInterval: */ 
  /*---------------------------------------------------------------------------*/
  
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x03,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP1,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_IN_EP1,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
  0x00,                               /* bInterval: ignore for Bulk transfer */   
  
  /*---------------------------------------------------------------------------*/  
  // IAD  Interface Association Descriptor
  0x08,	// bLength: Interface Descriptor size
  0x0B,		// bDescriptorType: IAD
  0x04,	// bFirstInterface
  0x02,	// bInterfaceCount
  0x02,	// bFunctionClass: CDC
  0x02,	// bFunctionSubClass
  0x01,	// bFunctionProtocol 
  0x02,	// iFunction

/*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x04,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */
  
  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,
  
  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */
  
  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */
  
  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  0x00,   /* bMasterInterface: Communication class interface */
  0x01,   /* bSlaveInterface0: Data Class Interface */
  
  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  CDC_CMD_EP2,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SZE),     /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SZE),
  0xFF,                           /* bInterval: */ 
  /*---------------------------------------------------------------------------*/
  
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x05,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_OUT_EP2,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  CDC_IN_EP2,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(CDC_DATA_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
  0x00                               /* bInterval: ignore for Bulk transfer */   
} ;


/*默认的串口通信参数*/
USBD_CDC_LineCodingTypeDef defaultLineCoding =
{
    115200, /* baud rate */
    0x00,   /* stop bits-1 */
    0x00,   /* parity - none */
    0x08    /* nb. of bits 8 */
};

static const struct
{
    uint8_t Instance;
    uint8_t data_in_ep;
    uint8_t data_out_ep;
    uint8_t command_ep;
    uint8_t command_itf;
} cdc_parameters[NUM_OF_CDC_UARTS] = 
{
#if (NUM_OF_CDC_UARTS > 0)
  {
    1,
    CDC_IN_EP,
    CDC_OUT_EP,
    CDC_CMD_EP,
    0x00,
  },
#endif
#if (NUM_OF_CDC_UARTS > 1)
  {
    2,
    CDC_IN_EP1,
    CDC_OUT_EP1,
    CDC_CMD_EP1,
    0x02,
  },
#endif
 #if (NUM_OF_CDC_UARTS > 2)
   {
     3,
     CDC_IN_EP2,
     CDC_OUT_EP2,
     CDC_CMD_EP2,
     0x04,
   },
#endif
};

USBD_CDC_LineCodingTypeDef  LineCode[NUM_OF_CDC_UARTS];
/**
  * @brief  usbd_cdc_Init
  *         Initialize the CDC interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
uint8_t  usbd_cdc_Init (void  *pdev, 
                               uint8_t cfgidx)
{
    uint8_t tmp;
    for(tmp = 0; tmp < NUM_OF_CDC_UARTS; tmp++)
    {
        /* Open EP IN */
        DCD_EP_Open(pdev,
                  cdc_parameters[tmp].data_in_ep,
                  CDC_DATA_IN_PACKET_SIZE,
                  USB_OTG_EP_BULK);

        /* Open EP OUT */
        DCD_EP_Open(pdev,
                  cdc_parameters[tmp].data_out_ep,
                  CDC_DATA_OUT_PACKET_SIZE,
                  USB_OTG_EP_BULK);

        /* Open Command IN EP */
        DCD_EP_Open(pdev,
                  cdc_parameters[tmp].command_ep,
                  CDC_CMD_PACKET_SZE,
                  USB_OTG_EP_INT);   

        LineCode[tmp] = defaultLineCoding;//这是默认的波特率等串口通信参数
        
        /*OUT端点准备接收下一个数据包*/
        DCD_EP_PrepareRx(pdev,
                       cdc_parameters[tmp].data_out_ep,
                       (uint8_t*)USB_Rx_Buffer,
                       CDC_DATA_OUT_PACKET_SIZE);
    }             
    return USBD_OK;
}

/**
  * @brief  usbd_cdc_Init
  *         DeInitialize the CDC layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
uint8_t  usbd_cdc_DeInit (void  *pdev, 
                                 uint8_t cfgidx)
{
    uint8_t tmp;
    for(tmp = 0; tmp < NUM_OF_CDC_UARTS; tmp++)
    {
        /* Open EP IN */
        DCD_EP_Close(pdev,
                  cdc_parameters[tmp].data_in_ep);

        /* Open EP OUT */
        DCD_EP_Close(pdev,
                  cdc_parameters[tmp].data_out_ep);

        /* Open Command IN EP */
        DCD_EP_Close(pdev,
                  cdc_parameters[tmp].command_ep);        
    }
  /* Restore default state of the Interface physical components */
  CDC_DeInit();
  
  return USBD_OK;
}

/**
  * @brief  usbd_cdc_Setup
  *         Handle the CDC specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
uint8_t  usbd_cdc_Setup (void  *pdev, 
                                USB_SETUP_REQ *req)
{
    uint8_t tmp;
    for(tmp = 0; tmp < NUM_OF_CDC_UARTS; tmp++)
    {
        if (cdc_parameters[tmp].command_itf != req->wIndex)
            continue;

        switch (req->bmRequest & USB_REQ_TYPE_MASK)
        {
            case USB_REQ_TYPE_CLASS :
            if (req->wLength)
            {
                if (req->bmRequest & 0x80)
                {
                    CDC_Ctrl(LineCode+tmp, req->bRequest, CmdBuff, req->wLength);
                    /* Send the data to the host */
                    USBD_CtlSendData (pdev ,CmdBuff ,req->wLength);                    
                }
                else
                {
                    /* Set the value of the current command to be processed */
                    cdcCmd[tmp] = req->bRequest;
                    cdcLen[tmp] = req->wLength;
                    /* Prepare the reception of the buffer over EP0
                    Next step: the received data will be managed in usbd_cdc_EP0_TxSent() 
                    function. */
                    USBD_CtlPrepareRx (pdev,
                                       CmdBuff,
                                       req->wLength);                    
                }
            }
            else
            {
                CDC_Ctrl(LineCode+tmp, req->bRequest, NULL, 0);
            }
            break;

            default: 
            break;
        }

        break;        
    }
    return USBD_OK;
}

/**
  * @brief  usbd_cdc_EP0_RxReady
  *         Data received on control endpoint
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  usbd_cdc_EP0_RxReady (void  *pdev)
{ 
    uint8_t tmp;
    for(tmp = 0; tmp < NUM_OF_CDC_UARTS; tmp++)
    {   
        if (cdcCmd[tmp] != NO_CMD)
        {
            CDC_Ctrl(LineCode+tmp,  cdcCmd[tmp], CmdBuff, cdcLen[tmp]);
            cdcCmd[tmp] = 0xFF;
        }        
    }
    return USBD_OK;
}


/**
  * @brief  usbd_audio_DataIn
  *         Data sent on non-control IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  usbd_cdc_DataIn (void *pdev, uint8_t epnum)
{
    uint16_t USB_Tx_ptr;
    uint16_t USB_Tx_length;
    uint8_t tmp;
    for(tmp = 0; tmp < NUM_OF_CDC_UARTS; tmp++)
    {
        if (USB_Tx_State == USB_CDC_BUSY)
        {
            if (APP_Rx_length == 0) 
            {
                USB_Tx_State = USB_CDC_IDLE;
            }
            else 
            {
                if (APP_Rx_length > CDC_DATA_IN_PACKET_SIZE)
                {
                    USB_Tx_ptr = APP_Rx_ptr_out;
                    USB_Tx_length = CDC_DATA_IN_PACKET_SIZE;

                    APP_Rx_ptr_out += CDC_DATA_IN_PACKET_SIZE;
                    APP_Rx_length -= CDC_DATA_IN_PACKET_SIZE;    
                }
                else 
                {
                    USB_Tx_ptr = APP_Rx_ptr_out;
                    USB_Tx_length = APP_Rx_length;

                    APP_Rx_ptr_out += APP_Rx_length;
                    APP_Rx_length = 0;
                    if(USB_Tx_length == CDC_DATA_IN_PACKET_SIZE)
                    {
                        USB_Tx_State = USB_CDC_ZLP;
                    }
                }

                /* Prepare the available data buffer to be sent on IN endpoint */
                DCD_EP_Tx (pdev,
                         cdc_parameters[tmp].data_in_ep,
                         (uint8_t*)&APP_Rx_Buffer[USB_Tx_ptr],
                         USB_Tx_length);
                return USBD_OK;
            }
        }  

        /* Avoid any asynchronous transfer during ZLP */
        if (USB_Tx_State == USB_CDC_ZLP)
        {
            /*Send ZLP to indicate the end of the current transfer */
            DCD_EP_Tx (pdev,
                   cdc_parameters[tmp].data_in_ep,
                   NULL,
                   0);

            USB_Tx_State = USB_CDC_IDLE;
        }
  }
  return USBD_OK;
}
/**
  * @brief  usbd_cdc_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  usbd_cdc_DataOut (void *pdev, uint8_t epnum)
{      
    uint16_t USB_Rx_Cnt;
    uint8_t tmp;
    
    /* Get the received data buffer and update the counter */
    USB_Rx_Cnt = ((USB_OTG_CORE_HANDLE*)pdev)->dev.out_ep[epnum].xfer_count;
    for(tmp = 0; tmp < NUM_OF_CDC_UARTS; tmp++)
    {
        if(cdc_parameters[tmp].data_out_ep == epnum)
        {
            /* USB data will be immediately processed, this allow next USB traffic being 
            NAKed till the end of the application Xfer */
            CDC_DataRx(USB_Rx_Buffer, USB_Rx_Cnt, tmp);
            /* Prepare Out endpoint to receive next packet */
            DCD_EP_PrepareRx(pdev,
                           cdc_parameters[tmp].data_out_ep,
                           (uint8_t*)(USB_Rx_Buffer),
                           CDC_DATA_OUT_PACKET_SIZE);
            break;
        }
    }
    return USBD_OK;
}
/**
  * @brief  usbd_audio_SOF
  *         Start Of Frame event management
  * @param  pdev: instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  usbd_cdc_SOF (void *pdev)
{      
  static uint32_t FrameCount = 0;
  
  if (FrameCount++ == CDC_IN_FRAME_INTERVAL)
  {
    /* Reset the frame counter */
    FrameCount = 0;
    
    /* Check the data to be sent through IN pipe */
    Handle_USBAsynchXfer(pdev);
  }
  
  return USBD_OK;
}

/**
  * @brief  Handle_USBAsynchXfer
  *         Send data to USB
  * @param  pdev: instance
  * @retval None
  */
static void Handle_USBAsynchXfer (void *pdev)
{
  uint16_t USB_Tx_ptr;
  uint16_t USB_Tx_length;
  
  if(USB_Tx_State == USB_CDC_IDLE)
  {
    if (APP_Rx_ptr_out == APP_RX_DATA_SIZE)
    {
      APP_Rx_ptr_out = 0;
    }
    
    if(APP_Rx_ptr_out == APP_Rx_ptr_in) 
    {
      USB_Tx_State = USB_CDC_IDLE; 
      return;
    }
    
    if(APP_Rx_ptr_out > APP_Rx_ptr_in) /* rollback */
    { 
      APP_Rx_length = APP_RX_DATA_SIZE - APP_Rx_ptr_out;
      
    }
    else 
    {
      APP_Rx_length = APP_Rx_ptr_in - APP_Rx_ptr_out;
      
    }
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
    APP_Rx_length &= ~0x03;
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
    
    if (APP_Rx_length > CDC_DATA_IN_PACKET_SIZE)
    {
      USB_Tx_ptr = APP_Rx_ptr_out;
      USB_Tx_length = CDC_DATA_IN_PACKET_SIZE;
      
      APP_Rx_ptr_out += CDC_DATA_IN_PACKET_SIZE;	
      APP_Rx_length -= CDC_DATA_IN_PACKET_SIZE;
      USB_Tx_State = USB_CDC_BUSY;
    }
    else
    {
      USB_Tx_ptr = APP_Rx_ptr_out;
      USB_Tx_length = APP_Rx_length;
      
      APP_Rx_ptr_out += APP_Rx_length;
      APP_Rx_length = 0;
      if(USB_Tx_length == CDC_DATA_IN_PACKET_SIZE)
      {
        USB_Tx_State = USB_CDC_ZLP;
      }
      else
      {
        USB_Tx_State = USB_CDC_BUSY;
      }
    }
    
    DCD_EP_Tx (pdev,
               CDC_IN_EP,
               (uint8_t*)&APP_Rx_Buffer[USB_Tx_ptr],
               USB_Tx_length);
  }  
}

/**
  * @brief  USBD_cdc_GetCfgDesc 
  *         Return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_cdc_GetCfgDesc (uint8_t speed, uint16_t *length)
{
    *length = sizeof (usbd_cdc_CfgDesc);
    return usbd_cdc_CfgDesc;
}

/**
  * @brief  USBD_cdc_GetCfgDesc 
  *         Return configuration descriptor
  * @param  pdev: device instance
  * @param  tx_buf : point to the data buffer which would be sent
  * @param  tx_len : the length of the data which would be sent
  * @param  enpoind: the in endpoint
  * @retval pointer to descriptor buffer
  */
uint8_t usbdevice2pc(USB_OTG_CORE_HANDLE *pdev, char *tx_buf, uint32_t tx_len, uint8_t enpoint)
{
    uint8_t tmp;
    uint16_t tmp_1;
    if(tx_len>=64)
    {
        for(tmp = 0; tmp < strlen(tx_buf)/64; tmp++)
        {
            DCD_EP_Tx(pdev, enpoint, (uint8_t*)(tx_buf+tmp*64), 64);
            for(tmp_1 = 0; tmp_1 < 200; tmp_1++){;}
        }
        if(tx_len%64!=0)
            DCD_EP_Tx(pdev, enpoint, (uint8_t*)(tx_buf+tmp*64), tx_len%64);
    }
    else
    {
        DCD_EP_Tx(pdev, enpoint, (uint8_t*)tx_buf, tx_len);
    }
    if(tx_len%64==0)
    {
        for(tmp_1 = 0; tmp_1 < 200; tmp_1++){;}
        DCD_EP_Tx(pdev, enpoint, NULL, 0);
    }  
    return USBD_OK;
}


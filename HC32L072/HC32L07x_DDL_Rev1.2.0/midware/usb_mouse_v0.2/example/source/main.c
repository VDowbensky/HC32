/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2019-06-28  1.0   First version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l176.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_bsp.h"
#include "usbd_hid_core.h"
#include "string.h"

#define JOY_LEFT        1   //�������
#define JOY_RIGHT       2   //�������
#define JOY_UP          3   //�������
#define JOY_DOWN        4   //�������

#define CURSOR_STEP     5   //����ƶ���С��λ

USB_OTG_CORE_HANDLE  USB_OTG_dev;
uint8_t press_flag;         //�����������־λ 1:������£�2���������

/**
 *******************************************************************************
 ** \brief �˿�GPIOA���ж���ں���
 **
 ** \param ��
 **
 ** \retval ��
 ******************************************************************************/
#ifdef BOARD_EVBHC32LF07X_V11
void PORTD_F_IRQHandler(void)
#else
void PORTA_IRQHandler(void)
#endif
{
    if(TRUE == Gpio_GetIrqStatus(EVB_KEY5_PORT, EVB_KEY5_PIN))
    {
        Gpio_ClearIrq(EVB_KEY5_PORT, EVB_KEY5_PIN);
        if(Gpio_GetInputIO(EVB_KEY5_PORT, EVB_KEY5_PIN) == FALSE)
        {
            press_flag = 1;            //����������
        }
        else
        {
            press_flag = 2;            //����������
        }
    }
}

/**
 *******************************************************************************
 ** \brief ��ȡ����ƶ��ķ������ҡ��ϡ���
 **
 ** \param ��
 **
 ** \retval ��
 ******************************************************************************/
uint8_t joystate(void)
{
    if(Gpio_GetInputIO(EVB_KEY1_PORT, EVB_KEY1_PIN) == FALSE)
    {
        return JOY_LEFT;
    }
    if(Gpio_GetInputIO(EVB_KEY2_PORT, EVB_KEY2_PIN) == FALSE)
    {
        return JOY_UP;
    }
    if(Gpio_GetInputIO(EVB_KEY3_PORT, EVB_KEY3_PIN) == FALSE)
    {
        return JOY_RIGHT;
    }
    if(Gpio_GetInputIO(EVB_KEY4_PORT, EVB_KEY4_PIN) == FALSE)
    {
        return JOY_DOWN;
    }
    else
    {
        return 0;
    }
}

/**
 *******************************************************************************
 ** \brief ���������ƶ����λ��
 **
 ** \param Keys������ƶ�����
 **
 ** \retval ��
 ******************************************************************************/
void Joystick_Send(uint8_t dir)
{
    uint8_t Mouse_Buffer[4] = {0, 0, 0, 0};
    int8_t X = 0, Y = 0;
    switch (dir)
    {
        case JOY_LEFT:
            X -= CURSOR_STEP;
        break;
        case JOY_RIGHT:
            X += CURSOR_STEP;
        break;
        case JOY_UP:
            Y -= CURSOR_STEP;
        break;
        case JOY_DOWN:
            Y += CURSOR_STEP;
        break;
        default:
            return;
    }
    Mouse_Buffer[1] = X;
    Mouse_Buffer[2] = Y;  
    DCD_EP_Tx (&USB_OTG_dev, HID_IN_EP, Mouse_Buffer, 4);
}

/**
 *******************************************************************************
 ** \brief ��������
 **
 ** \param state��ָ�����������״̬��ָ�� 1��������£�2���������
 **
 ** \retval ��
 ******************************************************************************/
void left_key(uint8_t *state)
{
    uint8_t Mouse_Buffer[4] = {0, 0, 0, 0};
    if(*state == 1)          //����������
    {
        *state = 0;
        Mouse_Buffer[0] = 1;
        DCD_EP_Tx (&USB_OTG_dev, HID_IN_EP, Mouse_Buffer, 4);
    }
    if(*state == 2)
    {
        *state = 0;
        Mouse_Buffer[0] = 0;
        DCD_EP_Tx (&USB_OTG_dev, HID_IN_EP, Mouse_Buffer, 4);        
    }
}

/**
 *******************************************************************************
 ** \brief ������main
 **
 ** \param ��
 **
 ** \retval ��
 ******************************************************************************/
int32_t main(void)
{
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_HID_cb, &USR_cb);    
    while(1)
    {
        if(joystate()!=0)      //������ҡ��ϡ����ƶ�
        {
            Joystick_Send(joystate());
        }
        if(press_flag != 0)    //���������
        {
            left_key(&press_flag);
        }
	}
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



/*************************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.    
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
/** \file lcd.c
 **
 ** WDT function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2018-5-3  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "lcd.h"

/**
 *******************************************************************************
 ** \addtogroup I2cGroup
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
 en_result_t LCD_SetClkSrc(en_lcd_clk_t enLcdClk)
 {
     en_result_t enRet = Error;
     M0P_LCD->CR1_f.CLKSRC = enLcdClk;
     enRet = Ok;
     return enRet;
 }
/**
  ************************************************** ****************************
  ** \brief LCD Bias source selection function
  **
  ** \param [in] enBiasSrc bias source selection
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_SelBiasSrc(en_lcd_biassrc_t enBiasSrc)
 {
     en_result_t enRet = Error;
     switch(enBiasSrc)
     {
         case LcdInRes_High:
         case LcdInRes_Low:
         case LcdInRes_Mid:
         case LcdExtCap:
         case LcdExtRes:
            M0P_LCD->CR0_f.BSEL = enBiasSrc;
            break;
        default:
            return ErrorInvalidParameter;
     }
     enRet = Ok;
     return enRet;
 }
/**
  ************************************************** ****************************
  ** \brief LCD duty cycle selection function
  **
  ** \param [in] enDuty duty cycle
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
en_result_t LCD_SetDuty(en_lcd_duty_t enDuty)
{
    en_result_t enRet = Error;
    switch(enDuty)
    {
        case LcdStatic:
        case LcdDuty2:
        case LcdDuty3:
        case LcdDuty4:
        case LcdDuty6:
        case LcdDuty8:
            M0P_LCD->CR0_f.DUTY = enDuty;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet; 
}
/**
  ************************************************** ****************************
  ** \brief LCD bias setting function
  **
  ** \param [in] enBias offset
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_SetBias(en_lcd_bias_t enBias)
 {
    en_result_t enRet = Error;
    switch(enBias)
    {
        case LcdBias3:
        case LcdBias2:
            M0P_LCD->CR0_f.BIAS = enBias;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet;     
 }
/**
  ************************************************** ****************************
  ** \brief LCD voltage pump clock frequency selection function
  **
  ** \param [in] enCpClk voltage pump frequency
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
en_result_t LCD_SelCpClk(en_lcd_cpclk_t enCpClk)
{
    en_result_t enRet = Error;
    switch(enCpClk)
    {
        case LcdClk2k:
        case LcdClk4k:
        case LcdClk8k:
        case LcdClk16k:
            M0P_LCD->CR0_f.CPCLK = enCpClk;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet;  
}
/**
  ************************************************** ****************************
  ** \brief LCD scan clock frequency selection function
  **
  ** \param [in] enScanClk scan clock frequency
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
en_result_t LCD_SelScanClk(en_lcd_scanclk_t enScanClk)
{
    en_result_t enRet = Error;
    switch(enScanClk)
    {
        case LcdClk64hz:
        case LcdClk128hz:
        case LcdClk256hz:
        case LcdClk512hz:
            M0P_LCD->CR0_f.LCDCLK = enScanClk;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet;    
}
/**
  ************************************************** ****************************
  ** \brief LCD Module Enable or Flash Screen Enable Disable Function
  **
  ** \param [in] enFunc function, bFlag is enabled or disabled
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_EnFunc(en_lcd_func_t enFunc,boolean_t bFlag)
 {
    en_result_t enRet = Error;
    switch(enFunc)
    {
        case LcdEn:
            M0P_LCD->CR0_f.EN = bFlag;
            break;
        case LcdBlinkEn:
            M0P_LCD->CR1_f.BLINKEN = bFlag;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet;
 }
/**
  ************************************************** ****************************
  ** \brief LCD display mode 0/1 settings
  **
  ** \param [in] enDispMode mode
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_SetDispMode(en_lcd_dispmode_t enDispMode)
 {
    en_result_t enRet = Error;
    switch(enDispMode)
    {
        case LcdMode0:
        case LcdMode1:
            M0P_LCD->CR1_f.MODE = enDispMode;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet; 
 }
/**
  ************************************************** ****************************
  ** \brief LCD contrast setting
  **
  ** \param [in] u8Contrast contrast
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_SetContrast(uint8_t u8Contrast)
 {
    en_result_t enRet = Error;
    M0P_LCD->CR0_f.CONTRAST = u8Contrast;
    enRet = Ok;
    return enRet;
 }
/**
  ************************************************** ****************************
  ** \brief LCD splash counter settings
  **
  ** \param [in] u8BlinkCnt counter
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_SetBlinkCnt(uint8_t u8BlinkCnt)
 {
    en_result_t enRet = Error;
    M0P_LCD->CR1_f.BLINKCNT = u8BlinkCnt;
    enRet = Ok;
    return enRet;   
 }
/**
  ************************************************** ****************************
  ** \brief LCD interrupt flag clear
  **
  ** \param [in] none
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
en_result_t LCD_ClrIntState(void)
{
	en_result_t enRet = Error;
	M0P_LCD->INTCLR_f.INTF = 0;
    enRet = Ok;
    return enRet;  
}
/**
  ************************************************** ****************************
  ** \brief Get port configuration according to LCD display mode
  **
  ** \param [in]enLcdRunMode: display mode, stcSegCom gets port parameters
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara,stc_lcd_segcom_t *pstcSegCom)
{
    en_result_t enRet = Error;
    if(pstcSegComPara->u8MaxSeg>40)
    {
        return ErrorInvalidParameter;
    }
    switch(pstcSegComPara->enBiasSrc)//seg32_35
    {
        case LcdInRes_High:
        case LcdInRes_Low:
        case LcdInRes_Mid:
            pstcSegCom->bMux = 1;
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom = 0xff;
            break;
        case LcdExtCap:
        case LcdExtRes:
            //VLCD analog port configuration
            if(pstcSegComPara->u8MaxSeg>36)
            {
                return ErrorInvalidParameter;
            }
            pstcSegCom->bMux = 0;
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom = 0x0f;//Seg32_35 is set to 0
            break;
        default:
          return ErrorInvalidParameter;
    }
    switch(pstcSegComPara->enDuty)//COM0_7
    {
        case LcdStatic:
            pstcSegCom->u8Com0_3 = 0xfe;
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom &= 0xff;
            break;
        case LcdDuty2:
            pstcSegCom->u8Com0_3 = 0xfc;//COM port configuration, default configuration in order com0/com1
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom &= 0xff;
            break;
        case LcdDuty3:
            pstcSegCom->u8Com0_3 = 0xf8;//Only take lowest 4bits
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom &= 0xff;
            break;
        case LcdDuty4:
            pstcSegCom->u8Com0_3 = 0xf0;//Only take lowest 4bits
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom &= 0xff;
            break;
        case LcdDuty6:
            if(pstcSegComPara->u8MaxSeg>38)
            {
                return ErrorInvalidParameter;
            }
            pstcSegCom->u8Com0_3 = 0xf0;//Only take lowest 4bits
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom &= 0xfc;
            break;
        case LcdDuty8:
            if(pstcSegComPara->u8MaxSeg>36)
            {
                return ErrorInvalidParameter;
            }
            pstcSegCom->u8Com0_3 = 0xf0;//Only take lowest 4bits
            pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom &= 0xf0;
            break;            
        default:
        return ErrorInvalidParameter;
    }
    return enRet;
}
/**
  ************************************************** ****************************
  ** \brief LCD COMSEG port configuration
  **
  ** \param [in] pstcSegCom port configuration structure
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_SetSegCom(stc_lcd_segcom_t *pstcSegCom)
 {
    en_result_t enRet = Error;
    M0P_LCD->POEN0 = pstcSegCom->u32Seg0_31;
    M0P_LCD->POEN1 = (uint32_t)(pstcSegCom->Seg32_39VLcdCom7_4_t.SegVLcdCom);
	M0P_LCD->POEN1_f.MUX = pstcSegCom->bMux;
    M0P_LCD->POEN1_f.C0 = pstcSegCom->u8Com0_3&0x01;
    M0P_LCD->POEN1_f.C1 = pstcSegCom->u8Com0_3&0x02;
    M0P_LCD->POEN1_f.C2 = pstcSegCom->u8Com0_3&0x04;
    M0P_LCD->POEN1_f.C3 = pstcSegCom->u8Com0_3&0x08;
    enRet = Ok;
    return enRet;
 }
 /**
  ************************************************** ****************************
  ** \brief LCD full display
  **
  ** \param [in] none
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
  en_result_t LCD_FullDisp(void)
  {
    en_result_t enRet=Error;
    uint8_t i;
	uint32_t volatile *p = NULL;
	p = &M0P_LCD->RAM0;
    for(i=0;i<8;i++)
    {
        *p = 0xffffffffu;
        p++;
    }
    for(i=0;i<8;i++)
    {
        *p = 0xffu;
        p++;
    } 
    enRet = Ok;
    return enRet;
  }
/**
  ************************************************** ****************************
  ** \brief LCD clear
  **
  ** \param [in] none
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_ClearDisp(void)
{
    en_result_t enRet=Error;
    uint8_t i;
    uint32_t volatile *p = NULL;
    p = &M0P_LCD->RAM0;
    for(i=0;i<16;i++)
    {
        *p = 0x00;
        p++;
    }
    enRet = Ok;
    return enRet;
}
/**
  ************************************************** ****************************
  ** \brief LCD RAM bit setting function
  **
  ** \param [in] u16Row RAM address index, u32List bit bit index, bData write 0 or 1
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
  en_result_t LCD_WriteRam(uint16_t u16Row, uint32_t u32List, boolean_t bData)
  {
    en_result_t  enRet = Error;
    uint8_t RamListSize = 0;
    volatile uint32_t *ptemp = NULL;
    ptemp = (volatile uint32_t*)&M0P_LCD->RAM0;
    if(u16Row>=8)
    {
        RamListSize = LCDRAM8_FSIZE;
    }
    else
    {
        RamListSize = LCDRAM0_7SIZE;
    }
    if ((u16Row > LCDRAMSIZE) || (u32List > RamListSize))
    {
        enRet = ErrorInvalidParameter;
        return enRet;
    }
    
    ptemp += u16Row;

    if (bData == TRUE)
    {
        *ptemp |= (uint32_t)(1 << u32List);
    } 
    else
    {
        *ptemp &= (uint32_t)(0 << u32List);
    }
    enRet = Ok;
    return  enRet; 
  }
/**
  ************************************************** ****************************
  ** \brief LCD RAM 0-7 register setting function
  **
  ** \param [in] u8Row RAM address index, u32Data write register value
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
en_result_t LCD_WriteRam0_7Int32(uint8_t u8Row,uint32_t u32Data)
{
    en_result_t  enRet = Error;
    volatile uint32_t *ptemp = NULL;
    ptemp = (volatile uint32_t*)&M0P_LCD->RAM0;

    if (u8Row > LCDRAMSIZE)
    {
        enRet = ErrorInvalidParameter;
        return enRet;
    }
    
    ptemp += u8Row;
    *ptemp = u32Data;
    enRet = Ok;
    return  enRet; 
}
/**
  ************************************************** ****************************
  ** \brief LCD RAM 8-f register setting function
  **
  ** \param [in] u8Row RAM address index, u8Data write register value
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
en_result_t LCD_WriteRam8_FInt8(uint8_t u8Row,uint8_t u8Data)
{
    en_result_t  enRet = Error;
    volatile uint32_t *ptemp = NULL;
    ptemp = (volatile uint32_t*)&M0P_LCD->RAM0;

    if (u8Row > LCDRAMSIZE)
    {
        enRet = ErrorInvalidParameter;
        return enRet;
    }
    
    ptemp += u8Row;
    *ptemp = u8Data;
    enRet = Ok;
    return  enRet;  
}
/**
  ************************************************** ****************************
  ** \brief LCD module initialization function
  **
  ** \param [in] stcLcdCfg configuration structure
  **
  ** \retval enRet success or failure
  **
  ************************************************** ****************************/
 en_result_t LCD_Init(stc_lcd_config_t *pstcLcdCfg)
 {
     en_result_t enRet = Error;
     enRet = LCD_SelBiasSrc(pstcLcdCfg->enBiasSrc);
     enRet = LCD_SetDuty(pstcLcdCfg->enDuty);
     enRet = LCD_SetBias(pstcLcdCfg->enBias);
     enRet = LCD_SelCpClk(pstcLcdCfg->enCpClk);
     enRet = LCD_SelScanClk(pstcLcdCfg->enScanClk);
     enRet = LCD_SetDispMode(pstcLcdCfg->enDispMode);
     enRet = LCD_SetClkSrc(pstcLcdCfg->enClk);
     if(Ok!=enRet)
     {
        return ErrorInvalidParameter;
     }
     if(pstcLcdCfg->bTouchNvic)
     {
         M0P_LCD->CR1_f.IE = 1;
         EnableNvic(LCD_IRQn,IrqLevel3,TRUE);
     }
     else
     {
         EnableNvic(LCD_IRQn,IrqLevel3,FALSE);
     }
     return Ok;
 }
//@} // LCDGroup

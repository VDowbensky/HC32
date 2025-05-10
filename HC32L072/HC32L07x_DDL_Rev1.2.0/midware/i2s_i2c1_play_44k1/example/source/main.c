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
 **   - 2019-03-01  1.0  Lux First version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l176.h"
#include "sysctrl.h"
#include "wm8731.h"
#include "hc32l17x_i2s.h"
#include "data_sound_441_i2s.h"
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                            
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
const uint16_t *pu16SoundData_l=au16PixieDustSoundI2s_441;
const uint16_t *pu16SoundData_r=au16PixieDustSoundI2s_441;
/******************************************************************************
 * Local type definitions ('typedef')                                         
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                             
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief  配置I2S0的引脚功能
 **
 ** \param  无
 **               
 ** \retval 无
 **         
 ******************************************************************************/
void i2s0_pin_config(void)
{
	//PD08->I2S0_SCK
	M0P_GPIO->PDDIR_f.PD08=0;//引脚配置从输出
	M0P_GPIO->PDADS_f.PD08=0;//引脚配置为数字端口
	M0P_GPIO->PDPU_f.PD08=1; //引脚使能上拉
	M0P_GPIO->PDDR_f.PD08=0; //引脚强驱动
	M0P_GPIO->PD08_SEL_f.SEL=2;//引脚作为I2S的SCK功能
	//PD10->I2S0_SD
	M0P_GPIO->PDDIR_f.PD10=0;//引脚配置从输出
	M0P_GPIO->PDADS_f.PD10=0;//引脚配置为数字端口
	
	M0P_GPIO->PD10_SEL_f.SEL=2;//引脚作为I2S的SD功能	
	//PD11->I2S0_WS
	M0P_GPIO->PDDIR_f.PD11=0;//引脚配置从输出
	M0P_GPIO->PDADS_f.PD11=0;//引脚配置为数字端口
	M0P_GPIO->PDPU_f.PD11=1; //引脚使能上拉
	M0P_GPIO->PDDR_f.PD11=0; //引脚强驱动
	M0P_GPIO->PD11_SEL_f.SEL=2;//引脚作为I2S的WS功能	
}



int32_t main(void)
{
	stc_wm8731_reg_t wm8731_reg;
	stc_i2s_config_t i2s_config;
	systemClock_xth();
	
	M0P_SYSCTRL->PERI_CLKEN0_f.GPIO=1;//使能GPIO端口时钟
	
	I2C_ConfigMaster(M0P_I2C1);//初始化I2C0端口
	
	wm8731_reg.LLIN = 0;
	wm8731_reg.RLIN = 0;
	wm8731_reg.LHOUT_f.LHPVOL = 0x5f;
	wm8731_reg.RHOUT_f.RHPVOL = 0x5f;
	wm8731_reg.AAPC = 0x38;
	wm8731_reg.DAPC = 0x04;
	wm8731_reg.PDC  = 0x04;
	wm8731_reg.DAIF = 0x02;
	wm8731_reg.SC   = 0;
	wm8731_reg.AC   = 0x01;
	wm8731_reg.RESET = 0;	
	WM8731_Init(M0P_I2C1, &wm8731_reg);
	
	M0P_SYSCTRL->PERI_CLKEN1_f.I2S0=1;//使能I2S0模块时钟
	i2s0_pin_config();	
	
	//配置波特率为8K
	i2s_config.i2s_Div   = 17;
	i2s_config.i2s_Fract = 0;
	i2s_config.i2s_Odd   = 0;
	i2s_config.i2s_Mckoe = DISABLE;
	//通信标准为philis，通道长度为16bit，数据长度为16bit，模式为主发送模式	
	i2s_config.i2s_Mode = I2sMasterSend;  //主模式 发送
	i2s_config.i2s_Std  = i2sstdPhilips;  //I2S PHILIPS标准
	i2s_config.i2s_Cksel = I2sPclk;       //时钟选择PCLK
	i2s_config.i2s_Datalen = i2sDatlen16Bit;//16位数据长度
	i2s_config.i2s_Chlen   = i2sChlen16Bit; //通道数据长度：16bit
	I2s_Init(M0P_I2S0, &i2s_config);

	I2S_ConfIt(M0P_I2S0, I2S_IT_TXE, ENABLE);

	NVIC_ClearPendingIRQ(SPI0_I2S0_IRQn);  //清除I2S0对应的中断挂起标志位
	NVIC_SetPriority(SPI0_I2S0_IRQn,3);    //设置I2S0中断优先级
	NVIC_EnableIRQ(SPI0_I2S0_IRQn);        //使能I2S0中断

	I2S_Cmd(M0P_I2S0, ENABLE);	
	while(1)
	{		

	}
}	
	

/**
 ******************************************************************************
 ** \brief  向左声道发送寄存器写16位数据
 **
 ** \param  无
 **               
 ** \retval 无
 **         
 ******************************************************************************/
void i2s0_lsend(void)
{
    uint16_t u16Data;

    u16Data =  *pu16SoundData_l++;
		M0P_I2S0->DRL_f.DRL=u16Data;//将数据装入左声道数据寄存器
		*pu16SoundData_l++;
    if(u32WavLen_44k <= (pu16SoundData_l - &au16PixieDustSoundI2s_441[0]))
    {
        pu16SoundData_l = &au16PixieDustSoundI2s_441[0];
    }	
}

/**
 ******************************************************************************
 ** \brief  向右声道发送寄存器写16位数据
 **
 ** \param  无
 **               
 ** \retval 无
 **         
 ******************************************************************************/
void i2s0_rsend(void)
{
    uint16_t u16Data;

    u16Data =  *pu16SoundData_r++;
		M0P_I2S0->DRR_f.DRR=u16Data;//将数据装入右声道数据寄存器
		*pu16SoundData_r++;
    if(u32WavLen_44k <= (pu16SoundData_r - &au16PixieDustSoundI2s_441[0]))
    {
        pu16SoundData_r = au16PixieDustSoundI2s_441+1;
    }	
}

/**
 ******************************************************************************
 ** \brief  I2S0中断处理函数
 **
 ** \param  无
 **               
 ** \retval 无
 **         
 ******************************************************************************/
void SPI0_I2S0_IRQHandler(void)
{
	if(M0P_I2S0->SR_f.TXE_L==1)
	{
		i2s0_lsend();
		M0P_I2S0->SR_f.TXE_L=0;//清除中断标志位
	}
	
	if(M0P_I2S0->SR_f.TXE_R==1)
	{
		i2s0_rsend();
		M0P_I2S0->SR_f.TXE_R=0;//清除中断标志位
	}	
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



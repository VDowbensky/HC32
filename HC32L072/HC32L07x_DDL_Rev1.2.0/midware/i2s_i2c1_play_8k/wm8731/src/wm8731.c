/*******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co., Ltd. ("HDSC").
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
/** \file wm8731.c
 **
 ** \brief I2S codec WM8731 driver API functions
 **
 **   - 2019-07-17  lsq First version
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
//#include "ddl.h"
#include "wm8731.h"

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
 ******************************************************************************
 ** \brief  ����I2Cx��Ӧ�����Ż���I2Cx��Ϊ���豸����ؼĴ���
 ** \param  i2cx: M0P_I2C0����M0P_I2C1            
 ** \retval ��
 **         
 ******************************************************************************/ 
void I2C_ConfigMaster(M0P_I2C_TypeDef *i2cx)
{
	if(i2cx == M0P_I2C0)
	{
		M0P_SYSCTRL->PERI_CLKEN0_f.I2C0 = 1;  //ʹ��I2C0ʱ��ģ��
		//I2C0 SCL:PA09
		M0P_GPIO->PAADS_f.PA09 = 0x00;
		M0P_GPIO->PA09_SEL     = 0x04;
		M0P_GPIO->PADIR_f.PA09 = 0x00;
		M0P_GPIO->PAOD_f.PA09  = 0x01;
		//I2C0_SDA:PA10
		M0P_GPIO->PAADS_f.PA10 = 0x00;
		M0P_GPIO->PA10_SEL     =0x04;
		M0P_GPIO->PADIR_f.PA10 =0x00;
		M0P_GPIO->PAOD_f.PA10  =0x01;
	}
	else if(i2cx == M0P_I2C1)
	{
		M0P_SYSCTRL->PERI_CLKEN0_f.I2C1=1;//ʹ��I2C1ʱ��ģ��
		//I2C1 SCL:PB10
		M0P_GPIO->PBADS_f.PB10 = 0x00;
		M0P_GPIO->PB10_SEL     = 0x01;
		M0P_GPIO->PBDIR_f.PB10 = 0x00;
		M0P_GPIO->PBOD_f.PB10  = 0x01;
		//I2C1 SDA:PB11
		M0P_GPIO->PBADS_f.PB11 = 0x00;
		M0P_GPIO->PB11_SEL     = 0x01;
		M0P_GPIO->PBDIR_f.PB11 = 0x00;
		M0P_GPIO->PBOD_f.PB11  = 0x01;		
	}
	
	i2cx->CR = 0;
	i2cx->TMRUN = 1;
	i2cx->TM_f.TM = 59;      //ϵͳ��ƵΪ48M,ͨ�Ų���������Ϊ100K
	i2cx->CR_f.ENS = 1;	
}

/**
 ******************************************************************************
 ** \brief  ͨ��I2C1����2�ֽ�����
 ** \param  i2cx: M0P_I2C0����M0P_I2C1
 ** \param  buf����Ҫ���͵����ݻ���            
 ** \retval len�����͵������ֽ���
 **         
 ******************************************************************************/
void I2C_WriteWm8731R(M0P_I2C_TypeDef *i2cx, uint8_t *buf, uint8_t len)
{
	uint8_t u8State = 0;
	uint8_t tmp=0, tmp_1;
	i2cx->CR_f.STA=1;
	while(1)
	{
		while(1!=i2cx->CR_f.SI);
		u8State = i2cx->STAT;
		switch(u8State)
		{
			case 0x08:
				i2cx->CR_f.STA = 0;
				i2cx->DATA = I2c_SlaveWt;
				break;
			case 0x10:
				i2cx->CR_f.STA = 0;
				i2cx->DATA = I2c_SlaveWt;
				break;
			case 0x18:
				i2cx->CR_f.STA = 0;
				tmp_1=buf[tmp++];
				i2cx->DATA = tmp_1;//�Ĵ�����ַ
				break;
			case 0x20:
			case 0x38:
			case 0x30:
			case 0x48:
				i2cx->CR_f.STA = 1;
				i2cx->CR_f.STO = 1;
			break;							
			case 0x28:
				if(tmp>=len)//����Ѿ�������2�ֽڣ���ֹͣI2C
				{
					i2cx->CR_f.STO = 1;
					i2cx->CR_f.SI = 0;	
					return;
				}
				i2cx->DATA = buf[tmp++];//���ͼĴ�������					
				break;	
		}
		i2cx->CR_f.SI = 0;	 	
	}		 
}

/**
 ******************************************************************************
  * @brief  ͨ��I2Cx��ʼ��WM8731����Ҫ�����ڲ��ĸ����Ĵ���
  * \param  i2cx: M0P_I2C0����M0P_I2C1
  * @param  pstcReg: ���ڳ�ʼ���Ĵ����Ľṹ��
  * @retval None
 **
 ******************************************************************************/
void WM8731_Init(M0P_I2C_TypeDef *i2cx, stc_wm8731_reg_t* pstcReg)
{
	uint8_t buf[2];
	uint8_t tmp;

	//Reset Register ����ȡ������
	tmp = (uint8_t)((pstcReg->RESET>>8) & 0x01);	
	buf[0] = (WM8731_REG_RESET<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->RESET & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Reset Register�Ĵ���	
	//Left Line In ����ȡ������
	tmp = (uint8_t)((pstcReg->LLIN>>8) & 0x01);	
	buf[0] = (WM8731_REG_LLINE_IN<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->LLIN & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Left Line In�Ĵ���
	//Right Line In����ȡ������
	tmp = (uint8_t)((pstcReg->RLIN>>8) & 0x01);
	buf[0] = (WM8731_REG_RLINE_IN<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->RLIN & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Right Line In�Ĵ���
	//Left Headphone Out ����ȡ������
	tmp = (uint8_t)((pstcReg->LHOUT>>8) & 0x01);
	buf[0] = (WM8731_REG_LHPHONE_OUT<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->LHOUT & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Left Headphone Out�Ĵ���
	//Right Headphone Out ����ȡ������
	tmp = (uint8_t)((pstcReg->RHOUT>>8) & 0x01);
	buf[0] = (WM8731_REG_RHPHONE_OUT<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->RHOUT & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Right Headphone Out �Ĵ���
	//Analogue Audio Path Control����ȡ������
	tmp = (uint8_t)((pstcReg->AAPC>>8) & 0x01);
	buf[0] = (WM8731_REG_ANALOG_PATH<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->AAPC & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Analogue Audio Path Control�Ĵ���
	//Digital Audio Path Control ����ȡ������
	tmp = (uint8_t)((pstcReg->DAPC>>8) & 0x01);
	buf[0] = (WM8731_REG_DIGITAL_PATH<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->DAPC & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Digital Audio Path Control�Ĵ���
	//Power Down Control ����ȡ������
	tmp = (uint8_t)((pstcReg->PDC>>8) & 0x01);
	buf[0] = (WM8731_REG_PDOWN_CTRL<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->PDC & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);          //����Power Down Control�Ĵ���
	//Digital Audio Interface Format ����ȡ������
	tmp = (uint8_t)((pstcReg->DAIF>>8) & 0x01);
	buf[0] = (WM8731_REG_DIGITAL_IF<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->DAIF & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);           //����Digital Audio Interface Format�Ĵ���
	//Sampling Control ����ȡ������ 
	tmp = (uint8_t)((pstcReg->SC>>8) & 0x01);
	buf[0] = (WM8731_REG_SAMPLING_CTRL<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->SC & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);           //����Sampling Control �Ĵ���	
	//Active Control ����ȡ������
	tmp = (uint8_t)((pstcReg->AC>>8) & 0x01);
	buf[0] = (WM8731_REG_ACTIVE_CTRL<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->AC & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2);           //����Active Control �Ĵ���		
}

/**
 ******************************************************************************
  * @brief  ͨ��I2Cx�������Ҷ���ͨ���������������Ҫ����Left Headphone Out��Right Headphone Out�Ĵ���
  * \param  i2cx: M0P_I2C0����M0P_I2C1
  * @param  pstcReg: ���ڳ�ʼ���Ĵ����Ľṹ��
	* @param  lhpvol : ��������ͨ������������Χλ0-2^7
  * @param  rhpvol : �Ҷ������ͨ������������Χλ0-2^7
  * @retval None
 **
 ******************************************************************************/
void WM8731_HPhoneVolume(M0P_I2C_TypeDef *i2cx, stc_wm8731_reg_t* pstcReg, uint8_t lhpvol, uint8_t rhpvol)
{
	uint8_t buf[2];
	uint8_t tmp;
	
	pstcReg->LHOUT_f.LHPVOL=lhpvol;
	tmp = (uint8_t)((pstcReg->LHOUT>>8) & 0x01);
	buf[0] = (WM8731_REG_LHPHONE_OUT<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->LHOUT & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2); 	
	
	pstcReg->RHOUT_f.RHPVOL=rhpvol;
	tmp = (uint8_t)((pstcReg->RHOUT>>8) & 0x01);
	buf[0] = (WM8731_REG_RHPHONE_OUT<<1) & (~1);
	buf[0] = buf[0] | tmp;
	buf[1] = (uint8_t)(pstcReg->RHOUT & 0xff);
	I2C_WriteWm8731R(i2cx, buf, 2); 
}
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

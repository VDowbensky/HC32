
#include "sysctrl.h"

/**
 ******************************************************************************
 ** \brief  ���ⲿ���پ������룬��ͨ��PLL��Ƶ��48MHz��Ϊ��Ƶ
 ** \brief  ��Ҫ�޸����Ƶ�ʣ�����ͨ���޸ġ�PLL����ʱ�������ʱ�ӵı�Ƶ��ϵ����������ͨ��PLL_CR�����޸�
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
 
void systemClock_xth(void)
{
	M0P_SYSCTRL->PERI_CLKEN0_f.FLASH=1;//��FLASH����ʱ��
	M0P_FLASH->BYPASS = 0x5A5A;
	M0P_FLASH->BYPASS = 0xA5A5;
	M0P_FLASH->CR_f.WAIT = 1;
	
  M0P_GPIO->PFADS_f.PF00 = 1;
  M0P_GPIO->PFADS_f.PF01 = 1;	
//	M0P_GPIO->PFDIR_f.PF00 = 1;
//	M0P_GPIO->PFDIR_f.PF01 = 1;
	M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
  M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
	M0P_SYSCTRL->SYSCTRL0_f.XTH_EN    = 1;	//ʹ��XTH�ⲿ����
	

	M0P_SYSCTRL->PLL_CR_f.STARTUP    = 7;//16384��PLL����
	M0P_SYSCTRL->PLL_CR_f.FRSEL      = 1;//����PLL��Ƶ�ʷ�ΧΪ6M-12M
	M0P_SYSCTRL->PLL_CR_f.DIVN       = 6;//PLL����ʱ�������ʱ�ӵı�Ƶ��ϵ
	M0P_SYSCTRL->PLL_CR_f.FOSC       = 7;//PLL���ʱ��Ƶ�ʷ�ΧΪ36M-48M
	M0P_SYSCTRL->PLL_CR_f.REFSEL     = 0;//ѡ���ⲿXTH��ΪPLL��ʱ������

	M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
  M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
	M0P_SYSCTRL->SYSCTRL0_f.PLL_EN    = 1;

	while(1 != M0P_SYSCTRL->PLL_CR_f.STABLE);//�ȴ�PLL�ȶ�
	
		M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
  M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
	M0P_SYSCTRL->SYSCTRL0_f.CLKSW=4;//ϵͳʱ��ѡ��PLL
	
	M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
  M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
	M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS=0;//HCLKֱ��ѡ��SystemClk
	
	M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
  M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
	M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS=0;//PCLKѡ��ֱ��HCLK
}	












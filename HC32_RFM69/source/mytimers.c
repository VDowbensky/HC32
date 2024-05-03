#include "mytimers.h"

void initTIM0(void);
//void Tim0Int(void);
void delay_ms (uint16_t ms);
void check_keys(void);

volatile uint16_t TimingDelay;

void TIM0_IRQHandler(void)
//void Tim0Int(void)   //TIM0 interrupt
{
static uint16_t pktimer; 
	
	if (TRUE == Bt_GetIntFlag(TIM0, BtUevIrq))  //Check if the TIM0 update interrupt occurs or not
    {
      Bt_ClearIntFlag(TIM0,BtUevIrq);  //Clear TIMx update interrupt flag 
      TimingDelay--;
			RF69_RXtimeout++;
			check_keys();
			pktimer++;
			if(pktimer >= (PkDelay*100))
			{
				pktimer = 0;
				PacketFlag = 1;
			}
			
    }
}


void initTIM0(void)
{
    uint16_t                  u16ArrValue;
    uint16_t                  u16CntValue;
    stc_bt_mode0_config_t     stcBtBaseCfg;
//    stc_gpio_config_t         stcLEDPortCfg;
    Sysctrl_SetPeripheralGate(SysctrlPeripheralBTim, TRUE); //Base Timer
		DDL_ZERO_STRUCT(stcBtBaseCfg);
    stcBtBaseCfg.enWorkMode = BtWorkMode0;                  
    stcBtBaseCfg.enCT       = BtTimer;                      
    stcBtBaseCfg.enPRS      = BtPCLKDiv1;                  
    stcBtBaseCfg.enCntMode  = Bt16bitArrMode;               
    stcBtBaseCfg.bEnTog     = FALSE;
    stcBtBaseCfg.bEnGate    = FALSE;
    stcBtBaseCfg.enGateP    = BtGatePositive;
   // stcBtBaseCfg.pfnTim0Cb  = Tim0Int; //Interrupt function entry
    Bt_Mode0_Init(TIM0, &stcBtBaseCfg);                     
    
    u16ArrValue = 65536-Sysctrl_GetPClkFreq()/1000; //0x6000;
    Bt_M0_ARRSet(TIM0, u16ArrValue);                        
    u16CntValue = 65536-Sysctrl_GetPClkFreq()/1000; //0x6000;
    Bt_M0_Cnt16Set(TIM0, u16CntValue);                      
    
    Bt_ClearIntFlag(TIM0,BtUevIrq);                         
    Bt_Mode0_EnableIrq(TIM0); //Enable TIM0 interrupt (only one interrupt when mode 0)                              
    EnableNvic(TIM0_IRQn, IrqLevel3, TRUE);                 
    Bt_M0_Run(TIM0);

}

/*
void Tim0Int(void)
{
    static uint8_t i;
    
    if(TRUE == Bt_GetIntFlag(TIM0, BtUevIrq))
    {
        if(i == 0)
        {
            Gpio_WriteOutputIO(GpioPortD, GpioPin5, TRUE);
            
            i = 1;
        }
        else
        {
            Gpio_WriteOutputIO(GpioPortD, GpioPin5, FALSE);
            
            i = 0;
        }
        
        Bt_ClearIntFlag(TIM0,BtUevIrq);
    }
}
*/



void check_keys(void)
{
	static int8_t K0cnt = 0;
  static int8_t K1cnt = 0;
  static uint8_t Tim0cnt = 0;
  static uint8_t k0, k1;
	
	if(Gpio_GetInputIO(KEYPORT, K0) == 0)
   {
     K0cnt++;
   }
   else
   {
     K0cnt--;
     if(K0cnt <= 0) K0cnt = 0;
   }
   
   if(Gpio_GetInputIO(KEYPORT, K1) == 0)
   {
     K1cnt++;
   }
   else
   {
     K1cnt--;
     if(K1cnt <= 0) K1cnt = 0;
   }
   
   Tim0cnt++;
   if(Tim0cnt == KEYDELAY)
   {
     Tim0cnt = 0;
     if (K0cnt >= KEYDELAY/2) k0 = 1;
     else k0 = 0;
     if (K1cnt >= KEYDELAY/2) k1 = 1;
     else k1 = 0;
     Key = (k1 << 1) + k0;
   }
}


void delay_ms (uint16_t ms)
{
 
  TimingDelay = ms+1;
	while (TimingDelay > 0);
}




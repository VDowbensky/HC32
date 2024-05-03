#include "myuart.h"
#include "uart.h"
#include "main.h"

void USART_init(uint32_t br);
void USART_SendBlock(uint8_t bl);
void DE_On (void);
void DE_Off (void);


void clearRXbuffer(void);

void cbUSART1_RXirq(void);
//void TxIntCallback(void);
//void RxIntCallback(void);

uint8_t TxCount;
uint8_t TxPointer;
//uint8_t TxBusy = 0;
volatile uint8_t RxPointer;

uint8_t TXbuffer[UART_TXBUFFERSIZE];
uint8_t RXbuffer[UART_RXBUFFERSIZE]; 

void UART0_IRQHandler(void)
{
	//TX
	if(Uart_GetStatus(UARTCH0, UartTC) == TRUE)
		{
		Uart_ClrStatus(UARTCH0, UartTC);
		if (TxPointer < TxCount)  	// it's end?
			{
				TxPointer++;			// next byte
				M0P_UART0->SBUF = TXbuffer[TxPointer];
//				Uart_ClrStatus(UARTCH0, UartTC);
			}
		else 
		{
			DE_Off();
			Uart_DisableIrq(UARTCH0,UartTxIrq);
			Uart_EnableIrq(UARTCH0,UartRxIrq);
			TxCount=0;
			TxPointer=0;
		}
		}
		
		else
		{			//RX
			

			if(Uart_GetStatus(UARTCH0, UartRC) == TRUE)
			{	
			//Uart_ClrStatus(UARTCH0, UartRC);
			if (TestMode == 0) cbUSART1_RXirq();
			else cbUSART1_RXtestirq();
			}
			else Uart_ClrIsr(UARTCH0); //other flags
		}
			
}


void USART_init(uint32_t br)
{

		//USART_InitTypeDef	usart;
		//NVIC_InitTypeDef NVIC_InitStructure;
		uint16_t u16Scnt = 0;
		stc_gpio_config_t gpio;
	
		stc_uart_config_t  stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
	  stc_uart_multimode_t stcMulti;
    stc_uart_baud_t stcBaud;
	
		en_uart_mmdorck_t enTb8;
	
		Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0, TRUE);
		DE_Off();
		DDL_ZERO_STRUCT(gpio);
		gpio.enDir = GpioDirOut;
		gpio.enDrv = GpioDrvH;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(UARTPORT, TXD_PIN, &gpio);
		Gpio_SetAfMode(UARTPORT,TXD_PIN, GpioAf2);
	
		gpio.enDir = GpioDirIn;
		gpio.enPuPd = GpioPu;
		gpio.enDrv = GpioDrvL;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(UARTPORT, RXD_PIN, &gpio);
		Gpio_SetAfMode(UARTPORT,RXD_PIN, GpioAf2);		
		
		DDL_ZERO_STRUCT(stcConfig);
    DDL_ZERO_STRUCT(stcUartIrqCb);
		DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
		
		//stcUartIrqCb.pfnRxIrqCb   = RxIntCallback;
    //stcUartIrqCb.pfnTxIrqCb   = TxIntCallback;
    stcUartIrqCb.pfnRxFEIrqCb = NULL;
    stcUartIrqCb.pfnPEIrqCb   = NULL;
    stcUartIrqCb.pfnCtsIrqCb  = NULL;
    //stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;
		
		stcConfig.enRunMode = UartMode1;
    stcConfig.enStopBit = Uart1bit;

		stcMulti.enMulti_mode = UartNormal;//??????
    enTb8 = UartEven;//???
    Uart_SetMMDOrCk(UARTCH0,enTb8);
    stcConfig.pstcMultiMode = &stcMulti;
    
    Uart_Init(UARTCH0, &stcConfig);
    
    Uart_SetClkDiv(UARTCH0,Uart8Or16Div);
		//Uart_SetClkDiv(UARTCH0,Uart16Or32Div);
		
    //stcBaud.u32Pclk = Sysctrl_GetPClkFreq();
    //stcBaud.enRunMode = UartMode3;
    //stcBaud.u32Baud = BAUDRATE;
		
    //u16Scnt = Uart_CalScnt(UARTCH0,&stcBaud);
		//DebugVar0 = u16Scnt;
		
		
		u16Scnt = (Sysctrl_GetPClkFreq())/(BAUDRATE*8UL);
		DebugVar0 = u16Scnt;
		
    Uart_SetBaud(UARTCH0,u16Scnt);
    Uart_ClrStatus(UARTCH0,UartRC);
    Uart_EnableIrq(UARTCH0,UartRxIrq);
    Uart_EnableFunc(UARTCH0,UartRx);
		//Uart_EnableFunc(UARTCH0,UartTx);
		
	

}


/*
void USART_SendBlock(uint8_t bl)
{

  uint8_t i;
	//uint32_t j;
	//TxPointer = 0;
  //TxCount = bl;
	//DebugVar0 = Sysctrl_GetPClkFreq();
	//DebugVar1 = Uart_GetBaud(UARTCH0,UartMode3,DebugVar0);
	for(i = 0; i < bl; i++)
	{
	//delay_ms(1);
	//for(j = 0; j < 10000; j++);
//		while(Uart_GetStatus(UARTCH0, UartTC) == FALSE);
	Uart_ClrStatus(UARTCH0,UartTC);
	M0P_UART0->SBUF = TXbuffer[i];
	while(Uart_GetStatus(UARTCH0, UartTC) == FALSE);
	Uart_ClrStatus(UARTCH0,UartTC);
	//	while(Uart_GetStatus(UARTCH0, UartTxe) != TRUE);
	//TxPointer++;
	}
	//Uart_DisableIrq(UARTCH0,UartRxIrq);
	//Uart_EnableIrq(UARTCH0,UartTxIrq);
	//M0P_UART0->SBUF = TXbuffer[0];
  

}
*/


void USART_SendBlock(uint8_t bl)
{

	TxPointer = 0;
  TxCount = bl;
	//DebugVar0 = Sysctrl_GetPClkFreq();
	//DebugVar1 = Uart_GetBaud(UARTCH0,UartMode3,DebugVar0);
	Uart_ClrStatus(UARTCH0,UartTC);
	DE_On();
	M0P_UART0->SBUF = TXbuffer[0];
	Uart_DisableIrq(UARTCH0,UartRxIrq);
	Uart_EnableIrq(UARTCH0,UartTxIrq);

}


void clearRXbuffer(void)
{

  RXbuffer[0] = 0;
  RxPointer = 0;

}


void cbUSART1_RXirq(void)
{
  //add byte to buffer and set rx flsg
    uint8_t tmp;
    //USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    //tmp = Uart_ReceiveData(UARTCH0);
		tmp = M0P_UART0->SBUF;
		Uart_ClrStatus(UARTCH0, UartRC);
    RXbuffer[RxPointer] = tmp;
    RxPointer++;
    if (RxPointer >= UART_RXBUFFERSIZE) RxPointer = 0; // overrun ptotection - circle buffer
}

void DE_On (void)
{
	Gpio_SetIO(DE_PORT, DE);
}
void DE_Off (void)
{
	Gpio_ClrIO(DE_PORT, DE);
}








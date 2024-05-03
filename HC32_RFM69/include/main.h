#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
#include "ddl.h"
#include "mygpio.h"
#include "mytimers.h"
#include "myuart.h"
#include "RFM69.h"
#include "myeeprom.h"

#include "user_settings.h"
#include "testmode.h"
#include "uart_commands.h"



#define WORK_MODE_STANDBY 0
#define WORK_MODE_RX 1
#define WORK_MODE_TX 2

extern void switch_to_tx (void);
extern void delay_ms (uint16_t ms);

extern volatile uint8_t Key; //key code
extern volatile uint8_t PacketDelay;
extern _Bool PacketFlag;


extern uint8_t work_mode;
extern volatile uint8_t RF69_RXflag;
extern volatile uint16_t RF69_RXtimeout;
//extern bool RxState;

extern int8_t Temperature;

extern int32_t DebugVar0;
extern int32_t DebugVar1;
extern int32_t DebugVar2;
extern int32_t DebugVar3;
extern int32_t DebugVar4;
extern int32_t DebugVar5;
extern int32_t DebugVar6;
extern int32_t DebugVar7;


#endif

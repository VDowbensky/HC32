#include "RFM69.h"
//variables
uint8_t RF69_TXbuffer[RF69BUFFERSIZE];
uint8_t RF69_RXbuffer[RF69BUFFERSIZE];
//uint8_t RF69_SyncValue[8] = {WORK_SYNC1, WORK_SYNC2, WORK_SYNC3, WORK_SYNC4, WORK_SYNC5, WORK_SYNC6, WORK_SYNC7, WORK_SYNC8};
uint8_t RF69_AesKey[16];
//uint8_t Channel = WORK_CHANNEL;
//uint32_t Bitrate = WORK_BITRATE;
//uint32_t Deviation = WORK_DEVIATION;
//uint8_t Txpower = WORK_TXPOWER;
//uint8_t NodeAddr = WORK_NODEADDR;
uint8_t NodeAddr; //maybe increment on TX restart



//low level routines
//write register
//reg - reg number, v - value
void RF69_writereg (uint8_t reg, uint8_t v);
//read register
//reg - reg number, returns reg value
uint8_t RF69_readreg (uint8_t reg);

//initial procedure
void RF69_init(void);
uint8_t RF69_getversion(void);


//set global parameters: bitrate, modulation
void RF69_setmodulation (uint8_t m);
void RF69_setdeviation(uint32_t d);
void RF69_setbitrate(uint32_t br);
//RC osc. calibration - check and perform if needed
void RF69_startRCcal(void);
uint8_t RF69_checkRCcal(void);
//listen mode settings
void RF69_setListenMode(uint8_t m1, uint8_t m2, uint8_t m3);
//batt. management settings

//TX parameters settings: PA select, PA ramp, PAbooster, current trimming
void RF69_setpower(uint8_t pwr); 
void RF69_setPAramp(uint8_t p);

//RX parameters: BW, DCC freq., AFC, OOK, RSSI, LNA, DAGC etc.
void setAFClowbeta(uint8_t a);
void RF69_setLNAgain (uint8_t g);
uint8_t RF69_getLNAgain(void);
void RF69_setRXBW(uint8_t d, uint8_t w);
void RF69_setAFCBW(uint8_t d, uint8_t w);
void RF69_setAFC(uint8_t a);
int16_t RF69_getAFC(void);
int16_t RF69_getFEI(void); //TODO
void RF69_startRSSI(void);
uint8_t RF69_checkRSSI(void);
//IRQ and IO mapping
void RF69_setDIOmapping(uint8_t m1, uint8_t m2); 
uint16_t RF69_getIRQflags(void);
void RF69_setRSSItr (uint8_t t); //TODO

void RF69_setRXtimeouts(uint8_t t1, uint8_t t2);

void RF69_restartRX(void);

int8_t RF69_tempmeas(void);


//packet handler parameters
//***********************************************************************************************


//operative settings

//operating mode (sleep, standby, synth, rx, tx)
void RF69_setopmode (uint8_t mode);
//channel
void RF69_setchannel(uint8_t ch); //uint8_t ch
//tx power
void RF69_setpower(uint8_t pwr);
//get RSSI
int8_t RF69_getRSSI(void); //propably maybe dependent on channel 
//get status (IRQ flags)
uint16_t RF69_getIRQflags(void);

void RF69_setRSSItr (uint8_t t); //TODO;
int8_t RF69_getRSSItr (void);
void RF69_setRXstartTO (uint8_t t); //TODO
void RF69_setRSSITO (uint8_t t); //TODO
void RF69_setPreambleSize (uint16_t s);
void RF69_setSyncConfig(uint8_t c);
void RF69_setSyncValue (void); // up to 8 bytes
void RF69_setPacketConfig1(uint8_t c);
void RF69_setPacketConfig2(uint8_t c);
void RF69_setPayLen (uint8_t l);
void RF69_setNodeAddr(uint8_t a);
void RF69_setBrAddr(uint8_t a);
void RF69_setAutoModes(uint8_t a);
//AES key
void RF69_setAESkey(void);
void RF69_setFIFOtr (uint8_t c, uint8_t tr);
//temperature
//test registers******************************************************************************
//test LNA
//PA_20 dBm
//fading margin
//low beta AFC offset
void RF69_setAFClowbeta(uint8_t a);
//fill FIFO
void RF69_writeFIFO (uint8_t n);
//read FIFO
void RF69_readFIFO (uint8_t n);
//clear FIFO
void RF69_clearFIFO (void);

void RF69_calctemp(void);
//**********************************************************************************************
//main communication procedures
//get packet
//send packet
void RF69_sendpacket(uint8_t packet_size, uint8_t address);
//implementation****************************************************************************************
//******************************************************************************************************
void RF69_init(void)
{
	RF69_HWreset();
        delay_ms(100);
				//DebugVar0 = RF69_readreg(REG_IRQFLAGS1);
				//DebugVar1 = RF69_readreg(REG_OPMODE);
				//DebugVar2 = RF69_readreg(REG_AUTOMODES);
	
        RF69_setchannel(Channel);
				RF69_setbitrate (BitRate);
				RF69_setmodulation (ModSetting);
				RF69_setdeviation(Deviation);
				
				RF69_writereg(REG_AUTOMODES, 0);
				RF69_setopmode (RF_OPMODE_STANDBY);
        
	//RF69_setDIOmapping(DIOM1_RX, DIOM2_DEFAULT);
        
	//TX amp parameters
				RF69_setpower(TxPower);
				RF69_setPAramp(WORK_PA_RAMP); //maybe changed
	//RX parameters
				RF69_setLNAgain(LnaSetting & ~LNABOOST); //maybe changed or parametrized
        //enable RX booster - maybe not mandatory in urban areas
        if(LnaSetting & LNABOOST) RF69_writereg(REG_TESTLNA, LNA_HIGH);
        else RF69_writereg(REG_TESTLNA, LNA_NORM);         
        //RX BW
        RF69_setRXBW(RbwDcc, Rbw);
        //RX AFC
        RF69_setAFCBW(AfcDcc, Abw);
        RF69_setAFC(AfcSetting); //AFCFEI
        
        RF69_writereg(REG_TESTDAGC, Dagc);
        
        //RF69_setAFClowbeta(AFC_LOWBETA_IMPROVED);//AFC low beta on
        RF69_setAFClowbeta(AFC_LOWBETA_STANDARD);
        //RF69_writereg(REG_TESTAFC, LbOffset); //2.9 kHz

        
        //RSSI
        RF69_setRSSItr(RssiTr);
        //timeouts
        RF69_setRXtimeouts(RxTo, RssiTo);
	//packet handler settings
        RF69_setPreambleSize(WORK_PREAMBLESIZE);
        RF69_setSyncConfig(WORK_SYNC_CONFIG);
        RF69_setSyncValue();
        RF69_setPayLen(66); //!!!
        RF69_setPacketConfig1(PkConfig1);
        RF69_setPacketConfig2(PkConfig2);
        RF69_setNodeAddr(NdAddr);
        RF69_setBrAddr(WORK_BRADDR);

        RF69_writereg(REG_FIFOTHRESH, WORK_FIFOTRESH);
        //RF69_setopmode(RF_OPMODE_RECEIVER);
        RF69_restartRX();

        
}

//get version
uint8_t RF69_getversion(void)
{
	return RF69_readreg(REG_VERSION);
}

//RC OSC calibration
void RF69_startRCcal(void)
{
	RF69_writereg(REG_OSC1, 0x80);
}

uint8_t RF69_checkRCcal(void)
{
	uint8_t t;
	t = RF69_readreg(REG_OSC1);
	t = (t & 0x40) >> 6;
	return t; //0 - calibration in progress, 1 - calibration done
}
//operative settings
//operating mode (sleep, standby, synth, rx, tx)

void RF69_setopmode (uint8_t m) //listen always off, sequencer always on
{
	uint8_t tmp;
	//DebugVar0 = RF69_readreg(REG_IRQFLAGS1);
	//DebugVar2 = RF69_readreg(REG_AUTOMODES);
	tmp = RF69_readreg(REG_OPMODE);
	tmp &= MODE_MASK; //
	tmp |= m;
	
	RF69_writereg(REG_OPMODE, tmp);
        while(!(RF69_readreg(REG_IRQFLAGS1) & MODE_READY))
				{
					//DebugVar0 = RF69_readreg(REG_IRQFLAGS1);
					//DebugVar1 = RF69_readreg(REG_OPMODE);
					//DebugVar2 = RF69_readreg(REG_AUTOMODES);
					
				}					//wait for mode changing
        
}

void RF69_setmodulation (uint8_t m)
{
	RF69_writereg(REG_DATAMODUL, m);
}

void RF69_setbitrate(uint32_t br)
{
	uint8_t t1, t2;
	t1 = HI(FOSC/br);
	t2 = LO(FOSC/br);
	RF69_writereg(REG_BITRATEMSB, t1);
	RF69_writereg(REG_BITRATELSB, t2);
}


// TX channel
void RF69_setchannel(uint8_t ch) //uint8_t ch
{
	//add channel offset/ Attention - offset frequency should be no more than 16777215 Hz!
	//e.g. for 256 channels max. step is 65535 kHz, for 100 channels - 167 kHz etc.
	//TODO: add this checking
	int32_t t;
        t = (F_Base/F_PREDIV)*F_MUL + ((F_Base%F_PREDIV)*F_MUL)/F_PREDIV + (F_Step*ch - F_Offset)*F_MUL/F_PREDIV;
      //temperature compensation
        t = t - ((Temperature - Tcal)*Tslope)*F_MUL/F_PREDIV;
        RF69_writereg(REG_FRFMSB, HIGL(t));
	RF69_writereg(REG_FRFMID, LOWH(t));
	RF69_writereg(REG_FRFLSB, LOWL(t));
}


//transmitter*****************************************

void RF69_setdeviation(uint32_t d)
{
	
	uint32_t t;
	uint8_t t1, t2;
	t = (d*F_MUL)/F_PREDIV;
	t1 = HI(t);
	t2 = LO(t);
	RF69_writereg(REG_FDEVMSB, t1);
	RF69_writereg(REG_FDEVLSB, t2);
	
}

//

//tx power
void RF69_setpower(uint8_t pwr) 
{
	RF69_writereg(REG_PALEVEL, (WORK_PA_SETTING + pwr));
}

void RF69_setPAramp(uint8_t p)
{
	RF69_writereg(REG_PARAMP, p);
}





//receiver**********************************
//AFC
void RF69_setAFClowbeta(uint8_t a)
{
	RF69_writereg(REG_AFCCTRL, a);
}

//listen mode (usually not in use)
void RF69_setListenMode(uint8_t m1, uint8_t m2, uint8_t m3)
{
	RF69_writereg(REG_LISTEN1, m1);
	RF69_writereg(REG_LISTEN2, m2);
	RF69_writereg(REG_LISTEN3, m3);
	
}

//LNA settings

void RF69_setLNAgain (uint8_t g)
{
	RF69_writereg(REG_LNA, g);
}

//get LNA gain
uint8_t RF69_getLNAgain(void)
{
	return (RF69_readreg(REG_LNA) & 0x38) >> 3;
}


//RX bandwidth
void RF69_setRXBW(uint8_t d, uint8_t w) 
{
    RF69_writereg(REG_RXBW, (d | w));
}

void RF69_setAFCBW(uint8_t d, uint8_t w)
{
    RF69_writereg(REG_AFCBW, (d | w));
}

//reg OOK Peak

//reg OOK Avg

//reg OOK Fix

//AFC settings
void RF69_setAFC(uint8_t a)
{
	RF69_writereg(REG_AFCFEI, a);
}


int16_t RF69_getAFC(void)//TODO
{
	return (((int16_t)RF69_readreg(REG_AFCMSB)) << 8) + (int16_t)RF69_readreg(REG_AFCLSB);
}

int16_t RF69_getFEI(void) //TODO
{
	return (((int16_t)RF69_readreg(REG_FEIMSB)) << 8) + (int16_t)RF69_readreg(REG_FEILSB);
}

//start RSSI

void RF69_startRSSI(void)
{
  RF69_writereg(REG_RSSICONFIG, 0x01);
}
uint8_t RF69_checkRSSI(void)
{
  return (RF69_readreg(REG_RSSICONFIG) & 0x02);
}

//get RSSI
int8_t RF69_getRSSI(void) //propably maybe dependent on channel 
{
  //RF69_startRSSI();
  //while(!(RF69_checkRSSI()));
  //return -(RF69_readreg(REG_RSSIVALUE)/2); //divide by 2 and negative
  return RF69_readreg(REG_RSSIVALUE)/2;
}

//DIO mapping
//temporary
void RF69_setDIOmapping(uint8_t m1, uint8_t m2)//TODO
{
    RF69_writereg(REG_DIOMAPPING1, m1); 
    RF69_writereg(REG_DIOMAPPING2, m2); 
}
//get irq flags - TODO!!!
uint16_t RF69_getIRQflags(void)
{
	return ((uint16_t)RF69_readreg(REG_IRQFLAGS1) << 8) + RF69_readreg(REG_IRQFLAGS2); //maybe vice versa
}
//set RSSI threshold
void RF69_setRSSItr (uint8_t t) //TODO
{
  RF69_writereg(REG_RSSITHRESH, t);
}
//get RSSI treshold
int8_t RF69_getRSSItr (void)
{
	return -(RF69_readreg(REG_RSSITHRESH)/2); //divide by 2 and negative
}

//set RX timeouts
void RF69_setRXtimeouts(uint8_t t1, uint8_t t2)
{
    RF69_writereg(REG_RXTIMEOUT1, t1);
    RF69_writereg(REG_RXTIMEOUT2, t2);
    
}

//packet handler*********************************************************************************

//set preamble size
void RF69_setPreambleSize (uint16_t s)
{
	RF69_writereg(PREAMBLEMSB, s >> 8);
	RF69_writereg(PREAMBLELSB, s & 0x00FF);
}
//set sync config
void RF69_setSyncConfig(uint8_t c)
{
	RF69_writereg(REG_SYNCCONFIG, c);
}
//set sync value - 8 bytes
void RF69_setSyncValue (void) //8 bytes. TODO
{
    uint8_t i;
    for(i=0; i < SYNC_SIZE+1; i++)
    {
      RF69_writereg(REG_SYNCVALUE1+i, SyncWord[i]);
    }
}
//packet format
void RF69_setPacketConfig1(uint8_t c)
{
	RF69_writereg(REG_PACKETCONFIG1, c);
}	
//packet config 2
void RF69_setPacketConfig2(uint8_t c)
{
	RF69_writereg(REG_PACKETCONFIG2, c);
}	
//payload length
void RF69_setPayLen (uint8_t l)
{
	RF69_writereg(REG_PAYLOADLENGTH, l);
}

//node address
void RF69_setNodeAddr(uint8_t a)
{
	RF69_writereg(REG_NODEADRS, a);
}
//broadcast address
void RF69_setBrAddr(uint8_t a)
{
        RF69_writereg(REG_BROADCASTADRS, a);
}


//auto modes
void RF69_setAutoModes(uint8_t a)
{
	RF69_writereg(REG_AUTOMODES , a);
}
//FIFO threshold
void RF69_setFIFOtr (uint8_t c, uint8_t tr) //condition; FIFO treshold
{
	RF69_writereg(REG_FIFOTHRESH, ((c <<7) | (tr & 0x7F)));
}

//AES key

void RF69_setAESkey(void)
{
	uint8_t i;
	for(i = 0; i < 16; i++)
	RF69_writereg(REG_AESKEY1 + i, RF69_AesKey[i]);
		
}

//temperature

int8_t RF69_tempmeas(void)
{
  RF69_writereg(REG_TEMP1, T_MEASSTART);
  while (RF69_readreg(REG_TEMP1) & T_MEASRUN)
	{
//		DebugVar1 = RF69_readreg(REG_TEMP1);
//		DebugVar2 = RF69_readreg(REG_OPMODE);
	} //wait for complete
  return RF69_readreg(REG_TEMP2);
}

void RF69_calctemp(void)
{
  //read temperature
  Temperature = TcalValue + Tcal - RF69_tempmeas();
  RF69_setchannel(Channel);
}

//test registers******************************************************************************

//test LNA

//PA_20 dBm

//fading margin

//low beta AFC offset

//fill FIFO
void RF69_writeFIFO (uint8_t n)
{
  
}
//read FIFO
void RF69_readFIFO (uint8_t n)
{
  uint8_t i;
  for (i = 0; i < n; i++) RF69_RXbuffer[i] = RF69_readreg(REG_FIFO);
}
//clear FIFO
void RF69_clearFIFO (void)
{
  //uint8_t i;
  //for(i = 0 ; i < RFM69_BUFFER_SIZE; ++i)   { RF69_readreg(REG_FIFO); }       // read every register one by one
  RF69_writereg(REG_IRQFLAGS2, FIFO_OVR);                      // clear flag if overrun
}
//**********************************************************************************************
//main communication procedures

//get packet

//send packet

void RF69_sendpacket(uint8_t packet_size, uint8_t address)
{

  uint8_t i;

  if(packet_size > RFM69_BUFFER_SIZE-1)  packet_size = RFM69_BUFFER_SIZE-1;                         // check size of the package
  RF69_clearFIFO();
  RF69_calctemp(); //frequency correction
  RF69_setopmode (RF_OPMODE_TRANSMITTER);                        // makes transmitter on
  RF69_TXbuffer[0] = packet_size+1;
  RF69_TXbuffer[1] = address;

  //RF69_writereg(REG_FIFO, packet_size + 1);                                    // transmit the packet size into FIFO
  //RF69_writereg(REG_FIFO, address);                                            // transmit address into FIFO
  //for(i = 0 ; i < packet_size ; ++i)
  for(i = 0 ; i < packet_size+2 ; i++)
  {
    RF69_writereg(REG_FIFO, RF69_TXbuffer[i]); // transmit packet payload into FIFO
  }
   checkDIO0();
  //exit on EXTI
  }

void RF69_restartRX(void)
{
  RF69_RXtimeout = 0;
  //RxState = FALSE;
	//RF69_setopmode (RF_OPMODE_SYNTHESIZER); 
  RF69_setopmode (RF_OPMODE_STANDBY);
  RF69_clearFIFO();
  //RF69_setAFC(AFC_AUTO_ON | AFC_AUTOCLEAR | AFC_CLEAR); //AFCFEI
  //RF69_setDIOmapping(DIOM1_RXWAIT, DIOM2_DEFAULT);
  RF69_setDIOmapping(DIOM1_RX, DIOM2_DEFAULT);
  RF69_setPacketConfig2(WORK_PACKETCONFIG2);
  RF69_calctemp(); //freq. correction
	//RF69_setopmode (RF_OPMODE_SYNTHESIZER); 
  RF69_setopmode (RF_OPMODE_RECEIVER);
  //start new RSSI measuring
  RF69_startRSSI();
  
}
  



//**********************************************************************************************

//low level routines
//based on external NCS handling (RF69_select, RF69_deselect) and SPI transfer (spi_transfer) functions


//write register
//reg - reg number, v - value
void RF69_writereg (uint8_t reg, uint8_t v)
{
	
    RF69_select();
    spi_transfer(reg | 0x80);
    spi_transfer(v);
    RF69_deselect();
	
}
//read register
//reg - reg number, returns reg value
uint8_t RF69_readreg (uint8_t reg)
{
    
    uint8_t r;
    RF69_select();
    spi_transfer(reg & 0x7F);
    r = spi_transfer(0);
    RF69_deselect();
    return r;
	
}






#include<LPC21XX.H>
#include"header.h"

void i2c_init(void){
 PINSEL0|=0X50;
 I2SCLH=75;
 I2SCLL=75;
 I2CONSET=(1<<6);
 }

 #define SI ((I2CONSET >>3)&1)

 void i2c_byt_wrt_frm(u8 sa,u8 mr,u8 data){
    //start
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI == 0);
	I2CONCLR=(1<<5);
	if(I2STAT != 0X8){
	uart0_tx_str("ERR:START -W\r\n");
	goto exit;
	}

  //SEND SA+W
  
  I2DAT = sa;
  I2CONCLR=(1<<3);//SI=0
  while(SI==0);
  if(I2STAT == 0x20){
   uart0_tx_str("ERR:SA+W -W\r\n");
	goto exit;
	}

	//SEND M/R
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0X30){
	uart0_tx_str("ERR:MR -W\r\n");
	goto exit;
	}

	//SEND DATA
	I2DAT=data;
	I2CONCLR=(1<<3);
	while(SI ==0);
	if(I2STAT == 0X30){
	  uart0_tx_str("ERR:DATA -W\r\n");
	goto exit;
	}

	//STOP
	exit:
	I2CONCLR=(1<<3);
	I2CONSET=(1<<4);
	}

  u8 i2c_byt_red_frm(u8 sa,u8 mr){
  u8 temp;
  //start
  I2CONSET=(1<<5);
  I2CONCLR=(1<<3);
  while(SI==0);
  I2CONCLR=(1<<5);
  if(I2STAT != 0X8){
	uart0_tx_str("ERR:START -R\r\n");
	goto exit;
	}

  //SEND SA+W
  I2DAT =sa;
  I2CONCLR=(1<<3);
  while(SI == 0);
  if(I2STAT == 0X20){
	  uart0_tx_str("ERR:SA+W -R\r\n");
	goto exit;
	}

  //SEND M/R
  I2DAT = mr;
  I2CONCLR=(1<<3);
  while(SI ==0);
  if(I2STAT == 0X30){
	    uart0_tx_str("ERR:M/R -R\r\n");
	goto exit;
	}

   //RESTART
   I2CONSET=(1<<5);
   I2CONCLR=(1<<3);
   while(SI == 0);
   I2CONCLR=(1<<5);
   if(I2STAT != 0X10){
	     uart0_tx_str("ERR:RESTART -R\r\n");
	goto exit;
	}

	//SEND SA+R
	I2DAT=sa|1;
	I2CONCLR=(1<<3);
	while(SI == 0);
	if(I2STAT == 0X48){
		uart0_tx_str("ERR:RESTART -R\r\n");
	goto exit;
	}

	//READ 
	I2CONCLR=(1<<3);
	while(SI==0);
	temp=I2DAT;
	exit:
	//STOP
	I2CONCLR=(1<<3);
	I2CONSET=(1<<4);
	//RETURN
	return temp;
	}








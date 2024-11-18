#include<lpc21xx.h>
#include"header.h"

extern CAN1 m;
extern char rxFlg;

void can_rx_handler(void) __irq{
    rxFlg=1;
    m.id=C1RID;
	m.dlc=((C1RFS >> 16) & 0x1f);
	m.rtr=((C1RFS >> 30) & 1);
	if(m.rtr == 0){//if data frame 
	  m.byteA=0;
	  m.byteB=0;
	  m.byteA=C1RDA;
	  m.byteB=C1RDB;
	  }
	  C1CMR=(1<<2);//release rx buf
	 
	  VICVectAddr=0;
	  }

void config_vic_and_Can(void){
   VICIntSelect=0;
   VICVectCntl0=26|(1<<5);
   VICVectAddr0=(u32)can_rx_handler;
   VICIntEnable=(1<<26);
   C1IER=1;//En CAN1 RX intr

   }
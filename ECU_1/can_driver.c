#include<lpc21xx.h>
#include"header.h"

#define RBS (C1GSR & 1)
void can1_rx(CAN1 *ptr){
     while(RBS ==0);
    ptr->id=C1RID;
	ptr->dlc=((C1RFS >> 16) &0x1f);
	ptr->rtr=((C1RFS >> 30)& 1);
	if(ptr->rtr == 0){//if data frame 
	  ptr->byteA=C1RDA;
	  ptr->byteB=C1RDB;
	  }
	  C1CMR=(1<<2);//release rx buf
  }

 unsigned int *ptr=(unsigned int *)0xE0038000;
  void can1_init(void){

    PINSEL1|=0x40000;//P0.25-->RDI
	VPBDIV=1;//PCLK-->60MHZ
	C1MOD=1;//RESET  MOD SELECT
	C1BTR=0X001C001D;//125 KBPS BAUD





	AFMR=0X2;
	C1MOD=0;//RELEASE RESET MODE
	}




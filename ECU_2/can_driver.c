#include<lpc21xx.h>
#include"header.h"

#define RBS (C2GSR & 1)
void can_rx(CAN *ptr){
     while(RBS ==0);
    ptr->id=C2RID;
	ptr->dlc=((C2RFS >> 16) &0x1f);
	ptr->rtr=((C2RFS >> 30)& 1);
	if(ptr->rtr == 0){//if data frame 
	  ptr->byteA=C2RDA;
	  ptr->byteB=C2RDB;
	  }
	  C1CMR=(1<<2);//release rx buf
  }
  
  
  #define TCS ((C2GSR >>3)&1)
  void ecu2_tx(CAN v){
  C2TID1=v.id;
  C2TFI1=(v.dlc << 16);
  if(v.rtr==0){ //data frame
     C2TDA1=v.byteA;
	 C2TDB1=v.byteB;
	 }
	 else//remote frame
	   C2TFI1|=(1<<30);
	  C2CMR=1|(1<<5);
	  while(TCS == 0);
	  }
 unsigned int *ptr=(unsigned int *)0xE0038000;
  void ecu2_init(void){

    PINSEL1|=0x14000;//P0.25-->RDI
	VPBDIV=1;//PCLK-->60MHZ
	C2MOD=1;//RESET  MOD SELECT
	C2BTR=0X001C001D;//125 KBPS BAUD





	AFMR=0X2;
	C2MOD=0;//RELEASE RESET MODE
	}




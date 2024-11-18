 #include<LPC21xx.H>
 #include"header.h"
 //#define sw3  ((IOPIN0>>16)&1)

 extern u8 hFlg,lFlg,rFlg;
 
 void EINT0H_handler(void) __irq{
	   hFlg=1;
	   EXTINT=1;
	   VICVectAddr=0;
	   }

  void EINT1L_handler(void) __irq{
	   lFlg=1;
	   EXTINT=2;
	   VICVectAddr=0;
	   }
 
  void EINT2R_handler(void) __irq{
	   rFlg=1;
	   EXTINT=4;
	   VICVectAddr=0;
	   }	   	   
	   

 void config_vic_for_eint(void){
     VICIntSelect=0;
	 
	 VICVectCntl1=14|(1<<5);             //H-IND sw-16	EXT0
	 VICVectAddr1=(u32)EINT0H_handler;
	 
	 VICVectCntl2=15|(1<<5);            //L-IND sw-14	EXT1
	 VICVectAddr2=(u32)EINT1L_handler;
	 
	 VICVectCntl3=16|(1<<5);            //r-IND sw-15	EXT2
	 VICVectAddr3=(u32)EINT2R_handler;
	 
	 VICIntEnable=1<<14|1<<15|1<<16;
	 }

void config_eint(void){
	PINSEL0|=0xA0000000;
	PINSEL1|=1;
	EXTMODE=0x7;
	EXTPOLAR=0;
}

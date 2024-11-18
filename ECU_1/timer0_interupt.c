#include"header.h"
 extern char tmrFlg;
void TMR1_handler(void) __irq{


	  tmrFlg^=1;
	T1IR=1; //ITR DESABLE
	VICVectAddr=0;
}

void config_vic_for_tmr1(void){
	VICIntSelect=0;
	VICVectCntl1=5|(1<<5);//SET
	VICVectAddr1=(u32)TMR1_handler;
	VICIntEnable=(1<<5);
}

void config_tmr1(unsigned int ms){
	T1PC=0;
	T1PR=15000-1;
	T1TC=0;
	T1TCR=1;
	T1MR0=ms; 
	T1MCR=3;
}




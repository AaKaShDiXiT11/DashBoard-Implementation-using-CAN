#include"header.h"
 extern char tmrFlg;
void TMR1_handler(void) __irq{


	  tmrFlg=1;
	T1IR=1; //ITR DESABLE
	VICVectAddr=0;
}

void config_vic_for_tmr1(void){
	VICIntSelect=0;
	VICVectCntl0=5|(1<<5);//SET
	VICVectAddr0=(u32)TMR1_handler;
	VICIntEnable=(1<<5);
}

void config_tmr1(unsigned int ms){
u32 a[]={15,60,30,15,15};
	T1PC=0;
	T1PR=a[VPBDIV]*1000-1;
	T1TC=0;
	T1TCR=1;
	T1MR0=ms; 
	T1MCR=3;
}




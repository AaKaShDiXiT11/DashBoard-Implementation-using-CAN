#include"header.h"
#include <lpc21xx.h>

void adc_init(void){
	PINSEL1 |= 0X15400000;
	ADCR=0X00200400;
}

u32 adc_read(u8 ch_num){
u32 result=0;

ADCR |=1<<ch_num;//channel select
ADCR |= (1<<24); // start conversion
while(((ADDR >> 31)&1)==0);//monitior done flag
ADCR ^= (1<<24);//stop adc
ADCR ^=  (1<<ch_num);//disselect channel
result=(ADDR >>6)& 0X3FF;
return result;
}



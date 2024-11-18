#include "header.h"
#include<lpc21xx.h>

void uart0_init(unsigned int baud){
	unsigned int result=0;
	int a[]={15,60,15,15};// CLOCK SPEED
	unsigned int pclk=a[VPBDIV]* 1000000 ;//SETTIND PCLK
	result = pclk/(16*baud);	// GETTING BAUDRATE WITH FORMULA
	PINSEL0 |= 5;//SETTING PIN FOR RX AND TX --> P0.0 AND P0.1
	U0LCR=0X83;	//SETTING LCR REG -->DLAB FLAG FOR BAUDRATE UNLOCK
	U0DLL= result & 0XFF;//LOWER NIBBLE TO DLL
	U0DLM = (result>> 8)& 0XFF;//HIGHER NIBBLE TO DLM
	U0LCR=3;   //SETTING LCR REG --> DLAB FALG FOR BAUDRATE LOCK
}

#define THRE ((U0LSR >> 5)&1) //DEFINE TO CHECK LSR REG --> 5TH BIT THRE FLAG FOR TX IS DONE OR NOT

void uart0_tx(unsigned char data){ 
   
    U0THR=data;	//DATA WRITTING IN THR REG (TX BUF)(8 BIT)
	while(THRE==0);	//WAITING TO TX THE DATA -->1 DATA TX /O DATA PRESENT
}

void uart0_tx_str(char * p){
while(*p){
U0THR=*p;
while(THRE==0);
p++;
}
}






//----- RX --------------------------------------------------------------------------------------------------------------------------
#define RDR (U0LSR &1) //DEFINE TO CHECK LSR REG --> 1ST BIT RDR FLAG FOR RX IS DONE OR NOT

unsigned char uart0_rx(void){
while(RDR ==0);//WAITING FOR DATA TO RECEIVE --> 1 DATA RECEIVED/0 DATA NOT PRESENT
return U0RBR;//READ THE DATA 
}

void uart0_rx_str(char *ptr,int max_bytes){
int i;
char ch;
	for(i=0;i<max_bytes;i++)
	{
        while(RDR ==0);
		ch=U0RBR;
        if(ch =='\b')
         i-=2;
		
		if(ch == 27)
		i++;

		if(ch !='\b' || ch != 27)
		 ptr[i]=ch;

		uart0_tx(ptr[i]);
		if(ptr[i]=='\r'){//if enter key
		break;
		}
	}
	ptr[i]='\0';
}




 void uart0_itoa(int n){
 int a[10],i;
 if(n==0)
 uart0_tx('0');
 if(n<0){
 uart0_tx('-');
 n=-n;
 }
 i=0;
 while(n){
 a[i]=n%10+48;
 n=n/10;
 i++;
 }
 for(i=i-1;i>=0;i--)
 uart0_tx(a[i]);
 }

 void uart0_float(float f){
 int num;
 if(f==0)
 uart0_tx_str("0.0");
 if(f<0){
 uart0_tx('-');
 f=-f;
 }
 num=f;
uart0_itoa(num);
uart0_tx('.');
num=(f-num)*10;
uart0_itoa(num);
}

	    
       
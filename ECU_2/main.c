#include"header.h"
#define L_ind 1<<17
#define H_ind 1<<18
#define R_ind 1<<19

char IND=0,hFlg=0,lFlg=0,rFlg=0,tmrFlg=0;
CAN v;
int L,R,H;
float res;

char s[16]="Et:__c BT 000\r";//10-L 11-H 12-R
 main(){

IODIR0=L_ind|H_ind|R_ind;
IOSET0=L_ind|H_ind|R_ind; 

ecu2_init();
config_vic_for_eint();
config_eint();
adc_init();
config_tmr1(500);
config_vic_for_tmr1();
	 uart0_init(9600);


while(1){

    if(lFlg){
		lFlg=0;
		v.id=0x203;
		v.dlc=1;
		v.rtr=0;
		L^=1;
		R=0;
		if(L){
		   v.byteA=1;
		   IOCLR0=L_ind;
		   IOSET0=R_ind;
			s[10]='1';//l on
			s[12]='0';//r off
		   }
		else{
		   v.byteA=0;
		    IOSET0=L_ind;
			s[10]='0';//l off
		   }
		ecu2_tx(v);	
	}

	    if(hFlg){
		hFlg=0;
		v.id=0x202;
		v.dlc=1;
		v.rtr=0;
		H^=1;
		if(H){
		   v.byteA=1;
		   IOCLR0=H_ind;
			s[11]='1';//h on
		   }
		else{
		   v.byteA=0;
		    IOSET0=H_ind;
			s[11]='0';//h off
		   }
		ecu2_tx(v);
		
	}

	    if(rFlg){
		rFlg=0;
		v.id=0x201;
		v.dlc=1;
		v.rtr=0;
		R^=1;
		L=0;
		if(R){
		   v.byteA=1;
		   IOCLR0=R_ind;
		   IOSET0=L_ind;
			s[12]='1';//r on
			s[10]='0';//l off
		   }
		else{
		   v.byteA=0;
		    IOSET0=R_ind;
			s[12]='0';//r off
		   }
		ecu2_tx(v);
		
	}

	if(tmrFlg){
	   tmrFlg=0;
		v.id=0x100;
		v.dlc=2;
		v.rtr=0;
		//v.byteA=adc_read(1);
		res=adc_read(1);
		res=res*3.3/1024;
		res=(res-0.5)/0.01;
		v.byteA=res;
		s[4]=v.byteA%10+48;
		s[3]=v.byteA/10+48;
		ecu2_tx(v);
	}

uart0_tx_str(s);
}



}



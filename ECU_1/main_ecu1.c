 #include<lpc21xx.h>
 #include"header.h"

  #define RLED 1<<16
  #define HLED 1<<15
  #define LLED 1<<14

 char IND,f=0,rxFlg=0,tmrFlg=0;
 CAN1 m;
TMR t;
void display(void);
void idCheck(int);
void setIND(int,int);
void setTime(void);
void displayTime(void);
char s[20]="ET:__c B:__% 000\r";//34-ET 9-10B l-13 h-14 r-15
 main(){
   
	IODIR0=RLED|HLED|LLED;
    can1_init();
	config_vic_and_Can();
	config_vic_for_tmr1();
	config_tmr1(1000);
	i2c_init();
	uart0_init(9600);
	uart0_tx_str("in rx node\r\n");
	while(1){
//	  can1_rx(&m);	 //polying

		 if(rxFlg){
		  if(m.rtr==0){
		  idCheck( m.id);
		  }
		  else{
		  uart0_tx_str("rx node:remote\r\n");
		  }
		  rxFlg=0;
		 }

	//   if(f){
	  if(IND&1){
	 // uart0_tx_str("R-LED-->on\r\n");
		  if(tmrFlg){
		  IOSET0=RLED;
		  s[15]='0';
		  }else{
		  IOCLR0=RLED;
				s[15]='1';
//		   uart0_tx_str("R-LED-->off\r\n");	
		   }
	  }
	  if(IND&2){
	  IOSET0=HLED;
			s[14]='0';
	  // uart0_tx_str("h-LED-->on\r\n");
	  }else{
	  IOCLR0=HLED;
			s[14]='1';
	 //  uart0_tx_str("h-LED-->off\r\n");
	  }

	  if(IND&4){
		  if(tmrFlg){
		  IOSET0=LLED;
				s[13]='0';
		  // uart0_tx_str("l-LED-->on\r\n");
		  }else{
		  IOCLR0=LLED;
				s[13]='1';
		  // uart0_tx_str("l-LED-->off\r\n");
		   }
	  }
	 // f=0;
			uart0_tx_str(s);
	  }
//	 }
	
	}


void display( ){
   lcd_cmd(0x01);
   //eng:__c BT <- ^ ->
  
   lcd_cmd(0x80);
   lcd_string(s);
   
   }


void displayTime(){
 //hh:mm:ss dd/mm
       t.sec= i2c_byt_red_frm(0xd0,0x0);
	   t.min= i2c_byt_red_frm(0xd0,0x1);
	   t.hr= i2c_byt_red_frm(0xd0,0x2);
	   t.amPm= (t.hr>>5)&1;
	   t.zone= (t.hr>>6)&1;
	   if(t.zone){
	   t.hr=t.hr&0x1f;
	   }
	   t.years=i2c_byt_red_frm(0xd0,0x6);;
       //t.Tyears= t.years==0?t.Tyears++:20;
       t.month=i2c_byt_red_frm(0xd0,0x5);
       t.date=i2c_byt_red_frm(0xd0,0x4);
       t.day=i2c_byt_red_frm(0xd0,0x3);
	  
	  lcd_cmd(0xc0);
	  
	   lcd_data((t.hr/0x10)+48);//0
	   lcd_data((t.hr%0x10)+48); //1
	   lcd_data(':');//2
	   lcd_data((t.min/0x10)+48);//3
	   lcd_data((t.min%0x10)+48);//4
	   lcd_data(':');//5
	   lcd_data((t.sec/0x10)+48);//6
	   lcd_data((t.sec%0x10)+48); //7
	   //////time zone//8
	   lcd_cmd(0xc9);
	   if(t.zone){//9
	   if(t.amPm){
	   lcd_string("P");
	   }else{
			lcd_string("A");
	   }
	   }
	   lcd_cmd(0xcb);
	   lcd_data((t.date/0x10)+48);//11
	   lcd_data((t.date%0x10)+48);//12
	   lcd_data('/');//13
	    lcd_data((t.month/0x10)+48);//14
	   lcd_data((t.month%0x10)+48);//15
//	   lcd_data('/');
//	   lcd_string("20");
//	    lcd_data((t.years/0x10)+48);
//	   lcd_data((t.years%0x10)+48);
//	   
//		lcd_cmd(0xcb);
//	   	switch(t.day){
//		 case 1: lcd_string("SUN");break;
//		 case 2: lcd_string("MON");break;
//		 case 3: lcd_string("TUE");break;
//		 case 4: lcd_string("WED");break;
//		 case 5: lcd_string("THU");break;
//		 case 6: lcd_string("FRI");break;
//		 case 7: lcd_string("SAT");break;
//		}
		}


void setTime(){
	lcd_cmd(0x01);
//	   set_sec();
//	   set_min();
//	   set_hr();
//	   set_years();
//	   set_months();
//	   set_date();
//	   set_day();
	lcd_cmd(0x01);
}

void idCheck(int id){
float res;
	int n;
  switch(id){
  case 0x100://ET
             res=((m.byteA&0x3ff) * 3.3 )/1023;	 //vout
			 res=(res-0.5)/0.01; //temp dc
	n=res;
	          s[4]=n%10+48;
		        s[3]=n/10+48;
        //     uart0_float(res);
			// uart0_tx_str("  :data ET \r\n");
			 break;
  case 0x200://BT
              res=((m.byteA&0x3ff) * 3.3 )/1023;	 //vout
//	     	   uart0_float(res);
//			 uart0_tx_str("  :data BV \r\n");
	
			 break;
  case 0x201://r-indi
				//uart0_tx_str("R-LED\r\n");
				 if(m.byteA	&0xff){
				 IND|=1;		// set 1st bit
				 IND=IND&(~(4));  
				 }else{
				 IND=IND&(~(1)); //clr 1st bit
				 }
				 f=1;
				 break;
  case 0x202: //h-indi
				//uart0_tx_str("H-LED\r\n");
				 if(m.byteA&0xff	){
				 IND|=2;  // set 2nd bit
				 
				 }else{
				 IND=IND&(~(2)); //clr 2nd bit
				 }
				 f=1;
				 break;
 case 0x203://l-indi
			//uart0_tx_str("L-LED\r\n");
				 if(m.byteA	&0xff){
				 IND|=4;  // set 3nd bit
				 IND=IND&(~(1));
				 }else{
				 IND=IND&(~(4)); //clr 3nd bit
				 }
				 f=1;
			  	 break;
 default:uart0_tx_str("Error\r\n");
			  
			  }

			  }
		 
		 	   
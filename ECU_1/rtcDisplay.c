
#include"rtcHeader.h"

 ///////DTOH///////
 u8 dtoh(u8 n){
	u8 t=0;
	t=(n/10)<<4;
	t|=(n%10);
	return t;
	}
 ///////SEC///////
 void set_sec(){

 u8 sec=0;
 lcd_cmd(0x80);
 lcd_string("SEC");
 while(1){
	if(SW1 == 0){
	 while(SW1 ==0);
		  sec++;
		  if(sec>=60)
		  sec=0;
		  }
		 
		 lcd_cmd(0xc0);
		 if(sec<10)
		 lcd_data('0');
		 lcd_int(sec);
		 
	if(SW2==0){
	while(SW2==0);
	break;
	 	 }
	}
	sec=dtoh(sec);
   i2c_byt_wrt_frm(0xd0,0x0,sec);
 }
 /////////MIN//////////
 void set_min(){
 u8 min=0;
 while(1){
	if(SW1 == 0){
	 while(SW1 ==0);
		  min++;
		  if(min>=60)
		  min=0;
		  }
		 lcd_cmd(0x80);
	     lcd_string("MIN");
		 lcd_cmd(0xc0);
		 if(min<10)
		 lcd_data('0');
		 lcd_int(min);
		 
	if(SW2==0){
	while(SW2==0);
	break;
	 	 }
	}
	min=dtoh(min);
   i2c_byt_wrt_frm(0xd0,0x1,min);
 }
 ////////////HR////////////
 void set_hr(){
 u8 hr,apm=0,mode;
 mode=set_mode();
if(mode){
 apm=set_apm();
 }
  hr=set_time(mode);
  mode=mode<<6;
  apm=apm<<5;
  hr=hr|apm|mode;
  
  i2c_byt_wrt_frm(0xd0,0x2,hr);
 }

 u8 set_time(u8 mode){
 	 u8 hr=1;
 while(1){
	if(SW1 == 0){
	 while(SW1 ==0);
		  hr++;
		  if(mode){
		  if(hr>=13)
		  hr=1;
		  }else{
		  	if(hr>=24)
		  hr=0;
		  }
		  }
		 lcd_cmd(0x80);
	     lcd_string("HR");
		 lcd_cmd(0xc0);
		 if(hr<10)
		 lcd_data('0');
		 lcd_int(hr);
		 
	if(SW2==0){
	while(SW2==0);
	break;
	 	 }
	}
	lcd_cmd(0x01);
	hr=dtoh(hr);
	return hr;
   
 }

 u8 set_mode(){
	   u8 zone= (i2c_byt_red_frm(0xd0,0x2)>>6)&1;
	   lcd_cmd(0x80);
       lcd_string("MODE");
	   while(1){
	   if(SW1==0){
	   while(SW1==0);
	   zone^=1;
	   }
	   lcd_cmd(0xc0);
	   if(zone){
		  lcd_string("12 hr mode");
		  }
		  else{
		  lcd_string("24 hr mode");
		  }
		if(SW2==0){
		while(SW2==0);
		break;
		}
	}
		lcd_cmd(0x01);
	return zone;
}
u8 set_apm(){
	   u8 apm= (i2c_byt_red_frm(0xd0,0x2)>>5)&1;
	   lcd_cmd(0x80);
       lcd_string("ZONE");
	   while(1){
	   if(SW1==0){
	   while(SW1==0);
	   apm^=1;
	   }
	   lcd_cmd(0xc0);
	   if(apm){
		  lcd_string("PM");
		  }
		  else{
		  lcd_string("AM");
		  }
		if(SW2==0){
		while(SW2==0);
		break;
		}
	}
		lcd_cmd(0x01);
	return apm;
}		   
///////////////DATE //////////
u32 year=0;
u8 months=0;
////////////////////
void set_years(){
u8 Tyears=20;
u8 years=0;
while(1){
   if(SW1 ==0){
     while(SW1 ==0);
	  years++;
	  if(years>=100){
	  Tyears++;
	  years=0;
	    }
	  }
	  lcd_cmd(0x80);
	     lcd_string("YEARS");
		 lcd_cmd(0xc0);
		 lcd_int(Tyears);
		 if(years<10)
		 lcd_data('0');
		 lcd_int(years);

		 	if(SW2==0){
            	while(SW2==0);
             	break;
	 	 }

	}
	year=years;
	years=dtoh(years);
   i2c_byt_wrt_frm(0xd0,0x6,years);
}

void set_months(){
u8 month=1;
lcd_cmd(0x01);
while(1){
   if(SW1 ==0){
     while(SW1 ==0);
	  month++;
	  if(month>=13){
	 
	  month=1;
	    }
	  }
	  lcd_cmd(0x80);
	     lcd_string("MONTHS");
		 lcd_cmd(0xc0);
		 if(month<10)
		 lcd_data('0');
		 lcd_int(month);

		 	if(SW2==0){
            	while(SW2==0);
             	break;
	 	 }

	}
	months=month;
	month=dtoh(month);
   i2c_byt_wrt_frm(0xd0,0x5,month);
}

void set_date(){
   u8 date=1;
   u32 lim;
    year=year+2000;
    lim= daysInMonth(months,year)+1;
  lcd_cmd(0x01);
 while(1){
	if(SW1 == 0){
	 while(SW1 ==0);
		  date++;
		  if(date>=lim)
		  date=1;
		  }
		 lcd_cmd(0x80);
	     lcd_string("DATE");
		 lcd_cmd(0xc0);
		 if(date<10)
		 lcd_data('0');
		 lcd_int(date);
		 
	if(SW2==0){
	while(SW2==0);
	break;
	 	 }
	}
	date=dtoh(date);
   i2c_byt_wrt_frm(0xd0,0x4,date);
 }
  ///////////////////DAY
  void set_day(){
 
   u8 day=1;
    lcd_cmd(0x01);
 while(1){
	if(SW1 == 0){
	 while(SW1 ==0);
		  day++;
		  if(day>=8)
		  day=1;
		  }
		 lcd_cmd(0x80);
	     lcd_string("DAY");
		 lcd_cmd(0xc0);
		switch(day){
		 case 1: lcd_string("SUN");break;
		 case 2: lcd_string("MON");break;
		 case 3: lcd_string("TUE");break;
		 case 4: lcd_string("WED");break;
		 case 5: lcd_string("THU");break;
		 case 6: lcd_string("FRI");break;
		 case 7: lcd_string("SAT");break;
		}
		 
	if(SW2==0){
	while(SW2==0);
	break;
	 	 }
	}
   i2c_byt_wrt_frm(0xd0,0x3,day);
 }

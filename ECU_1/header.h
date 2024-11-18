#include<lpc21xx.h>

//////// data types
typedef unsigned char u8;
typedef char s8;
typedef unsigned int u32;
typedef int s32;


//////// can--> data

typedef struct CAN1_MSG{
u32 id;
u32 byteA;
u32 byteB;
u8 dlc:4;
u8 rtr:1;
}CAN1;

/////// time -->struct

typedef struct timer {
  u8 hr:7;
  u8 min;
  u8 sec;
  u8 amPm:1;
  u8 zone:1;
  u8 years;
  u8 Tyears;
  u8 month:5;
  u8 date:6;
  u8 day:3;

  }TMR;

///////// can-->
 extern void can1_init(void);
 extern void can1_rx(CAN1 *ptr);


//////// uart-->
 extern void uart0_init(unsigned int);
 extern	void uart0_tx(unsigned char);
 extern	void uart0_tx_str(char * );
 extern	unsigned char uart0_rx(void);
 extern void uart0_rx_str(char *,int );
 extern void uart0_itoa(int);
 extern void uart0_float(float);

 ///////// adc-->
 extern void adc_init(void);
 extern u32 adc_read(u8 );

 ////////can-intr-->
 extern void config_vic_and_Can(void);

 ///////tmr1-intr-->
 extern void config_vic_for_tmr1(void);
 extern void config_tmr1(unsigned int );

 //////delay-->
 extern void delay_sec(u32 );
 extern void delay_ms(u32 );

 //////lcd-->
  extern void lcd_init(void);
 extern void lcd_cmd(u8);
 extern void lcd_data(u8);
 extern void lcd_cgram(void);
 extern void lcd_int(int);
 extern void lcd_string(char *);
 extern void lcd_cgram1(unsigned char *,unsigned char );
 
 ///////i2c-->
 extern void i2c_init(void);
extern void i2c_byt_wrt_frm(u8 ,u8 ,u8 );
extern u8 i2c_byt_red_frm(u8 ,u8 );


 //////funs-->
       

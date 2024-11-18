#include<lpc21xx.h>

//////// data types
typedef unsigned char u8;
typedef char s8;
typedef unsigned int u32;
typedef int s32;


//////// can--> data

typedef struct CAN_MSG{
u32 id;
u32 byteA;
u32 byteB;
u8 dlc:4;
u8 rtr:1;
}CAN;


///////can-->
extern void can_rx(CAN *);
extern void ecu2_tx(CAN );
extern void ecu2_init(void);

//////ext-int-->
void config_eint(void);
void config_vic_for_eint(void);


///////tmr1-intr-->
extern void config_vic_for_tmr1(void);
extern void config_tmr1(unsigned int );

///////// adc-->
extern void adc_init(void);
extern u32 adc_read(u8 );

////////uart0-->
 extern void uart0_init(unsigned int);
 extern	void uart0_tx(unsigned char);
 extern	void uart0_tx_str(char * );
 extern	unsigned char uart0_rx(void);
 extern void uart0_rx_str(char *,int );
 extern void uart0_itoa(int);
 extern void uart0_float(float);





#include<LPC21XX.H>
#include"header.h"
   #define SW1 ((IOPIN0 >> 14)&1)
   #define SW2 ((IOPIN0 >> 15)&1)


 extern void set_sec(void);
 extern void set_min(void);
 extern void set_hr(void);
 extern u8 dtoh(u8);
 extern void set_hr(void);
 extern u8 set_mode(void);
 extern u8 set_apm(void);
 extern u8 set_time(u8);
 extern void set_day(void);
 extern void set_date(void);
 extern void set_months(void);
 extern void set_years(void);
 extern int daysInMonth(int month,int year);
 extern int isLeapYear(int yr);

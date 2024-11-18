#include"rtcHeader.h"
///to check year is leap year

int isLeapYear(int yr){
if((yr%4==0 && yr % 100 ==0) || (yr % 400 == 0))
   return 1;
else 
   return 0;
   }

///to number of days in month
int daysInMonth(int month,int year){
  switch(month){
      case 1: case 3: case 5: case 7: case 8: case 10: case 12:
	     return 31;
	  case 4: case 6: case 9: case 11:
	     return 30;
	  case 2:
	     return (isLeapYear(year))? 29:28;
	  default: 
	  return -1;
	  }
	}

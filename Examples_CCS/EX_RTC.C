/////////////////////////////////////////////////////////////////////////
////                             EX_RTC.C                            ////
////                                                                 ////
////  This program reads and writes to an external Real Time Clock.  ////
////  It communicates to the user over the RS-232 interface.         ////
////                                                                 ////
////  Select either the ICD or your own RS232-to-PC connection       ////
////  for the text I/O.                                              ////
////                                                                 ////
////  This example will work with the PCB, PCM, PCD, and PCH         ////
////  compilers. The following conditional compilation lines are used////
////  to include a valid device for each compiler.  Change the       ////
////  device, clock and RS232 pins for your hardware if needed.      ////
/////////////////////////////////////////////////////////////////////////
////     (C) Copyright 1996,2003,2018 Custom Computer Services       ////
//// This source code may only be used by licensed users of the CCS  ////
//// C compiler.  This source code may only be distributed to other  ////
//// licensed users of the CCS C compiler.  No other use,            ////
//// reproduction or distribution is permitted without written       ////
//// permission.  Derivative programs created using this software    ////
//// in object code form are not restricted in any way.              ////
/////////////////////////////////////////////////////////////////////////

#if defined(__PCM__)
#include <16F887.h>
#elif defined(__PCB__)
#include <16F57.h>
#elif defined(__PCH__)
#include <18F4520.h>
#elif defined(__PCD__)
#include <30F2010.h>
#endif
#use delay(crystal=20mhz)
#use rs232(icd)                                  //Text through the ICD
//#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) //Text through the UART


#include <nju6355.c>

BYTE get_number() {
  char first,second;

  do {
    first=getc();
  } while ((first<'0') || (first>'9'));
  putc(first);
  first-='0';

  do {
    second=getc();
  } while (((second<'0') || (second>'9')) && (second!='\r'));
  putc(second);

  if(second=='\r')
    return(first);
  else
    return((first*10)+(second-'0'));
}

void set_clock(){
   BYTE day, mth, year, dow, hour, min;

   printf("\r\nPress ENTER after 1 digit answers.");
   printf("\r\nYear 20: ");
   year=get_number();
   printf("\r\nMonth: ");
   mth=get_number();
   printf("\r\nDay: ");
   day=get_number();
   printf("\r\nWeekday 1-7: ");
   dow=get_number();
   printf("\r\nHour: ");
   hour=get_number();
   printf("\r\nMin: ");
   min=get_number();

   rtc_set_datetime(day,mth,year,dow,hour,min);
   printf("\r\n\n");
}

void main() {
   char cmd;
   BYTE day, mth, year, dow, hour, min, sec;

   rtc_init();

   printf("\r\nPress S to change, D to display: ");

   do {
      cmd=getc()&0xdf;
   } while ((cmd!='D')&&(cmd!='S'));

   if(cmd=='S')
     set_clock();

   printf("\r\n");
   while (TRUE) {
      rtc_get_date( day, mth, year, dow);
      rtc_get_time( hour, min, sec );

      printf("%02u/%02u/%02u  %02u:%02u:%02u\r",mth,day,year,hour,min,sec);
      delay_ms(250);
   }
}

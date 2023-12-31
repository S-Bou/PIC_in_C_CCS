/////////////////////////////////////////////////////////////////////////
////                          EX_FLOAT.C                             ////
////                                                                 ////
////  This program shows input, output and standard operations with  ////
////  floating piont numbers.  I/O is RS232.                         ////
////                                                                 ////
////  Select either the ICD or your own RS232-to-PC connection       ////
////  for the text I/O.                                              ////
////                                                                 ////
////  This example will work with the PCM and PCH compilers.  The    ////
////  following conditional compilation lines are used to include a  ////
////  valid device for each compiler.  Change the device, clock and  ////
////  RS232 pins for your hardware if needed.                        ////
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
#elif defined(__PCH__)
#include <18F4520.h>
#elif defined(__MYPIC__)
#include <12F1612.h>
#endif

#use delay( crystal=20mhz )
#use rs232(icd)                                  //Text through the ICD
//#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) //Text through the UART

#include <stdlib.h>
#include <input.c>

void main() {
   long int l;
   float a, b;

   while(TRUE) {
      printf("\r\nEnter first number: ");
         a=get_float();

      printf("\r\nEnter second number: ");
         b=get_float();

      printf("\r\n\nA= %E\r\n", a);
      printf("B= %E\r\n", b);
      printf("\r\na + b = %E", a + b);
      printf("\r\na - b = %E", a - b);
      printf("\r\na * b = %E", a * b);
      printf("\r\na / b = %E\r\n", a / b);

      if(a <= b)
         printf("a<=b, ");
      else
         printf("a>b, ");
      if(a < b)
         printf("a<b, ");
      else
         printf("a>=b, ");
      if(a == b)
            printf("a==b\r\n");
      else
         printf("a!=b\r\n");

      l = (long int)a;
      printf("\r\n(long)a = %lu ", l);
      a = (float)l;
      printf("\r\n(float)(long)a = %E\r\n", a);
   }
}

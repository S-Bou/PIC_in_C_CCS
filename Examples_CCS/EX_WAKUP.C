/////////////////////////////////////////////////////////////////////////
////                          EX_WAKUP.C                             ////
////                                                                 ////
////  This example shows how to use the sleep function.  When the    ////
////  button is pushed, the processor goes into sleep mode.  When    ////
////  the button is released, the processor wakes up and continues   ////
////  counting.                                                      ////
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
#endif

#use delay(crystal=20mhz)
#use rs232(icd)                                  //Text through the ICD
//#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) //Text through the UART

// global flag to send processor into sleep mode
short sleep_mode;

// external interrupt when button pushed and released
#INT_EXT
void ext_isr() {
static short button_pressed = FALSE;

   if(!button_pressed)        // if button action and was not pressed
   {
      button_pressed=TRUE;    // the button is now down
      sleep_mode=TRUE;        // activate sleep
      printf("The processor is now sleeping.\r\n");
      ext_int_edge(L_TO_H);   // change so interrupts on release
   }
   else                       // if button action and was pressed
   {
      button_pressed=FALSE;   // the button is now up
      sleep_mode=FALSE;       // reset sleep flag
      ext_int_edge(H_TO_L);   // change so interrupts on press
   }
   if(!input(PIN_B0))         // keep button action sychronized wth button flag
      button_pressed=TRUE;
   delay_ms(100);             // debounce button
}

// main program that increments counter every second unless sleeping
void main()   {
   long counter;

   sleep_mode=FALSE;          // init sleep flag

   ext_int_edge(H_TO_L);      // init interrupt triggering for button press
   enable_interrupts(INT_EXT);// turn on interrupts
   enable_interrupts(GLOBAL);

   printf("\n\n");

   counter=0;                 // reset the counter
   while(TRUE)
   {
      if(sleep_mode)          // if sleep flag set
         sleep();             // make processor sleep
      printf("The count value is:  %5ld     \r\n",counter);
      counter++;              // display count value and increment
      delay_ms(1000);         // every second
   }
}

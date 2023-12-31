///////////////////////////////////////////////////////////////////////////
////                      EX_PCD_BOOTLOADER.C                          ////
////                                                                   ////
////  This program is an example standalone bootloader.                ////
////                                                                   ////
////  This program must be loaded into a target chip using a device    ////
////  programmer.  Afterwards this program may be used to load new     ////
////  versions of the application program.                             ////
////                                                                   ////
////  This bootloader is designed to detect a pushbutton low on reset. ////
////  It will then use the RS232 link to download a new program.       ////
////  Otherwise the application program is started.                    ////
////                                                                   ////
////  Use an RS232 link and the SIOW.EXE program to load a new HEX     ////
////  file into the target chip. See example EX_PCD_BOOTLOAD.C.        ////
////                                                                   ////
////  Uncomment the define BOOTLOADER_MODE2X to use an alternate       ////
////  bootloader that receives each line in the hex file twice and     ////
////  compares them before acknowledging the line and writing it to    ////
////  the target chip's memory.  This mode only works with the         ////
////  CCS_BOOTLOADER.exe program, add MODE2X to the command line to    ////
////  use this mode.                                                   ////
////                                                                   ////
////  The config bits will be write protected, in software, by the     ////
////  rom_modify() function.  To allow config bits to change then      ////
////  you need to #define ROM_WRITE_CAN_MODIFY_CONFIG_BITS             ////
////                                                                   ////
////  Select either the ICD or your own RS232-to-PC connection for the ////
////  text I/O.                                                        ////
////                                                                   ////
////  This example will work with the PCD compiler.  The               ////
////  following conditional compilation lines are used to include a    ////
////  valid device for the compiler.  Change the device, clock,        ////
////  push button, and RS232 pins for your hardware if needed.         ////
///////////////////////////////////////////////////////////////////////////
////     (C) Copyright 1996,2014,2018 Custom Computer Services         ////
//// This source code may only be used by licensed users of the CCS    ////
//// C compiler.  This source code may only be distributed to other    ////
//// licensed users of the CCS C compiler.  No other use,              ////
//// reproduction or distribution is permitted without written         ////
//// permission.  Derivative programs created using this software      ////
//// in object code form are not restricted in any way.                ////
///////////////////////////////////////////////////////////////////////////

// see explanation above
//#define ROM_WRITE_CAN_MODIFY_CONFIG_BITS

//These defines control the chip family that this program will compile for.
//The setup for 6 different chips, one from each of these chip families,
//is listed below.
//#define DSPIC33FJ
//#define DSPIC30F
//#define PIC24FJ
//#define PIC24FJ_REV2
#define PIC24HJ
//#define PIC24EP

#include <33FJ128GP706.h>
#use delay(crystal=12MHz)
#use rs232(icd)                      //Text through the ICD
//#use rs232(BAUD=9600,UART2,errors) //Text through the UART
#define PUSH_BUTTON PIN_B2


#define _bootloader
//#define BOOTLOADER_MODE2X

#include <pcd_bootloader.h>
#include <loader_pcd.c>

#org APPLICATION_START
void application(void)
{   
   while(TRUE);
}

void main(void)
{
   if(!input(PUSH_BUTTON))
   {
      delay_ms(140); // wait for PLL
      
      printf("\r\nBootloader Version 1.0\r\n");

      // Let the user know it is ready to accept a download
      printf("\r\nWaiting for download...");

      // Load the program
      load_program();
   }

   application();
}

#int_default
void isr(void)
{
   jump_to_isr(LOADER_END+5);
}


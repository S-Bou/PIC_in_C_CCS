/*
 * File:   main_hw.c
 * Author: bou
 *
 * Created on 24 de septiembre de 2023, 13:01
 */


#include <12f1612.h>

#fuses INTRC_IO, NOWDT
#use delay (clock = 16000000)
//#use standard_io(a)

void main(void) {
    
    //setup_oscillator(OSC_16MHZ);
    output_low(PIN_A2);
    int16 mytime = 100;
            
    while(TRUE){
        output_high(PIN_A2);
        delay_ms(mytime);
        output_low(PIN_A2);
        delay_ms(mytime);
    }//End while
}//End main

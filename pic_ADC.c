/* 
 * File:   aakhri.c
 * Author: Idris
 *
 * Created on December 31, 2019, 10:39 AM
 */

#include <stdlib.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
#include <xc.h>

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)



unsigned int pot_val;


void analog_config()     // configures analog input reg
{
 ADCON0= 0b10000001;      //Fosc=Fclk/32, channel 0 , converter on
 ADCON1= 0b10001000;      //left justified result, RA3 and RA2 set as reference voltages.
}

unsigned int analog_read()
{
    __delay_ms(2);  //cap discharge waiting time
    GO_nDONE=1;     //start conversion 
    while(GO_nDONE); //wait for completion for conversion
    return ((ADRESH<<8)+ADRESL);  //read and return  value
    
    
}

int main()
{   
   TRISA= 0xFF;    //set port A as input
   TRISB=0X00;     //set port B as output
   PORTB=0X00;     //clear output
   analog_config();
   
   while(1)
   {
       pot_val=analog_read();
       
       if(pot_val>=0  && pot_val<128)
           PORTB= 0b00000001;
                                                 //latch PORTB according to ADC values
       else if(pot_val>=128  && pot_val<256)
           PORTB= 0b00000011;
           
       else if(pot_val>=256  && pot_val<384)
           PORTB= 0b00000111;
       
       else if(pot_val>=384  && pot_val<512)
           PORTB= 0b00001111;
       
       else if(pot_val>=512  && pot_val<640)
           PORTB= 0b00011111;
       
       else if(pot_val>=640  && pot_val<768)
           PORTB= 0b00111111;
                   
       else if(pot_val>=768  && pot_val<896)
           PORTB= 0b01111111;
       else
           PORTB= 0b11111111;
   }    
   
}


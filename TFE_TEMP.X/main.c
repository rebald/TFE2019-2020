/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F45K50
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
//include "config.h"


// HC-SR Echo & Trigger pins are connected to RB0 & RB1 respectively

int valLM35;
float temperature;
float limite = 25;
int flag =0;
uint16_t distance;
/*
                         Main application
 */


__bit wait_sensor()
{
  uint16_t i = 0;
  TMR1H  = TMR1L = 0;   // reset Timer1
  TMR1ON = 1;           // enable Timer1 module
  while(!LATBbits.LATB0 && (i < 1000))
    i = ( TMR1H << 8 ) | TMR1L;   // read Timer1 and store its value in i
 
  if(i >= 1000)
    return 0;
 
  else
    return 1;
}
 
__bit get_distance(uint16_t *ticks)
{
  *ticks = 0;
  TMR1H  = TMR1L = 0;     // reset Timer1
 
  while( LATBbits.LATB0 && (*ticks < 23200) )
    *ticks = ( TMR1H << 8 ) | TMR1L;    // read Timer1 value
 
  TMR1ON = 0;   // disable Timer1 module
 
  if (*ticks >= 23200)
    return 1;
 
  else
    return 0;
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    OSCCON = 0x70;
    OSCTUNE = 0x40;
    
    PORTB  = 0;      // PORTB output is zero
    TRISB1 = 0;      // configure RB1 pin as input (HC-SR04 Echo pin)
 
    T1CON  = 0x10;        // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
    TMR1H  = TMR1L = 0;   // reset Timer1
    
    TRISDbits.TRISD0 = 0;
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 1;
    
    TRISAbits.TRISA0 = 1;
    __delay_ms(1000);   // wait 1 second
    ADC_SelectChannel(1);
    
    while (1)
    {
        if (flag == 0){
        valLM35 = ADC_GetConversion(1);
        temperature = (float)valLM35*(5/1024)*100;
         
        if(temperature>limite){
        LATDbits.LATD0 = 1;
        }
        flag =1;
        }
        if (flag == 1){
            // send 10us pulse to HC-SR04 Trigger pin
            LATBbits.LATB1 = 0;   // make sure trigger pin is low
            __delay_us(2);     // wait 2 us
            LATBbits.LATB1 = 1;   // now generate the 10 us pulse
            __delay_us(10);
            LATBbits.LATB1 = 0;
            
            // read pulse comes from HC-SR04 Echo pin
        if (wait_sensor())
        {    // if there is a response from the sensor

          uint16_t distance;

          if(get_distance(&distance))
          {       // if distance > 400 cm
             LATDbits.LATD0 = 1;
          }

          else
          {
            distance = distance / 58;     // calculate the actual distance in cm
          }

        }  // end if (wait_sensor())


      __delay_ms(200);  // wait 200 ms

      }
    }
}
/**
 End of File
*/
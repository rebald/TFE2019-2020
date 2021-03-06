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
#include "secret.c"

int valLM35;
float temperature;
float limite = 25;
float a = 0; //temperauture stocker pour comparaison

/*
                         Main application
 */


void RxData(uint8_t* pData, uint8_t dataLength, OpStatus_t status){};

void RxJoinResponse(bool status){};


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Initialize lorawan
    LORAWAN_GetDeviceEui; //obtenir le deviceEui (identifiant du module Lorawan)
    LORAWAN_Init(RxData, RxJoinResponse);
    
    /*
     3 identifiant necesaire � la connexion ABP*/
    LORAWAN_SetNetworkSessionKey(nwkSKey);
    
    LORAWAN_SetApplicationSessionKey(appSKey);
    
    LORAWAN_SetDeviceAddress(devAddr);
    
    //mode de connexion ABP obligatoire avec la plateforme enco/proximus
    
    int connected = LORAWAN_Join(ABP);
    
    OSCCON = 0x70;
    OSCTUNE = 0x40;
    
    TRISDbits.TRISD0 = 0;

    TRISAbits.TRISA0 = 1;
    
    ADC_SelectChannel(1);
    
    while (1)
    {
        LORAWAN_Mainloop();

       
        valLM35 = ADC_GetConversion(1);
        temperature = (float)valLM35*(5/1024)*100;
         
        if(temperature>limite){
        LATDbits.LATD0 = 1;
        }
        if(temperature =! a && connected){
            
            a= temperature;
            if(connected){
                LORAWAN_Send(UNCNF, 2, temperature, 2);
            }
        }
    }
}
/**
 End of File
*/
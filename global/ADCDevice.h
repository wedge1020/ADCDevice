/***
 *** Filename    : ADCDevice.h
 *** Description : C version of C++ Header file of Freenove ADC Module library.
 ***               Simplified version using global variable.
 *** Author      : Matthew Haas (based on code from www.freenove.com)
 *** modification: 2025/09/28
 ***
 **************************************************************************************/

#ifndef _ADCDEVICE_H
#define _ADCDEVICE_H

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////
//
// ADCDevice struct
//
struct ADCdevice
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ADCDevice attributes
    //
    int  _fd;
    int  address;
    int  cmd;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ADCDevice function pointers
    //
    int    (*analogRead)       (int);
    int    (*analogWrite)      (int);
    int    (*detectI2C)        (int);
};
typedef struct ADCdevice ADCDevice;

////////////////////////////////////////////////////////////////////////////////////////
//
// Declare global ADCDevice variable
//
ADCDevice *adc;

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
int        init_ADCDevice      ();
int        ADCDevice_detectI2C (int);
int        PCF8591_analogRead  (int); // has 4 ADC input pins, chn: 0-3
int        PCF8591_analogWrite (int); // has DAC function
int        ADS7830_analogRead  (int); // has 8 ADC inputs, chn: 0-7
int        ADS7830_analogWrite (int); 

#endif

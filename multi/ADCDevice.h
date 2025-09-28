/***
 *** Filename    : ADCDevice.h
 *** Description : C version of C++ Header file of Freenove ADC Module library.
 *** Author      : Matthew Haas (based on code from www.freenove.com)
 *** modification: 2025/09/27
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
    int  (*analogRead)    (struct ADCdevice *,  int);
    int  (*analogWrite)   (struct ADCdevice *,  int);
    int  (*detectI2C)     (struct ADCdevice **, int);
};
typedef struct ADCdevice ADCDevice;

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
int   init_ADCDevice      (ADCDevice **);
int   ADCDevice_detectI2C (ADCDevice **, int);

void  init_PCF8591        (ADCDevice **);      // PCF8591 default i2c addr: 0x48
int   PCF8591_analogRead  (ADCDevice *,  int); // has 4 ADC input pins, chn: 0-3
int   PCF8591_analogWrite (ADCDevice *,  int); // has DAC function

void  init_ADS7830        (ADCDevice **);      // ADS7830 default i2c addr: 0x4b
int   ADS7830_analogRead  (ADCDevice *,  int); // has 8 ADC inputs, chn: 0-7
int   ADS7830_analogWrite (ADCDevice *,  int); 

#endif

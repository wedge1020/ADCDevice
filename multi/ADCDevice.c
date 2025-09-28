/***
 *** Filename    : ADCDevice.c
 *** Description : C conversion of Freenove ADC Module library (C++)
 *** Author      : Matthew Haas (based on the code from: www.freenove.com)
 *** modification: 2025/09/27
 ***
 **************************************************************************************/

#include "ADCDevice.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize the ADCDevice library
//
int  init_ADCDevice (ADCDevice **adc)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int  status                = 1;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize wiringPi library
    //
    if (wiringPiSetup ()      == 0)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Set status to SUCCESS
        //
        status                 = 0;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Allocate memory and assign defaults
        //
        (*adc)                 = (ADCDevice *) malloc (sizeof (ADCDevice));
        (*adc) -> address      = 0;
        (*adc) -> detectI2C    = &ADCDevice_detectI2C;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // ADC chip detection: PCF8591
        //
        if ((*adc) -> detectI2C (&(*adc), 0x48))
        {
            (*adc) -> address  = 0x48;
            init_PCF8591 (&(*adc));       // If detected, initialize the PCF8591
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // ADC chip detection: ADS7830
        //
        else if ((*adc) -> detectI2C (&(*adc), 0x4b))
        {
            (*adc) -> address  = 0x4b;
            init_ADS7830 (&(*adc));      // If detected, initialize the ADS7830
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // ADC chip detection: neither module detected
        //
        else
        {
            fprintf (stderr, "[ERROR] No correct I2C address found!\n");
            fprintf (stderr,          "Please use the command 'i2cdetect -y 1' ");
            fprintf (stderr,          "to check the I2C address!\n");
            exit (1);
        }
    }

    return (status);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to detect which ADC module is in use
//
int ADCDevice_detectI2C (ADCDevice **adc, int addr)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int  _fd                           = 0;
    int  status                        = 0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize wiringPi I2C subsystem
    //
    (*adc) -> _fd                      = wiringPiI2CSetup (addr);   
    _fd                                = (*adc) -> _fd;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Check for failure of initializing wiringPi I2C subsystem
    //
    if (_fd                           <  0)
    {        
        fprintf (stderr, "[ERROR] address: 0x%x \n", addr);
        status                         = 0;
    } 

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Subsystem may have initialized, check for additional failure or success states
    //
    else
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Attempt writing to the device, checking for a failure
        //
        if (wiringPiI2CWrite (_fd, 0) <  0)
        {
            fprintf (stderr, "[ERROR] device not found at address 0x%x \n", addr);
            status                     = 0;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // If writing to the device was successful, we have our module
        //
        else
        {
            fprintf (stdout, "[ADCDevice] Found device at address 0x%x \n", addr);
            status                     = 1;
        }
    }

    return (status);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize the PCF8591 ADC module
//
void init_PCF8591 (ADCDevice **adc)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize ADCDevice attributes to PCF8591 settings
    //
    (*adc) -> address      = 0x48;
    (*adc) -> cmd          = 0x40;        // The default command for PCF8591 is 0x40.

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Attempt to detect the PCF8591
    //
    if ((*adc) -> detectI2C (&(*adc), (*adc) -> address))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Establish analogRead and analogWrite functions per detected ADC module
        //
        (*adc) -> analogRead   = &PCF8591_analogRead;
        (*adc) -> analogWrite  = &PCF8591_analogWrite;

        fprintf (stdout, "[ADCDevice] PCF8591 setup successful!\n");
    }
    else
    {
        fprintf (stderr, "[ERROR] PCF8591 setup FAILED!\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a PCF8591-compatible analogRead function (to be used with ADCDevice function
// pointer).
//
int PCF8591_analogRead (ADCDevice *adc, int chn)
{
    wiringPiI2CWrite (adc -> _fd, (adc -> cmd + chn));
    wiringPiI2CRead (adc -> _fd);
    wiringPiI2CWrite (adc -> _fd, (adc -> cmd + chn));
    return (wiringPiI2CRead (adc -> _fd));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a PCF8591-compatible analogWrite function (to be used with ADCDevice function
// pointer).
//
int PCF8591_analogWrite (ADCDevice *adc, int value)
{
    return (wiringPiI2CWriteReg8 (adc -> _fd, adc -> cmd, value));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// Initialize the ADS7830 ADC module
//
void init_ADS7830 (ADCDevice **adc)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialize ADCDevice attributes to ADS7830 settings
    //
    (*adc) -> address      = 0x4b;
    (*adc) -> cmd          = 0x84;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Attempt to detect the ADS7830
    //
    if ((*adc) -> detectI2C (&(*adc), (*adc) -> address))
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Establish analogRead and analogWrite functions per detected ADC module
        //
        (*adc) -> analogRead   = &ADS7830_analogRead;
        (*adc) -> analogWrite  = &ADS7830_analogWrite;

        fprintf (stdout, "[ADCDevice] ADS7830 setup successful!\n");
    }
    else
    {
        fprintf (stderr, "[ERROR] ADS7830 setup FAILED!\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a ADS7830-compatible analogRead function (to be used with ADCDevice function
// pointer).
//
int ADS7830_analogRead (ADCDevice *adc, int chn)
{
    wiringPiI2CWrite (adc -> _fd, adc -> cmd | (((chn << 2 | chn >> 1) & 0x07) << 4));
    return (wiringPiI2CRead (adc -> _fd));
}

////////////////////////////////////////////////////////////////////////////////////////
//
// a ADS7830-compatible analogWrite function (to be used with ADCDevice function
// pointer).
//
int ADS7830_analogWrite (ADCDevice *adc, int value)
{
    return (wiringPiI2CWriteReg8 (adc -> _fd, adc -> cmd, value));
}

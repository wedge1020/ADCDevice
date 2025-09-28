# ADCDevice

C ports of  Freenove ADCDevice C++ Library for accessing  the PCF8591 and
ADS7830 with wiringPi.

## Freenove

These ports are based on code  originally written in C++ for the Freenove
Raspberry Pi  electronics kits and  circuits presented in  their Tutorial
(specifically, their FNK0020 kit).

Source repository can be found at:

  * https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi

## C ports

### multi: de-OOP-ified multi-module capable ADCDevice

An "in  the spirit  of" port  of the original  ADCDevice C++  code, which
could support **multi**ple ADC modules in a program.

There is an "ADCDevice" struct making use of function pointers to provide
"a reasonably close" approximation of functionality.

A consequence of this  is that the functions have to  pass (by address) a
pointer to an instance of the ADCDevice.

### global: de-OOP-ified single module capable ADCDevice via global variable

The  de-OOP-ified implementation  above  gets a  lot cleaner-looking  if,
instead of the  ability to support multiple ADCDevice  instances, we only
allow for one, and make that instance a **global** variable.

The same selection of ADCDevice  modules is available, just we're locking
in to using exactly one per program.

This  will  likely be  an  acceptable  "average  case"  for a  number  of
utilizations, especially if following the Freenove Tutorial.

## Building

These  implementations,  like  their   Freenove  C++  ancestor,  build  a
shared-object  library  (libADCDevice.so)  which is  installed  with  the
`ADCDevice.h`  header  file,  into  the system  directories  where  these
resources are typically found.

Instead of a `build.sh` script, a UNIX Makefile is provided that does the
work of building and installing.

To build, simply run: `make`

To install, run: `sudo make install`

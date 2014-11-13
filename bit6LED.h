/********************
 bit6LED 
 6LEDs drive library for bitDuino using charlieplexing.

 2014/11/13 @maris_HY
********************/

#ifndef BIT6LED_h
#define BIT6LED_h

#include <inttypes.h>
#include <arduino.h>

void setLEDValue(byte led,byte value);
void TurnOn1LED(byte led);
void TurnOffAllLEDs();
void init6LED(byte pin0,byte pin1,byte pin2);
void start6LED();
void stop6LED();

#endif

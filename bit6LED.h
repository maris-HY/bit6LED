#ifndef BIT6LED_h
#define BIT6LED_h

#include <inttypes.h>
#include <arduino.h>

#define BRL_R	0
#define BRL_G	1
#define BRL_B	2

void setLEDValue(byte led,byte value);
void TurnOn1LED(byte led);
void TurnOffAllLEDs();
void init6LED(byte pin0,byte pin1,byte pin2);
void start6LED();
void stop6LED();

#endif

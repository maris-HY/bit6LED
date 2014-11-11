
#include "bit6LED.h"
#include "wiring_private.h"

volatile byte pwmCount = 0;
volatile byte pwmLowPin = 0;
byte LED_value[6];
byte LED_pin[3];

#if defined(__AVR_ATtiny13__) || defined(__AVR_ATtiny10__)
ISR(TIM0_OVF_vect)
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) 
ISR(TIMER1_OVF_vect)
#endif
{
  byte i;
  byte led;
  byte pinHIGH;
  if (pwmCount == 0){
    for(i=0;i<3;i++){
      pinMode(LED_pin[i],INPUT);
    }
    pwmLowPin++;
    if(pwmLowPin>2){
      pwmLowPin=0;
    }
    pinMode(LED_pin[pwmLowPin],OUTPUT);
    digitalWrite(LED_pin[pwmLowPin],LOW);
  }

  for(i=0;i<2;i++){
    led = (pwmLowPin<<1)+i;
    pinHIGH = LED_pin[i+((i<pwmLowPin)?0:1)];
    if((pwmCount == 0) && (LED_value[led] > 0)){
      pinMode(pinHIGH,OUTPUT);
      digitalWrite(pinHIGH,HIGH);
    } else if(LED_value[led] == pwmCount){
      pinMode(pinHIGH,INPUT);
    }
  } 
  pwmCount++;
}

void setLEDValue(byte led,byte value){
  LED_value[led] = value;
}

void TurnOn1LED(byte led){
  byte pinLOW = (led >> 1);
  byte pinHIGH = led - (pinLOW << 1);
  if(pinHIGH >= pinLOW){
    pinHIGH++;
  }
  TurnOffAllLEDs();
  pinMode(LED_pin[pinLOW] ,OUTPUT);digitalWrite(LED_pin[pinLOW ],LOW );
  pinMode(LED_pin[pinHIGH],OUTPUT);digitalWrite(LED_pin[pinHIGH],HIGH);
}

void TurnOffAllLEDs(){
  pinMode(LED_pin[0],INPUT);
  pinMode(LED_pin[1],INPUT);
  pinMode(LED_pin[2],INPUT);
}

void init6LED(byte pin0,byte pin1,byte pin2){
  LED_pin[0] = pin0;
  LED_pin[1] = pin1;
  LED_pin[2] = pin2;
  TurnOffAllLEDs();
//  start6LED();
}

void start6LED(){
  byte i;
  for(i = 0;i < 6;i++){
    LED_value[i] = 0;
  }
#if defined(__AVR_ATtiny10__)
  TCCR0A = (1 << WGM00);
  TCCR0B = ((1 << WGM02) | (1 << CS00));
  
  // enable timer 0 overflow interrupt
  sbi(TIMSK0, TOIE0);

#elif defined(__AVR_ATtiny13__)
  // set timer 0 prescale factor to None
  TCCR0B = 0;
  sbi(TCCR0B, CS00);
  // enable timer 0 overflow interrupt
  sbi(TIMSK0, TOIE0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) 
  // set timer 1 prescale factor to None
  TCCR1 = 0;
  sbi(TCCR1, CS00);
  // enable timer 0 overflow interrupt
  sbi(TIMSK, TOIE1);
#endif
  sei();
}

void stop6LED(){
#if defined(__AVR_ATtiny10__)
  cbi(TIMSK0, TOIE0);
#elif defined(__AVR_ATtiny13__)
  // disable timer 0 overflow interrupt
  cbi(TIMSK0, TOIE0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) 
  // set timer 1 prescale factor to None
  // disenable timer 0 overflow interrupt
  cbi(TIMSK, TOIE1);
#endif
}



#include <Arduino.h>

//Demo for timers and PWM
//Use timer0, 8 Bit
//PWM frequency is 1Khz
//I need CPS = 64



void setup() {
  // put your setup code here, to run once:
// 
TCCR1A = 0b00100011;
TCCR1B = 0b00011001;
OCR1A=7980;
OCR1B = 3989;
DDRB |= (1<<6);



}

void loop() {
  // // put your main code here, to run repeatedly:
  // OCR0B++;
  // delay(500);
  // if (OCR0B == OCR0A)
  //   OCR0B=0;

}


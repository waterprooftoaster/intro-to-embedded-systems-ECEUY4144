#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DDRD |= (1 << DDD0); 
  TCCR0A = 0b00100011;
  TCCR0B = 0b00001011;
  OCR0A = 125;
  DDRD &= ~(1 << 6); 
  ADMUX = 0b01000001;
  ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 <<
  ADATE) | (1 << ADPS2) | (1 << ADPS1);
  ADCSRB = 0b000100000;
  DIDR2 |= (1 << ADC9D);
}

void loop() {
  // put your main code here, to run repeatedly:
  float aval;
  long x;
  unsigned short *ADCData;
  unsigned short ADCVal;
  ADCData=(unsigned short *)0x78;
  ADCVal=(*ADCData & 0xFFC0) >> 6;
  float fADCVal; 
  x = millis();
  aval = abs(3 * sin(2 * 3.141592654 * x /
  1000));
  OCR0B = (int)(aval * 125 / 3);
  ADCVal = ADC;
  fADCVal = ((float)ADCVal / 1023.0) * 3.0;
  Serial.print(abs(aval));
  Serial.print(" ");
  Serial.println(fADCVal);
  delay(1);
}
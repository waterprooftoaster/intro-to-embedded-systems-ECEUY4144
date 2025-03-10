#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

void initADC();
void initPWM();
uint16_t getADC();
void adjustLED(uint16_t val);

void setup() {
  Serial.begin(9600);
  initADC();
  initPWM();
  DDRB |= (1 << DDB7);
}

void loop() {
  uint16_t sensorVal = getADC();
  adjustLED(sensorVal);
  delay(500);
}

void initADC() {
  ADMUX = 0;
  ADMUX |= (1 << REFS1) | (1 << REFS0);
  ADMUX |= (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (0 << MUX0);
  ADCSRA = 0;
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRB = 0;
}

void initPWM() {
  TCCR1A = 0;
  TCCR1A |= (1 << COM1C1) | (0 << COM1C0);
  TCCR1A |= (1 << WGM11) | (0 << WGM10);
  TCCR1B = 0;
  TCCR1B |= (1 << WGM13) | (1 << WGM12);
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  ICR1 = 999;
  OCR1C = 0;
}

uint16_t getADC() {
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

void adjustLED(uint16_t val) {
  const uint16_t MAX_ADC = 1023;
  uint16_t duty = (uint16_t)(((uint32_t)val * 999) / MAX_ADC);
  OCR1C = duty;
}

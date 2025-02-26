#include <Arduino.h>

#define MAX_DUTY_CYCLE 65535

void setup() {
  DDRB |= (1 << PB5);

  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);

  ICR1 = 19999;
  OCR1A = ICR1 / 2;
}

void loop() {
  static uint8_t direction = 0;
  static uint16_t dutyCycle = 0;

  if (direction == 0) {
    dutyCycle += 500;
    if (dutyCycle >= MAX_DUTY_CYCLE) {
      direction = 1;
    }
  } else {
    dutyCycle -= 500;
    if (dutyCycle == 0) {
      direction = 0;
    }
  }

  OCR1A = (dutyCycle * ICR1) / MAX_DUTY_CYCLE;
  delay(100);
}

#include <stdint.h>
#include <Arduino.h>
/*
=====================================================
Part 1:
-----------------------------------------------------
void adc_init(void)
{
    ADMUX = (1 << REFS0); // Set ADC multiplexer: use AVcc as reference
    ADCSRA = (1 << ADEN) | 7; // Enable ADC and set prescaler to 7 (ADPS2:0 = 0b111)
}

int readAdc(char chan)
{
    ADMUX = (1 << REFS0) | (chan & 0x0F);  // Select AVcc reference and ADC channel (lower 4 bits of chan)
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait until conversion completes (ADSC becomes 0)
    return ADCW; // ADCW holds the 10-bit conversion result (from ADCL and ADCH)
}
*/

/*
=====================================================
Part 2:
-----------------------------------------------------
*/
void adc_init(void)
{
  volatile uint8_t *admux = (volatile uint8_t *)0x7C;
  volatile uint8_t *adcsra = (volatile uint8_t *)0x7A;
  *admux = (1 << 6);
  *adcsra = (1 << 7) | 7;
}

int readAdc(char chan)
{
  volatile uint8_t *admux = (volatile uint8_t *)0x7C;
  volatile uint8_t *adcsra = (volatile uint8_t *)0x7A;
  volatile uint16_t *adcw = (volatile uint16_t *)0x78;
  *admux = (1 << 6) | (chan & 0x0F);
  *adcsra |= (1 << 6);
  while (*adcsra & (1 << 6))
    ;
  return *adcw;
}
s
/*
=====================================================
Part 3:
-----------------------------------------------------
*/
#define THRESHOLD_ON 210
#define THRESHOLD_OFF 200

void setup() {
  adc_init();
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}

void loop() {
  int adcValue = readAdc(0);
  static bool ledState = false;
  if (!ledState && adcValue > THRESHOLD_ON) {
    digitalWrite(4, HIGH);
    ledState = true;
  }
  else if (ledState && adcValue < THRESHOLD_OFF) {
    digitalWrite(4, LOW);
    ledState = false;
  }
  delay(50);
}
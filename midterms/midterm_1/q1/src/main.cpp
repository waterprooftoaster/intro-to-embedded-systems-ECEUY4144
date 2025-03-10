#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

void initADC();
void initPWM();
uint16_t fetchADC();
void setPWMRate(float temp);

int main(void) {
    initADC();
    initPWM();
    DDRB |= (1 << DDB7);

    while (1) {
        uint16_t sensorVal = fetchADC();
        float millivolts = (sensorVal * 5000.0) / 1024.0;
        float tempC = (millivolts - 500.0) / 10.0;
        setPWMRate(tempC);
    }
    return 0;
}

void initADC() {
    ADMUX = 0;
    ADMUX |= (0 << REFS1) | (1 << REFS0);
    ADMUX |= (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);
    ADCSRA = 0;
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0);
    ADCSRB = 0;
    DIDR0 |= (1 << ADC0D);
}

void initPWM() {
    TCCR1A = 0;
    TCCR1A |= (1 << COM1C1) | (0 << COM1C0);
    TCCR1A |= (1 << WGM11) | (0 << WGM10);
    TCCR1B = 0;
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
    ICR1 = 488;
    OCR1C = ICR1 / 2;
}

uint16_t fetchADC() {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

void setPWMRate(float temp) {
    uint16_t topLimit;

    if (temp <= 0) {
        topLimit = 488;
    } 

    if (temp >= 50) {
        topLimit = 9;
        ICR1 = topLimit;
        OCR1C = topLimit;
        return;

    } else {
        float freq;

        if (temp <= 25) {
            freq = 2.0 + (temp / 25.0) * 2.0;
        } 
        
        else {
            float norm = (temp - 25.0) / 25.0;
            freq = 4.0 + norm * norm * 96.0;
        }

        topLimit = (uint16_t)((1000000.0 / (1024.0 * freq)) - 1);
        if (topLimit > 65535) topLimit = 65535;
    }
    
    ICR1 = topLimit;
    OCR1C = topLimit / 2;
}

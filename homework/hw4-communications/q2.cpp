#include <avr/io.h>

void USART1_init(void) {
    UBRR1H = 0;        
    UBRR1L = 8;        
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
    UCSR1B = (1 << RXCIE1) | (1 << UDRIE1) | (1 << RXEN1);
    UCSR1A = 0;
}
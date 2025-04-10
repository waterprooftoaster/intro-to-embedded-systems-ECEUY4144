#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//function prototypes
void USART1_init(void);
void TransmitString(const char *str, uint8_t length);
uint8_t GetNextReceivedByte(void);

//global variables
volatile uint8_t receivedByte = 0;
volatile uint8_t newDataAvailable = 0;

// USART1 receive complete ISR
ISR(USART1_RX_vect) {
    receivedByte = UDR1;
    newDataAvailable = 1;
}

//initialize USART1 with settings from q2.
void USART1_init(void) {
  
    //set baud rate
    UBRR1H = 0;
    UBRR1L = 8;

    //frame format
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

    //enable receiver + disable transmitter + enable RX 
    UCSR1B = (1 << RXCIE1) | (1 << UDRIE1) | (1 << RXEN1);
    
    // Normal speed operation and no multi-processor mode.
    UCSR1A = 0;
}


void TransmitString(const char *str, uint8_t length) {
    uint8_t i;
    for (i = 0; i < length; i++) {
        while (!(UCSR1A & (1 << UDRE1))) {} //wait
        UDR1 = str[i];
    }
}

//clears the new data flag
uint8_t GetNextReceivedByte(void) {
    while (!newDataAvailable) {} //wait
    newDataAvailable = 0;
    return receivedByte;
}

int main(void) {
    // initialize USART1
    USART1_init();
    
    // wnable global interrupts
    sei();
    
    while (1) { //main loop
        uint8_t rxByte = GetNextReceivedByte();
      
        switch (rxByte) {
            case '1':
                TransmitString("One\n", 4);
                break;
            case '2':
                TransmitString("Two\n", 4);
                break;
            default:
                TransmitString("Default\n", 8);
                break;
        }
        
        _delay_ms(10);
    }
    
    return 0;
}

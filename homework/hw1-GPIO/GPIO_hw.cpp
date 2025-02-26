//Q1
/*
To set a GPIO pin, I need to use the Data Register to write output values to the pin and the Direction Register (DIR) to configure the pin as an output.
*/

//Q2
/*
Set a Bit: REG |= 0x01 sets the least significant bit.
Clear a Bit: REG &= ~0x01
Toggle a Bit: REG ^= 0x01 toggles the least significant bit.
Test a Bit: REG & 0x01
*/

//Q3
/*
D0 and D1
D2 and D3
D6, D9, D10
D12
 */

//Q4
/*a.
Pin 2: Connects to LED1 (LSB)
Pin 3: Connects to LED2
Pin 4: Connects to LED3 (MSB)
*/


//c
void setup() {
    pinMode(2, OUTPUT);  // Set pin 2 as output
    pinMode(3, OUTPUT);  // Set pin 3 as output
    pinMode(4, OUTPUT);  // Set pin 4 as output
}

//d
void loop() {
    for(int num = 0; num < 8; num++) {
        digitalWrite(2, num & 0x01);       // Set LSB LED1
        digitalWrite(3, (num >> 1) & 0x01); // Set LED2
        digitalWrite(4, (num >> 2) & 0x01); // Set MSB LED3
        delay(1000);                        // Wait for 1 second
    }
    // Reset from 111 to 000
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(1000);                          // Wait for 1 second
}

// Q5
void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, INPUT_PULLUP);  // Start/Stop button
    pinMode(6, INPUT_PULLUP);  // Reset button
}
#include <Arduino.h>
/*
void MyDelay (unsigned long mSecondsApx);

void setup() {
    unsigned char portDDRC;
    portDDRC = (unsigned char) 0x27;
    portDDRC |= 0x80;
    Serial.begin(9600);
}

void loop() {
  digitalWrite(13, HIGH);
  Serial.println("LED ON");
  delay(1000);
  digitalWrite(13, LOW);
  Serial.println("LED OFF");
  delay(1000);

  //previous task
    unsigned char *portC;
    portC = (unsigned char *) 0x28;

    *portC |= 0x80;
    MyDelay(500);
    *portC &= 0x7F;
    MyDelay(500);

    MyDelay(1000);

    for (int i = 0; i < 2; i++) {
        *portC |= 0x80;
        MyDelay(500);
        *portC &= 0x7F;
        MyDelay(500);
    }

    MyDelay(1000);

    for (int i = 0; i < 3; i++) {
        *portC |= 0x80;
        MyDelay(500);
        *portC &= 0x7F;
        MyDelay(500);
    }

    MyDelay(1000);
}

void MyDelay (unsigned long mSecondsApx) {
    volatile unsigned long i;
    unsigned long endTime = 250 * mSecondsApx;

    for (i = 0; i < endTime; i++);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

void MyDelay(unsigned long mSecondsApx);
void setup ()
{
unsigned char *portDDRC;
portDDRC = (unsigned char *) 0x27;
*portDDRC |= 0x80;
}
void loop ()
{
unsigned char *portC;
portC = (unsigned char *) 0x28;
*portC |= 0x80;
MyDelay(1000);
*portC &= 0x7F;
MyDelay (1000);
}
 
void MyDelay (unsigned long mSecondsApx)
{
volatile unsigned long i;
unsigned long endTime = 200 * mSecondsApx;
for (i = 0; i < endTime; i++);
}

void NewDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80;
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x28;
    *portC |= 0x80;
    NewDelay(1000);
    *portC &= 0x7F; // Corrected from %= to &= for bitwise AND operation
    NewDelay(1000);
}

void NewDelay(unsigned long mSecondsApx) {
    volatile unsigned long i;
    unsigned long endTime = 250 * mSecondsApx;
    for (i = 0; i < endTime; i++);
}

void NewDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80;  // Set the 7th bit of DDR C to 1 (configuring pin C7 as output)
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x28;
    *portC |= 0x80;  // Set pin C7 high (turn LED on)
    NewDelay(50);  // Wait for 1000 ms (1 second)
    *portC &= 0x7F;  // Clear pin C7 (turn LED off)
    NewDelay(50);  // Wait for 1000 ms (1 second)
}

void NewDelay(unsigned long mSecondsApx) {
    volatile unsigned long i, j, k;
    unsigned long endTime = 250 * mSecondsApx;  // Corrected the multiplier to 1000 for proper ms calculation
    for (i = 0; i < endTime; i++) {
      j = 10;
      do{
        j = j - i;
        k = i/j;
      } while (k>0);    
      }
}

*/

void NewDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80;  // Set the 5th bit of DDR C to 1 (configuring pin C5 as output)
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x28;
    *portC |= 0x80;  // Set pin C5 high (turn LED or similar device on)
    NewDelay(1000);  // Increased delay to make the toggle noticeable
    *portC &= 0x7F;  // Corrected bitmask to clear the 5th bit of Port C (turn LED off)
    NewDelay(1000);  // Increased delay to maintain consistent on-off pattern
}

void NewDelay(unsigned long mSecondsApx) {
    volatile unsigned long i, j;
    unsigned long endTime = 250 * mSecondsApx;  // Adjusted multiplier to 1000 for proper milliseconds delay
    i = j = 0;
    while (j == 0) {  // Corrected equality check for while condition
        i++;
        if (i == endTime) {  // Corrected equality check in if condition
            j = 1;
        }
    }
}

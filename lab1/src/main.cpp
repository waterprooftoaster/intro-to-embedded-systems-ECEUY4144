#include <Arduino.h>
void MyDelay (unsigned long mSecondsApx);

void setup() {
    unsigned char portDDRC;
    portDDRC = (unsigned char) 0x27;
    portDDRC |= 0x80;
}

void loop() {
    unsigned charportC;
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
        portC &= 0x7F;
        MyDelay(500);
    }

    MyDelay(1000);
}

void MyDelay (unsigned long mSecondsApx) {
    volatile unsigned long i;
    unsigned long endTime = 250 mSecondsApx;

    for (i = 0; i < endTime; i++);
}


 
// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

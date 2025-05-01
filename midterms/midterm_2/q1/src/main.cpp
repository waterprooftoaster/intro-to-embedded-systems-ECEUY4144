#include <Arduino.h>
#include <Wire.h>

// I²C address and register definitions
#define MAX30100_ADDRESS      0x57
#define REG_INT_STATUS        0x00  // Interrupt Status register
#define REG_INT_ENABLE        0x01  // Interrupt Enable register
#define REG_FIFO_DATA         0x05  // FIFO Data register
#define REG_MODE_CONFIG       0x06  // Mode Configuration register

// Bit masks
#define ENB_SPO2_RDY          (1 << 4)  // Enable only SpO₂ Ready interrupt
#define MODE_SPO2             0x03      // MODE[2:0]=011 for SpO₂

// Microcontroller I/O pins
static const uint8_t INT_PIN = 2;        // Must be an external interrupt pin (INT0)
static const uint8_t LED_PIN = LED_BUILTIN;

// Flag set by ISR when new SpO2 sample is ready
volatile bool dataReady = false;

// Forward declarations
void setupSensor();
void clearInterrupt();
void getData(uint16_t &red, uint16_t &ir);

// ISR: triggered when MAX30100 pulls INT low
void onDataReady() {
    dataReady = true;
}

// Configure MAX30100: enable SpO₂ interrupt, set SpO2 mode
void setupSensor() {
    // 1) Enable only the SpO₂ Ready interrupt
    Wire.beginTransmission(MAX30100_ADDRESS);
    Wire.write(REG_INT_ENABLE);
    Wire.write(ENB_SPO2_RDY);
    Wire.endTransmission();

    // 2) Set mode to SpO₂ only (others disabled)
    Wire.beginTransmission(MAX30100_ADDRESS);
    Wire.write(REG_MODE_CONFIG);
    Wire.write(MODE_SPO2);
    Wire.endTransmission();
}

void getData(uint16_t &red, uint16_t &ir) {
    // Read 4 bytes from FIFO_DATA: IR[15:8], IR[7:0], RED[15:8], RED[7:0]
    Wire.beginTransmission(MAX30100_ADDRESS);
    Wire.write(REG_FIFO_DATA);
    Wire.endTransmission(false);             // repeated start
    Wire.requestFrom(MAX30100_ADDRESS,  (uint8_t)4);

    if (Wire.available() == 4) {
        uint8_t buf[4];
        for (uint8_t i = 0; i < 4; i++) buf[i] = Wire.read();
        ir  = (uint16_t(buf[0]) << 8) | buf[1];
        red = (uint16_t(buf[2]) << 8) | buf[3];
    } else {
        // Incomplete read → set to zero to flag error
        ir = red = 0;
    }
}

// Clear MAX30100 interrupt by reading INT_STATUS
void clearInterrupt() {
    Wire.beginTransmission(MAX30100_ADDRESS);
    Wire.write(REG_INT_STATUS);
    Wire.endTransmission(false);
    Wire.requestFrom(MAX30100_ADDRESS, (uint8_t)1);
    if (Wire.available()) Wire.read();
}

void setup() {
    // Initialize debug serial port
    Serial.begin(115200);

    // Initialize I²C bus
    Wire.begin();

    // Configure onboard LED and interrupt pin
    pinMode(LED_PIN, OUTPUT);
    pinMode(INT_PIN, INPUT_PULLUP);

    // Configure sensor registers
    setupSensor();

    // Attach ISR on falling edge (INT is open-drain, active-low)
    attachInterrupt(digitalPinToInterrupt(INT_PIN), onDataReady, FALLING);

    Serial.println("MAX30100 SpO₂ interface initialized.");
}

void loop() {
    if (dataReady) {
        dataReady = false;

        uint16_t redSample, irSample;
        getData(redSample, irSample);

        // Output readings
        Serial.print("IR: ");  Serial.print(irSample);
        Serial.print("\tRED: "); Serial.println(redSample);

        // Blink onboard LED
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));

        // Clear the interrupt flag in the sensor
        clearInterrupt();
    }
}

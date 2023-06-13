#include <Arduino.h>

// PZEM-004T 1
#define RX_PIN_1 16   // ESP32 RX pin connected to PZEM-004T 1 TX pin
#define TX_PIN_1 17   // ESP32 TX pin connected to PZEM-004T 1 RX pin

// PZEM-004T 2
#define RX_PIN_2 18   // ESP32 RX pin connected to PZEM-004T 2 TX pin
#define TX_PIN_2 19   // ESP32 TX pin connected to PZEM-004T 2 RX pin

// Serial ports
HardwareSerial pzemSerial1(1);  // Create a HardwareSerial instance for PZEM-004T 1
HardwareSerial pzemSerial2(2);  // Create a HardwareSerial instance for PZEM-004T 2

void setup() {
  Serial.begin(9600);
  pzemSerial1.begin(9600, SERIAL_8N1, RX_PIN_1, TX_PIN_1);  // Set the baud rate and pin configuration for PZEM-004T 1
  pzemSerial2.begin(9600, SERIAL_8N1, RX_PIN_2, TX_PIN_2);  // Set the baud rate and pin configuration for PZEM-004T 2
}

void loop() {
  // Access PZEM-004T 1
  if (pzemSerial1.available()) {
    // Read data from PZEM-004T 1
    while (pzemSerial1.available()) {
      char data = pzemSerial1.read();
      Serial.print(data);
    }
    Serial.println();
  }
  pzemSerial1.write(0xB1);  // Send command to PZEM-004T 1 to read voltage and current

  // Access PZEM-004T 2
  if (pzemSerial2.available()) {
    // Read data from PZEM-004T 2
    while (pzemSerial2.available()) {
      char data = pzemSerial2.read();
      Serial.print(data);
    }
    Serial.println();
  }
  pzemSerial2.write(0xB1);  // Send command to PZEM-004T 2 to read voltage and current

  delay(1000);  // Wait for the response from PZEM-004T devices
}
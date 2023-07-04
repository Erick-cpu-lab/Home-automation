#include <SoftwareSerial.h>

#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial bluetoothSerial(RX_PIN, TX_PIN);

const int bulbPins[] = {4, 5, 6, 7}; // Pins connected to the bulbs
const int numBulbs = sizeof(bulbPins) / sizeof(bulbPins[0]); // Number of bulbs

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  for (int i = 0; i < numBulbs; i++) {
    pinMode(bulbPins[i], OUTPUT);
    digitalWrite(bulbPins[i], LOW); // Turn off all bulbs initially
  }
}

void loop() {
  if (bluetoothSerial.available()) {
    char receivedData = bluetoothSerial.read();
    handleCommand(receivedData);
  }
}

void handleCommand(char command) {
  if (command >= '1' && command <= '4') {
    int bulbIndex = command - '1'; // Convert command '1'-'4' to bulb index 0-3
    toggleBulb(bulbIndex);
  }
}

void toggleBulb(int bulbIndex) {
  if (bulbIndex >= 0 && bulbIndex < numBulbs) {
    digitalWrite(bulbPins[bulbIndex], !digitalRead(bulbPins[bulbIndex])); // Toggle the specified bulb
    if (digitalRead(bulbPins[bulbIndex])) {
      bluetoothSerial.write("Bulb ");
      bluetoothSerial.write(String(bulbIndex + 1).c_str());
      bluetoothSerial.write(" turned on\n");
    } else {
      bluetoothSerial.write("Bulb ");
      bluetoothSerial.write(String(bulbIndex + 1).c_str());
      bluetoothSerial.write(" turned off\n");
    }
  }
}


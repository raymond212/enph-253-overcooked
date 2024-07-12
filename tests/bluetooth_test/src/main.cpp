#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
int count = 0;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32");
}

void loop() {
  SerialBT.println("Hello from ESP32 - " + String(count));
  delay(1000);
}
#include <Arduino.h>

const int ledPin = 20;
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
  delay(1000);
}
#include <Arduino.h>

int stepPin = 27;
int dirPin = 14;

// int inputPin = 25;

const int STEPPER_PULSE_US = 1000;
const int STEPPER_DELAY_US = 1000;

String waitAndRead();
String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  int steps = waitAndRead().toInt();
  Serial.println("Moving " + String(steps) + " steps");
  if (steps > 0) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
    steps = -steps;
  }
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(STEPPER_PULSE_US);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(STEPPER_DELAY_US);
  }
}
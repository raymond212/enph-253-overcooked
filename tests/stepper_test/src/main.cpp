#include <Arduino.h>

int stepPin = 20;
int dirPin = 21;

const int STEPPER_PULSE_US = 250;
const int STEPPER_DELAY_US = 3000;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  int numSteps = 200;
  if (numSteps > 0) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
  numSteps = abs(numSteps);
  for (int i = 0; i < numSteps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(STEPPER_PULSE_US);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(STEPPER_DELAY_US);
  }
  delay(1000);
}
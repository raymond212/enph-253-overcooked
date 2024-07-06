#include <Arduino.h>

int stepPin = 20;
int dirPin = 21;

int inputPin = 25;

const int STEPPER_PULSE_US = 1000;
const int STEPPER_DELAY_US = 1000;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP);
}

void loop() {
  digitalWrite(dirPin, digitalRead(inputPin));

  digitalWrite(stepPin, HIGH);
  delayMicroseconds(STEPPER_PULSE_US);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(STEPPER_DELAY_US);

  // int numSteps = 200 * 10;
  // digitalWrite(dirPin, LOW);
  // for (int i = 0; i < numSteps; i++) {
  // }

  // digitalWrite(dirPin, HIGH);
  // for (int i = 0; i < numSteps; i++) {
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(STEPPER_PULSE_US);
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(STEPPER_DELAY_US);
  // }
}
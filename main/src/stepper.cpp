#include <stepper.h>

Stepper::Stepper(int stepPin, int dirPin) : stepPin(stepPin), dirPin(dirPin) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void Stepper::stepRevs(double numRevolutions) {
  step(int(numRevolutions * STEPS_PER_REVOLUTION));
}

void Stepper::step(int numSteps) {
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
}
#include <stepper.h>

Stepper::Stepper(int stepPin, int dirPin, double rps) : stepPin(stepPin), dirPin(dirPin), rps(rps) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  stepperPulseUS = (1 / (rps * STEPS_PER_REVOLUTION)) * 1000000 / 2;
  stepperDelayUS = stepperPulseUS;
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
    delayMicroseconds(stepperPulseUS);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepperDelayUS);
  }
}
#include <stepper.h>

Stepper::Stepper() {}

Stepper::Stepper(uint8_t stepPin, uint8_t dirPin, double rps) : stepPin(stepPin), dirPin(dirPin), rps(rps) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  stepperPulseUS = (int)((1 / (rps * STEPS_PER_REVOLUTION)) * 1000000 / 2);
}

void Stepper::stepRevs(double numRevolutions) {
  step((int)(numRevolutions * STEPS_PER_REVOLUTION));
}

void Stepper::step(int numSteps) {
  Serial.println("Stepping " + String(numSteps) + " steps");
  Serial.println("Stepper pulse time: " + String(stepperPulseUS));
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
    delayMicroseconds(stepperPulseUS);
  }
}

void Stepper::setSpeed(double rps) {
  this->rps = rps;
  stepperPulseUS = (int)((1 / (rps * STEPS_PER_REVOLUTION)) * 1000000 / 2);
}
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

// void Stepper::setTargetSteps(int targetSteps) {
//   if (targetSteps > 0) {
//     digitalWrite(dirPin, HIGH);
//   } else {
//     digitalWrite(dirPin, LOW);
//   }
//   this->targetSteps = abs(targetSteps);
//   lastPulseTime = micros();
//   state = LOW;
// }

// bool Stepper::nonBlockingStep() {
//   if (targetSteps == 0) {
//     return true;
//   }
//   if (micros() - lastPulseTime > stepperPulseUS) {
//     Network::wifiPrintln(String(micros()) + " " + String(lastPulseTime) + " " + String(stepperPulseUS) + " " + String(state) + " " + String(targetSteps));
//     lastPulseTime = micros();
//     if (state == LOW) {
//       digitalWrite(stepPin, HIGH);
//       state = HIGH;
//       targetSteps--;
//     } else {
//       digitalWrite(stepPin, LOW);
//       state = LOW;
//     }
//   }
//   return false;
// }
#include <stepper.h>

Stepper* Stepper::instances[4] = { nullptr, nullptr, nullptr, nullptr }; // Initialize the array with nullptrs

Stepper::Stepper() {}

Stepper::Stepper(uint8_t stepPin, uint8_t dirPin, double rps, int timerNum)
  : stepPin(stepPin), dirPin(dirPin), rps(rps), timerMux(portMUX_INITIALIZER_UNLOCKED), timerNum(timerNum) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  stepperPulseUS = (int)((1 / (rps * STEPS_PER_REVOLUTION)) * 1000000);

  instances[timerNum] = this; // Store the instance in the array

  // Initialize the timer
  timer = timerBegin(timerNum, 80, true); // timerNum, prescaler, countUp
  timerAttachInterrupt(timer, &Stepper::onTimerStatic, true); // Attach the static ISR
  timerAlarmWrite(timer, stepperPulseUS, true); // set the alarm value in microseconds
  timerAlarmEnable(timer);
  timerStop(timer); // Stop the timer initially
}

void Stepper::stepRevs(double numRevolutions) {
  step((int)(numRevolutions * STEPS_PER_REVOLUTION));
}

void Stepper::stepRevsBlocking(double numRevolutions) {
  stepRevs(numRevolutions);
  while (switchesRemaining > 0) {
    delay(10); // wait
  }
}

void Stepper::step(int numSteps) {
  if (numSteps > 0) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
  this->switchesRemaining = abs(numSteps);
  startTimer();
}

void Stepper::setSpeed(double rps) {
  this->rps = rps;
  stepperPulseUS = (int)((1 / (rps * STEPS_PER_REVOLUTION)) * 1000000 / 2);
  timerAlarmWrite(timer, stepperPulseUS, true);
}

void IRAM_ATTR Stepper::onTimerStatic() {
  for (int i = 0; i < 4; ++i) {
    if (instances[i] != nullptr) {
      instances[i]->onTimer();
    }
  }
}

void IRAM_ATTR Stepper::onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  if (switchesRemaining > 0) {
    digitalWrite(stepPin, !digitalRead(stepPin)); // Toggle the step pin
    switchesRemaining--;
  } else {
    stopTimer(); // Stop the timer when done
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

void Stepper::startTimer() {
  timerAlarmEnable(timer);
}

void Stepper::stopTimer() {
  timerAlarmDisable(timer);
  digitalWrite(stepPin, LOW); // Ensure the step pin is low when stopping
}

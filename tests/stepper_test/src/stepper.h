#pragma once

#include <Arduino.h>

#define STEPS_PER_REVOLUTION 200

class Stepper {
public:
  Stepper();
  Stepper(uint8_t stepPin, uint8_t dirPin, double rps, int timerNum);
  void stepRevs(double numRevolutions);
  void step(int numSteps);
  void setSpeed(double rps);

private:
  uint8_t stepPin;
  uint8_t dirPin;
  double rps;
  int stepperPulseUS;
  int switchesRemaining;
  hw_timer_t *timer;
  portMUX_TYPE timerMux;
  int timerNum;
  
  static void IRAM_ATTR onTimerStatic();
  void onTimer();
  void startTimer();
  void stopTimer();
  
  static Stepper* instances[4];
};
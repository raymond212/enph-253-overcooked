#pragma once

#include <Arduino.h>
#include <constants.h>
#include <network.h>

class Stepper {
  public:
    Stepper();

    Stepper(uint8_t stepPin, uint8_t dirPin, double rps);

    void stepRevs(double numRevolutions);

    void step(int numSteps);

    void setSpeed(double rps);

    // void setTargetSteps(int targetSteps);

    // bool nonBlockingStep();

  private:
    uint8_t stepPin;
    uint8_t dirPin;
    double rps;
    int stepperPulseUS;
    int targetSteps;
    long lastPulseTime;
    int state;
};

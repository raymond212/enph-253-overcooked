#pragma once

#include <Arduino.h>
#include <constants.h>

class Stepper {
  public:
    Stepper();

    Stepper(uint8_t stepPin, uint8_t dirPin, double rps);

    void stepRevs(double numRevolutions);

    void step(int numSteps);

    void setSpeed(double rps);

    void setTargetSteps(int numSteps);

  private:
    uint8_t stepPin;
    uint8_t dirPin;
    double rps;
    int stepperPulseUS;
};

#pragma once

#include <Arduino.h>
#include <constants.h>

class Stepper {
  public:
    Stepper(int stepPin, int dirPin, double rps);

    void stepRevs(double numRevolutions);

    void step(int numSteps);    
  private:
    int stepPin;
    int dirPin;
    double rps;
    int stepperPulseUS;
    int stepperDelayUS;
};

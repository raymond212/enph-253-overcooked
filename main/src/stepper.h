#pragma once

#include <Arduino.h>
#include <constants.h>

class Stepper {
  public:
    Stepper(int stepPin, int dirPin);

    void stepRevs(double numRevolutions);

    void step(int numSteps);    
  private:
    int stepPin;
    int dirPin;
};

#pragma once

#include <Arduino.h>
#include <Constants.h>

class Stepper {
  public:
    Stepper(int stepPin, int dirPin);

    void stepRevs(double numRevolutions);

    void step(int numSteps);    
  private:
    int stepPin;
    int dirPin;
};

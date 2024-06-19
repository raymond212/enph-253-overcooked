#pragma once

#include <Arduino.h>
#include <Constants.h>

class Motor {
  public:
    Motor(int pin1, int pin2, int enablePin);

    /**
     * Stop the motor
     */
    void stop();

    /**
     * Set motor to a certain speed
     * 
     * @param speed int between -255 to 255 inclusive
     */
    void setSpeed(double speed);
    double mapd(double x, double in_min, double in_max, double out_min, double out_max);
    
  private:
    int pin1;
    int pin2;
    int enablePin;
};

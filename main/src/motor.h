#pragma once

#include <Arduino.h>
#include <Constants.h>

class Motor {
  public:
    /**
     * Initialize a motor with pin1 as the forward pin and pin2 as the backward pin
     */
    Motor(int pin1, int pin2);

    /**
     * Stop the motor
     */
    void stop();

    /**
     * Set motor to a certain speed
     * 
     * @param speed double between -1.0 and 1.0
     */
    void setSpeed(double speed);    
  private:
    /**
     * Utility function to map a double from one range to another
     */
    double mapd(double x, double in_min, double in_max, double out_min, double out_max);
    int pin1;
    int pin2;
};

#pragma once

#include <Arduino.h>
#include <constants.h>

class Servo {
  public:
    /**
     * Declare a null servo motor
     */
    Servo();

    /**
     * Initialize a servo motor
     */
    Servo(uint8_t pin, uint8_t channel);

    /**
     * Set the servo to a certain angle
     * 
     * @param angle between 0 and 180
     */
    void setAngle(int angle);

    void setAngleSpeed(double targetAngle, double degPerSecond);

    double mapd(double x, double in_min, double in_max, double out_min, double out_max);

  private:
    uint8_t pin;
    uint8_t channel;
    int angle;
};
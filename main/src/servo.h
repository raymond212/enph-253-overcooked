#pragma once

#include <Arduino.h>
#include <constants.h>

#include <utils.h>

class Servo {
  public:
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

  private:
    uint8_t pin;
    uint8_t channel;
    int angle;
};
#pragma once

#include <Arduino.h>
#include <constants.h>

#include <utils.h>

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
    void setAngle(double angle);

  private:
    uint8_t pin;
    uint8_t channel;
};
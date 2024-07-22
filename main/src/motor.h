#pragma once

#include <Arduino.h>
#include <constants.h>

#include <utils.h>

class Motor {
  public:
    /**
     * Initialize an encoded motor
     */
    Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t motorChannelA, uint8_t motorChannelB);

    /**
     * Set motor to a certain speed
     * 
     * @param power double between -1.0 and 1.0
     */
    void setPower(double power);

    void setDutyCycle(int dutyCycle);
  private:
    uint8_t motorPinA;
    uint8_t motorPinB;

    uint8_t motorChannelA;
    uint8_t motorChannelB;
};

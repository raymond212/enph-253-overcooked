#pragma once

#include <Arduino.h>
#include <constants.h>

#include <utils.h>

class Motor {
  public:
    /**
     * Initialize a motor
     */
    Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t motorChannelA, uint8_t motorChannelB);

    /**
     * Set the motor to a certain speed
     * 
     * @param power between -1.0 and 1.0
     */
    void setPower(double power);

    /**
     * Set the motor to a duty cycle
     * 
     * @param dutyCycle between -255 and 255
     */
    void setDutyCycle(int dutyCycle);
    
  private:
    uint8_t motorPinA;
    uint8_t motorPinB;
    uint8_t motorChannelA;
    uint8_t motorChannelB;
};

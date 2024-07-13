#pragma once

#include <Arduino.h>
#include <constants.h>

#include <utils.h>

class Motor {
  public:
    /**
     * Initialize an encoded motor
     */
    Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t encoderPinA, uint8_t encoderPinB);

    /**
     * Set motor to a certain speed
     * 
     * @param power double between -1.0 and 1.0
     */
    void setPower(double power);

    /**
     * @return the number of encoder clicks
     */
    int getCount();

    /**
     * @return the distance traveled in inches
     */
    double getDistance();

    /**
     * Reset the encoder count
     */
    void resetEncoder();

    /**
     * An ISR to update the encoder count
     */
    void encoderISR();
  private:
    uint8_t motorPinA;
    uint8_t motorPinB;
    uint8_t encoderPinA;
    uint8_t encoderPinB;
    volatile int count = 0;
};

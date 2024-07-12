#pragma once

#include <Arduino.h>
#include <constants.h>
#include <utils.h>

class Motor {
  public:
    /**
     * Initialize a motor with 
     */
    Motor(int forwardPin, int backwardPin, int encoderPinA, int encoderPinB);

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

    int getCount();

    double getDistance();

    bool driveDistance(double targetDistance, double maxSpeed);

    void resetEncoder();

    void updateEncoder();
  private:
    int forwardPin;
    int backwardPin;
    int encoderPinA;
    int encoderPinB;
    volatile int count = 0;
};

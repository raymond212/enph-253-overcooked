#pragma once

#include <Arduino.h>
#include <constants.h>

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

    void resetEncoderPeriodically();

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

    void setSpeed_PID(double speed);

    double get_real_speed();
  private:
    /**
     * Utility function to map a double from one range to another
     */
    double mapd(double x, double in_min, double in_max, double out_min, double out_max);

    int forwardPin;
    int backwardPin;
    int encoderPinA;
    int encoderPinB;
    volatile int count = 0;
    volatile unsigned long lastResetTime = 0;
    volatile int polled_count = 0;
    double e_previous_error = 0.0;
    double e_sum_error = 0.0;    
};

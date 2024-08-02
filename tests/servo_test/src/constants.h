#pragma once

#include <Arduino.h>

// servo motors
const int SERVO_PWM_FREQ_HZ = 50;
const int SERVO_PWM_RESOLUTION = 16;
const int SERVO_PWM_TOTAL_TICKS = 1 << SERVO_PWM_RESOLUTION;
const int SERVO_PWM_PERIOD_US = 1000000 / SERVO_PWM_FREQ_HZ;
const int SERVO_PWM_MIN_US = 500;
const int SERVO_PWM_MAX_US = 2500;
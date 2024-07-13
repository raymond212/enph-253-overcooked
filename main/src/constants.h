#pragma once

#include <Arduino.h>

// wifi settings
const String ssid = "Raymond";
const String password = "lithiumRanger";
const uint16_t WIFI_PORT = 23;

// navigation motor parameters
const double TAPE_FOLLOW_HIGH_POWER = 0.5;
const double TAPE_FOLLOW_LOW_POWER = 0.3;
const double TURN_POWER = 0.15;

// motors and encoder pins
const uint8_t L_MOTOR_A = 20;
const uint8_t L_MOTOR_B = 21;
const uint8_t L_ENCODER_A = 38;
const uint8_t L_ENCODER_B = 37;

const uint8_t R_MOTOR_A = 22;
const uint8_t R_MOTOR_B = 19;
const uint8_t R_ENCODER_A = 34;
const uint8_t R_ENCODER_B = 35;

const int MOTOR_PWM_FREQ_HZ = 250;

const double WHEEL_DIAMETER_IN = 3.05;
const double WHEEL_CIRCUMFERENCE_IN = WHEEL_DIAMETER_IN * PI;
const int CLICKS_PER_REV = 2730; // 11 * 131 * 2 = 2882;
const double CLICKS_PER_IN = CLICKS_PER_REV / WHEEL_CIRCUMFERENCE_IN;
const double IN_PER_CLICK = 1 / CLICKS_PER_IN;

// tape sensors
const uint8_t TAPE_SENSOR_L = 36;
const uint8_t TAPE_SENSOR_R = 39;

const int LEFT_TAPE_THRESHOLD = 3200; // between 0 and 4095
const int RIGHT_TAPE_THRESHOLD = 3400; // between 0 and 4095

enum class TapeReading {
  NONE,
  LEFT,
  RIGHT,
  BOTH
};

enum class TurnDirection {
  LEFT,
  RIGHT
}

// stepper motor
const int STEPS_PER_REVOLUTION = 200;
const int STEPPER_PULSE_US = 500;
const int STEPPER_DELAY_US = 500;
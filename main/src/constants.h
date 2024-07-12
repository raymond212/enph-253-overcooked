#pragma once

#include <Arduino.h>

// wifi settings
const String ssid = "Raymond";
const String password = "lithiumRanger";
const int WIFI_PORT = 23;

// motor settings
const double MOTOR_FAST_SPEED = 0.5;
const double MOTOR_SLOW_SPEED = 0.3;

// motor pins
const int LEFT_M_F = 20;
const int LEFT_M_B = 21;
const int LEFT_M_E_A = 38;
const int LEFT_M_E_B = 37;

const int RIGHT_M_F = 22;
const int RIGHT_M_B = 19;
const int RIGHT_M_E_A = 34;
const int RIGHT_M_E_B = 35;


// wheel and encoder
const double WHEEL_DIAMETER_IN = 3;
const double WHEEL_CIRCUMFERENCE_IN = WHEEL_DIAMETER_IN * PI;
const int CLICKS_PER_REV = 11 * 131 * 2;
const double CLICKS_PER_IN = CLICKS_PER_REV / WHEEL_CIRCUMFERENCE_IN;

const double ACCEL_PER_INCH = 0.1;
const double STALL_SPEED = 0.2;

// tape following
const int LEFT_TAPE_THRESHOLD = 3200; // between 0 and 4095
const int RIGHT_TAPE_THRESHOLD = 3400; // between 0 and 4095

enum class TapeReading {
  NONE,
  LEFT,
  RIGHT,
  BOTH
};

enum class StoppingCondition {
  WALL,
  LEFT_TAPE,
  RIGHT_TAPE
};

// tape sensor pins
const int TAPE_SENSOR_L = 36;
const int TAPE_SENSOR_R = 39;

// destacker pins
const int DESTACKER_STEPPER_STEP = 2;
const int DESTACKER_STEPPER_DIR = 3;
const int DESTACKER_SERVO_PIN = 4;

// stepper motor
const int STEPS_PER_REVOLUTION = 200;
const int STEPPER_PULSE_US = 500;
const int STEPPER_DELAY_US = 500;
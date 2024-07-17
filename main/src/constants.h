#pragma once

#include <Arduino.h>

const int ROBOT_ID = 0; // 0 for top robot, 1 for bottom robot 

// measurements
const double WHEEL_DIAMETER = 3.05;
const double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;
const double TAPE_SENSOR_TO_WHEEL_DIST = 4.0;
const double WHEEL_TO_WHEEL_DIST = 4.0;

// wifi settings
const String ssid = "Raymond";
const String password = "enphteamtwo";
const uint16_t WIFI_PORT = 23;

// navigation motor parameters
const double TAPE_FOLLOW_HIGH_POWER = 0.5;
const double TAPE_FOLLOW_LOW_POWER = 0.3;
const double TURN_POWER = 0.15;

// motors and encoders
const uint8_t L_MOTOR_PIN_A = 20;
const uint8_t L_MOTOR_PIN_B = 21;
const uint8_t L_ENCODER_PIN_A = 38;
const uint8_t L_ENCODER_PIN_B = 37;

const uint8_t R_MOTOR_PIN_A = 22;
const uint8_t R_MOTOR_PIN_B = 19;
const uint8_t R_ENCODER_PIN_A = 34;
const uint8_t R_ENCODER_PIN_B = 35;

const uint8_t L_MOTOR_CHANNEL_A = 0;
const uint8_t L_MOTOR_CHANNEL_B = 1;
const uint8_t R_MOTOR_CHANNEL_A = 2;
const uint8_t R_MOTOR_CHANNEL_B = 3;

const int MOTOR_PWM_FREQ_HZ = 250;
const int MOTOR_PWM_RESOLUTION = 8; // 2^8 = 256

const int CLICKS_PER_REV = 2720; // 11 * 131 * 2 = 2882;
const double CLICKS_PER_IN = CLICKS_PER_REV / WHEEL_CIRCUMFERENCE;
const double IN_PER_CLICK = 1 / CLICKS_PER_IN;

// tape sensors
const uint8_t TAPE_SENSOR_L = 36;
const uint8_t TAPE_SENSOR_R = 39;

const int LEFT_TAPE_THRESHOLD = 3000; // between 0 and 4095
const int RIGHT_TAPE_THRESHOLD = 3200; // between 0 and 4095

// servo motors
const int SERVO_PWM_FREQ_HZ = 50;
const int SERVO_PWM_RESOLUTION = 16;
const int SERVO_PWM_TOTAL_TICKS = 1 << SERVO_PWM_RESOLUTION;
const int SERVO_PWM_PERIOD_US = 1000000 / SERVO_PWM_FREQ_HZ;
const int SERVO_PWM_MIN_US = 500;
const int SERVO_PWM_MAX_US = 2500;

enum class TapeReading {
  NONE,
  LEFT,
  RIGHT,
  BOTH
};

enum class TurnDirection {
  LEFT,
  RIGHT
};

// stations
enum class Table {
  TOP,
  MIDDLE,
  BOTTOM
};

struct Station {
  double position;
  Table table;

  Station(double position, Table table) : position(position), table(table) {}
};

enum class FacingDirection {
  TOP,
  RIGHT,
  BOTTOM,
  LEFT
};

enum class YPosition {
  TOP,
  TAPE,
  BOTTOM
};

static Station PATTIES(12, Table::TOP);
static Station BUNS(48, Table::TOP);
static Station POTATOES(84, Table::TOP);

static Station TOMATOES(6, Table::MIDDLE);
static Station CUTTING(30, Table::MIDDLE);
static Station COOKING(72.5, Table::MIDDLE);
static Station PLATES(90, Table::MIDDLE);

static Station CHEESE(6, Table::BOTTOM);
static Station SERVING(48, Table::BOTTOM);
static Station LETTUCE(90, Table::BOTTOM);

// stepper motor
const int STEPS_PER_REVOLUTION = 200;
const int STEPPER_PULSE_US = 500;
const int STEPPER_DELAY_US = 500;
#pragma once

#include <Arduino.h>

const int ROBOT_ID = 0; // 0 for top robot, 1 for bottom robot 

// wifi settings
const String ssid = "Roberts’s trapphone";
const String password = "eurostep";
const uint16_t WIFI_PORT = 23;

const double EPSILON = 0.001;

// navigation motor parameters
const double WALL_FOLLOW_ANGLE_DEG = 15;
const double WALL_FOLLOW_SLOW_POWER = 0.35;
const double WALL_FOLLOW_FAST_POWER = 0.6;
const int TAPE_DEBOUNCE_DELAY = 300;
const int WALL_FOLLOW_DELAY = 500;

// motors
const uint8_t FL_MOTOR_PIN_A = 22;
const uint8_t FL_MOTOR_PIN_B = 19;

const uint8_t FR_MOTOR_PIN_A = 20;
const uint8_t FR_MOTOR_PIN_B = 21;

const uint8_t BL_MOTOR_PIN_A = 26;
const uint8_t BL_MOTOR_PIN_B = 25;

const uint8_t BR_MOTOR_PIN_A = 33;
const uint8_t BR_MOTOR_PIN_B = 32;

const uint8_t FL_MOTOR_CHANNEL_A = 0;
const uint8_t FL_MOTOR_CHANNEL_B = 1;
const uint8_t FR_MOTOR_CHANNEL_A = 2;
const uint8_t FR_MOTOR_CHANNEL_B = 3;
const uint8_t BL_MOTOR_CHANNEL_A = 4;
const uint8_t BL_MOTOR_CHANNEL_B = 5;
const uint8_t BR_MOTOR_CHANNEL_A = 6;
const uint8_t BR_MOTOR_CHANNEL_B = 7;

const int MOTOR_PWM_FREQ_HZ = 250;
const int MOTOR_PWM_RESOLUTION = 8; // 2^8 = 256

// tape sensors
const uint8_t TAPE_SENSOR_F = 36;
const uint8_t TAPE_SENSOR_B = 39;

const int FRONT_TAPE_THRESHOLD = 3100; // between 0 and 4095
const int BACK_TAPE_THRESHOLD = 3100; // between 0 and 4095

// servo motors
const int SERVO_PWM_FREQ_HZ = 50;
const int SERVO_PWM_RESOLUTION = 16;
const int SERVO_PWM_TOTAL_TICKS = 1 << SERVO_PWM_RESOLUTION;
const int SERVO_PWM_PERIOD_US = 1000000 / SERVO_PWM_FREQ_HZ;
const int SERVO_PWM_MIN_US = 500;
const int SERVO_PWM_MAX_US = 2500;

// bottom robot modules
const uint8_t INPUT_SCRAPER_PIN = 8;
const uint8_t OUTPUT_SCRAPER_PIN = 7;
const uint8_t TRAPDOOR_PIN = 5;
const uint8_t PLATE_PIN = 15;

const uint8_t INPUT_SCRAPER_CHANNEL = 8;
const uint8_t OUTPUT_SCRAPER_CHANNEL = 9;
const uint8_t TRAPDOOR_CHANNEL = 10;
const uint8_t PLATE_CHANNEL = 11;

const uint8_t CAROUSEL_STEP_PIN = 27;
const uint8_t CAROUSEL_DIR_PIN = 14;
const uint8_t ELEVATOR_STEP_PIN = 12;
const uint8_t ELEVATOR_DIR_PIN = 13;

//top robot modules

const uint8_t TOP_INPUT_SCRAPER_PIN = 8;
const uint8_t TOP_OUTPUT_SCRAPER_PIN = 9;

const uint8_t SPIRAL_STEP_PIN = 27;
const uint8_t SPIRAL_DIR_PIN = 14;
const uint8_t LINEAR_STEP_PIN = 12;
const uint8_t LINEAR_DIR_PIN = 13;

enum class TapeReading {
  NONE,
  FRONT,
  BACK,
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

enum class DriveDirection {
  FORWARD,
  BACKWARD,
  RIGHT,
  LEFT
};

enum class WallLocation {
  RIGHT,
  LEFT
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
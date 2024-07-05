#pragma once

// motor pins
const int FRONT_M_F = 20;
const int FRONT_M_B = 21;

const int BACK_M_F = 22;
const int BACK_M_B = 19;

const int LEFT_M_F = 32;
const int LEFT_M_B = 33;

const int RIGHT_M_F = 26;
const int RIGHT_M_B = 25;

// tape following
const int TAPE_THRESHOLD = 2800; // between 0 and 4095
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

enum class Direction {
  FRONT,
  BACK,
  LEFT,
  RIGHT
};

// tape sensor pins
const int FRONT_TS_L = 38;
const int FRONT_TS_R = 37;
const int BACK_TS_L = 35;
const int BACK_TS_R = 34;
const int LEFT_TS_L = 0;
const int LEFT_TS_R = 0;
const int RIGHT_TS_L = 0;
const int RIGHT_TS_R = 0;

// destacker pins
const int DESTACKER_STEPPER_STEP = 2;
const int DESTACKER_STEPPER_DIR = 3;
const int DESTACKER_SERVO_PIN = 4;

// stepper motor
const int STEPS_PER_REVOLUTION = 200;
const int STEPPER_PULSE_US = 500;
const int STEPPER_DELAY_US = 500;
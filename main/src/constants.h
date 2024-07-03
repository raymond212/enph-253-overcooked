#pragma once

// motor pins
const int FRONT_LEFT_F = 22;
const int FRONT_LEFT_B = 21;
const int FRONT_LEFT_E = 20;

const int FRONT_RIGHT_F = 19;
const int FRONT_RIGHT_B = 8;
const int FRONT_RIGHT_E = 7;

const int BACK_LEFT_F = 33;
const int BACK_LEFT_B = 27;
const int BACK_LEFT_E = 14;

const int BACK_RIGHT_F = 26;
const int BACK_RIGHT_B = 32;
const int BACK_RIGHT_E = 25;

const int PWM_FREQ = 200;

// tape following constants
const int TAPE_THRESHOLD = 2800; // between 0 and 4095

// tape sensor pins
const int FRONT_LEFT_T = 38;
const int FRONT_RIGHT_T = 37;
const int BACK_LEFT_T = 34;
const int BACK_RIGHT_T = 35;

// destacker pins
const int DESTACKER_STEPPER_STEP = 2;
const int DESTACKER_STEPPER_DIR = 3;
const int DESTACKER_SERVO_PIN = 4;

// stepper motor
const int STEPS_PER_REVOLUTION = 200;
const int STEPPER_PULSE_US = 500;
const int STEPPER_DELAY_US = 500;
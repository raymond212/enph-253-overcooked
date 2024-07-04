#pragma once

// motor pins
const int FRONT_F = 21;
const int FRONT_B = 20;

const int BACK_F = 19;
const int BACK_B = 22;

const int LEFT_F = 32;
const int LEFT_B = 33;

const int RIGHT_F = 26;
const int RIGHT_B = 25;

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
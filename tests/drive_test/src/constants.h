#pragma once

// motor pins
const int FRONT_LEFT_F = 22;
const int FRONT_LEFT_B = 1;
const int FRONT_LEFT_E = 23;

const int FRONT_RIGHT_F = 3;
const int FRONT_RIGHT_B = 21;
const int FRONT_RIGHT_E = 19;

const int BACK_LEFT_F = 27;
const int BACK_LEFT_B = 26;
const int BACK_LEFT_E = 25;

const int BACK_RIGHT_F = 12;
const int BACK_RIGHT_B = 14;
const int BACK_RIGHT_E = 13;

// tape following constants
const int TAPE_THRESHOLD = 400; // between 0 and 1023

enum TAPE_COLOR {
  BLACK,
  WHITE
};
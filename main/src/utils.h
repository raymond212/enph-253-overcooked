#pragma once

#include <math.h>
#include <constants.h>

namespace Utils {
  static double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
    return (out_max - out_min) * (x - in_min) / (in_max - in_min) + out_min;
  }

  static double bind(double x, double min, double max) {
    return x < min ? min : x > max ? max : x;
  }

  static bool isEqual(double a, double b, double epsilon = 0.0001) {
    return abs(a - b) < epsilon;
  }

  static int leftMotorSpeedToDutyCycle(double speed) {
    if (speed < 2700) {
      return (int)(log(1 - speed / 3294.03)*(-21.2979) + 29);
    } else {
      return (int)(log(1 - speed / 5250.31)*(-70.2133) + 14.6885);
    }
  }

  static int rightMotorSpeedToDutyCycle(double speed) {
    if (speed < 2600) {
      return (int)(log(1 - speed / 5317.86)*(-39.1512) + 12);
    } else {
      return (int)(log(1 - speed / 4988.83)*(-94.6005) - 33.3284);
    }
  }
};
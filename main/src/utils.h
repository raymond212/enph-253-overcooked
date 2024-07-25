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

  static double directionToAngle(DriveDirection driveDirection) {
    switch (driveDirection) {
      case DriveDirection::FORWARD:
        return 0;
      case DriveDirection::BACKWARD:
        return 180;
      case DriveDirection::LEFT:
        return 90;
      case DriveDirection::RIGHT:
        return -90;
      default:
        return 0;
    }
  }

  static double invertAngle(double angle) {
    return angle > 0 ? angle - 180 : angle + 180;
  }
};
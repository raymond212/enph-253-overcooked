#pragma once

namespace Utils {
  static double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
    return (out_max - out_min) * (x - in_min) / (in_max - in_min) + out_min;
  }

  static double bind(double x, double min, double max) {
    return x < min ? min : x > max ? max : x;
  }
};
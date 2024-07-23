#pragma once

#include <Arduino.h>
#include <constants.h>

namespace TapeSensors {
  /**
   * Sets up the front tape sensors
   */
  void setupTapeSensors();

  /**
   * @return the tape sensor readings
   */
  TapeReading readTape();

  /**
   * @return true if the front sensor detects tape and false otherwise
   */
  bool frontIsTape();

  /**
   * @return true if the back sensor detects tape and false otherwise
   */
  bool backIsTape();

  /**
   * @return String the string representation of the tape sensor readings
   */
  String getValuesStr();
}
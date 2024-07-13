#include <tape_sensors.h>

namespace TapeSensors {
  void setupTapeSensors() {
    pinMode(TAPE_SENSOR_L, INPUT);
    pinMode(TAPE_SENSOR_R, INPUT);
  }

  TapeReading readTape() {
    bool left = leftIsTape();
    bool right = rightIsTape();

    if (left && right) {
      return TapeReading::BOTH;
    } else if (left) {
      return TapeReading::LEFT;
    } else if (right) {
      return TapeReading::RIGHT;
    } else {
      return TapeReading::NONE;
    }
  }

  bool leftIsTape() {
    return analogRead(TAPE_SENSOR_L) >= LEFT_TAPE_THRESHOLD;
  }

  bool rightIsTape() {
    return analogRead(TAPE_SENSOR_R) >= RIGHT_TAPE_THRESHOLD;
  }

  String getValuesStr() {
    return String(analogRead(TAPE_SENSOR_L)) + " " + String(analogRead(TAPE_SENSOR_R));
  }
}
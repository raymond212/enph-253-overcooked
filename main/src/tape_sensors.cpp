#include <tape_sensors.h>

namespace TapeSensors {
  void setupTapeSensors() {
    pinMode(TAPE_SENSOR_F, INPUT);
    pinMode(TAPE_SENSOR_B, INPUT);
  }

  TapeReading readTape() {
    bool forward = frontIsTape();
    bool back = backIsTape();

    if (back && forward) {
      return TapeReading::BOTH;
    }  else if (forward) {
      return TapeReading::FRONT;
    } else if (back) {
      return TapeReading::BACK;
    } else {
      return TapeReading::NONE;
    }
  }

  bool frontIsTape() {
    return analogRead(TAPE_SENSOR_F) >= FRONT_TAPE_THRESHOLD;
  }

  bool backIsTape() {
    return analogRead(TAPE_SENSOR_B) >= BACK_TAPE_THRESHOLD;
  }

  String getValuesStr() {
    return String(analogRead(TAPE_SENSOR_F)) + " " + String(analogRead(TAPE_SENSOR_B));
  }
}


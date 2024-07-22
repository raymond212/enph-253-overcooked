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
      }
      else if (back) {
        return TapeReading::BACK;
      }
      else {
        return TapeReading::NONE;
      }
    }

    // bool left = leftIsTape();
    // bool right = rightIsTape();

    // if (left && right) {
    //   return TapeReading::BOTH;
    // } else if (left) {
    //   return TapeReading::LEFT;
    // } else if (right) {
    //   return TapeReading::RIGHT;
    // } else {
    //   return TapeReading::NONE;
    // }

  bool frontIsTape() {
    return analogRead(TAPE_SENSOR_F) >= FRONT_TAPE_THRESHOLD;
    // return analogRead(TAPE_SENSOR_L) >= LEFT_TAPE_THRESHOLD;
  }

  bool backIsTape() {
    return analogRead(TAPE_SENSOR_B) >= BACK_TAPE_THRESHOLD;
    // return analogRead(TAPE_SENSOR_R) >= RIGHT_TAPE_THRESHOLD;
  }

  String getValuesStr() {
    return String(analogRead(TAPE_SENSOR_F)) + " " + String(analogRead(TAPE_SENSOR_B));
    // return String(analogRead(TAPE_SENSOR_L)) + " " + String(analogRead(TAPE_SENSOR_R));
  }
}


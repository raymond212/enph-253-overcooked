#include <tape_sensor.h>

TapeSensor::TapeSensor(int leftPin, int rightPin) : leftPin(leftPin), rightPin(rightPin) {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
}

TapeReading TapeSensor::reading() {
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

bool TapeSensor::leftIsTape() {
  return analogRead(leftPin) >= LEFT_TAPE_THRESHOLD;
}

bool TapeSensor::rightIsTape() {
  return analogRead(rightPin) >= RIGHT_TAPE_THRESHOLD;
}

String TapeSensor::getValuesStr() {
  return String(analogRead(leftPin)) + " " + String(analogRead(rightPin));
}
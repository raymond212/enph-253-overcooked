#include <tape_sensor.h>

TapeSensor::TapeSensor(int leftPin, int rightPin) : leftPin(leftPin), rightPin(rightPin) {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
}

TapeReading TapeSensor::getReading() {
  bool left = analogRead(leftPin) >= TAPE_THRESHOLD;
  bool right = analogRead(rightPin) >= TAPE_THRESHOLD;

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

String TapeSensor::getValues() {
  return String(analogRead(leftPin)) + " " + String(analogRead(rightPin));
}
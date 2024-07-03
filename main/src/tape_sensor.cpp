#include <tape_sensor.h>

TapeSensor::TapeSensor(int pin) : pin(pin) {
  pinMode(pin, INPUT);
}

bool TapeSensor::isTape() {
  return analogRead(pin) >= TAPE_THRESHOLD;
}

int TapeSensor::getValue() {
  return analogRead(pin);
}
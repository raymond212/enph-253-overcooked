#include <tape_sensor.h>

TapeSensor::TapeSensor(int pin) : pin(pin) {
  pinMode(pin, INPUT);
}

TAPE_COLOR TapeSensor::getColor() {
  if (analogRead(pin) >= TAPE_THRESHOLD) {
    return BLACK;
  } else {
    return WHITE;
  }
}
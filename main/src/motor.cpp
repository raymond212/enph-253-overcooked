#include <motor.h>

Motor::Motor(int pin1, int pin2) : pin1(pin1), pin2(pin2) {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void Motor::stop() {
  setSpeed(0);
}

void Motor::setSpeed(double speed) {
  if (abs(speed) < EPSILON) {
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
  } else if (speed > 0) {
    analogWrite(pin1, mapd(speed, 0, 1, 0, 255));
    analogWrite(pin2, 0);
  } else if (speed < 0) {
    analogWrite(pin1, 0);
    analogWrite(pin2, mapd(-speed, 0, 1, 0, 255));
  }
}

double Motor::mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
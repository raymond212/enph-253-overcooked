#include <Motor.h>

Motor::Motor(int pin1, int pin2, int enablePin) : pin1(pin1), pin2(pin2), enablePin(enablePin) {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void Motor::stop() {
  analogWrite(pin1, 0);
  analogWrite(pin2, 0);
  analogWrite(enablePin, 0);
}

void Motor::setSpeed(double speed) {
  if (speed > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  } else if (speed < 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  } else {
    stop();
    return;
  }
  analogWrite(enablePin, int(abs(mapd(speed, -1, 1, -255, 255))));
}

double Motor::mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
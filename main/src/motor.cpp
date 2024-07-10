#include <motor.h>

Motor::Motor(int forwardPin, int backwardPin, int encoderPinA, int encoderPinB) : forwardPin(forwardPin), backwardPin(backwardPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB) {
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
}

void Motor::stop() {
  setSpeed(0);
}

int Motor::getCount() {
  return count;
}

double Motor::getDistance() {
  return count / CLICKS_PER_IN;
}

void Motor::updateEncoder() {
  if (digitalRead(encoderPinB) == LOW) {
    count++;
  } else {
    count--;
  }
}

bool Motor::driveDistance(double targetDistance, double maxSpeed) {
  if (getDistance() >= targetDistance) {
    setSpeed(0);
    return true;
  }
  double travelledDistance = getDistance();


  return false;
}

void Motor::setSpeed(double speed) {
  if (abs(speed) < EPSILON) {
    analogWrite(forwardPin, 0);
    analogWrite(backwardPin, 0);
  } else if (speed > 0) {
    analogWrite(forwardPin, mapd(speed, 0, 1, 0, 255));
    analogWrite(backwardPin, 0);
  } else if (speed < 0) {
    analogWrite(forwardPin, 0);
    analogWrite(backwardPin, mapd(-speed, 0, 1, 0, 255));
  }
}

void Motor::resetEncoder() {
  noInterrupts();
  count = 0;
  interrupts();
}

double Motor::mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
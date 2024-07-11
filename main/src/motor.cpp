#include <motor.h>

Motor::Motor(int forwardPin, int backwardPin, int encoderPinA, int encoderPinB) : forwardPin(forwardPin), backwardPin(backwardPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB) {
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  lastResetTime = millis();
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
  resetEncoderPeriodically();
}

bool Motor::driveDistance(double targetDistance, double maxSpeed) {
  if (getDistance() >= targetDistance) {
    setSpeed(0);
    return true;
  }
  double travelledDistance = getDistance();
  return false;
}



void Motor::setSpeed_PID(double speed) {
  int target_encoders = speed / WHEEL_CIRCUMFERENCE_IN * 100 * 0.75 * 1141;
  double KP = 0.02;
  double KD = 0.01;
  double KI = 0.005;
  
  double e1_error = polled_count - getCount();
  speed += e1_error * KP + e_previous_error*KD + e_sum_error * KI;
  speed = max(min(float(1), float(speed)), float(0));

  e_previous_error = e1_error;
  e_sum_error += e1_error;
}




double Motor::get_real_speed() {
  return getDistance()/(millis() - lastResetTime); //inches per millisecond
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
  polled_count = count;
  count = 0;
  lastResetTime = millis();
  interrupts();
}

void Motor::resetEncoderPeriodically() {
  if (millis() - lastResetTime >= 100) {
    resetEncoder();
  }
}

double Motor::mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


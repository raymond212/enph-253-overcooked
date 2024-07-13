#include <motor.h>

Motor::Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t encoderPinA, uint8_t encoderPinB) : motorPinA(motorPinA), motorPinB(motorPinB), encoderPinA(encoderPinA), encoderPinB(encoderPinB) {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinA, OUTPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  analogWriteFrequency(motorPinA, MOTOR_PWM_FREQ_HZ);
  analogWriteFrequency(motorPinB, MOTOR_PWM_FREQ_HZ);
}

int Motor::getCount() {
  return count;
}

double Motor::getDistance() {
  return count / CLICKS_PER_IN;
}

void Motor::encoderISR() {
  if (digitalRead(encoderPinB) == digitalRead(encoderPinA)) {
    count--;
  } else {
    count++;
  }
}

void Motor::setPower(double power) {
  if (power >= 0) {
    analogWrite(motorPinA, Utils::mapd(power, 0, 1, 0, 255));
    analogWrite(motorPinB, 0);
  } else {
    analogWrite(motorPinA, 0);
    analogWrite(motorPinB, Utils::mapd(-power, 0, 1, 0, 255));
  }
}

void Motor::resetEncoder() {
  noInterrupts();
  count = 0;
  interrupts();
}
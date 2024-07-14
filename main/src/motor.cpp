#include <motor.h>

Motor::Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t encoderPinA, uint8_t encoderPinB, uint8_t motorChannelA, uint8_t motorChannelB) : motorPinA(motorPinA), motorPinB(motorPinB), encoderPinA(encoderPinA), encoderPinB(encoderPinB), motorChannelA(motorChannelA), motorChannelB(motorChannelB) {
  ledcSetup(motorChannelA, MOTOR_PWM_FREQ_HZ, MOTOR_PWM_RESOLUTION);
  ledcSetup(motorChannelB, MOTOR_PWM_FREQ_HZ, MOTOR_PWM_RESOLUTION);
  ledcAttachPin(motorPinA, motorChannelA);
  ledcAttachPin(motorPinB, motorChannelB);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
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
    ledcWrite(motorChannelA, Utils::mapd(power, 0, 1, 0, 255));
    ledcWrite(motorChannelB, 0);
  } else {
    ledcWrite(motorChannelA, 0);
    ledcWrite(motorChannelB, Utils::mapd(-power, 0, 1, 0, 255));
  }
}

void Motor::resetEncoder() {
  noInterrupts();
  count = 0;
  interrupts();
}
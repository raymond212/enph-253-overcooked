#include <motor.h>

Motor::Motor() {}

Motor::Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t motorChannelA, uint8_t motorChannelB) : motorPinA(motorPinA), motorPinB(motorPinB), motorChannelA(motorChannelA), motorChannelB(motorChannelB) {
  ledcSetup(motorChannelA, MOTOR_PWM_FREQ_HZ, MOTOR_PWM_RESOLUTION);
  ledcSetup(motorChannelB, MOTOR_PWM_FREQ_HZ, MOTOR_PWM_RESOLUTION);
  ledcAttachPin(motorPinA, motorChannelA);
  ledcAttachPin(motorPinB, motorChannelB);
}

void Motor::setPower(double power) {
  setDutyCycle((int)(power * 255));
}

void Motor::setDutyCycle(int dutyCycle) {
  if (dutyCycle >= 0) {
    ledcWrite(motorChannelA, dutyCycle);
    ledcWrite(motorChannelB, 0);
  } else {
    ledcWrite(motorChannelA, 0);
    ledcWrite(motorChannelB, -dutyCycle);
  }
}
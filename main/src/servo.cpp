#include <servo.h>

Servo::Servo(uint8_t pin, uint8_t channel) : pin(pin), channel(channel) {
  ledcSetup(channel, SERVO_PWM_FREQ_HZ, SERVO_PWM_RESOLUTION);
  ledcAttachPin(pin, channel);
}

void Servo::setAngle(double angle) {
  double pulseWidthUS = Utils::mapd(angle, 0, 180, SERVO_PWM_MIN_US, SERVO_PWM_MAX_US);
  ledcWrite(channel, (int) (1.0 * pulseWidthUS / (SERVO_PWM_PERIOD_US) * SERVO_PWM_TOTAL_TICKS));
}
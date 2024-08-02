#include <servo.h>

Servo::Servo() {}

Servo::Servo(uint8_t pin, uint8_t channel) : pin(pin), channel(channel) {
  ledcSetup(channel, SERVO_PWM_FREQ_HZ, SERVO_PWM_RESOLUTION);
  ledcAttachPin(pin, channel);
  angle = 90;
}

void Servo::setAngle(int angle) {
  double pulseWidthUS = mapd(angle, 0, 180, SERVO_PWM_MIN_US, SERVO_PWM_MAX_US);
  ledcWrite(channel, (int)((double)SERVO_PWM_TOTAL_TICKS * (double)pulseWidthUS / (double)SERVO_PWM_PERIOD_US));
  this->angle = angle;
}

void Servo::setAngleSpeed(double targetAngle, double degPerSecond) {
  while (angle != targetAngle) {
    if (angle < targetAngle) {
      angle++;
    } else {
      angle--;
    }
    setAngle(angle);
    delay(1 / degPerSecond * 1000);
  }
  angle = targetAngle;
}

double Servo::mapd(double x, double in_min, double in_max, double out_min, double out_max) {
  return (out_max - out_min) * (x - in_min) / (in_max - in_min) + out_min;
}
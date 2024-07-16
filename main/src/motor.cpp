#include <motor.h>

Motor::Motor(uint8_t motorPinA, uint8_t motorPinB, uint8_t encoderPinA, uint8_t encoderPinB, uint8_t motorChannelA, uint8_t motorChannelB) : motorPinA(motorPinA), motorPinB(motorPinB), encoderPinA(encoderPinA), encoderPinB(encoderPinB), motorChannelA(motorChannelA), motorChannelB(motorChannelB) {
  ledcSetup(motorChannelA, MOTOR_PWM_FREQ_HZ, MOTOR_PWM_RESOLUTION);
  ledcSetup(motorChannelB, MOTOR_PWM_FREQ_HZ, MOTOR_PWM_RESOLUTION);
  ledcAttachPin(motorPinA, motorChannelA);
  ledcAttachPin(motorPinB, motorChannelB);

  // pinMode(motorPinA, OUTPUT);
  // pinMode(motorPinB, OUTPUT);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  analogWriteFrequency(MOTOR_PWM_FREQ_HZ);
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
    // analogWrite(motorPinA, Utils::mapd(power, 0, 1, 0, 255));
    // analogWrite(motorPinB, 0);
    ledcWrite(motorChannelA, Utils::mapd(power, 0, 1, 0, 255));
    ledcWrite(motorChannelB, 0);
  } else {
    // analogWrite(motorPinA, 0);
    // analogWrite(motorPinB, Utils::mapd(-power, 0, 1, 0, 255));
    ledcWrite(motorChannelA, 0);
    ledcWrite(motorChannelB, Utils::mapd(-power, 0, 1, 0, 255));
  }
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

void Motor::resetEncoder() {
  noInterrupts();
  count = 0;
  interrupts();
}

double Motor::getSpeed() {
  long curTime = millis();
  long dt = curTime - lastTime;
  lastTime = curTime;

  int curCount = count;
  int dCount = curCount - lastCount;
  lastCount = curCount;

  return (double)dCount / ((double)dt / 1000);
}

// void Motor::setSpeedPID(double targetClicksPerSecond) {
//   double currentSpeed = getSpeed();
//   double error = targetClicksPerSecond - currentSpeed;

//   double adjustment = 
// }
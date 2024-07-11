#include <Arduino.h>

#include <constants.h>
#include <motor.h>
#include <tape_sensor.h>

Motor leftM = Motor(LEFT_M_F, LEFT_M_B, LEFT_M_E_A, LEFT_M_E_B);
Motor rightM = Motor(RIGHT_M_F, RIGHT_M_B, RIGHT_M_E_A, RIGHT_M_E_B);
TapeSensor tapeSensor = TapeSensor(TAPE_SENSOR_L, TAPE_SENSOR_R);

void drive(double leftSpeed, double rightSpeed);
void tapeFollow();
void stopAll();

void setup() {
  Serial.begin(9600);
  analogWriteFrequency(250);
  attachInterrupt(RIGHT_M_E_A, []{rightM.updateEncoder();}, RISING);
  attachInterrupt(LEFT_M_E_A, []{leftM.updateEncoder();}, RISING);
  rightM.resetEncoder();
  leftM.resetEncoder();
}

void loop() {
  tapeFollow();
  delay(10);

  // leftM.setSpeed(0.5);
  // rightM.setSpeed(0.5);
  // Serial.println(tapeSensor.getValuesStr());
  // Serial.println(String(leftM.getCount()) + " " + String(rightM.getCount()));
  // leftM.resetEncoder();
  // rightM.resetEncoder();
  // delay(1000);

  // rightM.setSpeed(1);
  // leftM.setSpeed(1);
  // Serial.println(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
  // // rightM.resetEncoder();
  // delay(1000);
}

void tapeFollow() {
  switch (tapeSensor.reading()) {
    case TapeReading::BOTH:
      // no tape, go straight
      Serial.println("straight");
      drive(MOTOR_FAST_SPEED, MOTOR_FAST_SPEED);
      break;
    case TapeReading::LEFT:
      // front left tape, turn left
      Serial.println("left");
      drive(MOTOR_SLOW_SPEED, MOTOR_FAST_SPEED);
      break;
    case TapeReading::RIGHT:
      // front right tape, turn right
      Serial.println("right");
      drive(MOTOR_FAST_SPEED, MOTOR_SLOW_SPEED);
      break;
    case TapeReading::NONE:
      // both tapes, stop
      Serial.println("stop");
      stopAll();
      // drive(0, 0);
      break;
  }
}

void drive(double leftSpeed, double rightSpeed) {
  leftM.setSpeed(leftSpeed);
  rightM.setSpeed(rightSpeed);
}

void stopAll() {
  leftM.stop();
  rightM.stop();
}

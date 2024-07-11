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
void drive_with_pid(double leftSpeed, double rightSpeed);
double e1_previous_error = 0.0;
double e2_previous_error = 0.0;
double left_speed = MOTOR_FAST_SPEED;
double right_speed = MOTOR_FAST_SPEED;
double e1_sum_error = 0.0;
double e2_sum_error = 0.0;

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
  delay(5);

  // leftM.setSpeed(1);
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
      drive_with_pid(left_speed, right_speed);
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

void drive_with_pid(double leftSpeed, double rightSpeed) {
  //take the target in terms of the set left wheel speed in spaces of 5 ms
  leftM.setSpeed(leftSpeed);
  rightM.setSpeed(rightSpeed);
  int target_encoders = leftSpeed / WHEEL_CIRCUMFERENCE_IN * 5 * 0.75;
  double KP = 0.02;
  double KD = 0.01;
  double KI = 0.005;
  leftM.resetEncoder();
  rightM.resetEncoder();
  delay (5);
  double e1_error = target_encoders - leftM.getCount();
  double e2_error = target_encoders - rightM.getCount();
  left_speed += e1_error * KP + e1_previous_error*KD + e1_sum_error * KI;
  right_speed += e2_error * KP + e2_previous_error*KD + e2_sum_error * KI;
  left_speed = max(min(float(1), float(left_speed)), float(0));
  right_speed = max(min(float(1), float(right_speed)), float(0));
  e1_previous_error = e1_error;
  e2_previous_error = e2_error;
  e1_sum_error += e1_error;
  e2_sum_error += e2_error;
}

void stopAll() {
  leftM.stop();
  rightM.stop();
}

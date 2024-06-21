#include <Arduino.h>

#include <constants.h>
#include <motor.h>
#include <tape_sensor.h>

Motor frontLeftM = Motor(FRONT_LEFT_F, FRONT_LEFT_B, FRONT_LEFT_E);
Motor frontRightM = Motor(FRONT_RIGHT_F, FRONT_RIGHT_B, FRONT_RIGHT_E);
Motor backLeftM = Motor(BACK_LEFT_F, BACK_LEFT_B, BACK_LEFT_E);
Motor backRightM = Motor(BACK_RIGHT_F, BACK_RIGHT_B, BACK_RIGHT_E);

TapeSensor frontLeft = TapeSensor(FRONT_LEFT_T);
TapeSensor frontRight = TapeSensor(FRONT_RIGHT_T);
TapeSensor backLeft = TapeSensor(BACK_LEFT_T);
TapeSensor backRight = TapeSensor(BACK_RIGHT_T);

void drive(double axial, double lateral, double yaw, double speed);
void lineFollowStraight();
void turnLeft(double speed);
void turnRight(double speed);

void setup() {
  Serial.begin(9600);
  // frontLeftM = Motor(FRONT_LEFT_F, FRONT_LEFT_B, FRONT_LEFT_E);
  // frontRightM = Motor(FRONT_RIGHT_F, FRONT_RIGHT_B, FRONT_RIGHT_E);
  // backLeftM = Motor(BACK_LEFT_F, BACK_LEFT_B, BACK_LEFT_E);
  // backRightM = Motor(BACK_RIGHT_F, BACK_RIGHT_B, BACK_RIGHT_E);
}

void loop() {
  // int a = frontLeft.getValue();
  // int b = frontRight.getValue();
  // Serial.println(String(a) + " " + String(b));
  // int c = backLeft.isTape();
  // int d = backRight.isTape();
  // digitalWrite(37, frontLeft.isTape() ? LOW : HIGH);
  // drive(-1, 0, 0, 1);
  lineFollowStraight();
  delay(10);
}

void lineFollowStraight() {
  double power = 0.5;
  
  // int a = frontLeft.getValue();
  // int b = frontRight.getValue();
  // Serial.println(String(a) + " " + String(b));
  if (!frontLeft.isTape() && !frontRight.isTape()) {
    drive(1, 0, 0, power);
  } else if (frontLeft.isTape() && !frontRight.isTape()) {
    // front left tape, turn left
    drive(0, 0, -1, power);
    // turnLeft(power);
  } else if (!frontLeft.isTape() && frontRight.isTape()) {
    // front right tape, turn right
    drive(0, 0, 1, power);
    // turnRight(power);
  } else {
    // spin
    drive(0, 0, 0, 0);
  }

  // if (!frontLeft.isTape() && !frontRight.isTape() && !backLeft.isTape() && !backRight.isTape()) {
  //   // no tape, drive straight
  //   drive(1, 0, 0, power);
  // } else if (frontLeft.isTape() && !frontRight.isTape() && !backLeft.isTape() && !backRight.isTape()) {
  //   // front left tape, turn right
  //   drive(0, 0, 1, power);
  // } else if (!frontLeft.isTape() && frontRight.isTape() && !backLeft.isTape() && !backRight.isTape()) {
  //   // front right tape, turn left
  //   drive(0, 0, -1, power);
  // } else if (!frontLeft.isTape() && !frontRight.isTape() && backLeft.isTape() && !backRight.isTape()) {
  //   // back left tape, turn right
  //   drive(0, 0, 1, power);
  // } else if (!frontLeft.isTape() && !frontRight.isTape() && !backLeft.isTape() && backRight.isTape()) {
  //   // back right tape, turn left
  //   drive(0, 0, -1, power);
  // } else {
  //   // spin
  //   drive(0, 0, 1.0, power);
  // }
}

void turnLeft(double speed) {
  frontLeftM.setSpeed(-speed);
  frontRightM.setSpeed(speed);
  backLeftM.setSpeed(speed * 0.5);
  backRightM.setSpeed(speed * 0.5);
}

void turnRight(double speed) {
  frontLeftM.setSpeed(speed);
  frontRightM.setSpeed(-speed);
  backLeftM.setSpeed(speed);
  backRightM.setSpeed(speed * 0.5);
}

/**
 * @param axial the forward/backward speed, between -1 and 1
 * @param lateral the left/right speed, between -1 and 1
 * @param yaw the rotational speed, between -1 and 1. CW is positive
 * @param speed the speed of the robot, between 0 and 1
 */
void drive(double axial, double lateral, double yaw, double speed) {
  double frontLeftPower = axial + lateral + yaw;
  double frontRightPower = axial - lateral - yaw;
  double backLeftPower = axial - lateral + yaw;
  double backRightPower = axial + lateral - yaw;
  
  double maxPower = max(abs(frontLeftPower), abs(frontRightPower));
  maxPower = max(abs(maxPower), abs(backLeftPower));
  maxPower = max(abs(maxPower), abs(backRightPower));

  if (maxPower > 1) {
    frontLeftPower /= maxPower;
    frontRightPower /= maxPower;
    backLeftPower /= maxPower;
    backRightPower /= maxPower;
  }

  frontLeftM.setSpeed(frontLeftPower * speed);
  frontRightM.setSpeed(frontRightPower * speed);
  backLeftM.setSpeed(backLeftPower * speed);
  backRightM.setSpeed(backRightPower * speed);
}
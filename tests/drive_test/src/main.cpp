#include <Arduino.h>

#include <constants.h>
#include <motor.h>
#include <tape_sensor.h>

Motor frontLeftM = Motor(FRONT_LEFT_F, FRONT_LEFT_B, FRONT_LEFT_E);
Motor frontRightM = Motor(FRONT_RIGHT_F, FRONT_RIGHT_B, FRONT_RIGHT_E);
Motor backLeftM = Motor(BACK_LEFT_F, BACK_LEFT_B, BACK_LEFT_E);
Motor backRightM = Motor(BACK_RIGHT_F, BACK_RIGHT_B, BACK_RIGHT_E);

// TapeSensor frontLeft;
// TapeSensor frontRight;
// TapeSensor backLeft;
// TapeSensor backRight;

void setup() {
  // frontLeftM = Motor(FRONT_LEFT_F, FRONT_LEFT_B, FRONT_LEFT_E);
  // frontRightM = Motor(FRONT_RIGHT_F, FRONT_RIGHT_B, FRONT_RIGHT_E);
  // backLeftM = Motor(BACK_LEFT_F, BACK_LEFT_B, BACK_LEFT_E);
  // backRightM = Motor(BACK_RIGHT_F, BACK_RIGHT_B, BACK_RIGHT_E);
}

void loop() {
  frontLeftM.setSpeed(0.5);
  frontRightM.setSpeed(0.5);
  backLeftM.setSpeed(0.5);
  backRightM.setSpeed(0.5);
  delay(1000);
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
  
  double maxPower = max(frontLeftPower, frontRightPower);
  maxPower = max(maxPower, backLeftPower);
  maxPower = max(maxPower, backRightPower);

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
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
// TapeSensor backLeft = TapeSensor(BACK_LEFT_T);
// TapeSensor backRight = TapeSensor(BACK_RIGHT_T);

void drive(double axial, double lateral, double yaw, double speed);
void lineFollowStraight();
String encodeTapeReadings();
void turnLeft(double speed);
void turnRight(double speed);
void stopAll();

void setup() {
  Serial.begin(9600);
}

void loop() {
  // analogWrite(21, 128);
  // digitalWrite(20, HIGH);
  // drive(1, 0, 0, 0.3);
  // delay(1000);
  lineFollowStraight();
  delay(1);
}

void lineFollowStraight() {
  Serial.println(encodeTapeReadings());
  
  double power = 0.5;
  
  if (!frontLeft.isTape() && !frontRight.isTape()) {
    Serial.println("straight");
    drive(1, 0, 0, power);
  } else if (frontLeft.isTape() && !frontRight.isTape()) {
    // front left tape, turn left
    Serial.println("left");
    drive(0, 0, -1, power);
    // turnLeft(power);
  } else if (!frontLeft.isTape() && frontRight.isTape()) {
    // front right tape, turn right
    Serial.println("right");
    drive(0, 0, 1, power);
    // turnRight(power);
  } else {
    // stop
    Serial.println("stop");
    drive(0, 0, 0, 0);
  }

  int a = frontLeft.getValue();
  int b = frontRight.getValue();
  // int c = backLeft.getValue();
  // int d = backRight.getValue();
  Serial.println(String(a) + " " + String(b));
  // bool e = frontLeft.isTape();
  // bool f = frontRight.isTape();
  // bool g = backLeft.isTape();
  // bool h = backRight.isTape();
  // Serial.println(String(e) + " " + String(f) + " " + String(g) + " " + String(h));
  // drive(1, 0, 0, power);

  // if (encodeTapeReadings() == "0000") {
  //   // no tape, drive straight
  //   drive(1, 0, 0, power);
  //   Serial.println("straight");
  // } else if (encodeTapeReadings() == "1000" || encodeTapeReadings() == "1001" || encodeTapeReadings() == "0001") {
  //   // front left tape, turn left
  //   drive(0, 0.5, -1, power);
  //   Serial.println("turn left");
  // } else if (encodeTapeReadings() == "0100" || encodeTapeReadings() == "0110" || encodeTapeReadings() == "0010") {
  //   // front right tape, turn right
  //   drive(0, 0.5, 1, power);
  //   Serial.println("turn right");
  // } else if (encodeTapeReadings() == "1010") {
  //   // drive left
  //   drive(0, -1, 0, power);
  //   Serial.println("drive left");
  // } else if (encodeTapeReadings() == "0101") {
  //   // drive right
  //   drive(0, 1, 0, power);
  //   Serial.println("drive right");
  // } else {
  //   // stop
  //   stopAll();
  //   Serial.println("stop");
  // }
}

String encodeTapeReadings() {
  
  return String(frontLeft.isTape() ? '1' : '0') + String(frontRight.isTape() ? '1' : '0');
  // return String(frontLeft.isTape() ? '1' : '0') + String(frontRight.isTape() ? '1' : '0') + String(backLeft.isTape() ? '1' : '0') + String(backRight.isTape() ? '1' : '0');
}

// void turnLeft(double speed) {
//   frontLeftM.setSpeed(-speed);
//   frontRightM.setSpeed(speed);
//   backLeftM.setSpeed(speed * 0.5);
//   backRightM.setSpeed(speed * 0.5);
// }

// void turnRight(double speed) {
//   frontLeftM.setSpeed(speed);
//   frontRightM.setSpeed(-speed);
//   backLeftM.setSpeed(speed);
//   backRightM.setSpeed(speed * 0.5);
// }

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
  maxPower = max(maxPower, abs(backLeftPower));
  maxPower = max(maxPower, abs(backRightPower));

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

void stopAll() {
  frontLeftM.stop();
  frontRightM.stop();
  backLeftM.stop();
  backRightM.stop();
}
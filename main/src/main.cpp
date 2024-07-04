#include <Arduino.h>

#include <constants.h>
#include <motor.h>
#include <tape_sensor.h>

Motor frontM = Motor(FRONT_F, FRONT_B);
Motor backM = Motor(BACK_F, BACK_B);
Motor leftM = Motor(LEFT_F, LEFT_B);
Motor rightM = Motor(RIGHT_F, RIGHT_B);

TapeSensor frontLeft = TapeSensor(FRONT_LEFT_T);
TapeSensor frontRight = TapeSensor(FRONT_RIGHT_T);

void drive(double left, double right);
void lineFollowStraight();
void stopAll();

void setup() {
  Serial.begin(9600);
}

void loop() {
  // drive(1, 1);
  // drive(0.7, 0.7); 5 Volts
  // delay(1000);

  lineFollowStraight();
  delay(10);
}

void lineFollowStraight() {  
  if (!frontLeft.isTape() && !frontRight.isTape()) {
    Serial.println("straight");
    drive(0.5, 0.5);
  } else if (frontLeft.isTape() && !frontRight.isTape()) {
    // front left tape, turn left
    Serial.println("left");
    drive(0.3, 0.5);
  } else if (!frontLeft.isTape() && frontRight.isTape()) {
    // front right tape, turn right
    Serial.println("right");
    drive(0.5, 0.3);
  } else {
    // stop
    drive(0, 0);
  }

  int a = frontLeft.getValue();
  int b = frontRight.getValue();
  Serial.println(String(a) + " " + String(b));
}

void drive(double left, double right) {
  leftM.setSpeed(left);
  rightM.setSpeed(right);
}

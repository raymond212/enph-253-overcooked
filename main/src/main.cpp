#include <Arduino.h>

#include <constants.h>
#include <motor.h>
#include <tape_sensor.h>

Motor frontM = Motor(FRONT_M_F, FRONT_M_B);
Motor backM = Motor(BACK_M_F, BACK_M_B);
Motor leftM = Motor(LEFT_M_F, LEFT_M_B);
Motor rightM = Motor(RIGHT_M_F, RIGHT_M_B);

TapeSensor frontTS = TapeSensor(FRONT_TS_L, FRONT_TS_R);
TapeSensor backTS = TapeSensor(BACK_TS_L, BACK_TS_R);
TapeSensor leftTS = TapeSensor(LEFT_TS_L, LEFT_TS_R);
TapeSensor rightTS = TapeSensor(RIGHT_TS_L, RIGHT_TS_R);

// relative motors/tape sensors for tape following
Direction tapeFollowDir = Direction::FRONT;
Motor* relLeftM = &leftM;
Motor* relRightM = &rightM;
TapeSensor* relFrontTS = &frontTS;
int motorDirectionFactor = 1; // 1 for normal, -1 for reverse

void drive(double leftSpeed, double rightSpeed);
void tapeFollowStraight();
void updateRelMandTS(Direction newDir);
void stopAll();

void setup() {
  Serial.begin(9600);
  // updateRelMandTS(Direction::FRONT);
}

void loop() {
  leftM.setSpeed(0.8);
  rightM.setSpeed(0.8);
  // frontM.setSpeed(-0.5);
  // backM.setSpeed(-0.5);
  // drive(1, 1);
  // drive(0.7, 0.7); 5 Volts
  delay(1000);

  // tapeFollowStraight();
  // delay(10);
}

void updateRelMandTS(Direction newDir) {
  switch (newDir) {
    case Direction::FRONT:
      relLeftM = &leftM;
      relRightM = &rightM;
      relFrontTS = &frontTS;
      motorDirectionFactor = 1;
      break;
    case Direction::BACK:
      relLeftM = &rightM;
      relRightM = &leftM;
      relFrontTS = &backTS;
      motorDirectionFactor = -1;
      break;
    case Direction::LEFT:
      relLeftM = &backM;
      relRightM = &frontM;
      relFrontTS = &leftTS;
      motorDirectionFactor = 1;
      break;
    case Direction::RIGHT:
      relLeftM = &frontM;
      relRightM = &backM;
      relFrontTS = &rightTS;
      motorDirectionFactor = -1;
      break;
  }
}

void tapeFollowStraight() {  
  switch ((*relFrontTS).getReading()) {
    case TapeReading::NONE:
      // no tape, go straight
      Serial.println("straight");
      drive(0.5, 0.5);
      break;
    case TapeReading::LEFT:
      // front left tape, turn left
      Serial.println("left");
      drive(0.3, 0.5);
      break;
    case TapeReading::RIGHT:
      // front right tape, turn right
      Serial.println("right");
      drive(0.5, 0.3);
      break;
    case TapeReading::BOTH:
      // both tapes, stop
      Serial.println("stop");
      drive(0, 0);
      break;
  }
  // Serial.println(relFrontTS.getValues());
}

void drive(double leftSpeed, double rightSpeed) {
  (*relLeftM).setSpeed(leftSpeed * motorDirectionFactor);
  (*relRightM).setSpeed(rightSpeed * motorDirectionFactor);
}

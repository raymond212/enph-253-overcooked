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
TapeSensor* relBackTS = &backTS;
TapeSensor* relLeftTS = &leftTS;
TapeSensor* relRightTS = &rightTS;

int motorDirectionFactor = 1; // 1 for normal, -1 for reverse

void drive(double leftSpeed, double rightSpeed);
bool tapeFollow(StoppingCondition condition, int sideTSNum=0);
void updateRelMandTS(Direction newDir);
bool checkStoppingCondition(StoppingCondition condition, int sideTSNum=0);
void resetTapeFollow();

void stopAll();

void setup() {
  Serial.begin(9600);
  updateRelMandTS(Direction::FRONT);
  analogWriteFrequency(300);
}

void loop() {
  resetTapeFollow();
  while (!tapeFollow(StoppingCondition::LEFT_TAPE, 1)) {
    // Serial.println(frontTS.getValues() + " | " + backTS.getValues() + " | " + leftTS.getValues() + " | " + rightTS.getValues());
    delay(1);
  }
  drive(-0.8, -0.8);
  delay(100);
  stopAll();
  delay(5000);

  // updateRelMandTS(Direction::BACK);
  // resetTapeFollow();
  // while (!tapeFollow(StoppingCondition::RIGHT_TAPE, 1)) {
  //   delay(10);
  // }
  // stopAll();
  // delay(2000);
  
}

void updateRelMandTS(Direction newDir) {
  switch (newDir) {
    case Direction::FRONT:
      relLeftM = &leftM;
      relRightM = &rightM;

      relFrontTS = &frontTS;
      relBackTS = &backTS;
      relLeftTS = &leftTS;
      relRightTS = &rightTS;

      motorDirectionFactor = 1;
      break;
    case Direction::BACK:
      relLeftM = &rightM;
      relRightM = &leftM;

      relFrontTS = &backTS;
      relBackTS = &frontTS;
      relLeftTS = &rightTS;
      relRightTS = &leftTS;

      motorDirectionFactor = -1;
      break;
    case Direction::LEFT:
      relLeftM = &backM;
      relRightM = &frontM;

      relFrontTS = &leftTS;
      relBackTS = &rightTS;
      relLeftTS = &backTS;
      relRightTS = &frontTS;

      motorDirectionFactor = 1;
      break;
    case Direction::RIGHT:
      relLeftM = &frontM;
      relRightM = &backM;

      relFrontTS = &rightTS;
      relBackTS = &leftTS;
      relLeftTS = &frontTS;
      relRightTS = &backTS;

      motorDirectionFactor = -1;
      break;
  }
}

bool sideTSPrev = true;
int sideTSCount = 0;

void resetTapeFollow() {
  sideTSPrev = true;
  sideTSCount = 0;
}

bool checkStoppingCondition(StoppingCondition condition, int sideTSNum) {
  // stop based on side tape
  if (condition == StoppingCondition::LEFT_TAPE || condition == StoppingCondition::RIGHT_TAPE) {
    bool curReading = (condition == StoppingCondition::LEFT_TAPE) ? (*relLeftTS).rightIsTape() : (*relRightTS).leftIsTape();
    if (!sideTSPrev && curReading) {
      sideTSCount++;
    }
    bool res = (sideTSCount == sideTSNum);
    // bool res = (sideTSCount == sideTSNum) && !curReading;
    sideTSPrev = curReading;
    // Serial.println(String(sideTSCount) + " " + String(curReading) + " " + String(res));
    return res;
  }
  // stop based on wall
  return false;
}

bool tapeFollow(StoppingCondition condition, int sideTSNum) {
  switch ((*relFrontTS).reading()) {
    case TapeReading::NONE:
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
    case TapeReading::BOTH:
      // both tapes, stop
      Serial.println("stop");
      stopAll();
      // drive(0, 0);
      break;
  }
  return checkStoppingCondition(condition, sideTSNum);
}

void drive(double leftSpeed, double rightSpeed) {
  (*relLeftM).setSpeed(leftSpeed * motorDirectionFactor);
  (*relRightM).setSpeed(rightSpeed * motorDirectionFactor);
}

void stopAll() {
  frontM.stop();
  backM.stop();
  leftM.stop();
  rightM.stop();
}

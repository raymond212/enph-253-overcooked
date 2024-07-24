#include <drivetrain.h>

namespace Drivetrain {
  Motor FLMotor = Motor(FL_MOTOR_PIN_A, FL_MOTOR_PIN_B, FL_MOTOR_CHANNEL_A, FL_MOTOR_CHANNEL_B);
  Motor FRMotor = Motor(FR_MOTOR_PIN_A, FR_MOTOR_PIN_B, FR_MOTOR_CHANNEL_A, FR_MOTOR_CHANNEL_B);
  Motor BLMotor = Motor(BL_MOTOR_PIN_A, BL_MOTOR_PIN_B, BL_MOTOR_CHANNEL_A, BL_MOTOR_CHANNEL_B);
  Motor BRMotor = Motor(BR_MOTOR_PIN_A, BR_MOTOR_PIN_B, BR_MOTOR_CHANNEL_A, BR_MOTOR_CHANNEL_B);

  void setupDrivetrain() {
    // Motor setup is done in the Motor constructor
    TapeSensors::setupTapeSensors();
  }

  void driveMotors(double FLPower, double FRPower, double BLPower, double BRPower) {
    FLMotor.setPower(FLPower);
    FRMotor.setPower(FRPower);
    BLMotor.setPower(BLPower);
    BRMotor.setPower(BRPower);
  }

  void driveMecanum(double theta, double rotation, double power) {
    double sinTerm = sin((theta + 45) * PI / 180);
    double cosTerm = cos((theta + 45) * PI / 180);
    double maxTerm = max(abs(sinTerm), abs(cosTerm));

    double FLPower = power * (cosTerm / maxTerm) + rotation;
    double FRPower = power * (sinTerm / maxTerm) - rotation;
    double BLPower = power * (sinTerm / maxTerm) + rotation;
    double BRPower = power * (cosTerm / maxTerm) - rotation;

    double maxPower = max(max(abs(FLPower), abs(FRPower)), max(abs(BLPower), abs(BRPower)));

    if (maxPower > 1) {
      FLPower /= maxPower;
      FRPower /= maxPower;
      BLPower /= maxPower;
      BRPower /= maxPower;
    }
    Serial.println(String(FLPower) + " " + String(FRPower) + " " + String(BLPower) + " " + String(BRPower));
    driveMotors(FLPower, FRPower, BLPower, BRPower);
  }

  void stopAll() {
    driveMotors(0, 0, 0, 0);
  }

  void run() {
    // run
  }

  void wallFollow(DriveDirection driveDirection, WallLocation wallLocation, int num) {
    int count = 0;
    int iter = 0;
    int lastTapeTime = millis();
    int start = millis();
    bool seeTape = false;
    if (driveDirection == DriveDirection::FORWARD) {
      if (wallLocation == WallLocation::RIGHT) {
        driveMecanum(-WALL_FOLLOW_ANGLE_DEG, 0, TAPE_FOLLOW_LOW_POWER);
      } else {
        driveMecanum(WALL_FOLLOW_ANGLE_DEG, 0, TAPE_FOLLOW_LOW_POWER);
      }
    } else if (driveDirection == DriveDirection::BACKWARD) {
      if (wallLocation == WallLocation::RIGHT) {
        driveMecanum(-180 + WALL_FOLLOW_ANGLE_DEG, 0, TAPE_FOLLOW_LOW_POWER);
      } else {
        driveMecanum(180 - WALL_FOLLOW_ANGLE_DEG, 0, TAPE_FOLLOW_LOW_POWER);
      }
    }

    while (count < num) {
      seeTape = driveDirection == DriveDirection::FORWARD ? TapeSensors::backIsTape() : TapeSensors::frontIsTape();
      if (seeTape && millis() - lastTapeTime > TAPE_DEBOUNCE_DELAY && millis() - start > WALL_FOLLOW_DELAY) {
        lastTapeTime = millis();
        count++;
      }
      iter++;
    }

    Network::wifiPrintln("Time: " + String(millis() - start) + " Iter: " + String(iter));

    // active breaking
    int breakAngle = driveDirection == DriveDirection::FORWARD ? 180 : 0;
    driveMecanum(breakAngle, 0, 0.4);
    delay(5);
    stopAll();

    // drive back into wall
    // int wallAngle = wallLocation == WallLocation::RIGHT ? -90 : 90;
    // driveMecanum(wallAngle, 0, 0.7);
    // delay(100);
    // stopAll();
  }

  void wallToWall(DriveDirection driveDirection) {
    int wallAngle = driveDirection == DriveDirection::RIGHT ? -90 : 90;
    driveMecanum(wallAngle, 0, 0.5);
    delay(440);
    driveMecanum(wallAngle, 0, 0.25);
    delay(135);
    stopAll();
  }

  void wallToWallSpin(DriveDirection driveDirection, int driveTimeMS, int spinTimeMS) {
    int wallAngle = driveDirection == DriveDirection::RIGHT ? -90 : 90;
    driveMecanum(wallAngle, 0, 0.25);
    delay(driveTimeMS);
    driveMecanum(0, 0.3, 0);
    delay(spinTimeMS);
    driveMecanum(wallAngle + 180, 0, 0.25);
    delay(driveTimeMS);
    stopAll();
  }
}
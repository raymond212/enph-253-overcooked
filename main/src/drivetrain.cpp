#include <drivetrain.h>

namespace Drivetrain {
  Motor FLMotor = Motor(FL_MOTOR_PIN_A, FL_MOTOR_PIN_B, FL_MOTOR_CHANNEL_A, FL_MOTOR_CHANNEL_B);
  Motor FRMotor = Motor(FR_MOTOR_PIN_A, FR_MOTOR_PIN_B, FR_MOTOR_CHANNEL_A, FR_MOTOR_CHANNEL_B);
  Motor BLMotor = Motor(BL_MOTOR_PIN_A, BL_MOTOR_PIN_B, BL_MOTOR_CHANNEL_A, BL_MOTOR_CHANNEL_B);
  Motor BRMotor = Motor(BR_MOTOR_PIN_A, BR_MOTOR_PIN_B, BR_MOTOR_CHANNEL_A, BR_MOTOR_CHANNEL_B);

  void setupDrivetrain() {
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

    double FLPower = power * (cosTerm / maxTerm) - rotation;
    double FRPower = power * (sinTerm / maxTerm) + rotation;
    double BLPower = power * (sinTerm / maxTerm) - rotation;
    double BRPower = power * (cosTerm / maxTerm) + rotation;

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

  void wallFollow(DriveDirection driveDirection, WallLocation wallLocation, int skip) {
    int count = 0;
    int iter = 0;
    int lastTapeTime = millis();
    int start = millis();
    bool seeTape = false;
    if (driveDirection == DriveDirection::FORWARD) {
      if (wallLocation == WallLocation::RIGHT) {
        driveMecanum(-WALL_FOLLOW_ANGLE_DEG, 0, WALL_FOLLOW_SLOW_POWER);
      } else {
        driveMecanum(WALL_FOLLOW_ANGLE_DEG, 0, WALL_FOLLOW_SLOW_POWER);
      }
    } else if (driveDirection == DriveDirection::BACKWARD) {
      if (wallLocation == WallLocation::RIGHT) {
        driveMecanum(-180 + WALL_FOLLOW_ANGLE_DEG, 0, WALL_FOLLOW_SLOW_POWER);
      } else {
        driveMecanum(180 - WALL_FOLLOW_ANGLE_DEG, 0, WALL_FOLLOW_SLOW_POWER);
      }
    }

    while (count < skip + 1) {
      seeTape = (driveDirection == DriveDirection::FORWARD) ? TapeSensors::backIsTape() : TapeSensors::frontIsTape();
      if (seeTape && millis() - lastTapeTime > TAPE_DEBOUNCE_DELAY && millis() - start > WALL_FOLLOW_DELAY) {
        lastTapeTime = millis();
        count++;
      }
      iter++;
    }

    Network::wifiPrintln("Time: " + String(millis() - start) + " Iter: " + String(iter));

    // active breaking
    int breakAngle = driveDirection == DriveDirection::FORWARD ? 180 : 0;
    driveMecanum(breakAngle, 0, 0.6);
    delay(10);
    stopAll();

    // drive back into wall
    // int wallAngle = wallLocation == WallLocation::RIGHT ? -90 : 90;
    // driveMecanum(wallAngle, 0, 0.7);
    // delay(300);
    // stopAll();
  }

  void wallToWall(DriveDirection driveDirection, int slowTimeMS, int fastTimeMS, double slowPower, double fastPower) {
    int wallAngle = Utils::directionToAngle(driveDirection);
    driveMecanum(wallAngle, 0, fastPower);
    delay(fastTimeMS);
    driveMecanum(wallAngle, 0, slowPower);
    delay(slowTimeMS);
    stopAll();
  }

  void wallToWallSpin(DriveDirection driveDirection, int driveTimeMS, int spinTimeMS, double drivePower, double spinPower) {
    int wallAngle = Utils::directionToAngle(driveDirection);
    driveMecanum(wallAngle, 0, drivePower);
    delay(driveTimeMS);
    driveMecanum(0, spinPower, 0);
    delay(spinTimeMS);
    driveMecanum(Utils::invertAngle(wallAngle), 0, drivePower);
    delay(driveTimeMS);
    stopAll();
  }
}
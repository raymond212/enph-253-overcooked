#pragma once

#include <Arduino.h>
#include <constants.h>

#include <motor.h>
#include <tape_sensors.h>
#include <network.h>
#include <utils.h>

namespace Drivetrain {
  /**
   * Initialize the drivetrain, which consists of two encoded motors
   */
  void setupDrivetrain();

  void driveTest();

  /**
   * Tape follow the target distance in inches
   */
  void tapeFollow(double targetDistance);

  /**
   * Turn the robot until tape is detected
   */
  void turnUntilTape(TurnDirection dir);

  void driveUpToTable();

  void backUpToTape();

  /**
   * Drive the robot with the specified left and right power
   */
  void drive(double leftPower, double rightPower);

  void run();
}
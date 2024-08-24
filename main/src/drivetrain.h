#pragma once

#include <Arduino.h>
#include <constants.h>

#include <motor.h>
#include <tape_sensors.h>
#include <utils.h>

namespace Drivetrain {
  void setupDrivetrain();

  void driveMotors(double FLPower, double FRPower, double BLPower, double BRPower);

  /**
   * Drive the robot in a mecanum drive configuration
   * 
   * @param theta the drive direction, measured CCW from the forward axis
   * @param rotation the CW rotation power, between -1.0 and 1.0
   * @param power the drive power, between -1.0 and 1.0
   */
  void driveMecanum(double theta, double rotation, double power);
  void driveMecanumTime(double theta, double rotation, double power, int timeMS);
  void stopAll();
  
  void wallFollow(DriveDirection driveDirection, WallLocation wallLocation, int skip, int slowDownTime, bool startOnTape, bool shouldBreak = true);
  void wallToWall(DriveDirection driveDirection, int slowTimeMS, int fastTimeMS, double slowPower, double fastPower);
  void wallToWallSpin(DriveDirection driveDirection, int driveTimeMS, int spinTimeMS, double drivePower, double spinPower);

  void wallToWallSpinSlow();
  void wallToWallSpinFast();
  void wallToWallSlow(DriveDirection driveDirection);
}
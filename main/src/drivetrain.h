#pragma once

#include <Arduino.h>
#include <constants.h>

#include <motor.h>
#include <tape_sensors.h>
#include <utils.h>

namespace Drivetrain {
  /**
   * Initialize the drivetrain, which consists of four motors
   */
  void setupDrivetrain();

  /**
   * Drive the motors at their respective powers
   * 
   * @param FLPower between -1.0 and 1.0
   * @param FRPower between -1.0 and 1.0
   * @param BLPower between -1.0 and 1.0
   * @param BRPower between -1.0 and 1.0
   */
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

  /**
   * Stop all motors
   */
  void stopAll();

  /**
   * Follow a wall until tape is detected
   * 
   * @param driveDirection the direction to drive in, either FORWARD or BACKWARD
   * @param wallLocation the location of the wall relative to the robot, either LEFT or RIGHT
   * @param skip the number of tapes to skip before stopping
   */
  void wallFollow(DriveDirection driveDirection, WallLocation wallLocation, int skip, int slowDownTime, bool startOnTape, bool shouldBreak = true, bool bottomCloseInput = false);

  /**
   * Move from wall to wall
   * 
   * @param driveDirection the direction to drive in, either LEFT or RIGHT
   */
  void wallToWall(DriveDirection driveDirection, int slowTimeMS, int fastTimeMS, double slowPower, double fastPower);

  /**
   * Move from wall to wall while making a 180 degree spin
   * 
   * @param driveDirection the direction to drive in, either LEFT or RIGHT
   */
  void wallToWallSpin(DriveDirection driveDirection, int driveTimeMS, int spinTimeMS, double drivePower, double spinPower);

  void wallToWallSpinSlow();
  void wallToWallSpinFast();
  void wallToWallSlow(DriveDirection driveDirection);
}
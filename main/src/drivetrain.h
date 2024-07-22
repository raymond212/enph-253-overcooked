#pragma once

#include <Arduino.h>
#include <constants.h>

#include <motor.h>
#include <tape_sensors.h>
#include <network.h>
#include <utils.h>

namespace Drivetrain {
  /**
   * Initialize the drivetrain, which consists of four motors
   */
  void setupDrivetrain();

  void driveMotors(double FLPower, double FRPower, double BLPower, double BRPower);

  void driveMecanum(double x, double y, double rotation);

  void stopAll();
  
  void run();

  void driveFUntilTape(int skip = 0);

  void driveBUntilTape(int skip = 0);
}
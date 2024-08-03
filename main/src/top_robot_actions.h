#pragma once

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <top_robot_modules.h>

namespace TopRobotActions {
  // ACTIONS
  void movePusherOut();
  void movePusherIn();
  void reloadPusherPatty();
  void inputRoutine();
  void transferRoutine();

  // DRIVING
  void startToBuns();
  void bottomBunDriveProcedure();
  void bunsToCutting();
  void cuttingToPatties();
  void pattiesToCooktop();
  void cooktopToBuns();
  void bunsToCooktop();
  void bunsToCooktop();
}
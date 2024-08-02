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

  // DRIVING
  void startToBuns();
}
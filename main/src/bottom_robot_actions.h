#pragma once

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <bottom_robot_modules.h>

namespace BottomRobotActions {
  // ACTIONS
  void inputSingle();
  void servingRoutine();

  // DRIVING
  void startToCutting();
  void cuttingToTomato();
  void tomatoToCheese();
  void cheeseToCooktop();
  void cooktopToLettuce();
  void lettuceToCooktop();
  void cooktopGrabPlate();
  void plateToServing();
  void servingToCooktop();
}
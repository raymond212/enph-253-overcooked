#pragma once

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <bottom_robot_modules.h>

namespace BottomRobotActions {
  void inputSingle();
  void cooktopGrabPlate();
  void plateToServing();
  void servingRoutine();
  void servingToCooktop();
  void wallToWallSpinSlow();
  void wallToWallSpinFast();

  // bottom robot assembles burger
  void startToCutting();
  void cuttingToTomato();
  void tomatoToCheese();
  void cheeseToCooktop();
  void cooktopToLettuce();
  void lettuceToCooktop();
}
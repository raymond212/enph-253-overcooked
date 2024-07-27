#pragma once

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <bottom_robot_modules.h>

namespace Actions {
  void startTomato1();
  void inputRoutine();
  void tomatoToLettuce();
  void alignLettuce1();
  void lettuceToCooktop();
  void cooktopGrabPlate();
  void plateToServing();
  void servingRoutine();
  void servingToCooktop();
  void wallToWallSpinSlow();
}
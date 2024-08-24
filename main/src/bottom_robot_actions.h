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
  void startToPlate();
  void plateToCutting();
  void cuttingToTomato();
  void tomatoToCheese();
  void cheeseToLettuce();
  void lettuceToCooktop();
  void cooktopToCutting();
  void cuttingToServing();
  void servingToCooktop();
  void servingToPlate();
}
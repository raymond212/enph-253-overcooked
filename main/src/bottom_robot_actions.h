#pragma once

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <bottom_robot_modules.h>

namespace BottomRobotActions {
  // ACTIONS
  void inputSingle();
  void servingRoutine();

  // DRIVING SINGLE BURGER V1
  void startToCutting();
  void cuttingToTomato();
  void tomatoToCheese();
  void cheeseToCooktop();
  void cooktopToLettuce();
  void lettuceToCooktop();
  void cooktopGrabPlate();
  void plateToServing();
  void servingToCooktop();

  // DRIVING SINGLE BURGER V2
  void startToPlate();
  void plateToCutting();
  // cuttingToTomato();
  // tomatoToCheese();
  void cheeseToLettuce();
  // lettuceToCooktop();
  void cooktopToCutting();
  void cuttingToServing();
  void servingToPlate();
}
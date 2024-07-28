#pragma once

#include <Arduino.h>
#include <constants.h>
#include <servo.h>
#include <stepper.h>
#include <drivetrain.h>

namespace TopRobotModules {
  void setupTopRobotModules();
  void closeInputScraper();
  void openInputScraper();
  void rotateSpiralLeft();
  void rotateSpiralRight();
  void raiseOutputScraper();
  void lowerOutputScraper();
  void moveLinearOut();
  void moveLinearIn();
  void InputOutputRoutine();
}
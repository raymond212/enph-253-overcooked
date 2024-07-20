#pragma once

#include <Arduino.h>
#include <constants.h>
#include <servo.h>
#include <stepper.h>
#include <drivetrain.h>

namespace BottomRobotModules {
  void setupBottomRobotModules();
  void run(String s);
  void closeInputScraper();
  void openInputScraper();
  void closeTrapdoor();
  void openTrapdoor();
  void rotateCarouselRight();
  void rotateCarouselLeft();
}
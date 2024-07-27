#pragma once

#include <Arduino.h>
#include <constants.h>
#include <servo.h>
#include <stepper.h>
#include <drivetrain.h>

namespace BottomRobotModules {
  void setupBottomRobotModules();
  void closeInputScraper();
  void openInputScraper();
  void closeTrapdoor();
  void openTrapdoor();
  void closeOutputScraper();
  void openOutputScraper();
  void closePlatePincher();
  void openPlatePincher();
  void rotateCarouselRight();
  void rotateCarouselLeft();
  void moveElevator(double distanceMM);
  void tomatoInputDestack();
}
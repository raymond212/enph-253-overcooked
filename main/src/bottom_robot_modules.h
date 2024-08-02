#pragma once

#include <Arduino.h>
#include <constants.h>
#include <servo.h>
#include <stepper.h>
#include <drivetrain.h>

namespace BottomRobotModules {
  void setupBottomRobotModules();
  // INPUT
  void closeInputScraper();
  void openInputScraper();
  // OUTPUT
  void closeOutputScraper();
  void openOutputScraper();
  // TRAPDOOR
  void closeTrapdoor();
  void openTrapdoor();
  // PLATE PINCHER
  void closePlatePincher();
  void openPlatePincher();
  // CAROUSEL
  void rotateCarouselRight();
  void rotateCarouselLeft();
  // ELEVATOR
  void moveElevator(double distanceMM);
}
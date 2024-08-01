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
  void setInputScraper(double angle);
  void rotateCarouselLeft();
  void rotateCarouselRight();
  void rotateCarousel(double angle);
  void raiseOutputScraper();
  void lowerOutputScraper();
  void setOutputScraper(double angle);
  void movePusherOut();
  void movePusherIn();
}
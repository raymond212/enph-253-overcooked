#pragma once

#include <Arduino.h>
#include <constants.h>
#include <servo.h>
#include <stepper.h>
#include <drivetrain.h>

namespace TopRobotModules {
  void setupTopRobotModules();
  // INPUT
  void closeInputScraper();
  void closeInputScraperPatty();
  void openInputScraper();
  void setInputScraper(double angle);
  // OUTPUT
  void raiseOutputScraper();
  void lowerOutputScraper();
  void setOutputScraper(double angle);
  // CAROUSEL
  void rotateCarouselLeft();
  void rotateCarouselRight();
  void rotateCarousel(double angle, double speed = 0.75);
  // PUSHER
  void movePusher(double revs, bool blocking);
}
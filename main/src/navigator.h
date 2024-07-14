#pragma once

#include <Arduino.h>
#include <constants.h>

#include <utils.h>
#include <drivetrain.h>

namespace Navigator {
  void setupNavigator();

  void navigateToStation(Station station);

  void turnToFace(FacingDirection facingDirection);

  int facingDirectionToInt(FacingDirection facingDirection);
}
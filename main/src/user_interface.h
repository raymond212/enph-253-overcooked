#pragma once

#include <Arduino.h>
#include <constants.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>

namespace UserInterface {
  void setupUserInterface();

  void displayOLED(String text);

  bool isButtonPressed();
}

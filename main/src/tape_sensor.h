#pragma once

#include <Arduino.h>
#include <constants.h>

class TapeSensor {
  public:
    TapeSensor(int leftPin, int rightPin);

    /**
     * Checks if tape is detected
     */
    TapeReading getReading();

    String getValues();
  private:
    int leftPin;
    int rightPin;
};
#pragma once

#include <Arduino.h>
#include <constants.h>

class TapeSensor {
  public:
    TapeSensor(int pin);

    /**
     * Checks if tape is detected
     * 
     * @return true if black is detected and false
     */
    bool isTape();
    int getValue();
  private:
    int pin;
};

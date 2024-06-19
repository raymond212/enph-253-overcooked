#pragma once

#include <Arduino.h>
#include <Constants.h>

class TapeSensor {
  public:
    TapeSensor(int pin);

    /**
     * Get the color detected by the tape sensor
     * 
     * @return BLACK or WHITE
     */
    TAPE_COLOR getColor();
  private:
    int pin;
};

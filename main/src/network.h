#pragma once

#include <Arduino.h>
#include <constants.h>

#include <WiFi.h>

namespace Network {
  extern String message;

  void setupWifi();

  void wifiPrintln(String msg);
  
  bool wifiInput();
}
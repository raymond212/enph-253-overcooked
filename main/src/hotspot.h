#pragma once

#include <Arduino.h>
#include <constants.h>
#include <ArduinoOTA.h>

#include <WiFi.h>

namespace Hotspot {
  extern String message;
  extern long lastOTATime;

  void setupWifi();
  void wifiPrintln(String msg);
  bool wifiInput();
  void handleOTA();
}
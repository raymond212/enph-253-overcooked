#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>

void setup() {
  Serial.begin(9600);

  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
}

void loop() {
  while (!Network::wifiInput()) {
    // wait
  }

  if (Network::message == "R") {
    Network::wifiPrintln("Turning right until tape");
    Drivetrain::turnUntilTape(TurnDirection::RIGHT, 500);
  } else if (Network::message == "L") {
    Network::wifiPrintln("Turning left until tape");
    Drivetrain::turnUntilTape(TurnDirection::LEFT, 500);
  } else {
    Network::wifiPrintln("Starting tape following");
    Drivetrain::tapeFollow(Network::message.toDouble());
  }
}
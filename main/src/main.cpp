#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>
#include <navigator.h>
#include <bottom_robot_modules.h>

void setup() {
  Serial.begin(9600);

  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  Navigator::setupNavigator();
  BottomRobotModules::setupBottomRobotModules();
}

void loop() {
  while (!Network::wifiInput()) {
    // wait
  }
  // while (Serial.available() == 0) {
  // }
  // String s = Serial.readStringUntil('\n');
  // s.trim();
  // BottomRobotModules::run(s);

  // if (Network::message == "R") {
  //   Network::wifiPrintln("Turning right until tape");
  //   Drivetrain::turnUntilTape(TurnDirection::RIGHT);
  // } else if (Network::message == "L") {
  //   Network::wifiPrintln("Turning left until tape");
  //   Drivetrain::turnUntilTape(TurnDirection::LEFT);
  // } else if (Network::message == "F"){
  //   while (!Network::wifiInput()) {
  //     // wait
  //   }
  //   Network::wifiPrintln("Starting tape following");
  //   Drivetrain::tapeFollow(Network::message.toDouble());
  // } else if (Network::message == "B") {
  //   Drivetrain::backUpToTape();
  // }

  String reading = Network::message;
  if (reading == "pa") {
    Navigator::navigateToStation(PATTIES);
  } else if (reading == "bu") {
    Navigator::navigateToStation(BUNS);
  } else if (reading == "po") {
    Navigator::navigateToStation(POTATOES);
  } else if (reading == "to") {
    Navigator::navigateToStation(TOMATOES);
  } else if (reading == "cu") {
    Navigator::navigateToStation(CUTTING);
  } else if (reading == "co") {
    Navigator::navigateToStation(COOKING);
  } else if (reading == "pl") {
    Navigator::navigateToStation(PLATES);
  } else if (reading == "ch") {
    Navigator::navigateToStation(CHEESE);
  } else if (reading == "se") {
    Navigator::navigateToStation(SERVING);
  } else if (reading == "le") {
    Navigator::navigateToStation(LETTUCE);
  } else if (reading == "R") {
    Drivetrain::turnUntilTape(TurnDirection::RIGHT);
  } else if (reading == "L") {
    Drivetrain::turnUntilTape(TurnDirection::LEFT);
  } else if (reading == "Tape") {
    Network::wifiPrintln(TapeSensors::getValuesStr());
  } else if (reading == "F") {
    while (!Network::wifiInput()) {
      // wait
    }
    Drivetrain::tapeFollow(Network::message.toDouble());
  } else if (reading == "Table") {
    Drivetrain::driveUpToTable();
  } else if (reading == "Back") {
    Drivetrain::backUpToTape();
  } else if (reading == "ic") {
    BottomRobotModules::closeInputScraper();
  } else if (reading == "io") {
    BottomRobotModules::openInputScraper();
  } else if (reading == "tc") {
    BottomRobotModules::closeTrapdoor();
  } else if (reading == "to") {
    BottomRobotModules::openTrapdoor();
  } else if (reading == "cr") {
    BottomRobotModules::rotateCarouselRight();
  } else if (reading == "cb") {
    BottomRobotModules::rotateCarouselLeft();
  } else if (reading == "straight") {
    Drivetrain::run();
  }
}
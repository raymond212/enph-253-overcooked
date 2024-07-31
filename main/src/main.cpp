#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>
#include <bottom_robot_modules.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>
#include <actions.h>
#include <user_interface.h>
#include <top_robot_modules.h>


void setup() {
  Serial.begin(9600);
  Serial.println("initializing");

  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  BottomRobotModules::setupBottomRobotModules();
  TopRobotModules::setupTopRobotModules();
  UserInterface::setupUserInterface();
  // Navigator::setupNavigator();
}

int duration = 1000;
double power = 0.4; 
int driveTime = 377;
int spinTime = 765;
int slowTime = 135;
int fastTime = 440;
double slowPower = 0.25;
double fastPower = 0.5;
double spinPower = 0.5;
int wallTime = 500;

String waitAndRead();
String wifiWaitAndRead();

String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

String wifiWaitAndRead() {
  while (!Network::wifiInput()) {
    // wait
  }
  return Network::message;
}

void loop() {
  // String s = waitAndRead();
  // if (s == "oo") {
  //   BottomRobotModules::openOutputScraper();
  // } else if (s == "oc") {
  //   BottomRobotModules::closeOutputScraper();
  // } else if (s == "po") {
  //   BottomRobotModules::openPlatePincher();
  // } else if (s == "pc") {
  //   BottomRobotModules::closePlatePincher();
  // } else if (s == "io") {
  //   BottomRobotModules::openInputScraper();
  // } else if (s == "ic") {
  //   BottomRobotModules::closeInputScraper();
  // } else if (s == "set") {
  //   BottomRobotModules::setInput(waitAndRead().toDouble());
  // }

  if (Network::wifiInput()) {
    String s = Network::message;
    UserInterface::displayOLED(s);
    if (s == "F") {
      Drivetrain::driveMecanum(0, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "B") {
      Drivetrain::driveMecanum(180, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "L") {
      Drivetrain::driveMecanum(90, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "R") {
      Drivetrain::driveMecanum(-90, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "time") {
      duration = wifiWaitAndRead().toInt();
    } else if (s == "power") {
      power = wifiWaitAndRead().toDouble();
    } else if (s == "FL") {
      Drivetrain::driveMotors(power, 0, 0, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "FR") {
      Drivetrain::driveMotors(0, power, 0, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "BL") {
      Drivetrain::driveMotors(0, 0, power, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "BR") {
      Drivetrain::driveMotors(0, 0, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "print") {
      Network::wifiPrintln("Duration: " + String(duration) + " Power: " + String(power));
      Network::wifiPrintln("Drive time: " + String(driveTime) + " Spin time: " + String(spinTime));
      Network::wifiPrintln("Drive power: " + String(power) + " Spin power: " + String(spinPower));
      Network::wifiPrintln("Slow time: " + String(slowTime) + " Fast time: " + String(fastTime));
      Network::wifiPrintln("Slow power: " + String(slowPower) + " Fast power: " + String(fastPower));
      Network::wifiPrintln("Wall delay: " + String(wallTime));
    } else if (s == "tape") {
      Network::wifiPrintln(TapeSensors::getValuesStr());
    } else if (s == "W") {
      String s = wifiWaitAndRead();
      int num = s.substring(0, 1).toInt();
      DriveDirection driveDirection = s.substring(1, 2) == "F" ? DriveDirection::FORWARD : DriveDirection::BACKWARD;
      WallLocation wallLocation = s.substring(2, 3) == "R" ? WallLocation::RIGHT : WallLocation::LEFT;
      Drivetrain::wallFollow(driveDirection, wallLocation, num, wallTime);
    } else if (s == "mec") {
      double angle = wifiWaitAndRead().toDouble();
      Drivetrain::driveMecanum(angle, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "spin") {
      double spinPower = wifiWaitAndRead().toDouble();
      Drivetrain::driveMecanum(0, spinPower, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "test") {
      Network::wifiPrintln("Hello World!");
    } else if (s == "WW") {
      DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
      Drivetrain::wallToWall(driveDirection, slowTime, fastTime, slowPower, fastPower);
    } else if (s == "driveT") {
      driveTime = wifiWaitAndRead().toInt();
    } else if (s == "spinT") {
      spinTime = wifiWaitAndRead().toInt();
    } else if (s == "slowT") {
      slowTime = wifiWaitAndRead().toInt();
    } else if (s == "fastT") {
      fastTime = wifiWaitAndRead().toInt();
    } else if (s == "wallT") {
      wallTime = wifiWaitAndRead().toInt();
    } else if (s == "slowP") {
      slowPower = wifiWaitAndRead().toDouble();
    } else if (s == "fastP") {
      fastPower = wifiWaitAndRead().toDouble();
    } else if (s == "spinP") {
      spinPower = wifiWaitAndRead().toDouble();
    } else if (s == "WWS") {
      DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
      Drivetrain::wallToWallSpin(driveDirection, driveTime, spinTime, power, spinPower);
    } else if (s == "ic") {
      BottomRobotModules::closeInputScraper();
    } else if (s == "io") {
      BottomRobotModules::openInputScraper();
    } else if (s == "tc") {
      BottomRobotModules::closeTrapdoor();
    } else if (s == "to") {
      BottomRobotModules::openTrapdoor();
    } else if (s == "oc") {
      BottomRobotModules::closeOutputScraper();
    } else if (s == "oo") {
      BottomRobotModules::openOutputScraper();
    } else if (s == "po") {
      BottomRobotModules::openPlatePincher();
    } else if (s == "pc") {
      BottomRobotModules::closePlatePincher();
    } else if (s == "cl") {
      BottomRobotModules::rotateCarouselLeft();
    } else if (s == "cr") {
      BottomRobotModules::rotateCarouselRight();
    } else if (s == "e") {
      double distanceMM = wifiWaitAndRead().toDouble();
      BottomRobotModules::moveElevator(distanceMM);
    } else if (s == "salad") {
      // make salad plate
      // tomato 1
      Actions::startTomato1();
      // tomato 2
      Actions::inputRoutine();
      // tomato 3
      Actions::inputRoutine();
      // tomato 4
      Actions::inputRoutine();

      // move to lettuce
      Actions::tomatoToLettuce();
      // lettuce 1
      Actions::alignLettuce1();
      // lettuce 2
      Actions::inputRoutine();
      // lettuce 3
      Actions::inputRoutine();
      // lettuce 4
      Actions::inputRoutine();

      // drive to cooktop
      Actions::lettuceToCooktop();
      delay(500);

      // serve salad 1
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
      // serve salad 2
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
      // serve salad 3
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
      // serve salad 4
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Drivetrain::driveMecanumTime(-90, 0, 0.4, 1000);
    } else if (s == "start") {
      Actions::startTomato1();
    } else if (s == "input") {
      Actions::inputRoutine();
    } else if (s == "lettuce") {
      Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
      Actions::alignLettuce1();
    } else if (s == "c2p") {
      Actions::cooktopGrabPlate();
    } else if (s == "serve") {
      Actions::servingRoutine();
    } else if (s == "WWSR") {
      Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 750, 1400, 0.3, 0.3);
    } else if (s == "p2s") {
      Actions::plateToServing();
    } else if (s == "cooktop") {
      Actions::lettuceToCooktop();
    } else if (s == "s2c") {
      Actions::servingToCooktop();
    } else if (s == "4salad") {
      Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
      Actions::alignLettuce1();
      // lettuce 2
      Actions::inputRoutine();
      // lettuce 3
      Actions::inputRoutine();
      // lettuce 4
      Actions::inputRoutine();

      // move to cooktop
      Actions::lettuceToCooktop();
      delay(500);
      // serve salad 1
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
      // serve salad 2
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
      // serve salad 3
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
      // serve salad 4
      Actions::cooktopGrabPlate();
      Actions::plateToServing();
      Actions::servingRoutine();
      Actions::servingToCooktop();
    } else if (s == "dTI") {
      BottomRobotModules::tomatoInputDestack();
    } else if (s == "dLI") {
      BottomRobotModules::lettuceInputDestack();
    } else if (s == "destack") {
      BottomRobotModules::rotateCarouselRight();
      BottomRobotModules::rotateCarouselRight();
      BottomRobotModules::rotateCarouselRight();
    } else if (s == "tRoutine") {
      TopRobotModules::InputOutputRoutine();
    }
  }

  Network::handleOTA();
  delay(10);
}
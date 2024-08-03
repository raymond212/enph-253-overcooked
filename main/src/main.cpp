#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>
// #include <bottom_robot_actions.h>
// #include <bottom_robot_modules.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>
#include <user_interface.h>
#include <top_robot_actions.h>
#include <top_robot_modules.h>


void setup() {
  Serial.begin(9600);
  Serial.println("initializing");

  UserInterface::setupUserInterface();
  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  // BottomRobotModules::setupBottomRobotModules();
  TopRobotModules::setupTopRobotModules();
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
  if (Network::wifiInput()) {
    String s = Network::message;
    UserInterface::displayOLED(s); // echo
    if (s == "test") {
      Network::wifiPrintln("Hello World!");
    // drive testing
    } else if (s == "F") {
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
    } else if (s == "WWSS") {
      Drivetrain::wallToWallSpinSlow();
    // bottom robot modules
    // } else if (s == "bic") {
    //   BottomRobotModules::closeInputScraper();
    // } else if (s == "bio") {
    //   BottomRobotModules::openInputScraper();
    // } else if (s == "btc") {
    //   BottomRobotModules::closeTrapdoor();
    // } else if (s == "bto") {
    //   BottomRobotModules::openTrapdoor();
    // } else if (s == "boc") {
    //   BottomRobotModules::closeOutputScraper();
    // } else if (s == "boo") {
    //   BottomRobotModules::openOutputScraper();
    // } else if (s == "bpo") {
    //   BottomRobotModules::openPlatePincher();
    // } else if (s == "bpc") {
    //   BottomRobotModules::closePlatePincher();
    // } else if (s == "bcl") {
    //   BottomRobotModules::rotateCarouselLeft();
    // } else if (s == "bcr") {
    //   BottomRobotModules::rotateCarouselRight();
    // } else if (s == "be") {
    //   double distanceMM = wifiWaitAndRead().toDouble();
    //   BottomRobotModules::moveElevator(distanceMM);
    // } else if (s == "serve") {
    //   BottomRobotActions::servingRoutine();
    // } else if (s == "burger") {
    //   // drive to cutting area, intake bottom bun
    //   BottomRobotModules::moveElevator(30);
    //   BottomRobotActions::startToCutting();
    //   delay(2000);
    //   BottomRobotActions::inputSingle();
    //   delay(2000);
    //   // drive to tomato area, intake tomato
    //   BottomRobotModules::moveElevator(-10);
    //   BottomRobotActions::cuttingToTomato();
    //   BottomRobotActions::inputSingle();
    //   delay(2000);
    //   // drive to cheese area, intake cheese
    //   BottomRobotModules::moveElevator(-5);
    //   BottomRobotActions::tomatoToCheese();
    //   BottomRobotActions::inputSingle();
    //   delay(2000);
    //   // drive to cooktop, intake patty
    //   BottomRobotModules::moveElevator(-10);
    //   BottomRobotActions::cheeseToCooktop();
    //   delay(2000);
    //   BottomRobotActions::inputSingle();
    //   delay(2000);
    //   // drive to lettuce area, intake lettuce
    //   BottomRobotModules::moveElevator(-5);
    //   BottomRobotActions::cooktopToLettuce();
    //   BottomRobotActions::inputSingle();
    //   delay(2000);
    //   // drive to cooktop, intake top bun
    //   BottomRobotActions::lettuceToCooktop();
    //   BottomRobotActions::inputSingle();
    //   delay(2000);
    //   // drive to plates, get plate
    //   BottomRobotActions::cooktopGrabPlate();
    //   delay(300);
    //   // drive to serving area, serve burger
    //   BottomRobotActions::plateToServing();
    //   BottomRobotActions::servingRoutine();
    //   // drive back to cooktop
    //   BottomRobotActions::servingToCooktop();
    // } else if (s == "start") {
    //   BottomRobotActions::startToCutting();
    // } else if (s == "c2t") {
    //   BottomRobotActions::cuttingToTomato();
    // } else if (s == "t2c") {
    //   BottomRobotActions::tomatoToCheese();
    // } else if (s == "c2c") {
    //   BottomRobotActions::cheeseToCooktop();
    // } else if (s == "c2l") {
    //   BottomRobotActions::cooktopToLettuce();
    // } else if (s == "l2c") {
    //   BottomRobotActions::lettuceToCooktop();
    // } else if (s == "c2p") {
    //   BottomRobotActions::cooktopGrabPlate();
    // } else if (s == "p2s") {
    //   BottomRobotActions::plateToServing();
    // } else if (s == "s2c") {
    //   BottomRobotActions::servingToCooktop();
    // } else if (s == "input") {
    //   BottomRobotActions::inputSingle();
    // top robot modules
    } else if (s == "tic") {
      TopRobotModules::closeInputScraper();
    } else if (s == "ticp") {
      TopRobotModules::closeInputScraperPatty();
    } else if (s == "tio") {
      TopRobotModules::openInputScraper();
    } else if (s == "ti") {
      TopRobotModules::setInputScraper(wifiWaitAndRead().toDouble());
    } else if (s == "tor") {
      TopRobotModules::raiseOutputScraper();
    } else if (s == "tol") {
      TopRobotModules::lowerOutputScraper();
    } else if (s == "to") {
      TopRobotModules::setOutputScraper(wifiWaitAndRead().toDouble());
    } else if (s == "tcl") {
      TopRobotModules::rotateCarouselLeft();
    } else if (s == "tcr") {
      TopRobotModules::rotateCarouselRight();
    } else if (s == "tc") {
      TopRobotModules::rotateCarousel(wifiWaitAndRead().toDouble());
    } else if (s == "tpo") {
      TopRobotActions::movePusherOut();
    } else if (s == "tpi") {
      TopRobotActions::movePusherIn();
    } else if (s == "tp") {
      TopRobotModules::movePusher(wifiWaitAndRead().toDouble(), false);
    } else if (s == "tpr") {
      TopRobotActions::reloadPusherPatty();
    // top robot driving
    } else if (s == "s2b") {
      TopRobotActions::startToBuns();
    } else if (s == "bbd") {
      TopRobotActions::bottomBunDriveProcedure();
    } else if (s == "b2cu") {
      TopRobotActions::bunsToCutting();
    } else if (s == "c2p") {
      TopRobotActions::cuttingToPatties();
    } else if (s == "p2c") {
      TopRobotActions::pattiesToCooktop();
    } else if (s == "c2b") {
      TopRobotActions::cooktopToBuns();
    } else if (s == "b2c") {
      TopRobotActions::bunsToCooktop();
    } else if (s == "ingr") {
      TopRobotActions::startToBuns();
      TopRobotActions::bottomBunDriveProcedure();
      // intake one bottom bun
      TopRobotActions::inputRoutine();
      // drive to cutting
      TopRobotActions::bunsToCutting();
      // serve bun
      TopRobotActions::transferRoutine();
      // go to patty
      TopRobotActions::cuttingToPatties();
      // intake one patty
      TopRobotActions::inputRoutine();
      // go to cooktop
      TopRobotActions::pattiesToCooktop();
      // serve patty
      TopRobotActions::transferRoutine();
      // go to buns
      TopRobotActions::cooktopToBuns();
      // intake one top bun
      TopRobotActions::inputRoutine();
      // go to cooktop
      TopRobotActions::bunsToCooktop();
      // serve bun
      TopRobotActions::transferRoutine();
    } else if (s == "tir") {
      TopRobotActions::inputRoutine();
    } else if (s == "tt") {
      TopRobotActions::transferRoutine();
    }
  }

  Network::handleOTA();
  delay(10);
}
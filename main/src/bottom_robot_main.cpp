#ifdef ENABLE_BOTTOM_ROBOT

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
// #include <hotspot.h>
#include <network.h>
#include <tape_sensors.h>
#include <bottom_robot_actions.h>
#include <bottom_robot_modules.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>
#include <user_interface.h>

void setup() {
  Serial.begin(9600);
  Serial.println("initializing");

  UserInterface::setupUserInterface();
  Drivetrain::setupDrivetrain();
  // Hotspot::setupWifi();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  BottomRobotModules::setupBottomRobotModules();
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
bool onTape = false;


String waitAndRead();
String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

// String wifiWaitAndRead();
// String wifiWaitAndRead() {
//   while (!Hotspot::wifiInput()) {
//     // wait
//   }
//   return Hotspot::message;
// }

void loop() {
  if (UserInterface::isButtonPressed()) {
    #ifdef ENABLE_HANDSHAKE
    UserInterface::displayOLED("Waiting for handshake!");
    Network::waitForHandshake();
    UserInterface::displayOLED("Handshake established");
    delay(200);
    #endif

    int numBurgers = 4;

    UserInterface::displayOLED("BURGER");
    // drive to plate area, grab on to plate
    BottomRobotModules::moveElevator(30);
    BottomRobotActions::startToPlate();
    for (int i = 1; i <= numBurgers; i++) {
      // drive to cutting area, intake bottom bun
      BottomRobotActions::plateToCutting();
      #ifdef ENABLE_HANDSHAKE
      if (i == 1) {
        Network::waitForHandshake();
      }
      #endif
      BottomRobotActions::inputSingle();
      // drive to tomato area, intake tomato
      BottomRobotModules::moveElevator(-15);
      BottomRobotActions::cuttingToTomato();
      BottomRobotActions::inputSingle();
      // drive to cheese area, intake cheese
      BottomRobotModules::moveElevator(-4);
      BottomRobotActions::tomatoToCheese();
      BottomRobotActions::inputSingle();
      // drive to lettuce area, intake lettuce
      BottomRobotModules::moveElevator(-4);
      BottomRobotActions::cheeseToLettuce();
      BottomRobotActions::inputSingle();
      // drive to cooktop, intake patty
      BottomRobotModules::moveElevator(-4);
      BottomRobotActions::lettuceToCooktop();
      BottomRobotActions::inputSingle();
      // drive to cutting area, intake top bun
      BottomRobotModules::moveElevator(-3);
      BottomRobotActions::cooktopToCutting();
      #ifdef ENABLE_HANDSHAKE
      Network::waitForHandshake();
      #endif
      BottomRobotActions::inputSingle();
      // elevate and serve burgers;
      BottomRobotModules::moveElevator(96);
      BottomRobotActions::cuttingToServing();
      // BottomRobotActions::servingRoutine();
      // drive back to cooktop
      if (i != numBurgers) {
        BottomRobotActions::servingToPlate();
      }
    }
    BottomRobotActions::servingToPlate();
  }

  // if (Hotspot::wifiInput()) {
  //   String s = Hotspot::message;
  //   UserInterface::displayOLED(s); // echo
  //   if (s == "test") {
  //     Hotspot::wifiPrintln("Hello World!");
  //   // drive testing
  //   } else if (s == "F") {
  //     Drivetrain::driveMecanum(0, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "B") {
  //     Drivetrain::driveMecanum(180, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "L") {
  //     Drivetrain::driveMecanum(90, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "R") {
  //     Drivetrain::driveMecanum(-90, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "time") {
  //     duration = wifiWaitAndRead().toInt();
  //   } else if (s == "power") {
  //     power = wifiWaitAndRead().toDouble();
  //   } else if (s == "FL") {
  //     Drivetrain::driveMotors(power, 0, 0, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "FR") {
  //     Drivetrain::driveMotors(0, power, 0, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "BL") {
  //     Drivetrain::driveMotors(0, 0, power, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "BR") {
  //     Drivetrain::driveMotors(0, 0, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "print") {
  //     Hotspot::wifiPrintln("Duration: " + String(duration) + " Power: " + String(power));
  //     Hotspot::wifiPrintln("Drive time: " + String(driveTime) + " Spin time: " + String(spinTime));
  //     Hotspot::wifiPrintln("Drive power: " + String(power) + " Spin power: " + String(spinPower));
  //     Hotspot::wifiPrintln("Slow time: " + String(slowTime) + " Fast time: " + String(fastTime));
  //     Hotspot::wifiPrintln("Slow power: " + String(slowPower) + " Fast power: " + String(fastPower));
  //     Hotspot::wifiPrintln("Wall delay: " + String(wallTime) + " On Tape: " + (onTape ? "YES" : "NO"));
  //   } else if (s == "tape") {
  //     Hotspot::wifiPrintln(TapeSensors::getValuesStr());
  //   } else if (s == "W") {
  //     String s = wifiWaitAndRead();
  //     int num = s.substring(0, 1).toInt();
  //     DriveDirection driveDirection = s.substring(1, 2) == "F" ? DriveDirection::FORWARD : DriveDirection::BACKWARD;
  //     WallLocation wallLocation = s.substring(2, 3) == "R" ? WallLocation::RIGHT : WallLocation::LEFT;
  //     Drivetrain::wallFollow(driveDirection, wallLocation, num, wallTime, onTape);
  //   } else if (s == "ontape") {
  //     onTape = true;
  //   } else if (s == "offtape") {
  //     onTape = false;
  //   } else if (s == "mec") {
  //     double angle = wifiWaitAndRead().toDouble();
  //     Drivetrain::driveMecanum(angle, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "spin") {
  //     double spinPower = wifiWaitAndRead().toDouble();
  //     Drivetrain::driveMecanum(0, spinPower, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "WW") {
  //     DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
  //     Drivetrain::wallToWall(driveDirection, slowTime, fastTime, slowPower, fastPower);
  //   } else if (s == "driveT") {
  //     driveTime = wifiWaitAndRead().toInt();
  //   } else if (s == "spinT") {
  //     spinTime = wifiWaitAndRead().toInt();
  //   } else if (s == "slowT") {
  //     slowTime = wifiWaitAndRead().toInt();
  //   } else if (s == "fastT") {
  //     fastTime = wifiWaitAndRead().toInt();
  //   } else if (s == "wallT") {
  //     wallTime = wifiWaitAndRead().toInt();
  //   } else if (s == "slowP") {
  //     slowPower = wifiWaitAndRead().toDouble();
  //   } else if (s == "fastP") {
  //     fastPower = wifiWaitAndRead().toDouble();
  //   } else if (s == "spinP") {
  //     spinPower = wifiWaitAndRead().toDouble();
  //   } else if (s == "WWS") {
  //     DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
  //     Drivetrain::wallToWallSpin(driveDirection, driveTime, spinTime, power, spinPower);
  //   } else if (s == "WWSS") {
  //     Drivetrain::wallToWallSpinSlow();
  //   }
  // }
  //   // bottom robot modules
  //   } else if (s == "bic") {
  //     BottomRobotModules::closeInputScraper();
  //   } else if (s == "bio") {
  //     BottomRobotModules::openInputScraper();
  //   } else if (s == "bi") {
  //     BottomRobotModules::setInputScraper(wifiWaitAndRead().toDouble());
  //   } else if (s == "btc") {
  //     BottomRobotModules::closeTrapdoor();
  //   } else if (s == "bto") {
  //     BottomRobotModules::openTrapdoor();
  //   } else if (s == "boc") {
  //     BottomRobotModules::closeOutputScraper();
  //   } else if (s == "boo") {
  //     BottomRobotModules::openOutputScraper();
  //   } else if (s == "bpo") {
  //     BottomRobotModules::openPlatePincher();
  //   } else if (s == "bpc") {
  //     BottomRobotModules::closePlatePincher();
  //   } else if (s == "bcl") {
  //     BottomRobotModules::rotateCarouselLeft();
  //   } else if (s == "bcr") {
  //     BottomRobotModules::rotateCarouselRight();
  //   } else if (s == "be") {
  //     double distanceMM = wifiWaitAndRead().toDouble();
  //     BottomRobotModules::moveElevator(distanceMM);
  //   } else if (s == "serve") {
  //     BottomRobotActions::servingRoutine();
  //   // driving test
  //   } else if (s == "start") {
  //     BottomRobotActions::startToPlate();
  //   } else if (s == "p2c") {
  //     BottomRobotActions::plateToCutting();
  //   } else if (s == "c2t") {
  //     BottomRobotActions::cuttingToTomato();
  //   } else if (s == "t2c") {
  //     BottomRobotActions::tomatoToCheese();
  //   } else if (s == "c2l") {
  //     BottomRobotActions::cheeseToLettuce();
  //   } else if (s == "l2c") {
  //     BottomRobotActions::lettuceToCooktop();
  //   } else if (s == "c2c") {
  //     BottomRobotActions::cooktopToCutting();
  //   } else if (s == "c2s") {
  //     BottomRobotActions::cuttingToServing();
  //   } else if (s == "run") {
  //     BottomRobotActions::startToPlate();
  //     delay(500);
  //     BottomRobotActions::plateToCutting();
  //     delay(500);
  //     BottomRobotActions::cuttingToTomato();
  //     delay(500);
  //     BottomRobotActions::tomatoToCheese();
  //     delay(500);
  //     BottomRobotActions::cheeseToLettuce();
  //     delay(500);
  //     BottomRobotActions::lettuceToCooktop();
  //     delay(500);
  //     BottomRobotActions::cooktopToCutting();
  //     delay(500);
  //     BottomRobotActions::cuttingToServing();
  //     delay(500);
  //   }
  // }

  // Hotspot::handleOTA();
  // delay(10);
}

#endif

// if (UserInterface::isButtonPressed()) {
  //   UserInterface::displayOLED("Waiting for handshake!");
  //   Network::waitForHandshake();
  //   UserInterface::displayOLED("Handshake established");
  //   delay(1000);

  //   UserInterface::displayOLED("BURGER");
  //   // drive to cutting area, intake bottom bun
  //   BottomRobotModules::moveElevator(30);
  //   BottomRobotActions::startToCutting();

  //   // wait for bottom bun
  //   Network::waitForHandshake(); // top robot will send out handshake after it has pushed out the top bun
  //   BottomRobotActions::inputSingle();
  //   delay(500);
  //   // drive to tomato area, intake tomato
  //   BottomRobotModules::moveElevator(-10);
  //   BottomRobotActions::cuttingToTomato();
  //   BottomRobotActions::inputSingle();
  //   // drive to cheese area, intake cheese
  //   BottomRobotModules::moveElevator(-5);
  //   BottomRobotActions::tomatoToCheese();
  //   BottomRobotActions::inputSingle();
  //   // drive to cooktop, intake patty
  //   BottomRobotModules::moveElevator(-10);
  //   BottomRobotActions::cheeseToCooktop();
  //   // intake patty
  //   BottomRobotActions::inputSingle();
  //   // drive to lettuce area, intake lettuce
  //   BottomRobotModules::moveElevator(-5);
  //   BottomRobotActions::cooktopToLettuce();
  //   BottomRobotActions::inputSingle();
  //   // drive to cooktop, intake top bun
  //   BottomRobotActions::lettuceToCooktop();
  //   // wait for top bun
  //   Network::waitForHandshake(); // wait for top robot to push out top bun
  //   BottomRobotActions::inputSingle();
  //   BottomRobotModules::moveElevator(53); // first time elevate burgers
  //   // drive to plates, get plate
  //   BottomRobotActions::cooktopGrabPlate();
  //   // drive to serving area, serve burger
  //   BottomRobotActions::plateToServing();
  //   BottomRobotActions::servingRoutine();
  //   // drive back to cooktop
  //   BottomRobotActions::servingToCooktop();
  //   BottomRobotModules::closeTrapdoor();
  // }
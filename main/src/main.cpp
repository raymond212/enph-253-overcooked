#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>
#include <bottom_robot_modules.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>


void setup() {
  Serial.begin(9600);

  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  BottomRobotModules::setupBottomRobotModules();
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
int wallTime = 1000;

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
  // mecanum drive testing
  if (Network::wifiInput()) {
    String s = Network::message;
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
    } else if (s == "lettuce") {
      // get lettuce
      BottomRobotModules::openInputScraper();
      Drivetrain::driveMecanumTime(90, 0, 0.5, 550);
      delay(500);
      BottomRobotModules::closeInputScraper();
      delay(900);
      // lettuce 2
      BottomRobotModules::inputRoutine();
      // lettuce 3
      BottomRobotModules::inputRoutine();
      // tomato 4
      BottomRobotModules::inputRoutine();

      // move to lettuce
      Drivetrain::driveMecanumTime(15, 0, 0.5, 1000);
      Drivetrain::driveMecanumTime(180, 0, 0.5, 30);
      delay(500);


      Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 377, 765, 0.4, 0.5);
      Drivetrain::driveMecanumTime(165, 0, 0.3, 300);

      Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 800);

      // get lettuce

      // lettuce 1
      BottomRobotModules::openInputScraper();
      Drivetrain::driveMecanumTime(15, 0, 0.3, 700);
      BottomRobotModules::closeInputScraper();
      delay(900);
      // lettuce 2
      BottomRobotModules::inputRoutine();
      // lettuce 3
      BottomRobotModules::inputRoutine();
      // lettuce 4
      BottomRobotModules::inputRoutine();
      
      BottomRobotModules::openInputScraper();
      delay(500);

      // leave lettuce
      Drivetrain::driveMecanumTime(15, 0, 0.5, 1000);
      // spin across
      Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 750, 1400, 0.3, 0.3);
      // go to cooktop
      Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 100);

      BottomRobotModules::openPlatePincher();
      delay(200);
      Drivetrain::driveMecanumTime(15, 0, 0.3, 1300);
      // Drivetrain::driveMecanumTime(180, 0, 0.5, 30); // break
      
      delay(1000);
      BottomRobotModules::closePlatePincher();
      delay(1000);

      // go to serve
      for (int i = 0; i < 4; i++) {
        Drivetrain::driveMecanumTime(165, 0, 0.5, 1600);
        Drivetrain::driveMecanumTime(0, 0, 0.5, 30);
        delay(500);

        Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 750, 1400, 0.3, 0.3);

        // serve
        
        BottomRobotModules::moveElevator(69);
        BottomRobotModules::openOutputScraper();
        delay(1000);
        BottomRobotModules::closeOutputScraper();
        BottomRobotModules::openPlatePincher();
        delay(1000);
        BottomRobotModules::openTrapdoor();
        BottomRobotModules::moveElevator(-69);

        
        // go back across counter
        Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 750, 1400, 0.3, 0.3);
        BottomRobotModules::closeTrapdoor();
        delay(1000);

        // go to plate
        Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 100);

        BottomRobotModules::openPlatePincher();
        delay(200);
        Drivetrain::driveMecanumTime(15, 0, 0.3, 1400);
        // Drivetrain::driveMecanumTime(180, 0, 0.5, 30); // break
        
        delay(1000);
        BottomRobotModules::closePlatePincher();
        delay(1000);
      }
      

    }
  }

  // Drivetrain::wallToW  allSpin(Direction::RIGHT, 377, 765, 0.4, 0.5);

  Network::handleOTA();
  delay(10);

  // top robot modules testing
  /*
  String s = waitAndRead();
  if (s == "input") {
    int angle = waitAndRead().toInt();
    inputServo.setAngle(angle);
  } else if (s == "output") {
    int angle = waitAndRead().toInt();
    outputServo.setAngle(angle);
  } else if (s == "linear") {
    double revs = waitAndRead().toDouble();
    outputStepper.step((int)(revs * 200));
  } else if (s == "carousel") {
    double revs = waitAndRead().toDouble();
    carouselStepper.step((int)(revs * 200));
  } else if (s == "ic") {
    inputServo.setAngle(107);
  } else if (s == "io") {
    inputServo.setAngle(180);
  } else if (s == "ou") {
    outputServo.setAngle(180);
  } else if (s == "od") {
    outputServo.setAngle(117);
  } else if (s == "lo") {
    outputStepper.stepRevs(2.5);
  } else if (s == "li") {
    outputStepper.stepRevs(-2.5);
  } else if (s == "ci") {
    carouselStepper.stepRevs(0.33);
  } else if (s == "co") {
    carouselStepper.stepRevs(-0.33);
  } */
}
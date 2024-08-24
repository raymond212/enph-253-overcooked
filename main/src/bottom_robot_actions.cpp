#ifdef ENABLE_BOTTOM_ROBOT

#include <bottom_robot_actions.h>

namespace BottomRobotActions {
  // ACTIONS
  void inputSingle() {
    BottomRobotModules::closeInputScraper();
    delay(1100);
    BottomRobotModules::openInputScraper();
  }

  void servingRoutine() {
    BottomRobotModules::openOutputScraper();  // push burger out with the output scraper
    delay(100);
    BottomRobotModules::closeOutputScraper(); // reset output scraper
    BottomRobotModules::moveElevator(-66);    // lower platform to input height
    BottomRobotModules::openPlatePincher();   // release plate
    BottomRobotModules::openTrapdoor();       // drop food
    delay(400);
  }

  // DRIVING
  void startToPlate() {
    BottomRobotModules::openInputScraper();
    Drivetrain::driveMecanumTime(45, 0, 1, 800);
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 1, 1400, false, false); // wall follow 1FL to cooktop
    BottomRobotModules::openPlatePincher();         // open plate pincher
    Drivetrain::driveMecanumTime(15, 0, 0.5, 550);  // drive forward
    delay(100);
    BottomRobotModules::closePlatePincher(); // grab plate
    delay(200);
  }

  void plateToCutting() {
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 1, 1400, true);
  }

  void cuttingToTomato() {
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0, true); // wall follow 0BL to tomato
  }

  void tomatoToCheese() {
    Drivetrain::driveMecanumTime(15, 0, WALL_FOLLOW_SLOW_POWER, 400); // wall follow forward slightly
    Drivetrain::wallToWallSpinFast();                                 // spin to bottom counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0, false);   // wall follow 0FL to cheese
  }

  void cheeseToLettuce() {
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 2300, true);
  }

  void lettuceToCooktop() {
    Drivetrain::driveMecanumTime(15, 0, WALL_FOLLOW_FAST_POWER, 200);                  // wall follow forward slightly
    Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 370, 880, 1, 1);
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0, false); // wall follow 0BL to cooktop
  }

  void cooktopToCutting() {
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 1000, true);
  }

  void cuttingToServing() {
    Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 465, 1060, 0.6, 0.7); 
    Drivetrain::driveMecanumTime(155, 0, 1, 600);
    BottomRobotModules::openOutputScraper();  // push burger out with the output scraper
    delay(1000);
    BottomRobotModules::closeOutputScraper(); // reset output scraper
    BottomRobotModules::moveElevator(-66);    // lower burger to input height
    BottomRobotModules::openPlatePincher();   // release plate
    BottomRobotModules::openTrapdoor();       // drop food
    delay(700);
  }

  void servingToCooktop() {
    Drivetrain::wallToWallSpinFast();                                                 // spin to middle counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0, false); // wall follow 0FL to cooktop
  }

  void servingToPlate() {
    Drivetrain::wallToWallSpinFast(); 
    BottomRobotModules::closeTrapdoor();
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 400, false, false);  // wall follow 0FL to cooktop
    BottomRobotModules::openPlatePincher();         // open plate pincher
    Drivetrain::driveMecanumTime(15, 0, 0.5, 550);  // drive forward
    delay(100);
    BottomRobotModules::closePlatePincher(); // grab plate
    delay(200);
  }
}

#endif
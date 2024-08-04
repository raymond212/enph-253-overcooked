#ifdef ENABLE_BOTTOM_ROBOT

#include <bottom_robot_actions.h>

namespace BottomRobotActions {
  // ACTIONS
  void inputSingle() {
    BottomRobotModules::closeInputScraper();
    delay(1500);
    BottomRobotModules::openInputScraper();
  }

  void servingRoutine() {
    delay(900);
    BottomRobotModules::openOutputScraper();  // push burger out with the output scraper
    delay(500);
    BottomRobotModules::closeOutputScraper(); // reset output scraper
    BottomRobotModules::moveElevator(-46.5);  // lower remaining burgers
    BottomRobotModules::openPlatePincher();   // release plate
    delay(300);
    BottomRobotModules::openTrapdoor();       // drop food
    delay(1000);
    // BottomRobotModules::rotateCarouselLeft();
  }

  // DRIVING
  void startToCutting() {
    BottomRobotModules::openInputScraper();                                     // open input scraper to prevent conflict
    Drivetrain::driveMecanumTime(90, 0, 0.6, 510);                              // drive sideways to middle counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0);  // wall follow 0FL to cutting
  }

  void cuttingToTomato() {
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0); // wall follow 0BL to tomato
  }

  void tomatoToCheese() {
    Drivetrain::driveMecanumTime(15, 0, WALL_FOLLOW_MEDIUM_POWER, 500);         // wall follow forward slightly
    Drivetrain::wallToWallSpinFast();                                           // spin to bottom counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0);  // wall follow 0FL to cheese
  }

  void cheeseToCooktop() {
    Drivetrain::driveMecanumTime(165, 0, WALL_FOLLOW_MEDIUM_POWER, 500);        // wall follow backward slightly
    Drivetrain::wallToWallSpinFast();                                           // spin to middle counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 1, 0);  // wall follow 1FL to cooktop
  }

  void cooktopToLettuce() {
    Drivetrain::wallToWallSpinFast();                                           // spin to bottom counter
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0); // wall follow 1BL to lettuce
  }

  void lettuceToCooktop() {
    Drivetrain::driveMecanumTime(15, 0, WALL_FOLLOW_MEDIUM_POWER, 300);         // wall follow forward slightly
    Drivetrain::wallToWallSpinFast();                                           // spin to middle counter
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0); // wall follow 0BL to cooktop
  }

  void cooktopGrabPlate() {
    BottomRobotModules::moveElevator(50);           // elevate burger to ring height
    BottomRobotModules::setInputScraper(4);         // set input scraper to non conflicting position
    BottomRobotModules::openPlatePincher();         // open plate pincher
    Drivetrain::driveMecanumTime(15, 0, 0.5, 800);  // drive forward
    delay(300);
    BottomRobotModules::closePlatePincher(); // grab plate
    delay(200);
  }

  void plateToServing() {
    // drive
    Drivetrain::driveMecanumTime(165, 0, 0.5, 1100);  // wall follow backward
    Drivetrain::driveMecanumTime(0, 0, 0.5, 30);      // break
    Drivetrain::wallToWallSpinSlow();                 // spin to bottom counter
    BottomRobotModules::moveElevator(46.5);           // elevate burger to output height
    Drivetrain::driveMecanumTime(15, 0, 0.5, 800);    // wall follow forward
    Drivetrain::driveMecanumTime(180, 0, 0.5, 30);    // break
  }

  void servingToCooktop() {
    Drivetrain::wallToWallSpinFast();                                           // spin to middle counter
    BottomRobotModules::closeTrapdoor();
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0);  // wall follow 0FL to cooktop
  }
}

#endif
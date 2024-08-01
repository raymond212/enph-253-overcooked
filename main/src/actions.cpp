#include <actions.h>

namespace Actions {
  void inputSingle() {
    BottomRobotModules::closeInputScraper();
    delay(1500);
    BottomRobotModules::openInputScraper();
  }

  void cooktopGrabPlate() {
    // drive from cooktop to plates
    BottomRobotModules::openPlatePincher();
    Drivetrain::driveMecanumTime(15, 0, 0.5, 1200);
    // grab plate
    delay(300);
    BottomRobotModules::closePlatePincher();
    delay(200);
  }

  void plateToServing() {
    // drive
    Drivetrain::driveMecanumTime(165, 0, 0.35, 1500);
    Drivetrain::driveMecanumTime(0, 0, 0.5, 30);
    delay(300);
    // wall to wall spin
    wallToWallSpinSlow();
    // wall follow
    Drivetrain::driveMecanumTime(15, 0, 0.35, 1300);
    Drivetrain::driveMecanumTime(180, 0, 0.5, 30);
  }

  void servingRoutine() {
    // open input scraper to prevent conflict
    BottomRobotModules::openInputScraper();
    // raise food
    BottomRobotModules::moveElevator(96.5);
    // push food to output position
    BottomRobotModules::openOutputScraper();
    delay(1000);
    // reset output scraper
    BottomRobotModules::closeOutputScraper();
    // release plate
    BottomRobotModules::openPlatePincher();
    delay(300);
    // drop food
    BottomRobotModules::openTrapdoor();
    // lower other food
    BottomRobotModules::moveElevator(-96.5);
    // rotate carousel
    BottomRobotModules::closeInputScraper();
    // rotate food
    // BottomRobotModules::rotateCarouselLeft();
  }

  void servingToCooktop() {
    wallToWallSpinFast(); 
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0);
  }

  void wallToWallSpinSlow() {
    Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 490, 1060, 0.6, 0.7);
  }

  void wallToWallSpinFast() {
    wallToWallSpinSlow();
    // Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 300, 760, 1, 1);
    // need to retune this
  }

  void startToCutting() {
    // drive to wall
    Drivetrain::driveMecanumTime(90, 0, 0.6, 510);
    // wall follow to cutting area: 0FL
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0);
  }

  void cuttingToTomato() {
    // wall follow to tomato: 0BL
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
  }

  void tomatoToCheese() {
    // drive forward a little
    Drivetrain::driveMecanumTime(15, 0, WALL_FOLLOW_MEDIUM_POWER, 500);
    // spin to cheese
    wallToWallSpinFast();
    // wall follow to cheese
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0);
  }

  void cheeseToCooktop() {
    Drivetrain::driveMecanumTime(165, 0, WALL_FOLLOW_MEDIUM_POWER, 500);
    wallToWallSpinFast();
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 1, 0);
  }

  void cooktopToLettuce() {
    wallToWallSpinFast();
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
  }

  void lettuceToCooktop() {
    Drivetrain::driveMecanumTime(15, 0, WALL_FOLLOW_MEDIUM_POWER, 300);
    wallToWallSpinFast();
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
  }
}
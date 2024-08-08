#ifdef ENABLE_TOP_ROBOT

#include <top_robot_actions.h>

namespace TopRobotActions {
  // ACTIONS
  void movePusherOut() {
    TopRobotModules::lowerOutputScraper();
    delay(400);
    TopRobotModules::movePusher(2.54, true);
    TopRobotModules::setOutputScraper(125);
  }

  void movePusherIn() {
    TopRobotModules::raiseOutputScraper();
    TopRobotModules::movePusher(-2.75, false);
  }

  void reloadPusherPatty() {
    TopRobotModules::setOutputScraper(127);
    delay(200);
    TopRobotModules::movePusher(-0.8, true);
    TopRobotModules::lowerOutputScraper();
    delay(200);
    TopRobotModules::movePusher(0.8, true);
  }

  void inputPatty() {
    movePusherIn();
    TopRobotModules::closeInputScraperPatty();
    delay(200);
    TopRobotModules::openInputScraper();
    delay(200);
    TopRobotModules::rotateCarousel(135 * 4);
  }

  void inputBun(bool carouselSpinLeft) {
    movePusherIn();
    TopRobotModules::closeInputScraperBun();
    delay(200);
    TopRobotModules::openInputScraper();
    delay(200);
    TopRobotModules::rotateCarousel(carouselSpinLeft ? 135 * 4 : -225 * 4);
  }

  void transferRoutine() {
    movePusherOut();
    TopRobotModules::rotateCarousel(45 * 4);
  }

  // DRIVING
  void startToBuns() {
    Drivetrain::driveMecanumTime(45, 0, 1, 830);
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 500, false, false);  // wall follow 0FL to cutting area
  }

  void bottomBunDriveProcedure() {
    Drivetrain::driveMecanumTime(15, 0, 0.6, 50);
    TopRobotModules::openInputScraper();
    delay(400);
    Drivetrain::driveMecanumTime(165, 0, 0.6, 350);
  }

  void bunsToCutting() {
    Drivetrain::wallToWallSlow(DriveDirection::RIGHT); // go to middle couunter
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::RIGHT, 0, 0, false);
    delay(200);
    Drivetrain::driveMecanumTime(-165, 0, 0.5, 120);
  }

  void cuttingToPatties() {
    Drivetrain::wallToWallSlow(DriveDirection::LEFT); // go to top counter
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0, false);
  }

  void pattiesToCooktop() {
    Drivetrain::wallToWallSlow(DriveDirection::RIGHT);
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::RIGHT, 1, 1200, false);
    delay(200);
    Drivetrain::driveMecanumTime(-165, 0, 0.5, 275);
  }

  void cooktopToBuns() {
    Drivetrain::wallToWallSlow(DriveDirection::LEFT);
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0, false);
  }

  void cuttingToBuns() {
    TopRobotModules::closeInputScraperFast();
    Drivetrain::wallToWallSlow(DriveDirection::LEFT); // go to top counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 0, false, false);
  }

  void resetToStart() {
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0, true);
  }

  void bunToPatty() {
    TopRobotModules::openInputScraper();
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0, true);
  }
}

#endif
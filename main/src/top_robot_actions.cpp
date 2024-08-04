#ifdef ENABLE_TOP_ROBOT

#include <top_robot_actions.h>

namespace TopRobotActions {
  // ACTIONS
  void movePusherOut() {
    TopRobotModules::lowerOutputScraper();
    delay(400);
    TopRobotModules::movePusher(0.8, true);
    TopRobotModules::setOutputScraper(121);
    TopRobotModules::movePusher(1.65, true);
    TopRobotModules::raiseOutputScraper();
  }

  void movePusherIn() {
    TopRobotModules::movePusher(-2.45, true);
    delay(100);
    TopRobotModules::movePusher(0.03, true);
    // TopRobotModules::movePusher(-0.35, true);
    // TopRobotModules::raiseOutputScraper();
    // TopRobotModules::movePusher(-2.15, true);
  }

  void reloadPusherPatty() {
    TopRobotModules::setOutputScraper(127);
    delay(200);
    TopRobotModules::movePusher(-0.8, true);
    TopRobotModules::lowerOutputScraper();
    delay(200);
    TopRobotModules::movePusher(0.8, true);
  }

  void inputRoutine() {
    movePusherIn();
    delay(500);
    TopRobotModules::closeInputScraper();
    delay(800);
    TopRobotModules::openInputScraper();
    delay(800);
    TopRobotModules::rotateCarousel(-135 * 4);
  }

  void transferRoutine() {
    movePusherOut();
    TopRobotModules::rotateCarousel(45 * 4);
  }

  // DRIVING
  void startToBuns() {
    Drivetrain::driveMecanumTime(90, 0, 0.6, 510);                              // drive sideways to top counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 1, 0);  // wall follow 1FL to cutting area
  }

  void bottomBunDriveProcedure() {
    Drivetrain::driveMecanumTime(15, 0, 0.6, 350);
    delay(100);
    TopRobotModules::openInputScraper();
    delay(1000);
    Drivetrain::driveMecanumTime(165, 0, 0.6, 350);
  }

  void bunsToCutting() {
    Drivetrain::wallToWallSlow(DriveDirection::RIGHT); // go to middle counter
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::RIGHT, 0, 0);
  }

  void cuttingToPatties() {
    Drivetrain::wallToWallSlow(DriveDirection::LEFT); // go to top counter
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
  }

  void pattiesToCooktop() {
    Drivetrain::wallToWallSlow(DriveDirection::RIGHT);
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::RIGHT, 1, 0);
  }

  void cooktopToBuns() {
    Drivetrain::wallToWallSlow(DriveDirection::LEFT);
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 0);
  }

  void bunsToCooktop() {
    Drivetrain::wallToWallSlow(DriveDirection::RIGHT);
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::RIGHT, 0, 0);
  }


}

#endif
#include <top_robot_actions.h>

namespace TopRobotActions {
  // ACTIONS
  void movePusherOut() {
    TopRobotModules::lowerOutputScraper();
    delay(400);
    TopRobotModules::movePusher(0.8);
    TopRobotModules::setOutputScraper(115.3);
    TopRobotModules::movePusher(1.65);
  }

  void movePusherIn() {
    TopRobotModules::movePusher(-0.35);
    TopRobotModules::raiseOutputScraper();
    TopRobotModules::movePusher(-2.15);
    delay(100);
    TopRobotModules::movePusher(0.03);
    TopRobotModules::lowerOutputScraper();
  }

  void reloadPusherPatty() {
    TopRobotModules::setOutputScraper(127);
    delay(200);
    TopRobotModules::movePusher(-0.8);
    TopRobotModules::lowerOutputScraper();
    delay(200);
    TopRobotModules::movePusher(0.8);
  }

  // DRIVING
  void startToBuns() {
    TopRobotModules::openInputScraper();                                        // open input scraper
    Drivetrain::driveMecanumTime(90, 0, 0.6, 510);                              // drive sideways to top counter
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 1, 0);  // wall follow 1FL to cutting area
  }
}
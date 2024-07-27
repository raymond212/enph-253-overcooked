#include <actions.h>

namespace Actions {
  void startTomato1() {
    BottomRobotModules::openInputScraper();
    Drivetrain::driveMecanumTime(90, 0, 0.3, 1000);
    delay(300);
    BottomRobotModules::closeInputScraper();
    delay(900);
  }

  void inputRoutine() {
    BottomRobotModules::openInputScraper();
    BottomRobotModules::rotateCarouselLeft();
    delay(800); // wait for food to be placed
    BottomRobotModules::closeInputScraper();
    delay(900); // close scraper
  }

  void tomatoToLettuce() {
    // drive forward left a bit
    Drivetrain::driveMecanumTime(15, 0, 0.5, 1000);
    Drivetrain::driveMecanumTime(180, 0, 0.5, 30);
    delay(500);
    // wall to wall spin
    wallToWallSpinSlow();
    // wall follow until lettuce area
    Drivetrain::driveMecanumTime(165, 0, 0.3, 300);
    Drivetrain::wallFollow(DriveDirection::BACKWARD, WallLocation::LEFT, 0, 800);
  }

  void alignLettuce1() {
    BottomRobotModules::openInputScraper();
    delay(900);
    Drivetrain::driveMecanumTime(15, 0, 0.3, 800);
    BottomRobotModules::closeInputScraper();
    delay(900);
  }

  void lettuceToCooktop() {
    Drivetrain::driveMecanumTime(15, 0, 0.5, 600);
    // spin across
    wallToWallSpinSlow();
    // go to cooktop
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 100);
  }

  void cooktopGrabPlate() {
    // drive from cooktop to plates
    BottomRobotModules::openPlatePincher();
    delay(200);
    Drivetrain::driveMecanumTime(15, 0, 0.3, 1700);
    // grab plate
    delay(500);
    BottomRobotModules::closePlatePincher();
    delay(500);
  }

  void plateToServing() {
    // drive
    Drivetrain::driveMecanumTime(165, 0, 0.35, 1500);
    Drivetrain::driveMecanumTime(0, 0, 0.5, 30);
    delay(300);
    // wall to wall spin
    wallToWallSpinSlow();
    // wall follow
    Drivetrain::driveMecanumTime(15, 0, 0.35, 900);
    Drivetrain::driveMecanumTime(180, 0, 0.5, 30);
  }

  void servingRoutine() {
    // open input scraper to prevent conflict
    BottomRobotModules::openInputScraper();
    // rotate food
    BottomRobotModules::rotateCarouselLeft();
    // raise food
    BottomRobotModules::moveElevator(79);
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
    BottomRobotModules::moveElevator(-79);
    // rotate carousel
    BottomRobotModules::closeInputScraper();
  }

  void servingToCooktop() {
    Drivetrain::driveMecanumTime(165, 0, 0.4, 200);
    BottomRobotModules::closePlatePincher();
    // go back across counter
    wallToWallSpinSlow();
    // close trapdoor
    BottomRobotModules::openPlatePincher();
    delay(500);
    BottomRobotModules::closeTrapdoor();
    // go to cooking
    Drivetrain::wallFollow(DriveDirection::FORWARD, WallLocation::LEFT, 0, 100);
  }

  void wallToWallSpinSlow() {
    Drivetrain::wallToWallSpin(DriveDirection::RIGHT, 680, 1350, 0.3, 0.3);
  }
}
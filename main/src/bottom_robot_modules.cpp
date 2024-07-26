#include <bottom_robot_modules.h>

namespace BottomRobotModules {
  Servo inputScraper, outputScraper, trapdoor, platePincher;
  Stepper carousel, elevator;

  void setupBottomRobotModules() {
    inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
    outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
    trapdoor = Servo(TRAPDOOR_PIN, TRAPDOOR_CHANNEL);
    platePincher = Servo(PLATE_PIN, PLATE_CHANNEL);

    carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 1);
    elevator = Stepper(ELEVATOR_STEP_PIN, ELEVATOR_DIR_PIN, 3);

    moveElevator(20);
  }

  void closeInputScraper() {
    // inputScraper.setAngle(17);
    inputScraper.setAngleSpeed(10, 110);
  }

  void openInputScraper() {
    // inputScraper.setAngle(137);
    inputScraper.setAngleSpeed(137, 110);
  }

  void closeTrapdoor() {
    trapdoor.setAngle(176);
  }

  void openTrapdoor() {
    trapdoor.setAngle(55);
  }

  void openOutputScraper() {
    outputScraper.setAngle(25);
  }

  void closeOutputScraper() {
    outputScraper.setAngle(170);
  }

  void openPlatePincher() {
    platePincher.setAngle(125);
  }

  void closePlatePincher() {
    platePincher.setAngle(137);
  }

  void moveElevator(double distanceMM) {
    elevator.step((int)(distanceMM / 8 * 200));
  }

  void rotateCarouselRight() {
    carousel.step(200);
    elevator.step(50);
  }

  void rotateCarouselLeft() {
    carousel.step(-200);
    elevator.step(-50);
  }

  void inputRoutine() {
    BottomRobotModules::openInputScraper();
    BottomRobotModules::rotateCarouselLeft();
    delay(1000);
    BottomRobotModules::closeInputScraper();
    delay(900);

  }
}
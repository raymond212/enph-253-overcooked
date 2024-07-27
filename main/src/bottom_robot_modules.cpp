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

    moveElevator(10);
    closeInputScraper();
    closeOutputScraper();
    closePlatePincher();
    closeTrapdoor();
  }

  void closeInputScraper() {
    inputScraper.setAngle(17);
  }

  void openInputScraper() {
    inputScraper.setAngle(137);
  }

  void closeTrapdoor() {
    trapdoor.setAngle(176);
  }

  void openTrapdoor() {
    trapdoor.setAngle(55);
  }

  void openOutputScraper() {
    outputScraper.setAngle(18);
  }

  void closeOutputScraper() {
    outputScraper.setAngle(173);
  }

  void openPlatePincher() {
    platePincher.setAngle(125);
  }

  void closePlatePincher() {
    platePincher.setAngle(140);
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

  void tomatoInputDestack() {
    inputScraper.setAngle(8);
  }
}
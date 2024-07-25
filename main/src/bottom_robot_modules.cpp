#include <bottom_robot_modules.h>

namespace BottomRobotModules {
  Servo inputScraper, outputScraper, trapdoor, platePincher;
  Stepper carousel, elevator;

  void setupBottomRobotModules() {
    inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
    outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
    trapdoor = Servo(TRAPDOOR_PIN, TRAPDOOR_CHANNEL);
    platePincher = Servo(PLATE_PIN, PLATE_CHANNEL);

    carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 0.5);
    elevator = Stepper(ELEVATOR_STEP_PIN, ELEVATOR_DIR_PIN, 4);
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

  void rotateCarouselRight() {
    carousel.step(-200);
  }

  void rotateCarouselLeft() {
    carousel.step(200);
  }

  void openOutputScraper() {
    outputScraper.setAngle(0);
  }

  void closeOutputScraper() {
    outputScraper.setAngle(180);
  }

  void openPlatePincher() {
    platePincher.setAngle(0);
  }

  void closePlatePincher() {
    platePincher.setAngle(180);
  }

  void moveElevator(double distanceMM) {
    elevator.step((int)(distanceMM / 8 * 200));
  }


}
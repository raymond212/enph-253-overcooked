#include <bottom_robot_modules.h>

namespace BottomRobotModules {
  Servo inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
  Servo outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
  Servo trapdoor = Servo(TRAPDOOR_PIN, TRAPDOOR_CHANNEL);
  Servo platePincher = Servo(PLATE_PIN, PLATE_CHANNEL);

  Stepper carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 0.75, 2);
  Stepper elevator = Stepper(ELEVATOR_STEP_PIN, ELEVATOR_DIR_PIN, 3, 3);

  void setupBottomRobotModules() {
    closeInputScraper();
    closeOutputScraper();
    closeTrapdoor();
    closePlatePincher();
  }

  void closeInputScraper() {
    inputScraper.setAngle(0);
  }

  void openInputScraper() {
    inputScraper.setAngle(180);
  }

  void closeOutputScraper() {
    outputScraper.setAngle(165);
  }

  void openOutputScraper() {
    outputScraper.setAngleSpeed(100, 100);
    outputScraper.setAngleSpeed(22, 50);
  }

  void closeTrapdoor() {
    trapdoor.setAngle(176);
  }

  void openTrapdoor() {
    trapdoor.setAngle(55);
  }
  
  void closePlatePincher() {
    platePincher.setAngle(132);
  }

  void openPlatePincher() {
    platePincher.setAngle(120);
  }

  void rotateCarouselRight() {
    carousel.step(200);
    elevator.step(50);
  }

  void rotateCarouselLeft() {
    carousel.step(-200);
    elevator.step(-50);
  }
  
  void moveElevator(double distanceMM) {
    elevator.step((int)(distanceMM / 8 * 200));
  }
}
#ifdef ENABLE_BOTTOM_ROBOT

#include <bottom_robot_modules.h>

namespace BottomRobotModules {
  Servo inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
  Servo outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
  Servo trapdoor = Servo(TRAPDOOR_PIN, TRAPDOOR_CHANNEL);
  Servo platePincher = Servo(PLATE_PIN, PLATE_CHANNEL);

  Stepper carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 0.75, 0);
  Stepper elevator = Stepper(ELEVATOR_STEP_PIN, ELEVATOR_DIR_PIN, 4.8, 1);

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

  void setInputScraper(double angle) {
    inputScraper.setAngle(angle);
  }

  void closeOutputScraper() {
    outputScraper.setAngle(169);
  }

  void openOutputScraper() {
    outputScraper.setAngle(20);
  }

  void closeTrapdoor() {
    trapdoor.setAngle(176);
  }

  void openTrapdoor() {
    trapdoor.setAngle(40);
  }
  
  void closePlatePincher() {
    platePincher.setAngle(135);
  }

  void openPlatePincher() {
    platePincher.setAngle(120);
  }

  void rotateCarouselRight() {
    elevator.stepRevsBlocking(0.25);
    carousel.stepRevs(1);
  }

  void rotateCarouselLeft() {
    elevator.stepRevsBlocking(-0.25);
    carousel.stepRevs(-1);
  }
  
  void moveElevator(double distanceMM) {
    elevator.step((int)(distanceMM / 8 * 200));
  }
}

#endif
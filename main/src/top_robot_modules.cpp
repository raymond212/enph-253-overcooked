#ifdef ENABLE_TOP_ROBOT

#include <top_robot_modules.h>

namespace TopRobotModules {
  Servo inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
  Servo outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
  
  Stepper carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 0.75, 0);
  Stepper pusher = Stepper(PUSHER_STEP_PIN, PUSHER_DIR_PIN, 2, 1);

  void setupTopRobotModules() {
    closeInputScraperFast();
    raiseOutputScraper();
  }

  void closeInputScraperPatty() {
    inputScraper.setAngleSpeed(130, 100);
    inputScraper.setAngleSpeed(180, 50);
  }

  void closeInputScraperBun() {
    inputScraper.setAngleSpeed(130, 100);
    inputScraper.setAngleSpeed(178, 50);
  }

  void closeInputScraperFast() {
    inputScraper.setAngle(180);
  }

  void openInputScraper() {
    inputScraper.setAngle(100);
  }

  void setInputScraper(double angle) {
    inputScraper.setAngle(angle);
  }

  void raiseOutputScraper() {
    outputScraper.setAngle(165);
  }

  void lowerOutputScraper() {
    // outputScraper.setAngle(117);
    outputScraper.setAngle(115);
  }

  void setOutputScraper(double angle) {
    outputScraper.setAngle(angle);
  }

  void rotateCarouselLeft(){
    carousel.stepRevs(1);
  }

  void rotateCarouselRight() {
    carousel.stepRevs(-1);
  }

  void rotateCarousel(double angle, double speed) {
    carousel.setSpeed(speed);
    carousel.stepRevs(angle / 360);
  }

  void movePusher(double revs, bool blocking) {
    if (blocking) {
      pusher.stepRevsBlocking(revs);
    } else {
      pusher.stepRevs(revs);
    }
  }
}

#endif
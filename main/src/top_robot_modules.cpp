#include <top_robot_modules.h>

namespace TopRobotModules {
  Servo inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
  Servo outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
  
  Stepper carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 0.75, 0);
  Stepper pusher = Stepper(PUSHER_STEP_PIN, PUSHER_DIR_PIN, 2, 1);

  void setupTopRobotModules() {
    closeInputScraper();
    raiseOutputScraper();
  }

  void closeInputScraper() {
    inputScraper.setAngle(130);
    inputScraper.setAngleSpeed(173, 50);
  }

  void closeInputScraperPatty() {
    inputScraper.setAngleSpeed(173, 50);
  }

  void openInputScraper() {
    inputScraper.setAngle(0);
  }

  void setInputScraper(double angle) {
    inputScraper.setAngle(angle);
  }

  void raiseOutputScraper() {
    outputScraper.setAngle(165);
  }

  void lowerOutputScraper() {
    outputScraper.setAngle(114.8);
  }

  void setOutputScraper(double angle) {
    outputScraper.setAngle(angle);
  }

  void rotateCarouselLeft(){
    carousel.stepRevs(-1);
  }

  void rotateCarouselRight() {
    carousel.stepRevs(1);
  }

  void rotateCarousel(double angle) {
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
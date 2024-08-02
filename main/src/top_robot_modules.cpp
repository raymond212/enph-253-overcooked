#include <top_robot_modules.h>

namespace TopRobotModules {
  Servo inputScraper, outputScraper;
  Stepper carousel, pusher;

  void setupTopRobotModules() {
    inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
    outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
    
    carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 1);
    pusher = Stepper(PUSHER_STEP_PIN, PUSHER_DIR_PIN, 2);
  }

  void closeInputScraper() {
    inputScraper.setAngle(171);
  }

  void closeInputScraperPatty() {
    inputScraper.setAngle(120);
    inputScraper.setAngleSpeed(175, 50);
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

  void movePusher(double revs) {
    pusher.stepRevs(revs);
  }
}
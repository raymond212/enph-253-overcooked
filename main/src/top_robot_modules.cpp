#include <top_robot_modules.h>

namespace TopRobotModules {
  Servo inputScraper, outputScraper;
  Stepper carousel, pusher;

  void setupTopRobotModules() {
    inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
    outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
    
    carousel = Stepper(CAROUSEL_STEP_PIN, CAROUSEL_DIR_PIN, 1);
    pusher = Stepper(PUSHER_STEP_PIN, PUSHER_DIR_PIN, 1);
  }

  void closeInputScraper() {
    inputScraper.setAngle(155);
  }

  void openInputScraper() {
    inputScraper.setAngle(0);
  }

  void setInputScraper(double angle) {
    inputScraper.setAngle(angle);
  }

  void raiseOutputScraper() {
    outputScraper.setAngle(177);
  }

  void lowerOutputScraper() {
    outputScraper.setAngle(117);
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

  void rotateCarousel(double angle) {
    carousel.stepRevs(angle / 360);
  }

  void movePusherOut() {
    pusher.stepRevs(2.5);
  }

  void movePusherIn() {
    pusher.stepRevs(-2.7); // move the pusher in a bit more to home
  }
}
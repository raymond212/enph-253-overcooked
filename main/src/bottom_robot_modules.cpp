#include <bottom_robot_modules.h>

namespace BottomRobotModules {
  Servo inputScraper = Servo(INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
  Stepper carousel = Stepper(25, 26);
  // Servo outputScraper = Servo(OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
  // Servo trapdoor = Servo(TRAPDOOR_PIN, TRAPDOOR_CHANNEL);

  bool inputScraperIsClosed = false;

  void setupBottomRobotModules() {

  }

  void run(String s) {
    if (s == "io") {
      Serial.println("openingInputScraper");
      openInputScraper();
    } else if (s == "ic") {
      Serial.println("closingInputScraper");
      closeInputScraper();
    } else if (s == "to") {
      Serial.println("openingTrapdoor");
      openTrapdoor();
    } else if (s == "tc") {
      Serial.println("closingTrapdoor");
      closeTrapdoor();
    } else if (s == "s") {
      while (Serial.available() == 0) {
        // wait
      }
      s = Serial.readStringUntil('\n');
      s.trim();
      inputScraper.setAngle(s.toInt());
    } else {
      carousel.step(s.toInt());
    }
  }

  void closeInputScraper() {
    inputScraper.setAngle(17);
  }

  void openInputScraper() {
    inputScraper.setAngle(137);
  }

  void closeTrapdoor() {
    // trapdoor.setAngle(178);
    // delay(2000);
  }

  void openTrapdoor() {
    // trapdoor.setAngle(55);
    // delay(2000);
  }
}
#include <bottom_robot_modules.h>

namespace BottomRobotModules {
  Servo inputScraper = Servo(5, INPUT_SCRAPER_CHANNEL);
  Stepper carousel = Stepper(25, 26);
  Stepper leadScrew = Stepper(32, 33);
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
    } else if (s == "ca") {
      Serial.println("Moving -quarter");
      carousel.step(200);
    } else if (s == "cb") {
      Serial.println("Moving +quarter");
      carousel.step(-200);
    } else if (s == "s") {
      Serial.println("Enter angle");
      while (Serial.available() == 0) {
        // wait
      }
      s = Serial.readStringUntil('\n');
      s.trim();
      inputScraper.setAngle(s.toInt());
    } else if (s == "c") {
      Serial.println("Enter carousel steps");
      while (Serial.available() == 0) {
        // wait
      }
      s = Serial.readStringUntil('\n');
      s.trim();
      carousel.step(s.toInt());
    } else if (s == "input") {
      closeInputScraper();
      delay(800);
      openInputScraper();
      carousel.step(-200);
    } else {
      Serial.println("Moving lead screw");
      double mm = s.toDouble();
      leadScrew.step((int)(mm * 200));
      // leadScrew.step((int)(mm / 8 * 200));
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
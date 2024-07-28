#include <top_robot_modules.h>

namespace TopRobotModules {

  Servo inputScraper, outputScraper;
  Stepper spiral, linear;

  void setupTopRobotModules() {
    inputScraper = Servo(TOP_INPUT_SCRAPER_PIN, INPUT_SCRAPER_CHANNEL);
    outputScraper = Servo(TOP_OUTPUT_SCRAPER_PIN, OUTPUT_SCRAPER_CHANNEL);
    
    spiral = Stepper(SPIRAL_STEP_PIN, SPIRAL_DIR_PIN, 1);
    linear = Stepper(LINEAR_STEP_PIN, LINEAR_DIR_PIN, 2);
  }

  // top robot modules testing
  /*
  String s = waitAndRead();
  if (s == "input") {
    int angle = waitAndRead().toInt();
    inputServo.setAngle(angle);
  } else if (s == "output") {
    int angle = waitAndRead().toInt();
    outputServo.setAngle(angle);
  } else if (s == "linear") {
    double revs = waitAndRead().toDouble();
    outputStepper.step((int)(revs * 200));
  } else if (s == "carousel") {
    double revs = waitAndRead().toDouble();
    carouselStepper.step((int)(revs * 200));
  } else if (s == "ic") {
    inputServo.setAngle(107);
  } else if (s == "io") {
    inputServo.setAngle(180);
  } else if (s == "ou") {
    outputServo.setAngle(180);
  } else if (s == "od") {
    outputServo.setAngle(117);
  } else if (s == "lo") {
    outputStepper.stepRevs(2.5);
  } else if (s == "li") {
    outputStepper.stepRevs(-2.5);
  } else if (s == "ci") {
    carouselStepper.stepRevs(0.33);
  } else if (s == "co") {
    carouselStepper.stepRevs(-0.33);
  } */


  void closeInputScraper() {
    inputScraper.setAngle(107);
  }

  void openInputScraper() {
    inputScraper.setAngle(180);
  }


  void raiseOutputScraper() {
    outputScraper.setAngle(180);
  }

  void lowerOutputScraper() {
    outputScraper.setAngle(117);
  }

  void rotateSpiralLeft(){
    spiral.stepRevs(0.33);
  }


  void rotateSpiralRight() {
    spiral.stepRevs(-0.33);
  }

  void moveLinearOut() {
    linear.stepRevs(2.5);
  }
  void moveLinearIn() {
    linear.stepRevs(-2.5);
  }


  void InputOutputRoutine() {

    TopRobotModules::raiseOutputScraper();

    for (int i = 0; i < 4; i++) {
      delay(1000);
      TopRobotModules::openInputScraper();
      delay(3000);
      TopRobotModules::closeInputScraper();
      delay(1000);
      TopRobotModules::rotateSpiralRight();
    }

    delay(900);

    for (int i = 0; i < 4; i++) {
    TopRobotModules::lowerOutputScraper();
    delay(900);
    TopRobotModules::moveLinearOut();
    delay(900);
    TopRobotModules::raiseOutputScraper();
    delay(400);
    TopRobotModules::moveLinearIn();
    delay(400);
    TopRobotModules::rotateSpiralLeft();
    delay(1000);
    }
  }
}
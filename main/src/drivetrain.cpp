#include <drivetrain.h>

namespace Drivetrain {
  Motor leftM = Motor(L_MOTOR_PIN_A, L_MOTOR_PIN_B, L_ENCODER_PIN_A, L_ENCODER_PIN_B, L_MOTOR_CHANNEL_A, L_MOTOR_CHANNEL_B);
  Motor rightM = Motor(R_MOTOR_PIN_A, R_MOTOR_PIN_B, R_ENCODER_PIN_A, R_ENCODER_PIN_B, R_MOTOR_CHANNEL_A, R_MOTOR_CHANNEL_B);

  void setupDrivetrain() {
    // Motor setup is done in the Motor constructor
    attachInterrupt(L_ENCODER_PIN_A, []{leftM.encoderISR();}, CHANGE);
    attachInterrupt(R_ENCODER_PIN_A, []{rightM.encoderISR();}, CHANGE);
  }

  void driveTest() {
    while (true) {
      drive(0.15, 0.15);
      Serial.println(String(leftM.getCount()) + " " + String(rightM.getCount()));
      delay(100);
    }
  }

  void tapeFollow(double targetDistance) {
    leftM.resetEncoder();
    rightM.resetEncoder();
    double distance = 0;
    TurnDirection lastTurnAttempt = TurnDirection::RIGHT;

    while (distance < targetDistance) {
      switch (TapeSensors::readTape()) {
        case TapeReading::BOTH:
          // both tape, go straight
          // Network::wifiPrintln("straight");
          drive(0.5, 0.5);
          break;
        case TapeReading::LEFT:
          // front left tape, turn left
          // Network::wifiPrintln("turn left");
          drive(0.25, 0.5);
          lastTurnAttempt = TurnDirection::LEFT;
          break;
        case TapeReading::RIGHT:
          // front right tape, turn right
          // Network::wifiPrintln("turn right");
          drive(0.5, 0.25);
          lastTurnAttempt = TurnDirection::RIGHT;
          break;
        case TapeReading::NONE:
          // no tape, stop
          // Network::wifiPrintln("stop");
          if (lastTurnAttempt == TurnDirection::RIGHT) {
            drive(0.15, -0.07);
          } else {
            drive(-0.15, 0.07);
          }
          break;
      }
      delay(1);
      distance = ((leftM.getDistance() + rightM.getDistance()) / 2);
    }
    // Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    // Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
    // Network::wifiPrintln("Distance (in): " + String(distance));
    
    // active breaking
    drive(-0.6, -0.6);
    delay(100);
    drive(0, 0);
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
  }

  void turnUntilTape(TurnDirection dir) {
    leftM.resetEncoder();
    rightM.resetEncoder();
    // double turningThresholdDistance = (WHEEL_TO_WHEEL_DIST * PI / 4) - 1;
    // double distance = 0;

    long startTime = millis();
    while (!(TapeSensors::readTape() == TapeReading::BOTH && millis() - startTime > 500)) {
      if (dir == TurnDirection::LEFT) {
        // Network::wifiPrintln("Turning left");
        drive(-0.27, 0.22);
      } else {
        // Network::wifiPrintln("Turning right");
        drive(0.27, -0.22);
      }
      // distance = ((abs(leftM.getDistance()) + abs(rightM.getDistance())) / 2);
      // delay(1);
    }
    // Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    // active breaking
    if (dir == TurnDirection::LEFT) {
      drive(0.6, -0.6);
      delay(60);
    } else {
      drive(-0.6, 0.6);
      delay(60);
    }
    drive(0, 0);
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
  }

  void driveUpToTable() {
    leftM.resetEncoder();
    rightM.resetEncoder();
    double distance = 0;
    TurnDirection lastTurnAttempt = TurnDirection::RIGHT;
    bool tapeEnded = false;

    while (!(tapeEnded && distance > 7)) {
      tapeEnded = false;
      switch (TapeSensors::readTape()) {
        case TapeReading::BOTH:
          // both tape, go straight
          // Network::wifiPrintln("straight");
          drive(0.3, 0.3);
          break;
        case TapeReading::LEFT:
          // front left tape, turn left
          // Network::wifiPrintln("turn left");
          drive(-0.19, 0.1);
          lastTurnAttempt = TurnDirection::LEFT;
          break;
        case TapeReading::RIGHT:
          // front right tape, turn right
          // Network::wifiPrintln("turn right");
          drive(0.19, -0.1);
          lastTurnAttempt = TurnDirection::RIGHT;
          break;
        case TapeReading::NONE:
          tapeEnded = true;
          if (lastTurnAttempt == TurnDirection::RIGHT) {
            drive(0.19, -0.1);
          } else {
            drive(-0.19, 0.1);
          }
          break;
      }
      delay(1);
      distance = ((leftM.getDistance() + rightM.getDistance()) / 2);
    }
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
    
    // active breaking
    drive(-0.6, -0.6);
    delay(40);
    drive(0, 0);
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
  }

  void backUpToTape() {
    leftM.resetEncoder();
    rightM.resetEncoder();
    double distance = 0;

    while (distance < 7.3) {
      drive(-0.3, -0.25);
      delay(1);
      distance = -((leftM.getDistance() + rightM.getDistance()) / 2);
    }

    drive(0.5, 0.5);
    delay(50);
    drive(0, 0);
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
  }

  void drive(double leftPower, double rightPower) {
    leftM.setPower(leftPower);
    rightM.setPower(rightPower);
  }

  void run(int speed) {
    // while (true) {
    //   rightM.setDutyCycle(21);
    //   delay(1000);
    //   Serial.println(rightM.getSpeed());
    // }

    int leftDuty = Utils::leftMotorSpeedToDutyCycle(speed);
    int rightDuty = Utils::rightMotorSpeedToDutyCycle(speed);
    leftM.setDutyCycle(leftDuty);
    rightM.setDutyCycle(rightDuty);
    delay(2000);

    while (true) {
      Serial.println(String(leftDuty) + " " + String(rightDuty));
      leftM.setDutyCycle(leftDuty);
      rightM.setDutyCycle(rightDuty);
      delay(1000);
      Serial.println(String(leftM.getSpeed()) + " " + String(rightM.getSpeed()));
    }

    // for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    //   rightM.setDutyCycle(dutyCycle);
    //   leftM.setDutyCycle(dutyCycle);
    //   // delay(250);
    //   // leftM.getSpeed();
    //   // rightM.getSpeed();
    //   delay(500);
    //   Serial.println(String(dutyCycle) + ", " + String(leftM.getSpeed()) + ", " + String(rightM.getSpeed()));
    // }
  }
}
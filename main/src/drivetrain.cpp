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

    while (distance < targetDistance) {
      switch (TapeSensors::readTape()) {
        case TapeReading::BOTH:
          // both tape, go straight
          Serial.println("straight");
          drive(TAPE_FOLLOW_HIGH_POWER, TAPE_FOLLOW_HIGH_POWER);
          break;
        case TapeReading::LEFT:
          // front left tape, turn left
          Serial.println("turn left");
          drive(TAPE_FOLLOW_LOW_POWER, TAPE_FOLLOW_HIGH_POWER);
          break;
        case TapeReading::RIGHT:
          // front right tape, turn right
          Serial.println("turn right");
          drive(TAPE_FOLLOW_HIGH_POWER, TAPE_FOLLOW_LOW_POWER);
          break;
        case TapeReading::NONE:
          // no tape, stop
          Serial.println("stop");
          drive(0, 0);
          break;
      }
      delay(10);
      distance = ((leftM.getDistance() + rightM.getDistance()) / 2);
    }
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
    Network::wifiPrintln("Distance (in): " + String(distance));
    
    // active breaking
    drive(-1, -1);
    delay(200);
    drive(0, 0);
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
    Network::wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
  }

  void turnUntilTape(TurnDirection dir, int minDelayMs) {
    leftM.resetEncoder();
    rightM.resetEncoder();

    long startTime = millis();
    while (!(TapeSensors::readTape() == TapeReading::BOTH && millis() - startTime > minDelayMs)) {
      if (dir == TurnDirection::LEFT) {
        Network::wifiPrintln("Turning left");
        drive(-0.1 * 1.5, 0.1);
      } else {
        Network::wifiPrintln("Turning right");
        drive(0.1 * 1.5, -0.1);
      }
      delay(10);
    }

    // active breaking
    if (dir == TurnDirection::LEFT) {
      drive(1, -1);
    } else {
      drive(-1, 1);
    }
    delay(15);
    drive(0, 0);
    Network::wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
  }

  void drive(double leftPower, double rightPower) {
    leftM.setPower(leftPower);
    rightM.setPower(rightPower);
  }
}
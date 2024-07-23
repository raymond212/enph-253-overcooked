#include <drivetrain.h>

namespace Drivetrain {
  Motor FLMotor = Motor(FL_MOTOR_PIN_A, FL_MOTOR_PIN_B, FL_MOTOR_CHANNEL_A, FL_MOTOR_CHANNEL_B);
  Motor FRMotor = Motor(FR_MOTOR_PIN_A, FR_MOTOR_PIN_B, FR_MOTOR_CHANNEL_A, FR_MOTOR_CHANNEL_B);
  Motor BLMotor = Motor(BL_MOTOR_PIN_A, BL_MOTOR_PIN_B, BL_MOTOR_CHANNEL_A, BL_MOTOR_CHANNEL_B);
  Motor BRMotor = Motor(BR_MOTOR_PIN_A, BR_MOTOR_PIN_B, BR_MOTOR_CHANNEL_A, BR_MOTOR_CHANNEL_B);

  void setupDrivetrain() {
    // Motor setup is done in the Motor constructor
    TapeSensors::setupTapeSensors();
  }

  void driveMotors(double FLPower, double FRPower, double BLPower, double BRPower) {
    FLMotor.setPower(FLPower);
    FRMotor.setPower(FRPower);
    BLMotor.setPower(BLPower);
    BRMotor.setPower(BRPower);
  }

  void driveMecanum(double theta, double rotation, double power) {
    double sinTerm = sin((theta + 45) * PI / 180);
    double cosTerm = cos((theta + 45) * PI / 180);
    double maxTerm = max(abs(sinTerm), abs(cosTerm));

    double FLPower = power * (cosTerm / maxTerm) + rotation;
    double FRPower = power * (sinTerm / maxTerm) - rotation;
    double BLPower = power * (sinTerm / maxTerm) + rotation;
    double BRPower = power * (cosTerm / maxTerm) - rotation;

    double maxPower = max(max(abs(FLPower), abs(FRPower)), max(abs(BLPower), abs(BRPower)));

    if (maxPower > 1) {
      FLPower /= maxPower;
      FRPower /= maxPower;
      BLPower /= maxPower;
      BRPower /= maxPower;
    }
    Serial.println(String(FLPower) + " " + String(FRPower) + " " + String(BLPower) + " " + String(BRPower));
    driveMotors(FLPower, FRPower, BLPower, BRPower);
  }

  void stopAll() {
    driveMotors(0, 0, 0, 0);
  }

  void run() {
    // run
  }

  void driveFUntilTape(int num) {
    int count = 0;
    bool prevFrontTape = TapeSensors::frontIsTape();
    int iter = 0;
    long start = millis();
    driveMecanum(-10, 0, 0.5);

    while (count < num) {
      if (!prevFrontTape && TapeSensors::frontIsTape()) {
        count++;
      }
      prevFrontTape = TapeSensors::frontIsTape();
      iter++;
    }

    Network::wifiPrintln("Time: " + String(millis() - start) + " Iter: " + String(iter));

    driveMecanum(180, 0, 1);
    delay(50);
    stopAll();
  }

  // void driveBUntilTape(int skip = 0) {

  //   int count = 0;
  //   unsigned long time = millis();

  //   driveMotors(-0.5,-0.5,-0.5,-0.5);
  //   //edit values above^

  //   while (true) {
  //     if (TapeSensors::backIsTape()) {
  //       if (count == skip){
  //         stopAll();
  //         break;
  //       } else {
  //         count ++;
  //         delay(100);
  //       }
  //     }
  //     }

  // }


}
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include <constants.h>
#include <motor.h>
#include <tape_sensor.h>

Motor leftM = Motor(LEFT_M_F, LEFT_M_B, LEFT_M_E_A, LEFT_M_E_B);
Motor rightM = Motor(RIGHT_M_F, RIGHT_M_B, RIGHT_M_E_A, RIGHT_M_E_B);
TapeSensor tapeSensor = TapeSensor(TAPE_SENSOR_L, TAPE_SENSOR_R);

WiFiServer server(WIFI_PORT);
WiFiClient remoteClient;

void drive(double leftSpeed, double rightSpeed);
void tapeFollow();
void stopAll();
void wifiPrintln(String msg);
bool wifiInput();

void setup() {
  // Serial setup
  Serial.begin(9600);

  // Wifi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
    ESP.restart();
  }

  server.begin();
  Serial.println("Server started");
  Serial.println("IP Address: " + WiFi.localIP());

  // Other setup
  analogWriteFrequency(250);
  attachInterrupt(RIGHT_M_E_A, []{rightM.updateEncoder();}, CHANGE);
  attachInterrupt(LEFT_M_E_A, []{leftM.updateEncoder();}, CHANGE);
  rightM.resetEncoder();
  leftM.resetEncoder();
}

void loop() {
  while (!wifiInput()) {
    Serial.println("Waiting");
    delay(100);
  }
  wifiPrintln("Starting tape following");

  long start = millis();

  rightM.resetEncoder();
  leftM.resetEncoder();
  while (millis() - start < 2000) {
    // drive(0.4, 0.4);
    wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
    tapeFollow();
    delay(10);
  }
  wifiPrintln("Done tape following");
  wifiPrintln("Distance:" + String(leftM.getDistance()) + " " + String(rightM.getDistance()));
  drive(-1, -1);
  while (millis() - start < 2250) {
    wifiPrintln(String(leftM.getCount()) + " " + String(rightM.getCount()));
    // tapeFollow();
    delay(10);
  }
  stopAll();
  // wifiPrintln("Encoder readings: " + String(leftM.getCount()) + " " + String(rightM.getCount()));

  // wifiPrintln(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
  // delay(5000);

  // leftM.setSpeed(0.5);
  // rightM.setSpeed(0.5);
  // Serial.println(tapeSensor.getValuesStr());
  // Serial.println(String(leftM.getCount()) + " " + String(rightM.getCount()));
  // leftM.resetEncoder();
  // rightM.resetEncoder();
  // delay(1000);

  // rightM.setSpeed(1);
  // leftM.setSpeed(1);
  // Serial.println(String(leftM.getDistance()) + " " + String(rightM.getDistance()));
  // // rightM.resetEncoder();
  // delay(1000);
}

void tapeFollow() {
  switch (tapeSensor.reading()) {
    case TapeReading::BOTH:
      // no tape, go straight
      wifiPrintln("straight");
      drive(MOTOR_FAST_SPEED, MOTOR_FAST_SPEED);
      break;
    case TapeReading::LEFT:
      // front left tape, turn left
      wifiPrintln("left");
      drive(MOTOR_SLOW_SPEED, MOTOR_FAST_SPEED);
      break;
    case TapeReading::RIGHT:
      // front right tape, turn right
      wifiPrintln("right");
      drive(MOTOR_FAST_SPEED, MOTOR_SLOW_SPEED);
      break;
    case TapeReading::NONE:
      // both tapes, stop
      wifiPrintln("stop");
      stopAll();
      // drive(0, 0);
      break;
  }
}

void drive(double leftSpeed, double rightSpeed) {
  leftM.setSpeed(leftSpeed);
  rightM.setSpeed(rightSpeed);
}

void stopAll() {
  leftM.stop();
  rightM.stop();
}

void wifiPrintln(String msg) {
  if (server.hasClient()) {
    if (remoteClient.connected()) {
      Serial.println("Connection rejected: already connected");
      server.available().stop();
    } else {
      Serial.println("Connection accepted");
      remoteClient = server.available();
    }
  }
  if (remoteClient.connected()) {
    remoteClient.println(msg);
  }
}

bool wifiInput() {
  if (server.hasClient()) {
    if (remoteClient.connected()) {
      Serial.println("Connection rejected: already connected");
      server.available().stop();
    } else {
      Serial.println("Connection accepted");
      remoteClient = server.available();
    }
  }
  if (remoteClient.connected() && remoteClient.available()) {
    String message = remoteClient.readStringUntil('\n');
    if (message.length() > 0) {
      Serial.println("Received: " + message);
      wifiPrintln("Echo:" + message);
      return true;
    }
  }
  return false;
}
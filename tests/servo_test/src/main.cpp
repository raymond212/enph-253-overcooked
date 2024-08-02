#include <Arduino.h>
#include <Servo.h>

int servoPin = 8;
int curPosition = 0;

String waitAndRead();
String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

void outputTrapdoor();
void inputScraper();
void moveServo(int delayMs, int target);

Servo servo = Servo(8, 0);

void setup() {
  Serial.begin(9600);
  Serial.println("Enter servo position: ");
  // analogWriteFrequency(50);
}

void loop() {
  int angle = waitAndRead().toInt();
  Serial.println("Moving servo to " + String(angle));
  servo.setAngle(angle);
}
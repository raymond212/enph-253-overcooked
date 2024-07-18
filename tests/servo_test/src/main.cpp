#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;
int servoPin = 13;
int curPosition = 0;

void outputTrapdoor();
void inputScraper();
void moveServo(int delayMs, int target);

void setup() {
  Serial.begin(9600);
	myservo.setPeriodHertz(50);
	myservo.attach(servoPin, 500, 2500);
  Serial.println("Enter servo position: ");
  // analogWriteFrequency(50);
}

void loop() {
  outputTrapdoor();
}

void moveServo(int delayMs, int target) {
  while (curPosition != target) {
    if (curPosition < target) {
      curPosition++;
    } else {
      curPosition--;
    }
    myservo.write(curPosition);
    delay(delayMs);
  }
}

void outputTrapdoor() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "o") {
      myservo.write(55);
      // moveServo(65, 25);
    } else if (input == "c") {
      myservo.write(176);
      // delay(1000);
      // myservo.write(55);
      // moveServo(174, 25);
    } else {
      myservo.write(input.toInt());
    }
  }
} 

void inputScraper() {
  // input scraper: 140 to 20 

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    myservo.write(20);
    delay(800);
    myservo.write(140);
  }
}
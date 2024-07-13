#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;
int servoPin = 13;
 
void setup() {
  Serial.begin(9600);
	myservo.setPeriodHertz(50);
	myservo.attach(servoPin, 500, 2500);
  Serial.println("Enter servo position: ");
  // analogWriteFrequency(50);
}
 
int curPosition = 140;

void loop() {
  // input scraper: 140 to 20 

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    // input.trim();
    // int targetPosition = (input == "O") ? 140 : 20;
    // // int targetPosition = input.toInt();
    // Serial.println("Moving to position: " + String(targetPosition));
    myservo.write(20);
    delay(800);
    myservo.write(140);
    // delay();
    // if (targetPosition >= 0 && targetPosition <= 180) {
    //   myservo.write(targetPosition);
    //   curPosition = targetPosition;
    //   // while (curPosition != targetPosition) {
    //   //   if (curPosition < targetPosition) {
    //   //     curPosition++;
    //   //   } else {
    //   //     curPosition--;
    //   //   }
    //   //   myservo.write(curPosition);
    //   //   delay(15);
    //   // }
    // } else {
    //   Serial.println("Invalid position.");
    // }
  }
}
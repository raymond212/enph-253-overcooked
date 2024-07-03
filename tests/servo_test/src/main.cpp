#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;
int servoPin = 13;
 
void setup() {
	myservo.setPeriodHertz(50);
	myservo.attach(servoPin, 500, 2500);
  
  // analogWriteFrequency(50);
}
 
void loop() {
  int T = 1300;
  myservo.write(0);
  delay(T);
  myservo.write(180);
  delay(T);
}
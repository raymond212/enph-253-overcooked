#include <Arduino.h>

const int motorF = 21;
const int motorB = 22;
// const int motorE = 20;
const int pot = 25;

void setup() {
  pinMode(motorF, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(pot, INPUT);
  // pinMode(motorE, OUTPUT);
  // analogWriteFrequency(2000);
}

void loop() {
  int speed = analogRead(pot);

  analogWrite(motorF, map(speed, 0, 4095, 0, 255));
  digitalWrite(motorB, LOW);

  analogWrite(motorB, 60);
  digitalWrite(motorF, LOW);
  delay(20);
}
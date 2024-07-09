#include <Arduino.h>

const int motorF = 22;
const int motorB = 19;
const int potPin = 37;
const int encoder = 35;

volatile int num = 0;

void increment();

void increment() {
  num++;
}

void setup() {
  Serial.begin(9600);
  pinMode(motorF, OUTPUT);
  pinMode(motorB, OUTPUT);

  pinMode(potPin, INPUT);
  pinMode(encoder, INPUT_PULLUP);
  attachInterrupt(encoder, increment, RISING);

  analogWriteFrequency(250);
}

void loop() {
  int analogValue = analogRead(potPin);

  analogWrite(motorF, map(analogValue, 0, 4095, 0, 255));
  analogWrite(motorB, 0);

  Serial.println(num);
  num = 0;
  delay(1000);
}
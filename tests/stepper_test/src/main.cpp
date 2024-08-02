#include <Arduino.h>
#include <stepper.h>
#include <namespaceTest.h>

String waitAndRead();
String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

void setup() {
  Serial.begin(9600);
  NamespaceTest::setupNamespaceTest();
}

void loop() {
  double revs = waitAndRead().toDouble();
  Serial.println("Moving " + String(revs) + " revolutions");
  NamespaceTest::rotate(revs);
  for (int i = 0; i < 50; i++) {
    Serial.println(i);
    delay(50);
  }
}
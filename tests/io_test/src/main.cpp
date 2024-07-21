#include <Arduino.h>

String waitAndRead();

void setup() {
  Serial.begin(9600);
}

void loop() {
  // String input = waitAndRead();
  // Serial.println(input);
  // if (input == "pwm") {
  int pin = 20;
  int frequency = waitAndRead().toInt();
  Serial.println("Frequency: " + String(frequency));
  int dutyCycle = waitAndRead().toInt();
  Serial.println("Duty cycle: " + String(dutyCycle));
  Serial.println("Running PWM");
  int channel = 0;
  ledcSetup(channel, frequency, 8);
  ledcAttachPin(pin, channel);
  ledcWrite(channel, dutyCycle);
  delay(5000);
  ledcWrite(channel, 0);
  ledcDetachPin(pin);
  // }
  // if (input == "pwm") {

  // }
}

String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  return Serial.readString();
}


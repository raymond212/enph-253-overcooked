#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define ANALOG_PIN PA0
#define DIGITAL_PIN PA1

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

long start;
long counter;

void display(String s);

void setup() {
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);

  pinMode(ANALOG_PIN, INPUT);
  pinMode(DIGITAL_PIN, INPUT);
  start = micros();
  counter = 0;
}

void loop() {
  if (micros() - start >= 1000000) {
    display(String(counter));
    counter = 0;
    start = micros();
  } else {
    // digitalRead(DIGITAL_PIN);
    analogRead(ANALOG_PIN);
    counter++;
  }
}

void display(String s) {
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println(s);
  display_handler.display();
}
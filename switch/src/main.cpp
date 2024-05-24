#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define PIN_SWITCH PB11
#define BUILTIN_LED PC13

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void handleSwitchPress();
void display(String s);

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_SWITCH), handleSwitchPress, CHANGE);

  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
}

void handleSwitchPress() {
  if (digitalRead(PIN_SWITCH) == HIGH) {
    display("Pressed!");
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    display("Released!");
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void display(String s) {
  display_handler.clearDisplay();
  display_handler.setTextSize(2);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println(s);
  display_handler.display();
}
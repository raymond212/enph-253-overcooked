#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 10
#define OLED_SCL 9

Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void oledPrint(String s);
String waitAndRead();

void setup() {
  Serial.begin(9600);
  pinMode(35, INPUT);
  Wire.begin(OLED_SDA, OLED_SCL);
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.clearDisplay();
  display_handler.setTextSize(2);
  display_handler.setTextColor(SSD1306_WHITE);
}

void loop() {
  // String s = waitAndRead();
  oledPrint(String(digitalRead(35)));
}

void oledPrint(String s) {
  display_handler.clearDisplay();
  display_handler.setCursor(0, 0);
  display_handler.println(s);
  display_handler.display();
}

String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}
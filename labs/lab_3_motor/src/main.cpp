#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define MOTOR_A_PIN PA_0
#define MOTOR_B_PIN PA_1
#define POT_PIN PA_2

const int PWM_FREQ = 2000;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void display(String s);

void setup() {
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);

  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.clearDisplay();
  display_handler.setTextSize(2);
  display_handler.setTextColor(SSD1306_WHITE);
}

void loop() {
  int analog_value = analogRead(POT_PIN);
  int pwm_value = map(analog_value, 0, 1023, -4095, 4095);
  if (pwm_value > 0) {
    pwm_start(MOTOR_A_PIN, PWM_FREQ, pwm_value, RESOLUTION_12B_COMPARE_FORMAT);
  } else {
    pwm_start(MOTOR_B_PIN, PWM_FREQ, -pwm_value, RESOLUTION_12B_COMPARE_FORMAT);
  }
  display("PWM: " + String(analog_value));
  delay(100);
}

void display(String s) {
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println(s);
  display_handler.display();
}
#include <user_interface.h>

namespace UserInterface { 
  Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  
  void setupUserInterface() {
    pinMode(BUTTON_PIN, INPUT);

    Wire.begin(OLED_SDA, OLED_SCL);
    display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display_handler.clearDisplay();
    display_handler.setTextSize(2);
    display_handler.setTextColor(SSD1306_WHITE);

    #ifdef LEFT_FIELD
    String s = "Left";
    #else
    String s = "Right";
    #endif
    displayOLED("OLED" + s);
  }

  void displayOLED(String text) {
    display_handler.clearDisplay();
    display_handler.setCursor(0, 0);
    display_handler.println(text);
    display_handler.display();
  }

  bool isButtonPressed() {
    return digitalRead(BUTTON_PIN) == HIGH;
  }
}

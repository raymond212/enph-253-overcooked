#include <user_interface.h>

namespace UserInterface { 
  Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  
  void setupUserInterface() {  
    Wire.begin(OLED_SDA, OLED_SCL);
    display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display_handler.clearDisplay();
    display_handler.setTextSize(2);
    display_handler.setTextColor(SSD1306_WHITE);

    displayOLED("OLED initialized");
  }

  void displayOLED(String text) {
    display_handler.clearDisplay();
    display_handler.setCursor(0, 0);
    display_handler.println(text);
    display_handler.display();
  }
}

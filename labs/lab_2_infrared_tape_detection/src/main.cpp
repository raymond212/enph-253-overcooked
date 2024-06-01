/**
* @brief IR Detection: Detects distance and frequency
*/

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define IR_INPUT PA0
#define THRESHOLD 400

volatile int startTime;

/**
 * @brief Initialize LED pin as digital write.
 * @param none
 * @retval none
 */
void setup()
{
  //initialize IR phototransistor as an input
  pinMode(IR_INPUT, INPUT);

  //initialize OLED
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.clearDisplay();
  display_handler.setTextSize(3);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
}

/**
 * @brief Turn LED on for 1 sec and off for 1 sec.
 * @param none
 * @retval none
 */
void loop()
{
  //read the IR photoresistor  
  int infraredReading = analogRead(IR_INPUT);
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println(infraredReading);
  if (infraredReading >= THRESHOLD) {
    display_handler.println("black");
  } else {
    display_handler.println("white");
  }
  display_handler.display();
  delay(1000);
}
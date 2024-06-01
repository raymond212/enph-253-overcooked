#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define IR_PIN PA0
#define TEST_PERIOD_S 0.05
#define SAMPLE_FREQUENCY_HZ (10000.0)
#define SAMPLE_PERIOD_S (1 / SAMPLE_FREQUENCY_HZ)
#define NUM_SAMPLES int(TEST_PERIOD_S / SAMPLE_PERIOD_S)

#define _1_KHZ_PERIOD_S (1.0 / 1000)
#define _3_KHZ_PERIOD_S (1.0 / 3000)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long initialPollTime;
unsigned long prev;

float _1kHzReference[NUM_SAMPLES];
float _3kHzReference[NUM_SAMPLES];
float reading[NUM_SAMPLES];
int samplesTaken = 0;

float crossCorrelate(float reading[], float reference[]);
float arrayAvg(float array[], int length);
void centerArray(float array[], int length);
void display(String s);

void setup() {
  pinMode(IR_PIN, INPUT);
  initialPollTime = micros();
  // Set up display
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  // Create 1kHz and 3kHz reference signals
  for (int i = 0; i < NUM_SAMPLES; i++) {
    _1kHzReference[i] = sin(2 * PI * i * SAMPLE_PERIOD_S / _1_KHZ_PERIOD_S);
    _3kHzReference[i] = sin(2 * PI * i * SAMPLE_PERIOD_S / _3_KHZ_PERIOD_S);
  }
}

void loop() {
  if (samplesTaken == NUM_SAMPLES) {
    long timeTaken = micros() - prev;
    centerArray(reading, NUM_SAMPLES);
    float max1kHz = crossCorrelate(reading, _1kHzReference);
    float max3kHz = crossCorrelate(reading, _3kHzReference);
    display("1kHz: " + String(max1kHz) + "\n3kHz: " + String(max3kHz) + "\nTest period (us): \n" + String(timeTaken));
    initialPollTime = micros();
    samplesTaken = 0;
    prev = micros();
  } else if ((micros() - initialPollTime) / 1e6 >= SAMPLE_PERIOD_S * (samplesTaken + 1)) {
    reading[samplesTaken++] = analogRead(IR_PIN);
  }
}

float crossCorrelate(float reading[], float reference[]) {
  float res = -1e9;
  for (int shift = 0; shift < NUM_SAMPLES; shift++) {
    float sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
      if (i + shift >= 0 && i + shift < NUM_SAMPLES) {
        sum += reading[i] * reference[i + shift];
      }
    }
    res = max(res, sum);
  }
  return res;
}

void display(String s) {
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println(s);
  display_handler.display();
}

void centerArray(float array[], int length) {
  float avg = arrayAvg(array, length);
  for (int i = 0; i < length; i++) {
    array[i] -= avg;
  }
}

float arrayAvg(float array[], int length) {
  float sum = 0;
  for (int i = 0; i < length; i++) {
    sum += array[i];
  }
  return sum / length;
}
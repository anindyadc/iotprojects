#include <FastLED.h>

// Color Wipe: LEDs light up in a color, one by one.
// Rainbow Cycle: A smooth color transition effect.
// Chase: A “chasing” effect across the matrix.
// Theater Chase: Creates a marquee effect, popular in T1000-based designs.
// Random Sparkle: Random LEDs blink on and off.

#define NUM_LEDS 60              // Total number of LEDs (5 rows x 12 LEDs)
#define DATA_PIN 6               // Pin connected to the Data In of the first LED strip
#define BRIGHTNESS 100           // Brightness of the LEDs
#define ROWS 5                   // Number of rows in the matrix
#define COLUMNS 12               // Number of columns in the matrix
#define DELAY_TIME 100           // Delay between pattern updates

CRGB leds[NUM_LEDS];

// Zigzag mapping: Convert (x, y) coordinates to LED index
int XY(int x, int y) {
  if (y % 2 == 0) {
    return (y * COLUMNS) + x;  // Even rows: left to right
  } else {
    return (y * COLUMNS) + (COLUMNS - 1 - x);  // Odd rows: right to left
  }
}

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  colorWipe(CRGB::Red);     // Example pattern 1
  delay(500);
  rainbowCycle();           // Example pattern 2
  delay(500);
  chaseEffect(CRGB::Blue);  // Example pattern 3
  delay(500);
  theaterChase(CRGB::Green);// Example pattern 4
  delay(500);
  randomSparkle();          // Example pattern 5
  delay(500);
}

// Color Wipe Effect
void colorWipe(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
    delay(DELAY_TIME);
  }
  FastLED.clear();  // Clear after the effect completes
}

// Rainbow Cycle
void rainbowCycle() {
  for (int j = 0; j < 256; j++) {  // Cycle through all 256 colors
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV((i + j) & 255, 255, 255);
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Chase Effect
void chaseEffect(CRGB color) {
  for (int i = 0; i < COLUMNS; i++) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      leds[XY(i, y)] = color;  // Light up one column at a time
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Theater Chase Effect
void theaterChase(CRGB color) {
  for (int j = 0; j < 10; j++) {  // Run this effect 10 times
    for (int q = 0; q < 3; q++) { // Loop through each position in a 3-step sequence
      for (int i = 0; i < NUM_LEDS; i += 3) {
        leds[(i + q) % NUM_LEDS] = color;  // Light every third LED
      }
      FastLED.show();
      delay(DELAY_TIME);
      for (int i = 0; i < NUM_LEDS; i += 3) {
        leds[(i + q) % NUM_LEDS] = CRGB::Black; // Turn off every third LED
      }
    }
  }
}

// Random Sparkle Effect
void randomSparkle() {
  FastLED.clear();
  for (int i = 0; i < 50; i++) {  // Sparkle 50 times
    int ledIndex = random(NUM_LEDS);
    leds[ledIndex] = CRGB::White;  // Random LED turns white
    FastLED.show();
    delay(50);
    leds[ledIndex] = CRGB::Black;  // Turn it off
  }
}
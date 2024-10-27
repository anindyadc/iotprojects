#include <FastLED.h>

//	Expanding Circle: LEDs light up in a circular pattern that expands outward.
//	Rings: Concentric rings moving outward.
//	Wave Pattern: A ripple effect going across the matrix.
//	Sparkling Stars: Random sparkling lights to mimic a twinkling effect.

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
  expandingCircle(CRGB::Blue);
  delay(500);
  rings(CRGB::Green);
  delay(500);
  wavePattern(CRGB::Red);
  delay(500);
  sparklingStars();
  delay(500);
}

// Expanding Circle Effect
void expandingCircle(CRGB color) {
  int centerX = COLUMNS / 2;
  int centerY = ROWS / 2;

  for (int radius = 0; radius < 4; radius++) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLUMNS; x++) {
        int distance = abs(centerX - x) + abs(centerY - y);
        if (distance == radius) {
          leds[XY(x, y)] = color;
        }
      }
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Rings Effect
void rings(CRGB color) {
  for (int radius = 0; radius < 3; radius++) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLUMNS; x++) {
        int distance = (x + y) % 2 + radius;  // Alternate ring effect
        if (distance % 2 == 0) {
          leds[XY(x, y)] = color;
        }
      }
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Wave Pattern Effect
void wavePattern(CRGB color) {
  for (int phase = 0; phase < COLUMNS; phase++) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      int xPos = (y + phase) % COLUMNS;  // Offset by row to create wave
      leds[XY(xPos, y)] = color;
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Sparkling Stars Effect
void sparklingStars() {
  FastLED.clear();
  for (int i = 0; i < 20; i++) {  // Sparkle effect for 20 cycles
    int ledIndex = random(NUM_LEDS);
    leds[ledIndex] = CRGB::White;  // Random LED turns white
    FastLED.show();
    delay(50);
    leds[ledIndex] = CRGB::Black;  // Turn it off
  }
}
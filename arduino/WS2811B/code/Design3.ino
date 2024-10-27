#include <FastLED.h>

//  Meteor Rain: A “meteor” or “comet” effect that streaks across the matrix.
//. Firework Burst: A burst that spreads outwards, mimicking a firework.
//. Sparkle Pulse: Creates a pulsing “breathing” effect, where LEDs fade in and out with random sparkles.
//. Color Wave: A smooth wave of colors that moves across the matrix.
//. Scanner Effect: A bouncing bar of light moving back and forth across the matrix.

#define NUM_LEDS 60              // Total number of LEDs (5 rows x 12 LEDs)
#define DATA_PIN 6               // Pin connected to the Data In of the first LED strip
#define BRIGHTNESS 100           // Brightness of the LEDs
#define ROWS 5                   // Number of rows in the matrix
#define COLUMNS 12               // Number of columns in the matrix
#define DELAY_TIME 50            // Delay between pattern updates

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
  meteorRain(CRGB::Blue);
  delay(500);
  fireworkBurst(CRGB::Yellow);
  delay(500);
  sparklePulse(CRGB::Pink);
  delay(500);
  colorWave();
  delay(500);
  scannerEffect(CRGB::Green);
  delay(500);
}

// Meteor Rain Effect
void meteorRain(CRGB color) {
  for (int startPos = COLUMNS; startPos > -COLUMNS; startPos--) {
    FastLED.clear();
    for (int i = 0; i < 5; i++) {  // Length of the meteor tail
      int pos = startPos - i;
      for (int y = 0; y < ROWS; y++) {
        if (pos >= 0 && pos < COLUMNS) {
          leds[XY(pos, y)] = color;
          leds[XY(pos, y)].fadeToBlackBy(i * 40);  // Tail fade effect
        }
      }
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Firework Burst Effect
void fireworkBurst(CRGB color) {
  int centerX = COLUMNS / 2;
  int centerY = ROWS / 2;
  for (int radius = 0; radius < 5; radius++) {  // Expands outward
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLUMNS; x++) {
        int distance = abs(centerX - x) + abs(centerY - y);  // Simple distance calculation
        if (distance == radius) {
          leds[XY(x, y)] = color;
        }
      }
    }
    FastLED.show();
    delay(DELAY_TIME * 2);
  }
}

// Sparkle Pulse Effect
void sparklePulse(CRGB color) {
  for (int brightness = 0; brightness <= BRIGHTNESS; brightness += 10) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = color;
      leds[i].fadeLightBy(255 - brightness);  // Fade in
    }
    if (random(5) < 2) {  // Random sparkles
      leds[random(NUM_LEDS)] = CRGB::White;
    }
    FastLED.show();
    delay(30);
  }
  for (int brightness = BRIGHTNESS; brightness >= 0; brightness -= 10) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeLightBy(255 - brightness);  // Fade out
    }
    FastLED.show();
    delay(30);
  }
}

// Color Wave Effect
void colorWave() {
  uint8_t hue = 0;
  for (int phase = 0; phase < COLUMNS; phase++) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      int xPos = (y + phase) % COLUMNS;
      leds[XY(xPos, y)] = CHSV(hue + (y * 10), 255, 255);  // Gradient effect
    }
    hue += 8;  // Change hue for smooth color flow
    FastLED.show();
    delay(DELAY_TIME);
  }
}

// Scanner Effect
void scannerEffect(CRGB color) {
  for (int x = 0; x < COLUMNS; x++) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      leds[XY(x, y)] = color;
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
  for (int x = COLUMNS - 1; x >= 0; x--) {
    FastLED.clear();
    for (int y = 0; y < ROWS; y++) {
      leds[XY(x, y)] = color;
    }
    FastLED.show();
    delay(DELAY_TIME);
  }
}
#include <FastLED.h>

#define NUM_LEDS 60              // Total number of LEDs (5 rows x 12 LEDs)
#define DATA_PIN 6               // Pin connected to the Data In of the first LED strip
#define BRIGHTNESS 100           // Brightness of the LEDs
#define ROWS 5                   // Number of rows in the matrix
#define COLUMNS 12               // Number of columns in the matrix
#define DISPLAY_DELAY 1000       // Delay between each character display

CRGB leds[NUM_LEDS];

// Character definitions (5x5 pixel grid for each character)
byte alphabet[][5] = {
  {0b01110, 0b10001, 0b11111, 0b10001, 0b10001}, // A
  {0b11110, 0b10001, 0b11110, 0b10001, 0b11110}, // B
  {0b01110, 0b10001, 0b10000, 0b10001, 0b01110}, // C
  {0b11100, 0b10010, 0b10001, 0b10010, 0b11100}, // D
  {0b11111, 0b10000, 0b11110, 0b10000, 0b11111}, // E
  {0b11111, 0b10000, 0b11110, 0b10000, 0b10000}, // F
  {0b01111, 0b10000, 0b10111, 0b10001, 0b01111}, // G
  {0b10001, 0b10001, 0b11111, 0b10001, 0b10001}, // H
  {0b01110, 0b00100, 0b00100, 0b00100, 0b01110}, // I
  {0b00001, 0b00001, 0b00001, 0b10001, 0b01110}, // J
  {0b10001, 0b10010, 0b11100, 0b10010, 0b10001}, // K
  {0b10000, 0b10000, 0b10000, 0b10000, 0b11111}, // L
  {0b10001, 0b11011, 0b10101, 0b10001, 0b10001}, // M
  {0b10001, 0b11001, 0b10101, 0b10011, 0b10001}, // N
  {0b01110, 0b10001, 0b10001, 0b10001, 0b01110}, // O
  {0b11110, 0b10001, 0b11110, 0b10000, 0b10000}, // P
  {0b01110, 0b10001, 0b10101, 0b10010, 0b01101}, // Q
  {0b11110, 0b10001, 0b11110, 0b10010, 0b10001}, // R
  {0b01111, 0b10000, 0b01110, 0b00001, 0b11110}, // S
  {0b11111, 0b00100, 0b00100, 0b00100, 0b00100}, // T
  {0b10001, 0b10001, 0b10001, 0b10001, 0b01110}, // U
  {0b10001, 0b10001, 0b10001, 0b01010, 0b00100}, // V
  {0b10001, 0b10001, 0b10101, 0b10101, 0b01010}, // W
  {0b10001, 0b01010, 0b00100, 0b01010, 0b10001}, // X
  {0b10001, 0b01010, 0b00100, 0b00100, 0b00100}, // Y
  {0b11111, 0b00010, 0b00100, 0b01000, 0b11111}, // Z
};

// Numeric definitions (5x5 pixel grid for each digit 0-9)
byte numbers[][5] = {
  {0b01110, 0b10001, 0b10001, 0b10001, 0b01110}, // 0
  {0b00100, 0b01100, 0b00100, 0b00100, 0b01110}, // 1
  {0b01110, 0b00001, 0b01110, 0b10000, 0b11111}, // 2
  {0b11110, 0b00001, 0b00110, 0b00001, 0b11110}, // 3
  {0b10001, 0b10001, 0b11111, 0b00001, 0b00001}, // 4
  {0b11111, 0b10000, 0b11110, 0b00001, 0b11110}, // 5
  {0b01110, 0b10000, 0b11110, 0b10001, 0b01110}, // 6
  {0b11111, 0b00001, 0b00010, 0b00100, 0b01000}, // 7
  {0b01110, 0b10001, 0b01110, 0b10001, 0b01110}, // 8
  {0b01110, 0b10001, 0b01111, 0b00001, 0b01110}  // 9
};

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
  FastLED.clear(); // Ensure all LEDs are off initially
}

void displayCharacter(int charIndex, bool isLetter) {
  FastLED.clear();
  byte* charData = isLetter ? alphabet[charIndex] : numbers[charIndex];
  
  // Display the character at the starting position (0 offset)
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 5; col++) {
      int ledIndex = XY(col, row);
      if (ledIndex < NUM_LEDS && ledIndex >= 0) {
        // Corrected bit extraction for left-to-right orientation
        if (charData[row] & (1 << col)) {
          leds[ledIndex] = CRGB::Red;  // Turn on LED for character pixel
        } else {
          leds[ledIndex] = CRGB::Black;  // Turn off LED
        }
      }
    }
  }
  FastLED.show();
}

void loop() {
  // Loop through each letter in the alphabet array
  for (int i = 0; i < sizeof(alphabet) / sizeof(alphabet[0]); i++) {
    displayCharacter(i, true);  // Display letter
    delay(DISPLAY_DELAY);
  }

  // Loop through each number in the numbers array
  for (int j = 0; j < sizeof(numbers) / sizeof(numbers[0]); j++) {
    displayCharacter(j, false); // Display number
    delay(DISPLAY_DELAY);
  }
}
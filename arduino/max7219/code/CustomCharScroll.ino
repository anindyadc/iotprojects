#include <LedControl.h>

// Pin definitions
const int dataIn = 2;  // Data pin
const int clk = 3;     // Clock pin
const int cs = 4;      // Chip select pin
LedControl lc = LedControl(dataIn, clk, cs, 4); // Initialize 4 MAX7219 modules

// Character definitions
byte sequenceH[] = {
    0b00000000, // Row 0
    0b01000100, // Row 1
    0b01000100, // Row 2
    0b01000100, // Row 3
    0b01111100, // Row 4
    0b01000100, // Row 5
    0b01000100, // Row 6
    0b00000000  // Row 7
};

byte sequenceE[] = {
        0b01111100, // Row 0
        0b01000000, // Row 1
        0b01000000, // Row 2
        0b01111000, // Row 3
        0b01000000, // Row 4
        0b01000000, // Row 5
        0b01111100, // Row 6
        0b00000000  // Row 7
    };

byte sequenceL[] = {
        0b01000000, // Row 0
        0b01000000, // Row 1
        0b01000000, // Row 2
        0b01000000, // Row 3
        0b01000000, // Row 4
        0b01000000, // Row 5
        0b01111100, // Row 6
        0b00000000  // Row 7
    };

    byte sequenceO[] = {
        0b00111100, // Row 0
        0b01000010, // Row 1
        0b01000010, // Row 2
        0b01000010, // Row 3
        0b01000010, // Row 4
        0b01000010, // Row 5
        0b00111100, // Row 6
        0b00000000  // Row 7
    };

// Create an array of sequences for "HELLO"
byte* sequences[] = {sequenceH, sequenceE, sequenceL, sequenceL, sequenceO};

void setup() {
    for (int i = 0; i < 4; i++) {
        lc.shutdown(i, false); // Wake up each module
        lc.setIntensity(i, 8); // Set brightness level (0 is min, 15 is max)
        lc.clearDisplay(i);    // Clear each module
    }
}

void loop() {
    const int totalChars = 5; // "HELLO"
    const int scrollLength = 4; // Number of characters that can fit on display

    // Scrolling effect
    for (int position = 0; position < totalChars + scrollLength; position++) {
        for (int row = 0; row < 8; row++) {
            byte displayValue[4] = {0, 0, 0, 0}; // Clear for each row

            // Determine which characters to display
            for (int ch = 0; ch < scrollLength; ch++) {
                int charIndex = position - ch;
                if (charIndex >= 0 && charIndex < totalChars) {
                    // Merge character data into display value for each module
                    displayValue[ch] = sequences[charIndex][row];
                }
            }

            // Set the rows for each module
            for (int mod = 0; mod < 4; mod++) {
                lc.setRow(mod, row, displayValue[mod]);
            }
        }
        delay(200); // Adjust speed of scrolling
    }

    // Clear the display after scrolling
    for (int i = 0; i < 4; i++) {
        lc.clearDisplay(i); // Clear each module
    }
    delay(1000); // Wait before restarting the loop
}


#include <LedControl.h>

// Pin definitions
const int dataIn = 2;  // Data pin
const int clk = 3;     // Clock pin
const int cs = 4;      // Chip select pin
LedControl lc = LedControl(dataIn, clk, cs, 4); // Initialize 4 MAX7219 modules

void setup() {
    for (int i = 0; i < 4; i++) {
        lc.shutdown(i, false); // Wake up each module
        lc.setIntensity(i, 8); // Set brightness level (0 is min, 15 is max)
        lc.clearDisplay(i);    // Clear each module
    }
}

void loop() {
    // Define the byte sequences for each character
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

    // Display "HELLO" on all 4 modules
    for (int ch = 0; ch < 5; ch++) { // For each character
        for (int i = 0; i < 8; i++) { // For each row
            for (int j = 0; j < 4; j++) { // For each module
                lc.setRow(j, i, sequences[ch][i]); // Set the same character on all modules
            }
        }
        delay(1000); // Show each character for 1 second
    }

    // Clear the display after showing the message
    for (int i = 0; i < 4; i++) {
        lc.clearDisplay(i); // Clear each module
    }
    delay(5); // Wait before repeating
}

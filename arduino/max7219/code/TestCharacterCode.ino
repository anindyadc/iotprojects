#include <LedControl.h>

// Pin configuration
const int DATA_IN = 2;  // DIN pin
const int CLK = 3;      // CLK pin
const int CS = 4;       // CS pin

// Number of devices (4 matrices)
const int NUM_DEVICES = 4;

// Create LedControl instance
LedControl lc = LedControl(DATA_IN, CLK, CS, NUM_DEVICES);

void setup() {
    // Initialize each device
    for (int i = 0; i < NUM_DEVICES; i++) {
        lc.shutdown(i, false);       // Wake up the MAX7219
        lc.setIntensity(i, 8);       // Set brightness level
        lc.clearDisplay(i);          // Clear display register
    }
}

void loop() {
    // Test each character manually
    displayCharacter(0); // A
    delay(1000);         // Wait 1 second
    displayCharacter(1); // B
    delay(1000);         // Wait 1 second
    displayCharacter(2); // C
    delay(1000);         // Wait 1 second
    displayCharacter(3); // D
    delay(1000);         // Wait 1 second
}

void displayCharacter(int index) {
    lc.clearDisplay(0); // Clear the first device
    
    // Character patterns for A, B, C, D
    const uint8_t characters[4][8] = {
        {0b00000000, 0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01111100, 0b00000000, 0b00000000}, // A
        {0b00000000, 0b01111110, 0b10000010, 0b10000010, 0b10000010, 0b01111110, 0b00000000, 0b00000000}, // B
        {0b00000000, 0b00111100, 0b01000010, 0b01000010, 0b01000010, 0b00111100, 0b00000000, 0b00000000}, // C
        {0b00000000, 0b01111110, 0b01000010, 0b01000010, 0b01000010, 0b00111100, 0b00000000, 0b00000000}  // D
    };

    // Set each row for the selected character
    for (int row = 0; row < 8; row++) {
        lc.setRow(0, row, characters[index][row]); // Display on first matrix
    }
}

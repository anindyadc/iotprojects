#include <LedControl.h>

// Pin configuration
const int DATA_IN = 11;  // DIN pin
const int CLK = 13;      // CLK pin
const int CS = 10;       // CS pin

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
    // Test each matrix one by one
    for (int device = 0; device < NUM_DEVICES; device++) {
        lc.clearDisplay(device); // Clear the current matrix

        // Turn on each LED one by one
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                lc.setLed(device, row, col, true); // Turn on LED
                delay(100); // Wait to see the LED
                lc.setLed(device, row, col, false); // Turn off LED
            }
        }

        // After testing, turn on all LEDs for a final check
        lc.clearDisplay(device); // Clear before full display
        for (int row = 0; row < 8; row++) {
            lc.setRow(device, row, 0xFF); // Set all LEDs on
        }
        delay(1000); // Show all LEDs for 1 second
        lc.clearDisplay(device); // Clear the matrix
    }

    // Pause before repeating
    delay(2000); // Wait 2 seconds before next round
}

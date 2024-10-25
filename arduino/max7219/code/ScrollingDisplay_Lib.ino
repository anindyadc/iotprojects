#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the connections for the FC16 module
#define DATA_PIN    11
#define CS_PIN      10
#define CLK_PIN     13

// Create a Parola object with appropriate parameters for the display
MD_Parola myDisplay = MD_Parola(MD_MAX72XX::FC16_HW, DATA_PIN, CLK_PIN, CS_PIN, 4);

const char* messages[] = {"Hello World", "Arduino Rocks", "Scrolling Text"};
int currentMessageIndex = 0;

void setup() {
myDisplay.begin();
myDisplay.setIntensity(0); // Set brightness (0 is min, 15 is max)
myDisplay.displayText(messages[currentMessageIndex], PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
if (myDisplay.displayAnimate()) {
currentMessageIndex = (currentMessageIndex + 1) % (sizeof(messages) / sizeof(messages[0]));
myDisplay.displayText(messages[currentMessageIndex], PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}
}
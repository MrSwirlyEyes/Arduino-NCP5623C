/**
 * NCP5623C example: RGB Toggle
 * 
 * Toggles the NCP5623C LEDs to cycle between RED, GREEN, and BLUE.
 */

#include <NCP5623C.h>

#define PIN_RED 2
#define PIN_GREEN 0
#define PIN_BLUE 1

#define MAX_CURRENT 10

#define DELAY 500

NCP5623C led = NCP5623C(PIN_RED,PIN_GREEN,PIN_BLUE);

void setup() {
  led.initialize();

  led.setCurrent(MAX_CURRENT);
}

void loop() {
  led.setColor(255,0,0); // Set MAX intensity RED
  delay(DELAY);

  led.setColor(0,255,0); // Set MAX intensity GREEN
  delay(DELAY);

  led.setColor(0,0,255); // Set MAX intensity BLUE
  delay(DELAY);
}

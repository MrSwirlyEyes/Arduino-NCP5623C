/**
 * NCP5623C example: RGB Sweep
 * 
 * Sweeps the NCP5623C LEDs to cycle between RED, GREEN, and BLUE using the gradual dim feature.
 * 
 * TODO: Add feature to time when gradual dim step will end
 */

#include <NCP5623C.h>

#define PIN_RED 2
#define PIN_GREEN 0
#define PIN_BLUE 1

#define DELAY 7465

NCP5623C led = NCP5623C(PIN_RED,PIN_GREEN,PIN_BLUE);

void setup() {
  led.initialize();
}

void loop() {
  static uint8_t color = 0;

  switch(color % 3) {
    case(0): // RED
      led.setColor(255,0,0);
    break;
    case(1): // GREEN
      led.setColor(0,255,0);
    break;
    case(2): // BLUE
      led.setColor(0,0,255);
    break;
  }

  led.gradualSweep(255,255,RAMP_UPWARD); // Ramp UP

  delay(DELAY);

  led.gradualSweep(0,255,RAMP_DOWNWARD); // Ramp DOWN

  delay(DELAY);

  color++;
}

#include <Arduino.h>
#include <Wire.h>
#include "NCP5623C.h"

NCP5623C::NCP5623C(uint8_t pinRed = DEFAULT_PIN_RED, uint8_t pinGreen = DEFAULT_PIN_GREEN, uint8_t pinBlue = DEFAULT_PIN_BLUE) {
  _address = NCP5623C_ADDRESS;

  _pinRed = pinRed;
  _pinGreen = pinGreen;
  _pinBlue = pinBlue;
}

void NCP5623C::initialize() {
  Wire.begin();

  off();
}

void NCP5623C::setCurrent(uint8_t magnitudeCurrent) {
  writeRegister(NCP5623C_REGISTER_SET_MAX_LED_CURRENT, (magnitudeCurrent > NCP5623C_MAX_VALUE ? NCP5623C_MAX_VALUE : magnitudeCurrent) & 0x1F);
}

void NCP5623C::setColor(uint8_t magnitudeRed, uint8_t magnitudeGreen, uint8_t magnitudeBlue) {
  setLED(_pinRed,magnitudeRed);
  setLED(_pinGreen,magnitudeGreen);
  setLED(_pinBlue,magnitudeBlue);
}

// 7465 max delay for 30 steps
void NCP5623C::gradualSweep(uint8_t intensity, uint8_t stepDelay, bool direction) {
  stepDelay = (stepDelay > (NCP5623C_MAX_VALUE - 1) ? (NCP5623C_MAX_VALUE - 1) : stepDelay) & 0x1F;

  // _steps = abs(((intensity > NCP5623C_MAX_VALUE ? NCP5623C_MAX_VALUE : intensity) & 0x1F) - _steps);

  // Serial.println(_steps);

  // Serial.println(
  //   (
  //     (
  //       (((stepDelay & 0x10) > 0) * 128) +
  //       (((stepDelay & 0x8) > 0) * 64) +
  //       (((stepDelay & 0x4) > 0) * 32) +
  //       (((stepDelay & 0x2) > 0) * 16) +
  //       (((stepDelay & 0x1) > 0) * 8)
  //     ) * _steps
  //   ) + 25
  // );

  writeRegister(direction ? NCP5623C_REGISTER_TARGET_UPWARD_IEND : NCP5623C_REGISTER_TARGET_DOWNWARD_IEND, (intensity >> 3));

  writeRegister(NCP5623C_REGISTER_GRADUAL_DIMMING_STEP_TIME, stepDelay);
}

void NCP5623C::off() {
  setCurrent(0);
}

void NCP5623C::setLED(uint8_t pin, uint8_t intensity) {
  writeRegister(NCP5623C_REGISTER_LED1 + pin, (intensity >> 3));
}

void NCP5623C::writeRegister(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(_address);
  Wire.write((reg << 5) | (val & NCP5623C_MAX_VALUE));
  Wire.endTransmission();
}

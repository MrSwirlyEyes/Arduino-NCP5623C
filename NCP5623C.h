#ifndef NCP5623C_H
#define NCP5623C_H

/**
 * NCP5623C datasheet: https://www.onsemi.com/pdf/datasheet/ncp5623c-d.pdf
 */

#define NCP5623C_ADDRESS 0x39

#define DEFAULT_PIN_RED 0
#define DEFAULT_PIN_GREEN 1
#define DEFAULT_PIN_BLUE 2

#define NCP5623C_REGISTER_CHIP_SHUTDOWN 0x0
#define NCP5623C_REGISTER_SET_MAX_LED_CURRENT 0x1
#define NCP5623C_REGISTER_LED1 0x2
#define NCP5623C_REGISTER_LED2 0x3
#define NCP5623C_REGISTER_LED3 0x4
#define NCP5623C_REGISTER_TARGET_UPWARD_IEND 0x5
#define NCP5623C_REGISTER_TARGET_DOWNWARD_IEND 0x6
#define NCP5623C_REGISTER_GRADUAL_DIMMING_STEP_TIME 0x7

#define NCP5623C_MAX_VALUE 0x1F

#define RAMP_UPWARD 1
#define RAMP_DOWNWARD 0

class NCP5623C {
  public:
    /**
     * Constructor
     * 
     * @param pin_nSleep - pin number corresponding to NCP5623C's nSleep input
     * @param pin_in1 - pin number corresponding to NCP5623C's IN1 input
     * @param pin_in2 - pin number corresponding to NCP5623C's IN2 input
     * @param invertDirection - reverses pin_in1 and pin_in2 assignment to adjust forward/reverse direction
     */
    NCP5623C(uint8_t pinRed = DEFAULT_PIN_RED, uint8_t pinGreen = DEFAULT_PIN_GREEN, uint8_t pinBlue = DEFAULT_PIN_BLUE);

    /**
     * Initializes NCP5623C
     */
    void initialize();

    /**
     * Sets the NCP5623C driver to drive in a given direction at a specified magnitude
     * 
     * @param magnitude - magnitude of driving speed
     * @param direction - direction of driving
     */
    void setCurrent(uint8_t magnitudeCurrent);

    /**
     * Sets the NCP5623C driver to drive in a given direction at a specified magnitude
     * 
     * @param magnitude - magnitude of driving speed
     * @param direction - direction of driving
     */
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    void gradualSweep(uint8_t intensity, uint8_t stepDelay, bool direction);

    /**
     * Sets the NCP5623C driver to drive in a given direction at a specified magnitude
     * 
     * @param magnitude - magnitude of driving speed
     * @param direction - direction of driving
     */
    void off();

  private:
    /**
     * NCP5623C I2C address
     */
    uint8_t _address;

    /**
     * NCP5623C red pin number
     */
    uint8_t _pinRed;

    /**
     * NCP5623C green pin number
     */
    uint8_t _pinGreen;

    /**
     * NCP5623C blue pin number
     */
    uint8_t _pinBlue;

    // uint8_t _steps = 0;

    /**
     * Set NCP5623C's given LED pin brightness intensity
     * 
     * @param pin - pin to set intensity to
     * @param intensity - brightness intensity
     */
    void setLED(uint8_t pin, uint8_t intensity);

    /**
     * Write to NCP5623C's register
     * 
     * @param reg - register to write to
     * @param value - value to write
     */
    void writeRegister(uint8_t reg, uint8_t value);
};

#endif

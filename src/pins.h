#ifndef PINS_H
#define PINS_H

const byte pin_led_green = 41;
const byte pin_led_blue = 40;

const byte pin_button_black = 38;
const byte pin_button_joystick = 39;

const byte pin_x_joystick = PIN_A13;
const byte pin_y_joystick = PIN_A12;

// These are the four touchscreen analog pins
// Y+ X+ Y- X- these are the 4 resistive touch screen pads, which can be read with analog pins to determine touch points. They are completely separated from the TFT electrically (the overlay is glued on top)

#define XP 43  // can be a digital pin
#define XM A14 // must be an analog pin, use "An" notation!
#define YP A15 // must be an analog pin, use "An" notation!
#define YM 42  // can be a digital pin

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.

// this is the TFT SPI data or command selector pin
#define TFT_DC 48

// this is the TFT SPI chip select pin
#define TFT_CS 49

// this is the SD card chip select, used if you want to read from the SD card.
#define SD_CCS 47

// this is the SD card detect pin, it floats when a card is inserted, and tied to ground when the card is not inserted. We don't use this in our code but you can use this as a switch to detect if an SD card is in place without trying to electrically query it. Don't forget to use a pullup on this pin if so!
#define SD_CD 46

// this is the PWM input for the backlight control. It is by default pulled high (backlight on) you can PWM at any frequency or pull down to turn the backlight off
#define TFT_LITE 44

// this is the TFT reset pin. There's auto-reset circuitry on the breakout so this pin is not required but it can be helpful sometimes to reset the TFT if your setup is not always resetting cleanly. Connect to ground to reset the
#define TFT_RST 45

#endif // PINS_H

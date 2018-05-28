#ifndef PINS_H
#define PINS_H

// LEDs
const byte pin_led_green = 41;
const byte pin_led_blue = 40;

// Joystick
const byte pin_button_joystick = 39;
const byte pin_x_joystick = PIN_A13;
const byte pin_y_joystick = PIN_A12;

// Stand alone button
const byte pin_button_black = 38;

// TFT SPI data or command selector pin
const byte pin_tft_dc = 48;

// TFT SPI chip select pin
const byte pin_tft_cs = 49;

// PWM input for the backlight control. It is by default pulled high (backlight on)
// you can PWM at any frequency or pull down to turn the backlight off
const byte pin_tft_lite = 44;

// TFT reset pin. There's auto-reset circuitry on the breakout so this pin is not
// required but it can be helpful sometimes to reset the TFT if your setup is not
// always resetting cleanly. Connect to ground to the reset.
const byte pin_tft_rst = 45;

// SD card chip select, used if you want to read from the SD card.
const byte pin_sd_ccs = 47;

// SD card detect pin, it floats when a card is inserted, and tied to ground when the
// card is not inserted. We don't use this in our code but you can use this as a switch
// to detect if an SD card is in place without trying to electrically query it.
// Don't forget to use a pullup on this pin if so!
const byte pin_sd_cd = 46;

// These are the four touchscreen analog pins
// Y+ X+ Y- X- these are the 4 resistive touch screen pads,
// which can be read with analog pins to determine touch points.
// They are completely separated from the TFT electrically (the overlay is glued on top)
const byte pin_tft_xp = 43;      // can be a digital pin
const byte pin_tft_xm = PIN_A14; // must be an analog pin, use "An" notation!
const byte pin_tft_yp = PIN_A15; // must be an analog pin, use "An" notation!
const byte pin_tft_ym = 42;      // can be a digital pin

#endif // PINS_H

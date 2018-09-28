#ifndef PINS_H
#define PINS_H

// LEDs
const byte pin_led_green = 32;
const byte pin_led_blue = 33;

// Stand alone button
const byte pin_button_black = 34;

// Joystick
const byte pin_button_joystick = 35;
const byte pin_x_joystick = PIN_A1;
const byte pin_y_joystick = PIN_A0;

// TFT data pins
// D0..D7 hardwired to pins 22..29 on Arduino Mega (on the 2-row header at the end of the board)
// It is possible to change only by modifying bit masks in the TFT library

// TFT control pins
// The control pins for the LCD can be assigned to any digital or
// analog pins... but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).

// TFT chip select pin
const byte pin_tft_cs = PIN_A8;

// TFT data or command selector pin
const byte pin_tft_dc = PIN_A9;

// TFT write
const byte pin_tft_wr = PIN_A10;

// TFT read
const byte pin_tft_rd = PIN_A11;

// TFT reset pin. There's auto-reset circuitry on the breakout so this pin is not
// required but it can be helpful sometimes to reset the TFT if your setup is not
// always resetting cleanly. Connect to ground to the reset.
const byte pin_tft_rst = 30;

// PWM input for the backlight control. It is by default pulled high (backlight on)
// you can PWM at any frequency or pull down to turn the backlight off
const byte pin_tft_lite = 31;

// These are the four touchscreen analog pins
// Y+ X+ Y- X- these are the 4 resistive touch screen pads,
// which can be read with analog pins to determine touch points.
// They are completely separated from the TFT electrically (the overlay is glued on top)
const byte pin_tft_xp = PIN_A8;  // can be a digital pin
const byte pin_tft_yp = PIN_A9;  // must be an analog pin, use "An" notation!
const byte pin_tft_xm = PIN_A10; // must be an analog pin, use "An" notation!
const byte pin_tft_ym = PIN_A11; // can be a digital pin

// SD card chip select, used if you want to read from the SD card.
// All other pins are connected via hardware SPI pin layout
const byte pin_sd_do = 50; // miso
const byte pin_sd_di = 51; // mosi
const byte pin_sd_clk = 52;
const byte pin_sd_ccs = 53;

#endif // PINS_H

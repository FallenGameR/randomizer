#ifndef PINS_H
#define PINS_H

#include <LiquidCrystal.h>

// Pins used
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const byte pin_led_green = 4;
const byte pin_led_blue = 5;
const byte pin_button_black = 6;
const byte pin_button_joystick = 13;
const byte pin_x_joystick = 1;
const byte pin_y_joystick = 0;

#endif // PINS_H

#ifndef PINS_H
#define PINS_H

#include <LiquidCrystal.h>

// Pins used
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const int pin_led_green = 4;
const int pin_led_blue = 5;
const int pin_button_black = 6;
const int pin_button_joystick = 13;
const int pin_x_joystick = 0;
const int pin_y_joystick = 1;

#endif // PINS_H

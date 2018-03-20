#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "pins.h"

/*

enum Input
{
    button_black,
    button_joystick,
    x_left,
    x_right,
    x_center,
    y_up,
    y_down,
    y_center,
};

input_current
input_started
input_ready
*/

bool button_black_pressed = false;
bool button_joystick_pressed = false;
bool x_left = false;
bool x_right = false;
bool x_center = false;
bool y_up = false;
bool y_down = false;
bool y_center = false;
bool input_allowed = false;

void readInput()
{
    button_black_pressed = !digitalRead(pin_button_black);
    button_joystick_pressed = !digitalRead(pin_button_joystick);

    int x = analogRead(pin_x_joystick);
    int y = analogRead(pin_y_joystick);

    x_left = x < 400;
    x_right = x > 600;
    x_center = !x_left && !x_right;
    y_up = y > 600;
    y_down = y < 400;
    y_center = !y_up && !y_down;

    if (x_center && y_center && !button_black_pressed && !button_joystick_pressed)
    {
        // needs to be in this state for at least 100ms
        // otherwise we may have accidental triggering
        input_allowed = true;
    }
}

#endif // INPUT_H

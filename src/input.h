#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "pins.h"

enum Input
{
    button_black,
    button_joystick,
    xx_left,
    xx_right,
    xx_center,
    yy_up,
    yy_down,
    yy_center,
    size
};

bool input_current[Input::size];
unsigned long input_started[Input::size];
bool input_ready[Input::size];

unsigned long now;
bool input_allowed = false;

void processInput(int input)
{
}

#define button_black_pressed input_ready[Input::button_black]
#define button_joystick_pressed input_ready[Input::button_joystick]
#define x_left input_ready[Input::xx_left]
#define x_right input_ready[Input::xx_right]
#define x_center input_ready[Input::xx_center]
#define y_up input_ready[Input::yy_up]
#define y_down input_ready[Input::yy_down]
#define y_center input_ready[Input::yy_center]

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

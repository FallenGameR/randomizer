#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "pins.h"

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
    size,
};

bool input_current[Input::size];
unsigned long input_started[Input::size];
bool input_ready[Input::size];
bool input_allowed = false;
unsigned long now;

void processInput(int input)
{
}

void readInput()
{
    now = millis();

    input_ready[Input::button_black] = !digitalRead(pin_button_black);
    input_ready[Input::button_joystick] = !digitalRead(pin_button_joystick);

    int x = analogRead(pin_x_joystick);
    int y = analogRead(pin_y_joystick);

    input_ready[Input::x_left] = x < 400;
    input_ready[Input::x_right] = x > 600;
    input_ready[Input::x_center] = !input_ready[Input::x_left] && !input_ready[Input::x_right];
    input_ready[Input::y_up] = y > 600;
    input_ready[Input::y_down] = y < 400;
    input_ready[Input::y_center] = !input_ready[Input::y_up] && !input_ready[Input::y_down];

    if (input_ready[Input::x_center] && input_ready[Input::y_center] && !input_ready[Input::button_black] && !input_ready[Input::button_joystick])
    {
        // needs to be in this state for at least 100ms
        // otherwise we may have accidental triggering
        input_allowed = true;
    }
}

#endif // INPUT_H

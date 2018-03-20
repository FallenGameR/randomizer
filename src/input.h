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

#define BUTTON_BLACK input_ready[Input::button_black]
#define BUTTON_JOYSTICK input_ready[Input::button_joystick]
#define X_LEFT input_ready[Input::x_left]
#define X_RIGHT input_ready[Input::x_right]
#define X_CENTER input_ready[Input::x_center]
#define Y_UP input_ready[Input::y_up]
#define Y_DOWN input_ready[Input::y_down]
#define Y_CENTER input_ready[Input::y_center]

void readInput()
{
    BUTTON_BLACK = !digitalRead(pin_button_black);
    BUTTON_JOYSTICK = !digitalRead(pin_button_joystick);

    int x = analogRead(pin_x_joystick);
    int y = analogRead(pin_y_joystick);

    X_LEFT = x < 400;
    X_RIGHT = x > 600;
    X_CENTER = !X_LEFT && !X_RIGHT;
    Y_UP = y > 600;
    Y_DOWN = y < 400;
    Y_CENTER = !Y_UP && !Y_DOWN;

    if (X_CENTER && Y_CENTER && !BUTTON_BLACK && !BUTTON_JOYSTICK)
    {
        // needs to be in this state for at least 100ms
        // otherwise we may have accidental triggering
        input_allowed = true;
    }
}

#endif // INPUT_H

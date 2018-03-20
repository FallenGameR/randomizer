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
const unsigned long input_threshold_ms = 300;

void processInput(int key, bool value)
{
    // Cancellation
    if (!value)
    {
        input_current[key] = false;
        input_started[key] = 0;
        input_ready[key] = false;
        return;
    }

    // Processing
    if (!input_current[key])
    {
        // Start
        input_current[key] = true;
        input_started[key] = now;
        input_ready[key] = false;
    }
    else
    {
        // Continue
        input_ready[key] = now - input_started[key] >= input_threshold_ms;
    }
}

#define BUTTON_BLACK (input_ready[Input::button_black])
#define BUTTON_JOYSTICK (input_ready[Input::button_joystick])
#define X_LEFT (input_ready[Input::x_left])
#define X_RIGHT (input_ready[Input::x_right])
#define X_CENTER (input_ready[Input::x_center])
#define Y_UP (input_ready[Input::y_up])
#define Y_DOWN (input_ready[Input::y_down])
#define Y_CENTER (input_ready[Input::y_center])

void readInput()
{
    now = millis();
    int x = analogRead(pin_x_joystick);
    int y = analogRead(pin_y_joystick);

    processInput(Input::button_black, !digitalRead(pin_button_black));
    processInput(Input::button_joystick, !digitalRead(pin_button_joystick));
    processInput(Input::x_left, x < 400);
    processInput(Input::x_right, x > 600);
    processInput(Input::x_center, x >= 400 && x <= 600);
    processInput(Input::y_up, y > 600);
    processInput(Input::y_down, y < 400);
    processInput(Input::y_center, y >= 400 && y <= 600);

    if (X_CENTER && Y_CENTER && !BUTTON_BLACK && !BUTTON_JOYSTICK)
    {
        // needs to be in this state for at least 100ms
        // otherwise we may have accidental triggering
        input_allowed = true;
    }
}

#endif // INPUT_H

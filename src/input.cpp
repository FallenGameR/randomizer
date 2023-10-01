#include "input.h"

#include <Arduino.h>
#include "shared.h"
#include "pins.h"

const unsigned long input_threshold_ms = 100;
bool input_current[Input::size];
unsigned long input_started[Input::size];
bool input_ready[Input::size];
unsigned long now;

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
    processInput(Input::y_up, y < 400);
    processInput(Input::y_down, y > 600);
    processInput(Input::y_center, y >= 400 && y <= 600);

    if (X_CENTER && Y_CENTER && !BUTTON_BLACK && !BUTTON_JOYSTICK)
    {
        // needs to be in this state for at least 100ms
        // otherwise we may have accidental triggering due to electric noise and accidental wire movements
        // thus all input is done via processInput that measures input persistence against time threshold
        input_allowed = true;
    }
}

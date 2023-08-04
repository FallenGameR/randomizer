#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "shared.h"
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

#define BUTTON_BLACK (input_ready[Input::button_black])
#define BUTTON_JOYSTICK (input_ready[Input::button_joystick])
#define X_LEFT (input_ready[Input::x_left])
#define X_RIGHT (input_ready[Input::x_right])
#define X_CENTER (input_ready[Input::x_center])
#define Y_UP (input_ready[Input::y_up])
#define Y_DOWN (input_ready[Input::y_down])
#define Y_CENTER (input_ready[Input::y_center])

const unsigned long input_threshold_ms = 100;

extern bool input_current[Input::size];
extern unsigned long input_started[Input::size];
extern bool input_ready[Input::size];
extern unsigned long now;

void processInput(int key, bool value);

void readInput();

#endif // INPUT_H

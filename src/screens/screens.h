#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>

enum Screen
{
    RandomizerInit = 0,
    GameSelection = 1,
    PlayerSelection = 2,
    FighterSelection = 3,
};

byte screen_selected = Screen::RandomizerInit;
bool screen_redraw = true;

#endif // SCREENS_H
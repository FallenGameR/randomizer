#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>

enum Screen
{
    RandomizerInit = 0,
    GameIconSelection,
    GameSelection,
    PlayerSelection,
    FighterSelection,
};

byte screen_selected = Screen::RandomizerInit;
bool screen_redraw = true;

#endif // SCREENS_H
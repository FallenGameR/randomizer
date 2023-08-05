#ifndef SCREENS_H
#define SCREENS_H

enum Screen
{
    RandomizerInit = 0,
    GameIconSelection,
    GameSelection,
    PlayerSelection,
    FighterSelection,
    TotalsShow,
    Tester,
};

// Entry function of the init screen
void RandomizerInitScreen();

#endif // SCREENS_H
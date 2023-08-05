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

// Entry function of the game screen
void GameIconSelectionScreen();

// Entry function of the fighter screen
void FighterSelectionScreen();

#endif // SCREENS_H
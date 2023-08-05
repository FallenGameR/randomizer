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

// Entry function of the totals screen
void TotalShowScreen();

#endif // SCREENS_H
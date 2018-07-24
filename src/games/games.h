#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"
#include "guilty_gear_xrd_rev2.h"
#include "king_of_fighters_14.h"
#include "killer_instinct.h"
#include "mortal_kombat_xl.h"
#include "street_fighter_5.h"
#include "..\fighters.h"
#include "..\files.h"

// Game variables
byte game_index = 0;
byte game_tag = 0;
byte n_games = 0;
bool isTagGame = false;

// Screen is 480px and min font is 6 pixels wide (by default we actually use font that is twise as big)
// For safety there should also be logic for making sure we don't reach the end of buffer
// But we can add it later on, for now we just have large buffer
char bufferLine[480 / 6];

// Constant string for comma
const char str_comma[] PROGMEM = ", ";

void FightersToBufferLine(byte a, byte b, byte c)
{
    setFighterName(game_index, a);
    strcpy(bufferLine, bufferName);

    if (b != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        setFighterName(game_index, b);
        strcat(bufferLine, bufferName);
    }

    if (c != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        setFighterName(game_index, c);
        strcat(bufferLine, bufferName);
    }
}

// Select current game
void SelectGame(byte gameIndex)
{
    n_fighters = readNumberOfFighters(gameIndex);
    game_tag = readGameTag(gameIndex);

    if (game_tag == 0)
    {
        isTagGame = false;
    }
}

#endif // GAMES_H
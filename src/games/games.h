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
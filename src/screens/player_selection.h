#ifndef PLAYER_SELECTION_H
#define PLAYER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\players.h"

void PlayerSelectionScreen()
{
    player_index_first = 0;
    player_index_second = 1;

    if (n_players > 2)
    {
        Serial.print(players[player_index_first]);
        Serial.print(F(" and "));
        Serial.println(players[player_index_second]);
    }

    screen_selected = Screen::FighterSelection;
}

#endif // PLAYER_SELECTION_H
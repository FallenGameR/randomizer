#ifndef PLAYER_SELECTION_H
#define PLAYER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\players.h"
#include "..\memory.h"

void PlayerSelectionScreen()
{
    player_index_first = 0;
    player_index_second = 1;

    if (n_players > 2)
    {
        SERIAL_PRINT(players, player_index_first);
        Serial.print(F(" and "));
        SERIAL_PRINT(players, player_index_second);
        Serial.println();
    }

    screen_selected = Screen::FighterSelection;
}

#endif // PLAYER_SELECTION_H
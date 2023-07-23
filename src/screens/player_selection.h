#ifndef PLAYER_SELECTION_H
#define PLAYER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\players.h"
#include "..\print.h"

void PlayerSelectionScreen()
{
    // Reshuffle if we reached end of list
    byte pair_index = n_match % n_fairness;
    if (pair_index == 0)
    {
        ShufflePlayerPairs();
    }

    player_index_first = player_pairs[pair_index * 2 + 0];
    player_index_second = player_pairs[pair_index * 2 + 1];

    PRINT_BS(setPlayerName(player_index_first));
    PRINT(F(" and "), Serial);
    PRINT_BS(setPlayerName(player_index_second));
    Serial.println();

    screen_selected = Screen::FighterSelection;
}

#endif // PLAYER_SELECTION_H
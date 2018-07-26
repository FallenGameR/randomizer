#ifndef PLAYER_SELECTION_H
#define PLAYER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\players.h"
#include "..\print.h"

void PlayerSelectionScreen()
{
    // By default for two players choose always firs pair
    byte pair_index = 0;

    // If there are more players use the shuffled player pairs
    if (n_players > 2)
    {
        pair_index = match_current % random_fairness;

        // Shuffle all the pairs at the start and
        // each time the whole list is traversed
        if (pair_index == 0)
        {
            ShufflePlayerPairs();
        }
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
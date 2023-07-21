#ifndef PLAYERS_H
#define PLAYERS_H

#include "colors.h"
#include "shared.h"

// There could be max 10 players we would not be able to fit more on the screen.
// Plus if number of players is > 16 the fairness value no longer fits into byte.
#define MAX_PLAYERS 10

#define MIN_FAIRNESS (n_players * (n_players - 1))

void PrintPairs()
{
    for (byte pair = 0; pair < random_fairness; pair++)
    {
        Serial.print(player_pairs[pair * 2 + 0]);
        Serial.print(" vs ");
        Serial.print(player_pairs[pair * 2 + 1]);
        Serial.println();
    }
}

// Shuffle the pairs in a random unbiased way
void ShufflePlayerPairs()
{
    byte swap;

    for (byte moved_pair = 0; moved_pair < random_fairness - 1; moved_pair++)
    {
        byte new_place = random(moved_pair + 1, random_fairness);

        swap = player_pairs[moved_pair * 2 + 0];
        player_pairs[moved_pair * 2 + 0] = player_pairs[new_place * 2 + 0];
        player_pairs[new_place * 2 + 0] = swap;

        swap = player_pairs[moved_pair * 2 + 1];
        player_pairs[moved_pair * 2 + 1] = player_pairs[new_place * 2 + 1];
        player_pairs[new_place * 2 + 1] = swap;
    }

    Serial.println("Reshuffled players");

#ifdef DEBUG
    PrintPairs();
#endif
}

void InitPlayerPairs()
{
    // This array would never be freed or resized
    player_pairs = (byte *)malloc(random_fairness * 2);

    // Populate the pairs
    byte index = 0;
    for (byte stage = 0; stage < random_fairness / MIN_FAIRNESS; stage++)
    {
        for (byte first = 0; first < n_players; first++)
        {
            for (byte second = 0; second < n_players; second++)
            {
                if (first == second)
                {
                    continue;
                }

                player_pairs[index++] = first;
                player_pairs[index++] = second;
            }
        }
    }
}

#endif // PLAYERS_H
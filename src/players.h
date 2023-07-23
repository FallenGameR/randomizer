#ifndef PLAYERS_H
#define PLAYERS_H

#include "colors.h"
#include "shared.h"

// We need at least 2 players to play =)
#define MIN_PLAYERS 2

// There could be max 10 players we would not be able to fit more on the screen.
// Plus if number of players is > 16 the fairness value no longer fits into byte.
#define MAX_PLAYERS 10

void PrintPairs()
{
    for (byte pair = 0; pair < n_fairness; pair++)
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

    for (byte moved_pair = 0; moved_pair < n_fairness - 1; moved_pair++)
    {
        byte new_place = random(moved_pair + 1, n_fairness);

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

// Players array is the list of players that were selected.
// Array value is the player index on the SD card.
void InitPlayerPairs()
{
    // On soft reset we need to cleanup after the first run
    if( player_pairs != 0 ) { free(player_pairs); }
    player_pairs = (byte *)malloc(n_players * 2);

    // Populate the pairs
    byte index = 0;
    byte n_stages = n_fairness / (n_players * (n_players - 1));
    for (byte stage = 0; stage < n_stages; stage++)
    {
        // Shuffle otherwise
        for (byte first = 0; first < n_players; first++)
        {
            for (byte second = 0; second < n_players; second++)
            {
                if (first == second)
                {
                    continue;
                }

                // If there are only 2 players we don't really need to shuffle
                Serial.print("Pair: ");
                player_pairs[index] = players[n_players <= 2 ? 0 : first];
                Serial.print(player_pairs[index]);
                index++;

                Serial.print(" vs ");
                player_pairs[index] = players[n_players <= 2 ? 1 : second];
                Serial.print(player_pairs[index]);
                index++;

                Serial.println();
            }
        }
    }
}

#endif // PLAYERS_H
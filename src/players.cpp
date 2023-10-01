#include "players.h"
#include "colors.h"
#include "shared.h"

void PrintPairs()
{
    for (byte pair = 0; pair < n_fairness; pair++)
    {
        Serial.print("Player pair: ");
        Serial.print(player_pairs[pair * 2 + 0]);
        Serial.print(" vs ");
        Serial.print(player_pairs[pair * 2 + 1]);
        Serial.println();
    }
}

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
                player_pairs[index++] = players[n_players <= 2 ? 0 : first];
                player_pairs[index++] = players[n_players <= 2 ? 1 : second];
            }
        }
    }
}
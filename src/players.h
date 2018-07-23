#ifndef PLAYERS_H
#define PLAYERS_H

// There could be max 16 players, otherwise fairness gets too big and don't fit into byte
byte n_players = 0;

byte *player_pairs = 0;
byte match_current = 0;

byte player_index_first = -1;
byte player_index_second = -1;

// These have to be declared here to ensure there is no cyclic dependency
byte random_fairness = 0;
byte random_fairness_divider = 0;
byte random_fairness_multiplier = 0;

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
    for (byte stage = 0; stage < random_fairness_multiplier; stage++)
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
#ifndef PLAYERS_H
#define PLAYERS_H

#include "colors.h"

// There could be max 10 players we would not be able to fit more on the screen.
// Plus if number of players is > 16 the fairness value no longer fits into byte.
#define MAX_PLAYERS 10

byte n_players = 0;

byte *player_pairs = 0;
byte match_current = 0;

byte player_index_first = -1;
byte player_index_second = -1;

// `Fairness` is how many games needs to be played out for everybody to play equal amount of times in all configurations.
// Minimal fairness value get a chance for everybody to play as soon as possible.
// But as it `fairness` value grows the pair distribution can become more and more strange but fair
// on the larger scale. It could be that some players would not change seats for several games in a row
// but after the `fairness` number of games all players will play equal amount of games regardless.
// `Fairness` makes sense only if there are >2 players.
byte random_fairness = 0;
byte random_fairness_increment = 0;

unsigned int playerColors[MAX_PLAYERS] = {
    CYAN,       // Player 0
    YELLOW,     // Player 1
    LT_PURPLE,  // Player 2
    BLUE,       // Player 3
    ORANGE,     // Player 4
    MAGENTA,    // Player 5
    DK_BLUE,    // Player 6
    DK_YELLOW,  // Player 7
    PURPLE,     // Player 8
    DK_CYAN,    // Player 9
};

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
    for (byte stage = 0; stage < random_fairness / random_fairness_increment; stage++)
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
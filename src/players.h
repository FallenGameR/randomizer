#ifndef PLAYERS_H
#define PLAYERS_H

// We need at least 2 players to play =)
#define MIN_PLAYERS 2

// There could be max 10 players we would not be able to fit more on the screen.
// Plus if number of players is > 16 the fairness value no longer fits into byte.
#define MAX_PLAYERS 10

// Shuffle the pairs in a random unbiased way
void ShufflePlayerPairs();

// Players array is the list of players that were selected.
// Array value is the player index on the SD card.
void InitPlayerPairs();

#endif // PLAYERS_H
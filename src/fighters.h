#ifndef FIGHTERS_H
#define FIGHTERS_H

#include <Arduino.h>

// Placeholder for empty fighter index
#define NO_FIGHTER 255

// Actually it is 54 as per scripts/Find-MaxFighters.ps1, but we'll round it up
#define MAX_FIGHTERS_IN_GAME 64

// For regular matches
extern byte fighter_index_first;
extern byte fighter_index_second;

// For tag matches
extern byte fighter_index_first2;
extern byte fighter_index_second2;
extern byte fighter_index_first3;
extern byte fighter_index_second3;

// Number of fighters in the current game
extern byte n_fighters;

// We randomize fighters in a way that every fighter is used at least once before repeating
// But at the same time it is ok for the same fighter to be present on both sides
// This logic maximizes the number of unique fighters in the game session while allowing for twin matches

// Randomized fighters for the left seat
extern byte fighters_left[];

// Randomized fighters for the right seat
extern byte fighters_right[];

// Current position in the fighters on the left seat array
extern size_t fighters_left_position;

// Current position in the fighters on the right seat array
extern size_t fighters_right_position;

#endif // FIGHTERS_H
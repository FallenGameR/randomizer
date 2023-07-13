#ifndef FIGHTERS_H
#define FIGHTERS_H

// Placeholder for empty fighter index
#define NO_FIGHTER 255

// Actually it is 54 as per scripts/Find-MaxFighters.ps1, but we'll round it up
#define MAX_FIGHTERS_IN_GAME 64

// For regular matches
byte fighter_index_first = NO_FIGHTER;
byte fighter_index_second = NO_FIGHTER;

// For tag matches
byte fighter_index_first2 = NO_FIGHTER;
byte fighter_index_second2 = NO_FIGHTER;
byte fighter_index_first3 = NO_FIGHTER;
byte fighter_index_second3 = NO_FIGHTER;

// Number of fighters in the current game
byte n_fighters = 0;

// We randomize fighters in a way that every fighter is used at least once before repeating
// But at the same time it is ok for the same fighter to be present on both sides
// This logic maximizes the number of unique fighters in the game session while allowing for twin matches

// Randomized fighters for the left seat
byte fighters_left[MAX_FIGHTERS_IN_GAME];

// Randomized fighters for the right seat
byte fighters_right[MAX_FIGHTERS_IN_GAME];

// Current position in the fighters on the left seat array
size_t fighters_left_position = 0;

// Current position in the fighters on the right seat array
size_t fighters_right_position = 0;

#endif // FIGHTERS_H
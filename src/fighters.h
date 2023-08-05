#ifndef FIGHTERS_H
#define FIGHTERS_H

#include <Arduino.h>

// Placeholder for empty fighter index
#define NO_FIGHTER 255

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

// Current position in the fighters on the left seat array
extern size_t fighters_left_position;

// Current position in the fighters on the right seat array
extern size_t fighters_right_position;

#endif // FIGHTERS_H
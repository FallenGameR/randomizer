#include "fighters.h"
#include <Arduino.h>

byte fighter_index_first = NO_FIGHTER;
byte fighter_index_second = NO_FIGHTER;
byte fighter_index_first2 = NO_FIGHTER;
byte fighter_index_second2 = NO_FIGHTER;
byte fighter_index_first3 = NO_FIGHTER;
byte fighter_index_second3 = NO_FIGHTER;
byte n_fighters = 0;
byte fighters_left[MAX_FIGHTERS_IN_GAME];
byte fighters_right[MAX_FIGHTERS_IN_GAME];
size_t fighters_left_position = 0;
size_t fighters_right_position = 0;

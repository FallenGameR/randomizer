#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"

// Using PROGMEM here to save some spavce for variables

const char games_Tekken7[] PROGMEM = "Tekken 7";
const char games_DeadOrAlive5[] PROGMEM = "Dead or Alive 5";

const char *const games[] PROGMEM = {
    games_Tekken7,
    games_DeadOrAlive5,
};

#define n_games (sizeof(games) / sizeof(const char *))

int games_index = 0;

const char *const *fighter_map[] = {
    tekken7,
    doa5,
};

const byte n_fighter_map[] = {
    n_tekken7,
    n_doa5,
};

const char *const *fighter_map_selected = tekken7;
byte n_fighter_map_selected = n_tekken7;

#endif // GAMES_H
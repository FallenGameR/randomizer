#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"

const char *games[] = {
    "Tekken 7",
    "Dead or Alive 5",
};

const char **fighter_map[] = {
    tekken7,
    doa5,
};

const int n_fighter_map[] = {
    n_tekken7,
    n_doa5,
};

#define n_games (sizeof(games) / sizeof(const char *))

#endif // GAMES_H
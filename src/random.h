#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include <Entropy.h>
#include "players.h"

#define RANDOM_EX1(max, current, except1) \
    do                                    \
    {                                     \
        current = random(max);            \
    } while (current == except1);

#define RANDOM_EX2(max, current, except1, except2) \
    do                                             \
    {                                              \
        current = random(max);                     \
    } while ((current == except1) || (current == except2));

// Entropy library actually returns uint32_t, but negative values have something to them when correcting the seed
int random_seed = 0;

void initRandom()
{
    Entropy.Initialize();

    random_seed = Entropy.random();
    randomSeed(random_seed);

    random_fairness_divider = n_players * (n_players - 1);
    random_fairness_multiplier = 1;
    random_fairness = random_fairness_divider * random_fairness_multiplier;
}

#endif // RANDOM_H

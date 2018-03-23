#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include <Entropy.h>
#include "pins.h"

int random_seed = 0;
int random_fairness = 20;

void initRandom()
{
    Entropy.Initialize();
    random_seed = Entropy.random();
    randomSeed(random_seed);
}

#endif // RANDOM_H

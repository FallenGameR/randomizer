#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include "pins.h"

int random_seed = 0;
int random_fairness = 20;

// http://planetmath.org/goodhashtableprimes
int getRandomSeedFromAnalogNoise()
{
    return analogRead(0) * 53 +
           analogRead(1) * 97 +
           analogRead(2) * 193 +
           analogRead(3) * 389 +
           analogRead(4) * 769 +
           analogRead(5) * 1543;
}

void initRandom()
{
    random_seed = getRandomSeedFromAnalogNoise();
    randomSeed(random_seed);
}

#endif // RANDOM_H

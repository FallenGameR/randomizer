#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include "pins.h"

int seed = 0;
int fairness_selected = 20;

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
    seed = getRandomSeedFromAnalogNoise();
    randomSeed(seed);
}

#endif // RANDOM_H

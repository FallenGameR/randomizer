#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include <Entropy.h>

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

int random_seed = 0;
int random_fairness = 20;

void initRandom()
{
    Entropy.Initialize();
    random_seed = Entropy.random();
    randomSeed(random_seed);
}

#endif // RANDOM_H

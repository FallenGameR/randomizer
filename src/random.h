#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>

// Entropy library actually returns uint32_t,
// but negative values are fun when changing
// the seed manually

int initEntropy();

byte nextRandom(byte* array, const size_t size, size_t* position);

#endif // RANDOM_H

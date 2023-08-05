#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>

// Initialize the entropy library and return the first true random value.
// Entropy library actually returns uint32_t, but negative values are
// fun when changing the seed manually, so we use int.
int initEntropy();

// Return the next random value from the array while advancing the position.
// If the array was not used yet, it will be initialized with indexes and shuffled.
byte nextRandom(byte* array, const size_t size, size_t* position);

#endif // RANDOM_H

#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include <Entropy.h>

// Entropy library actually returns uint32_t,
// but negative values are fun when changing
// the seed manually
int random_seed = 0;

void initRandom()
{
    Entropy.Initialize();
    random_seed = Entropy.random();
    randomSeed(random_seed);
}

byte nextRandom(byte* array, const size_t size, size_t* position)
{
    // Initialize the array on the first usage
    if( *position == 0 )
    {
        // Populate the array with indexes
        for( size_t i = 0; i < size; i++ )
        {
            array[i] = i;
        }

        // Shuffle the array
        for (size_t current = 0; current < size - 1; current++)
        {
            size_t other = random(current + 1, size);
            byte temp = array[current];
            array[current] = array[other];
            array[other] = temp;
        }
    }

    // Return the next value and increment the position
    byte result = array[*position];
    *position = (*position + 1) % size;
    return result;
}

#endif // RANDOM_H

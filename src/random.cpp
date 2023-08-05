#include "random.h"
#include <Entropy.h>

int initEntropy()
{
    Entropy.Initialize();
    return Entropy.random();
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

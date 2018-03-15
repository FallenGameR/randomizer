#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>
#include "pins.h"

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
    int seed = getRandomSeedFromAnalogNoise();
    randomSeed(seed);

    lcd.setCursor(0, 0);
    lcd.print("Randomizer");
    lcd.setCursor(0, 1);
    lcd.print("Seed ");
    lcd.print(seed);
}

#endif // DOA5_H

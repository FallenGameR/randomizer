#ifndef TOTALS_H
#define TOTALS_H

#include <Arduino.h>

// Count how many times player with that index won
byte countPlayerWins(byte player);

// Render the totals screen
void renderTotals();

#endif // TOTALS_H
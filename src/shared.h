#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>

// `Fairness` is how many games needs to be played out for everybody to play equal amount of times in all configurations.
// Minimal fairness value get a chance for everybody to play as soon as possible.
// But as it `fairness` value grows the pair distribution can become more and more strange but fair
// on the larger scale. It could be that some players would not change seats for several games in a row
// but after the `fairness` number of games all players will play equal amount of games regardless.
// `Fairness` makes sense only if there are >2 players.
byte random_fairness = 0;

byte n_players = 0;

#endif // SHARED_H
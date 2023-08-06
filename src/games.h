#ifndef GAMES_H
#define GAMES_H

#include <Arduino.h>

// Populate b_line with fighter names
// a, b, c - indexes of fighters
void setFightersToLineBuffer(byte a, byte b, byte c);

// Select current game
void selectGame(byte game_index);

// Select players for the current match
void selectPlayers();

#endif // GAMES_H
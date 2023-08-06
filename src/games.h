#ifndef GAMES_H
#define GAMES_H

#include <Arduino.h>

// Current game index
extern byte game_index;

// Current game tag value
extern byte game_tag;

// If current game is a tag game
extern bool isTagGame;

// Buffer that holds one line of text that fits the screen with the default font
extern char b_line[];

// Populate b_line with fighter names
// a, b, c - indexes of fighters
void setFightersToLineBuffer(byte a, byte b, byte c);

// Select current game
void selectGame(byte game_index);

// Select players for the current match
void selectPlayers();

#endif // GAMES_H
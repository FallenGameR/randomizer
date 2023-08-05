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
extern char bufferLine[];

// Populate bufferLine with fighter names
// a, b, c - indexes of fighters
void FightersToBufferLine(byte a, byte b, byte c);

// Select current game
void SelectGame(byte game_index);

// Select players for the current match
void SelectPlayers();

#endif // GAMES_H
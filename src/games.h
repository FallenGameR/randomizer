#ifndef GAMES_H
#define GAMES_H

#include <Arduino.h>

// Game variables
extern byte game_index;
extern byte game_tag;
extern bool isTagGame;

// Screen is 480px and min font is 6 pixels wide (by default we actually use font that is twice as big)
// For safety there should also be logic for making sure we don't reach the end of buffer
// But we can add it later on, for now we just have large buffer
extern char bufferLine[];

void FightersToBufferLine(byte a, byte b, byte c);

// Select current game
void SelectGame(byte game_index);

void SelectPlayers();

#endif // GAMES_H
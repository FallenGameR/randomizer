#ifndef GAMES_H
#define GAMES_H

#include "fighters.h"
#include "files.h"

// Game variables
byte game_index = 0;
byte game_tag = 0;
bool isTagGame = false;

// Screen is 480px and min font is 6 pixels wide (by default we actually use font that is twice as big)
// For safety there should also be logic for making sure we don't reach the end of buffer
// But we can add it later on, for now we just have large buffer
char bufferLine[480 / 6];

void FightersToBufferLine(byte a, byte b, byte c)
{
    readFighterName(game_index, a);
    strcpy(bufferLine, b_string);

    if (b != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        readFighterName(game_index, b);
        strcat(bufferLine, b_string);
    }

    if (c != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        readFighterName(game_index, c);
        strcat(bufferLine, b_string);
    }
}

// Select current game
void SelectGame(byte game_index)
{
    n_fighters = readNumberOfFighters(game_index);
    fighters_left_position = 0;
    fighters_right_position = 0;

    game_tag = readGameTag(game_index);

    if (game_tag == 0)
    {
        isTagGame = false;
    }

    Serial.print(F("Game selected: "));
    Serial.print(game_index);
    Serial.print(F(", tag = "));
    Serial.println(game_tag);
}

#endif // GAMES_H
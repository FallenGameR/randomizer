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
    setFighterName(game_index, a);
    strcpy(bufferLine, b_string);

    if (b != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        setFighterName(game_index, b);
        strcat(bufferLine, b_string);
    }

    if (c != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        setFighterName(game_index, c);
        strcat(bufferLine, b_string);
    }
}

// Select current game
void SelectGame(byte gameIndex)
{
    n_fighters = readNumberOfFighters(gameIndex);
    fighters_left_position = 0;
    fighters_right_position = 0;

    game_tag = readGameTag(gameIndex);

    if (game_tag == 0)
    {
        isTagGame = false;
    }

    Serial.println(F("Game selected:"));

    Serial.print(F("  index = "));
    Serial.println(gameIndex);

    Serial.print(F("  tag =  "));
    Serial.println(game_tag);

    Serial.print(F("  fighters =  "));
    Serial.println(n_fighters);
}

#endif // GAMES_H
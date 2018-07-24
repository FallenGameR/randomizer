#ifndef FIGHTERS_H
#define FIGHTERS_H

#define NO_FIGHTER 255

// For regular matches
byte fighter_index_first = NO_FIGHTER;
byte fighter_index_second = NO_FIGHTER;

// For tag matches
byte fighter_index_first2 = NO_FIGHTER;
byte fighter_index_second2 = NO_FIGHTER;
byte fighter_index_first3 = NO_FIGHTER;
byte fighter_index_second3 = NO_FIGHTER;

// Number of fighters in the current game
byte n_fighters = 0;

// Screen is 480px and min font is 6 pixels wide (by default we actually use font that is twise as big)
// For safety there should also be logic for making sure we don't reach the end of buffer
// But we can add it later on, for now we just have large buffer
char bufferLine[480 / 6];

// Constant string for comma
const char str_comma[] PROGMEM = ", ";

void FightersToBufferLine(byte a, byte b, byte c)
{
    setFighterName(game_index, a);
    strcpy(bufferLine, bufferName);

    if (b != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        setFighterName(game_index, b);
        strcat(bufferLine, bufferName);
    }

    if (c != NO_FIGHTER)
    {
        strcat_P(bufferLine, str_comma);
        setFighterName(game_index, c);
        strcat(bufferLine, bufferName);
    }
}

#endif // FIGHTERS_H
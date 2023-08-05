#include "games.h"
#include "fighters.h"
#include "files.h"
#include "shared.h"
#include "screens.h"
#include "players.h"
#include <Arduino.h>

byte game_index = 0;
byte game_tag = 0;
bool isTagGame = false;
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

void SelectPlayers()
{
    // Reshuffle if we reached end of list
    byte pair_index = n_match % n_fairness;
    if (pair_index == 0)
    {
        ShufflePlayerPairs();
    }

    player_index_first = player_pairs[pair_index * 2 + 0];
    player_index_second = player_pairs[pair_index * 2 + 1];

    PRINT(F("Players: "), Serial);
    PRINT_BS(readPlayerName(player_index_first));
    PRINT(F(" and "), Serial);
    PRINT_BS(readPlayerName(player_index_second));
    Serial.println();

    screen_selected = Screen::FighterSelection;
}

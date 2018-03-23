#ifndef STATS_H
#define STATS_H

#include <Arduino.h>
#include "games\games.h"
#include "players.h"
#include "fighters.h"
#include "memory.h"

enum Winner
{
    None,
    First,
    Second,
    Draw,
};

enum Stats
{
    FirstPlayer,
    SecondPlayer,
    Game,
    FirstFighter,
    SecondFighter,
    Won,
    NotFair,
    Size,
};

byte winner_selected;
bool not_fair_win;

// Arduino UNO is at the capacity data-wise.
// 80 matches is ok since practically we didn't do more than 60.
// But if there is a way to use Program memory to store this data (place
// array on stack?) then we should be able to increase the capacity x10.
//      Device : atmega328p
//      Program : 7560 bytes(23.1 % Full)(.text +.data +.bootloader)
//      Data : 1978 bytes(96.6 % Full)(.data +.bss +.noinit)
const int match_limit = 80;
int match_current = 0;
byte matches[1][Stats::Size];

void RecordMatchOutcome()
{
    // Record in the stats table
    if (match_current < match_limit)
    {
        matches[match_current][Stats::FirstPlayer] = player_index_first;
        matches[match_current][Stats::SecondPlayer] = player_index_second;
        matches[match_current][Stats::Game] = games_index;
        matches[match_current][Stats::FirstFighter] = fighter_index_first;
        matches[match_current][Stats::SecondFighter] = fighter_index_second;
        matches[match_current][Stats::Won] = winner_selected;
        matches[match_current][Stats::NotFair] = not_fair_win;
        match_current++;
    }

    // Output to console
    switch (winner_selected)
    {
    case Winner::Draw:
        Serial.print(F("Draw"));
        break;

    case Winner::First:
        SERIAL_PRINT(players, player_index_first);
        Serial.print(F(" won ("));
        SERIAL_PRINT(fighter_map_selected, fighter_index_first);
        Serial.print(F(")"));
        break;

    case Winner::Second:
        SERIAL_PRINT(players, player_index_second);
        Serial.print(F(" won ("));
        SERIAL_PRINT(fighter_map_selected, fighter_index_second);
        Serial.print(F(")"));
        break;
    }

    if (not_fair_win)
    {
        Serial.print(F(" (opponent says not fair)"));
    }
    Serial.println();
}

void DumpStats()
{
    if (match_current == 0)
    {
        Serial.println(F("No stats available"));
        return;
    }

    Serial.println(F("FirstPlayer,SecondPlayer,Game,FirstFighter,SecondFighter,Won,NotFair"));
    for (int i = 0; i < match_current; i++)
    {
        Serial.print(matches[i][Stats::FirstPlayer]);
        Serial.print(F(","));
        Serial.print(matches[i][Stats::SecondPlayer]);
        Serial.print(F(","));
        Serial.print(matches[i][Stats::Game]);
        Serial.print(F(","));
        Serial.print(matches[i][Stats::FirstFighter]);
        Serial.print(F(","));
        Serial.print(matches[i][Stats::SecondFighter]);
        Serial.print(F(","));
        Serial.print(matches[i][Stats::Won]);
        Serial.print(F(","));
        Serial.print(matches[i][Stats::NotFair]);
        Serial.print(F(","));
        Serial.println();
    }
}

#endif // STATS_H

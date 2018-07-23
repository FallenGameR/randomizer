#ifndef STATS_H
#define STATS_H

#include <Arduino.h>
#include "games\games.h"
#include "players.h"
#include "fighters.h"
#include "memory.h"
#include "files.h"

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
    FirstFighter2,
    SecondFighter2,
    FirstFighter3,
    SecondFighter3,
    Won,
    NotFair,
    Size,
};

byte winner_selected;
bool not_fair_win;

// Arduino UNO is short on data memory even when we move all static strings into PROGMEM.
// 150 matches is ok since practically we didn't do more than 60 in one day.
//      Device : atmega328p
//      Program:    7714 bytes (33.8% Full)
//      Data:       1451 bytes (74.5% Full)

const int match_limit = 100;
int match_current = 0;
byte matches[match_limit][Stats::Size];

void DumpMatch(int i)
{
    const char *const *fighterMap = fighter_map[matches[i][Stats::Game]];

    Serial.print(i + 1);
    Serial.print(F(","));
    SERIAL_PRINT_PLAYER(matches[i][Stats::FirstPlayer]);
    Serial.print(F(","));
    SERIAL_PRINT_PLAYER(matches[i][Stats::SecondPlayer]);
    Serial.print(F(","));
    SERIAL_PRINT_GAME(matches[i][Stats::Game]);
    Serial.print(F(","));

    switch (matches[i][Stats::Won])
    {
    case Winner::None:
        Serial.print(F("None"));
        break;

    case Winner::First:
        SERIAL_PRINT_PLAYER(matches[i][Stats::FirstPlayer]);
        break;

    case Winner::Second:
        SERIAL_PRINT_PLAYER(matches[i][Stats::SecondPlayer]);
        break;

    case Winner::Draw:
        Serial.print(F("Draw"));
        break;
    }
    Serial.print(F(","));

    if (matches[i][Stats::NotFair])
    {
        Serial.print(F("false"));
    }
    else
    {
        Serial.print(F("true"));
    }
    Serial.print(F(","));

    // First player fighters
    SERIAL_PRINT(fighterMap, matches[i][Stats::FirstFighter]);
    Serial.print(F(","));
    if (matches[i][Stats::FirstFighter2] != NO_FIGHTER)
    {
        SERIAL_PRINT(fighterMap, matches[i][Stats::FirstFighter2]);
    }
    Serial.print(F(","));
    if (matches[i][Stats::FirstFighter3] != NO_FIGHTER)
    {
        SERIAL_PRINT(fighterMap, matches[i][Stats::FirstFighter3]);
    }
    Serial.print(F(","));

    // Second player fighters
    SERIAL_PRINT(fighterMap, matches[i][Stats::SecondFighter]);
    Serial.print(F(","));
    if (matches[i][Stats::SecondFighter2] != NO_FIGHTER)
    {
        SERIAL_PRINT(fighterMap, matches[i][Stats::SecondFighter2]);
    }
    Serial.print(F(","));
    if (matches[i][Stats::SecondFighter3] != NO_FIGHTER)
    {
        SERIAL_PRINT(fighterMap, matches[i][Stats::SecondFighter3]);
    }
    Serial.println();
}

void RecordMatchOutcome()
{
    // Record in the stats table
    if (match_current < match_limit)
    {
        matches[match_current][Stats::FirstPlayer] = player_index_first;
        matches[match_current][Stats::SecondPlayer] = player_index_second;
        matches[match_current][Stats::Game] = game_index;
        matches[match_current][Stats::FirstFighter] = fighter_index_first;
        matches[match_current][Stats::SecondFighter] = fighter_index_second;
        matches[match_current][Stats::FirstFighter2] = fighter_index_first2;
        matches[match_current][Stats::SecondFighter2] = fighter_index_second2;
        matches[match_current][Stats::FirstFighter3] = fighter_index_first3;
        matches[match_current][Stats::SecondFighter3] = fighter_index_second3;
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
        SERIAL_PRINT_PLAYER(player_index_first);
        Serial.print(F(" won ("));
        SERIAL_PRINT(fighter_map_selected, fighter_index_first);
        if (fighter_index_first2 != NO_FIGHTER)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_first2);
        }
        if (fighter_index_first3 != NO_FIGHTER)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_first3);
        }
        Serial.print(F(")"));
        break;

    case Winner::Second:
        SERIAL_PRINT_PLAYER(player_index_second);
        Serial.print(F(" won ("));
        SERIAL_PRINT(fighter_map_selected, fighter_index_second);
        if (fighter_index_second2 != NO_FIGHTER)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_second2);
        }
        if (fighter_index_second3 != NO_FIGHTER)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_second3);
        }
        Serial.print(F(")"));
        break;
    }

    if (not_fair_win)
    {
        Serial.print(F(" (opponent says not fair)"));
    }
    Serial.println();

    // Just in case of failure dump csv form as well
    DumpMatch(match_current - 1);
}

void DumpStats()
{
    if (match_current == 0)
    {
        Serial.println(F("No stats available"));
        return;
    }

    Serial.println(F("Match,FirstPlayer,SecondPlayer,Game,Winner,Fair,FirstFighter,FirstFighter2,FirstFighter3,SecondFighter,SecondFighter2,SecondFighter3"));
    for (int i = 0; i < match_current; i++)
    {
        DumpMatch(i);
    }
}

#endif // STATS_H

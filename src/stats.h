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

// Arduino UNO is short on data memory even when we move all static strings into PROGMEM.
// 150 matches is ok since practically we didn't do more than 60 in one day.
// 150 matches lead to buggy behaviour
//      Device : atmega328p
//      Program:    7714 bytes (23.5% Full)
//      Data:       1451 bytes (70.8% Full)

const int match_limit = 150;
int match_current = 0;
byte matches[match_limit][Stats::Size];

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

    Serial.println(F("FirstPlayer,SecondPlayer,Game,FirstFighter,SecondFighter,Winner,Fair"));
    for (int i = 0; i < match_current; i++)
    {
        const char *const *fighterMap = fighter_map[matches[i][Stats::Game]];

        SERIAL_PRINT(players, matches[i][Stats::FirstPlayer]);
        Serial.print(F(","));
        SERIAL_PRINT(players, matches[i][Stats::SecondPlayer]);
        Serial.print(F(","));
        SERIAL_PRINT(games, matches[i][Stats::Game]);
        Serial.print(F(","));
        SERIAL_PRINT(fighterMap, matches[i][Stats::FirstFighter]);
        Serial.print(F(","));
        SERIAL_PRINT(fighterMap, matches[i][Stats::SecondFighter]);
        Serial.print(F(","));

        switch (matches[i][Stats::Won])
        {
        case Winner::None:
            Serial.print(F("None"));
            break;

        case Winner::First:
            SERIAL_PRINT(players, matches[i][Stats::FirstPlayer]);
            break;

        case Winner::Second:
            SERIAL_PRINT(players, matches[i][Stats::SecondPlayer]);
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

        Serial.println();
    }
}

#endif // STATS_H

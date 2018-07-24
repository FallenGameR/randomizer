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
byte matches[match_limit][Stats::Size];

File statsFile;

// print to serial, file
#define PRINT_SF(printable) \
    PRINT2(printable, Serial, statsFile)

// print bufferName to serial, file
#define PRINT_BSF(buffer_name_setup) \
    buffer_name_setup;               \
    PRINT_SF(bufferName)

// print program memory to serial, file
#define PRINT_PSF(tableElement) \
    PRINT2_P(tableElement, Serial, statsFile)

void InitStatsFile()
{
    setStatsPath();
    statsFile = SD.open(bufferPath, FILE_WRITE);
    statsFile.println(F("Match,FirstPlayer,SecondPlayer,Game,Winner,Fair,FirstFighter,FirstFighter2,FirstFighter3,SecondFighter,SecondFighter2,SecondFighter3"));
}

void DumpMatch(int i)
{
    const char *const *fighterMap = fighter_map[matches[i][Stats::Game]];

    PRINT_SF(i + 1);
    PRINT_SF(F(","));

    PRINT_BSF(setPlayerName(matches[i][Stats::FirstPlayer]));
    PRINT_SF(F(","));

    PRINT_BSF(setPlayerName(matches[i][Stats::SecondPlayer]));
    PRINT_SF(F(","));

    PRINT_BSF(setGameName(matches[i][Stats::Game]));
    PRINT_SF(F(","));

    switch (matches[i][Stats::Won])
    {
    case Winner::None:
        PRINT_SF(F("None"));
        break;

    case Winner::First:
        PRINT_BSF(setPlayerName(matches[i][Stats::FirstPlayer]));
        break;

    case Winner::Second:
        PRINT_BSF(setPlayerName(matches[i][Stats::SecondPlayer]));
        break;

    case Winner::Draw:
        PRINT_SF(F("Draw"));
        break;
    }
    PRINT_SF(F(","));

    if (matches[i][Stats::NotFair])
    {
        PRINT_SF(F("false"));
    }
    else
    {
        PRINT_SF(F("true"));
    }
    PRINT_SF(F(","));

    // First player fighters
    PRINT_PSF(fighterMap[matches[i][Stats::FirstFighter]]);
    PRINT_SF(F(","));

    if (matches[i][Stats::FirstFighter2] != NO_FIGHTER)
    {
        PRINT_PSF(fighterMap[matches[i][Stats::FirstFighter2]]);
    }
    PRINT_SF(F(","));

    if (matches[i][Stats::FirstFighter3] != NO_FIGHTER)
    {
        PRINT_PSF(fighterMap[matches[i][Stats::FirstFighter3]]);
    }
    PRINT_SF(F(","));

    // Second player fighters
    PRINT_PSF(fighterMap[matches[i][Stats::SecondFighter]]);
    PRINT_SF(F(","));

    if (matches[i][Stats::SecondFighter2] != NO_FIGHTER)
    {
        PRINT_PSF(fighterMap[matches[i][Stats::SecondFighter2]]);
    }
    PRINT_SF(F(","));

    if (matches[i][Stats::SecondFighter3] != NO_FIGHTER)
    {
        PRINT_PSF(fighterMap[matches[i][Stats::SecondFighter3]]);
    }

    Serial.println();
    statsFile.println();
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

#ifndef STATS_H
#define STATS_H

#include <Arduino.h>
#include <SD.h>
#include "games.h"
#include "players.h"
#include "print.h"
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

// For regular matches
extern byte fighter_index_first;
extern byte fighter_index_second;

// For tag matches
extern byte fighter_index_first2;
extern byte fighter_index_second2;
extern byte fighter_index_first3;
extern byte fighter_index_second3;

extern byte winner_selected;

extern bool not_fair_win;

// Arduino UNO is short on data memory even when we move all static strings into PROGMEM.
// 150 matches is ok since practically we didn't do more than 60 in one day.
//      Device : atmega328p
//      Program:    7714 bytes (33.8% Full)
//      Data:       1451 bytes (74.5% Full)

const int match_limit = 100;
extern byte matches[match_limit][Stats::Size];

void InitStatsFile(int random_seed);

void RecordMatchOutcome();

void dumpStats();

#endif // STATS_H

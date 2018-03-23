#ifndef STATS_H
#define STATS_H

#include <Arduino.h>
#include "games\games.h"
#include "players.h"
#include "fighters.h"

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

int winner_selected;
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
        Serial.print("Draw");
        break;

    case Winner::First:
        Serial.print(players[player_index_first]);
        Serial.print(" won (");
        Serial.print(fighter_map_selected[fighter_index_first]);
        Serial.print(")");
        break;

    case Winner::Second:
        Serial.print(players[player_index_second]);
        Serial.print(" won (");
        Serial.print(fighter_map_selected[fighter_index_second]);
        Serial.print(")");
        break;
    }

    if (not_fair_win)
    {
        Serial.print(" (opponent says not fair)");
    }
    Serial.println();
}

void DumpStats()
{
    if (match_current == 0)
    {
        Serial.println("No stats available");
        return;
    }

    Serial.println("FirstPlayer,SecondPlayer,Game,FirstFighter,SecondFighter,Won,NotFair");
    for (int i = 0; i < match_current; i++)
    {
        Serial.print(matches[i][Stats::FirstPlayer]);
        Serial.print(",");
        Serial.print(matches[i][Stats::SecondPlayer]);
        Serial.print(",");
        Serial.print(matches[i][Stats::Game]);
        Serial.print(",");
        Serial.print(matches[i][Stats::FirstFighter]);
        Serial.print(",");
        Serial.print(matches[i][Stats::SecondFighter]);
        Serial.print(",");
        Serial.print(matches[i][Stats::Won]);
        Serial.print(",");
        Serial.print(matches[i][Stats::NotFair]);
        Serial.print(",");
        Serial.println();
    }
}

#endif // STATS_H

#ifndef STATS_H
#define STATS_H

#include <Arduino.h>
#include "games.h"
#include "players.h"
#include "fighters.h"
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

#define PRINT2_BSF_F(fighter_index) \
    PRINT2_BSF(setFighterName(matches[i][Stats::Game], matches[i][Stats::fighter_index]));

#define PRINT2_BSF_F_OPT(fighter_index)                 \
    if (matches[i][Stats::fighter_index] != NO_FIGHTER) \
    {                                                   \
        PRINT2_BSF_F(fighter_index);                    \
    }

void InitStatsFile(int random_seed)
{
    setStatsPath(random_seed);
    statsFile = SD.open(b_path, FILE_WRITE);
    statsFile.println(F("Match,FirstPlayer,SecondPlayer,Game,Winner,Fair,FirstFighter,FirstFighter2,FirstFighter3,SecondFighter,SecondFighter2,SecondFighter3"));
}

void DumpMatch(int i)
{
    PRINT2_SF(i + 1);
    PRINT2_SF(F(","));

    PRINT2_BSF(setPlayerName(matches[i][Stats::FirstPlayer]));
    PRINT2_SF(F(","));

    PRINT2_BSF(setPlayerName(matches[i][Stats::SecondPlayer]));
    PRINT2_SF(F(","));

    PRINT2_BSF(setGameName(matches[i][Stats::Game]));
    PRINT2_SF(F(","));

    switch (matches[i][Stats::Won])
    {
    case Winner::None:
        PRINT2_SF(F("None"));
        break;

    case Winner::First:
        PRINT2_BSF(setPlayerName(matches[i][Stats::FirstPlayer]));
        break;

    case Winner::Second:
        PRINT2_BSF(setPlayerName(matches[i][Stats::SecondPlayer]));
        break;

    case Winner::Draw:
        PRINT2_SF(F("Draw"));
        break;
    }
    PRINT2_SF(F(","));

    if (matches[i][Stats::NotFair])
    {
        PRINT2_SF(F("false"));
    }
    else
    {
        PRINT2_SF(F("true"));
    }
    PRINT2_SF(F(","));

    // First player fighters
    PRINT2_BSF_F(FirstFighter);
    PRINT2_SF(F(","));

    PRINT2_BSF_F_OPT(FirstFighter2);
    PRINT2_SF(F(","));

    PRINT2_BSF_F_OPT(FirstFighter3);
    PRINT2_SF(F(","));

    // Second player fighters
    PRINT2_BSF_F(SecondFighter);
    PRINT2_SF(F(","));

    PRINT2_BSF_F_OPT(SecondFighter2);
    PRINT2_SF(F(","));

    PRINT2_BSF_F_OPT(SecondFighter3);
    PRINT2_SF(F(","));

    Serial.println();
    statsFile.println();
    statsFile.flush();
}

void RecordMatchOutcome()
{
    // Record in the stats table
    if (n_match < match_limit)
    {
        matches[n_match][Stats::FirstPlayer] = player_index_first;
        matches[n_match][Stats::SecondPlayer] = player_index_second;
        matches[n_match][Stats::Game] = game_index;
        matches[n_match][Stats::FirstFighter] = fighter_index_first;
        matches[n_match][Stats::SecondFighter] = fighter_index_second;
        matches[n_match][Stats::FirstFighter2] = fighter_index_first2;
        matches[n_match][Stats::SecondFighter2] = fighter_index_second2;
        matches[n_match][Stats::FirstFighter3] = fighter_index_first3;
        matches[n_match][Stats::SecondFighter3] = fighter_index_second3;
        matches[n_match][Stats::Won] = winner_selected;
        matches[n_match][Stats::NotFair] = not_fair_win;
        n_match++;
    }

    // Output to console
    switch (winner_selected)
    {
    case Winner::Draw:
        Serial.print(F("Draw"));
        break;

    case Winner::First:
        PRINT_BS(setPlayerName(player_index_first));
        PRINT(F(" won ("), Serial);
        FightersToBufferLine(fighter_index_first, fighter_index_first2, fighter_index_first3);
        PRINT(bufferLine, Serial);
        Serial.print(F(")"));
        break;

    case Winner::Second:
        PRINT_BS(setPlayerName(player_index_second));
        PRINT(F(" won ("), Serial);
        FightersToBufferLine(fighter_index_second, fighter_index_second2, fighter_index_second3);
        PRINT(bufferLine, Serial);
        Serial.print(F(")"));
        break;
    }

    if (not_fair_win)
    {
        PRINT(F(" (opponent says not fair)"), Serial);
    }

    Serial.println();

    // Just in case of failure, to be able to recover stats we dump csv line as well
    DumpMatch(n_match - 1);
}

void DumpStats()
{
    if (n_match == 0)
    {
        Serial.println(F("No stats available"));
        return;
    }

    Serial.println(F("Match,FirstPlayer,SecondPlayer,Game,Winner,Fair,FirstFighter,FirstFighter2,FirstFighter3,SecondFighter,SecondFighter2,SecondFighter3"));
    for (int i = 0; i < n_match; i++)
    {
        DumpMatch(i);
    }
}

#endif // STATS_H

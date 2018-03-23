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

int match_current = 0;
const int match_limit = 1000;
byte coords[match_limit][Stats::Size];

void RecordMatchOutcome()
{
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

#endif // STATS_H
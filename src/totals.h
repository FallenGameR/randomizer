#ifndef TOTALS_H
#define TOTALS_H

#include "shared.h"
#include "colors.h"
#include "graph.h"
#include "stats.h"
#include "files.h"
#include <Arduino.h>

// Used only for finding out borders of the graph
extern byte playerWins[];

extern unsigned int playerColors[MAX_PLAYERS];

void ClearPlayerWinsArray();

byte countPlayerWins(byte player);

void GroupPlayerWins();

byte GetMaxWins();

box InitScreen();

box InitPlot();

box InitLine(box &screen, box &plot);

bool IsPlayerWon(byte player, byte match);

bool IsPlayerDraw(byte player, byte match);

byte GetOtherPlayer(byte player, byte match);

// Function assumes that plot is allocated and has length of match_limit + 1
// First element is always 0
// Elements until GetMatchCount are filled, the remainder left as is
void FillPlayerWinsGraph(byte player, byte *graph);

void FillPlayerFairWinsGraph(byte player, byte *graph);

#define DOT_OFFSET 3
#define DOT_WIDTH (DOT_OFFSET * 2 + 1)

void RenderGraph(byte player, byte *graph, box &screen, box &plot, unsigned int color, bool isBold);

void RenderTotals();

#endif // TOTALS_H
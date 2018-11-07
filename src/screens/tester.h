#ifndef TESTER_H
#define TESTER_H

#include "screens.h"
#include "..\graph.h"
#include "..\stats.h"
#include "..\random.h"

void MockRecordMatchOutcome()
{
    match_current = 0;

    for (int match = 0; match < 42; match += 1)
    {
        matches[match_current][Stats::FirstPlayer] = random(3);
        matches[match_current][Stats::SecondPlayer] = random(3);
        matches[match_current][Stats::Game] = 0;
        matches[match_current][Stats::FirstFighter] = 0;
        matches[match_current][Stats::SecondFighter] = 0;
        matches[match_current][Stats::FirstFighter2] = 0;
        matches[match_current][Stats::SecondFighter2] = 0;
        matches[match_current][Stats::FirstFighter3] = 0;
        matches[match_current][Stats::SecondFighter3] = 0;
        matches[match_current][Stats::Won] = random(1) ? matches[match_current][Stats::FirstPlayer] : matches[match_current][Stats::SecondPlayer];
        matches[match_current][Stats::NotFair] = false;
        match_current++;
    }
}

void TesterScreen()
{
    MockRecordMatchOutcome();
    tft.fillScreen(BLACK);

    double x = 0;
    double y = random(10);

    box screen;
    screen.xlo = 0;
    screen.ylo = 0;
    screen.xhi = tft.width() - 1;
    screen.yhi = tft.height() - 1;

    box plot;
    plot.xlo = 0;
    plot.xhi = 60;
    plot.ylo = 0;  //(int)y - 5;
    plot.yhi = 10; //(int)y + 5;

    box line;
    line.xlo = MAP_X(x, plot, screen);
    line.ylo = MAP_Y(y, plot, screen);

    // Draw grid
    InitializeGrid(screen, plot, 10, 1, DKBLUE, WHITE, BLACK);
    InitializeAxes(screen, plot, "Totals", "matches", "wins", RED, WHITE, BLACK);

    // Draw graph
    for (double x = 1; x <= 60; x += 1)
    {
        line.xhi = x;
        line.yhi = random(10);
        Graph(screen, plot, line, GREEN);
        delay(100);
    }
}

#endif // TESTER_H
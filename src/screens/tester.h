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
        matches[match_current][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[match_current][Stats::NotFair] = false;
        match_current++;
    }
}

byte GetMatchCount()
{
    return match_current;
}

byte playerWins[MAX_PLAYERS];

void ClearPlayerWinsArray()
{
    for (byte i = 0; i < MAX_PLAYERS; i++)
    {
        playerWins[i] = 0;
    }
}

void GroupPlayerWins()
{
    ClearPlayerWinsArray();

    for (byte i = 0; i < GetMatchCount(); i++)
    {
        byte firstPlayer = matches[i][Stats::FirstPlayer];
        byte secondPlayer = matches[i][Stats::SecondPlayer];

        switch (matches[i][Stats::Won])
        {
        case Winner::Draw:
            playerWins[firstPlayer] += 1;
            playerWins[secondPlayer] += 1;
            break;

        case Winner::First:
            playerWins[firstPlayer] += 1;
            break;

        case Winner::Second:
            playerWins[secondPlayer] += 1;
        }
    }
}

byte GetMaxWins()
{
    byte maxWins = 0;

    for (byte i = 0; i < MAX_PLAYERS; i++)
    {
        maxWins = playerWins[i] > maxWins ? playerWins[i] : maxWins;
    }

    return maxWins;
}

box InitScreen()
{
    box screen;
    screen.xlo = 0;
    screen.ylo = 0;
    screen.xhi = tft.width() - 1;
    screen.yhi = tft.height() - 1;
    return screen;
}

box InitPlot()
{
    box plot;
    plot.xlo = 0;
    plot.xhi = GetMatchCount();
    plot.ylo = 0;
    plot.yhi = GetMaxWins();
    return plot;
}

box InitLine(box &screen, box &plot)
{
    box line;
    double x = 0;
    double y = 0;
    line.xlo = MAP_X(x, plot, screen);
    line.ylo = MAP_Y(y, plot, screen);
}

void TesterScreen()
{
    // Init
    MockRecordMatchOutcome();
    GroupPlayerWins();
    tft.fillScreen(BLACK);

    // Draw grid
    box screen = InitScreen();
    box plot = InitPlot();
    InitializeGrid(screen, plot, 5, 1, DKBLUE, WHITE, BLACK);
    InitializeAxes(screen, plot, "Totals", "matches", "wins", RED, WHITE, BLACK);

    // Graw win graph for each player
    for (byte player = 0; player < n_players; player += 1)
    {
        box line = InitLine(screen, plot);
        byte playerWins = 0;

        for (byte i = 0; i < GetMatchCount(); i += 1)
        {
            byte firstPlayer = matches[i][Stats::FirstPlayer];
            byte secondPlayer = matches[i][Stats::SecondPlayer];

            switch (matches[i][Stats::Won])
            {
            case Winner::Draw:
                if ((player == firstPlayer) || (player == secondPlayer))
                {
                    playerWins += 1;
                }
                break;

            case Winner::First:
                if (player == firstPlayer)
                {
                    playerWins += 1;
                }
                break;

            case Winner::Second:
                if (player == secondPlayer)
                {
                    playerWins += 1;
                }
            }

            line.xhi = i + 1;
            line.yhi = playerWins;
            Graph(screen, plot, line, GREEN);
            delay(100);
        }
    }
}

#endif // TESTER_H
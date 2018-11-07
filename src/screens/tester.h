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
    return line;
}

unsigned int playerColors[MAX_PLAYERS];

void InitPlayerColors()
{
    playerColors[0] = CYAN;
    playerColors[1] = YELLOW;
    playerColors[2] = LTPURPLE;

    playerColors[3] = BLUE;
    playerColors[4] = ORANGE;
    playerColors[5] = MAGENTA;

    playerColors[6] = DKBLUE;
    playerColors[7] = DKYELLOW;
    playerColors[8] = PURPLE;

    playerColors[9] = DKCYAN;
    playerColors[10] = DKORANGE;
    playerColors[11] = DKMAGENTA;

    playerColors[12] = GREEN;
    playerColors[13] = RED;
    playerColors[14] = LTGREEN;
    playerColors[15] = LTRED;
}

void TesterScreen()
{
    // Init
    MockRecordMatchOutcome();
    GroupPlayerWins();
    InitPlayerColors();
    tft.fillScreen(BLACK);

    // Draw grid
    box screen = InitScreen();
    box plot = InitPlot();
    InitializeGrid(screen, plot, 5, 1, DKBLUE, WHITE, BLACK);
    InitializeAxes(screen, plot, "Totals", "matches", "wins", RED, WHITE, BLACK);

    // Draw legend
    for (byte player = 0; player < n_players; player += 1)
    {
        tft.setTextSize(1);
        tft.setTextColor(playerColors[player], BLACK);
        tft.setCursor(
            screen.xlo + 40,
            screen.ylo + 10 + player * 10);

        setPlayerName(player);
        tft.print(bufferName);
    }

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
            Graph(screen, plot, line, playerColors[player]);
            delay(100);
        }
    }

    delay(5000);
}

#endif // TESTER_H
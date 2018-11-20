#ifndef TOTALS_H
#define TOTALS_H

#include "colors.h"
#include "graph.h"
#include "stats.h"

byte playerWins[MAX_PLAYERS];

byte GetMatchCount()
{
    return match_current;
}

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

void RenderTotals()
{
    // Init
    GroupPlayerWins();
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
        byte playerWins = 0;
        box line;

        // Draw winnins streak line
        line = InitLine(screen, plot);

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
        }

        /* Need to know playerWins for each point...

        // Draw whom did the player lost to
        line = InitLine(screen, plot);

        for (byte i = 0; i < GetMatchCount(); i += 1)
        {
            byte firstPlayer = matches[i][Stats::FirstPlayer];
            byte secondPlayer = matches[i][Stats::SecondPlayer];
            byte winner = matches[i][Stats::Won];

            bool didReallyWin = true;
            byte otherPlayer;

            if ((player == firstPlayer) && (winner == Winner::Second))
            {
                didReallyWin = false;
                otherPlayer = secondPlayer;
            }

            if ((player == secondPlayer) && (winner == Winner::First))
            {
                didReallyWin = false;
                otherPlayer = firstPlayer;
            }

            line.xhi = i + 1;
            line.yhi = playerWins;
            double x = MAP_X(line.xhi, plot, screen);
            double y = MAP_Y(line.yhi, plot, screen);

            if (!didReallyWin)
            {
                unsigned int dotColor = didReallyWin ? playerColors[player] : playerColors[otherPlayer];
                tft.fillRect(x - DOT_OFFSET, y - DOT_OFFSET, DOT_WIDTH, DOT_WIDTH, dotColor);
                tft.drawRect(x - DOT_OFFSET, y - DOT_OFFSET, DOT_WIDTH, DOT_WIDTH, BLACK);
            }

            line.xlo = x;
            line.ylo = y;

        }
        /**/
    }
}

#endif // TOTALS_H
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

bool IsPlayerWon(byte player, byte match)
{
    byte firstPlayer = matches[match][Stats::FirstPlayer];
    byte secondPlayer = matches[match][Stats::SecondPlayer];
    byte winner = matches[match][Stats::Won];

    if ((winner == Winner::First) && (player == firstPlayer))
    {
        return true;
    }

    if ((winner == Winner::Second) && (player == secondPlayer))
    {
        return true;
    }

    return false;
}

bool IsPlayerDraw(byte player, byte match)
{
    byte firstPlayer = matches[match][Stats::FirstPlayer];
    byte secondPlayer = matches[match][Stats::SecondPlayer];
    byte winner = matches[match][Stats::Won];

    return (winner == Winner::Draw) && ((player == firstPlayer) || (player == secondPlayer));
}

byte GetOtherPlayer(byte player, byte match)
{
    byte firstPlayer = matches[match][Stats::FirstPlayer];
    byte secondPlayer = matches[match][Stats::SecondPlayer];

    if (player == firstPlayer)
    {
        return secondPlayer;
    }

    if (player == secondPlayer)
    {
        return firstPlayer;
    }

    Serial.println("First:");
    Serial.println(firstPlayer);
    Serial.println("Second");
    Serial.println(secondPlayer);
    Serial.println("Player");
    Serial.println(player);
    Serial.println("Match");
    Serial.println(match);
    return -1;
}

// Function assumes that plot is allocated and has length of match_limit + 1
// First element is always 0
// Elements until GetMatchCount are filled, the remainder left as is
void FillPlayerPlot(byte player, byte *graph)
{
    graph[0] = 0;

    for (byte i = 0; i < GetMatchCount(); i += 1)
    {
        graph[i + 1] = graph[i];
        if (IsPlayerWon(player, i) || IsPlayerDraw(player, i))
        {
            graph[i + 1] += 1;
        }
    }
}

#define DOT_OFFSET 3
#define DOT_WIDTH (DOT_OFFSET * 2 + 1)

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
    box line;
    byte graph[match_limit + 1];

    for (byte player = 0; player < n_players; player += 1)
    {
        // Find plot points
        FillPlayerPlot(player, graph);

        // Draw winnins streak line
        line = InitLine(screen, plot);
        for (byte i = 0; i < GetMatchCount(); i += 1)
        {
            line.xhi = i + 1;
            line.yhi = graph[i + 1];
            Graph(screen, plot, line, playerColors[player]);
        }

        // Draw whom did the player lost to
        line = InitLine(screen, plot);
        for (byte i = 0; i < GetMatchCount(); i += 1)
        {
            line.xhi = i + 1;
            line.yhi = graph[i + 1];
            double x = MAP_X(line.xhi, plot, screen);
            double y = MAP_Y(line.yhi, plot, screen);

            if (!IsPlayerWon(player, i))
            {
                byte otherPlayer = GetOtherPlayer(player, i);
                tft.fillRect(x - DOT_OFFSET, y - DOT_OFFSET, DOT_WIDTH, DOT_WIDTH, playerColors[otherPlayer]);
                tft.drawRect(x - DOT_OFFSET, y - DOT_OFFSET, DOT_WIDTH, DOT_WIDTH, BLACK);
            }

            line.xlo = x;
            line.ylo = y;
        }

        delay(10000);
    }
}

#endif // TOTALS_H
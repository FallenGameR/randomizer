#ifndef TOTALS_H
#define TOTALS_H

#include "shared.h"
#include "colors.h"
#include "graph.h"
#include "stats.h"

// Used only for finding out borders of the graph
byte playerWins[MAX_PLAYERS];

unsigned int playerColors[MAX_PLAYERS] = {
    CYAN,       // Player 0
    YELLOW,     // Player 1
    LT_PURPLE,  // Player 2
    BLUE,       // Player 3
    ORANGE,     // Player 4
    MAGENTA,    // Player 5
    DK_BLUE,    // Player 6
    DK_YELLOW,  // Player 7
    PURPLE,     // Player 8
    DK_CYAN,    // Player 9
};


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

    for (byte i = 0; i < n_match; i++)
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
    plot.xhi = n_match;
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

    return NO_FIGHTER;
}

// Function assumes that plot is allocated and has length of match_limit + 1
// First element is always 0
// Elements until GetMatchCount are filled, the remainder left as is
void FillPlayerWinsGraph(byte player, byte *graph)
{
    graph[0] = 0;

    for (byte i = 0; i < n_match; i += 1)
    {
        graph[i + 1] = graph[i];
        if (IsPlayerWon(player, i) || IsPlayerDraw(player, i))
        {
            graph[i + 1] += 1;
        }
    }
}

void FillPlayerFairWinsGraph(byte player, byte *graph)
{
    graph[0] = 0;

    for (byte i = 0; i < n_match; i += 1)
    {
        graph[i + 1] = graph[i];

        if( matches[i][Stats::NotFair] )
        {
            continue;
        }

        if (IsPlayerWon(player, i) || IsPlayerDraw(player, i))
        {
            graph[i + 1] += 1;
        }
    }
}

#define DOT_OFFSET 3
#define DOT_WIDTH (DOT_OFFSET * 2 + 1)

void RenderGraph(byte player, byte *graph, box &screen, box &plot, unsigned int color, bool isBold)
{
    // Draw win streak line
    box line = InitLine(screen, plot);
    for (byte i = 0; i < n_match; i += 1)
    {
        line.xhi = i + 1;
        line.yhi = graph[i + 1];
        Graph(screen, plot, line, color, isBold);
    }

    // Draw whom did the player lost to
    line = InitLine(screen, plot);
    for (byte i = 0; i < n_match; i += 1)
    {
        line.xhi = i + 1;
        line.yhi = graph[i + 1];
        double x = MAP_X(line.xhi, plot, screen);
        double y = MAP_Y(line.yhi, plot, screen);

        if (!IsPlayerWon(player, i))
        {
            byte otherPlayer = GetOtherPlayer(player, i);
            bool playedThisMatch = otherPlayer != NO_FIGHTER;
            if (playedThisMatch)
            {
                tft.fillRect(x - DOT_OFFSET, y - DOT_OFFSET, DOT_WIDTH, DOT_WIDTH, playerColors[otherPlayer]);
                tft.drawRect(x - DOT_OFFSET, y - DOT_OFFSET, DOT_WIDTH, DOT_WIDTH, BLACK);
            }
        }

        line.xlo = x;
        line.ylo = y;
    }
}

void RenderTotals()
{
    // Init
    GroupPlayerWins();
    tft.fillScreen(BLACK);

    // Screen coordinates (physical x: width, y: height)
    box screen = InitScreen();

    // Plot coordinates (logical x: match, y: wins)
    box plot = InitPlot();

    // Next line segment to draw
    box line;

    // Draw grid
    InitializeGrid(screen, plot, 5, 1, DK_BLUE, WHITE, BLACK);
    InitializeAxes(screen, plot, "Totals", "matches", "wins", RED, WHITE, BLACK);

    // Draw legend
    for (byte player_idx = 0; player_idx < n_players; player_idx += 1)
    {
        byte player = players[player_idx];
        tft.setTextSize(1);
        tft.setTextColor(playerColors[player], BLACK);
        tft.setCursor(
            screen.xlo + 40,
            screen.ylo + 10 + player_idx * 10);

        setPlayerName(player);
        tft.print(b_name);
    }

    // Draw game separators
    byte maxWins = GetMaxWins();
    for (byte i = 1; i < n_match; i += 1)
    {
        bool gameChanged = matches[i][Stats::Game] != matches[i - 1][Stats::Game];
        if (gameChanged)
        {
            line.xlo = MAP_X(i, plot, screen);
            line.ylo = MAP_Y(0, plot, screen);
            line.xhi = line.xlo;
            line.yhi = MAP_Y(maxWins, plot, screen);
            tft.drawLine(line.xlo, line.ylo, line.xhi, line.yhi, GREY);
        }
    }

    // Number of wins at each match
    byte graph[match_limit + 1];

    // Draw win graph for each player
    for (byte player_idx = 0; player_idx < n_players; player_idx += 1)
    {
        byte player = players[player_idx];
        unsigned int color = playerColors[player];

        FillPlayerFairWinsGraph(player, graph);
        RenderGraph(player, graph, screen, plot, color, false);

        FillPlayerWinsGraph(player, graph);
        RenderGraph(player, graph, screen, plot, color, true);
    }
}

#endif // TOTALS_H
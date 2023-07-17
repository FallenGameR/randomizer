#ifndef GAME_SELECTION_H
#define GAME_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\print.h"
#include "..\stats.h"
#include "..\games.h"

void GameSelectionScreen()
{
    if (screen_redraw)
    {
        SelectGame(game_index);
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0);
        tft.setTextSize(FONT_SIZE);
        tft.setTextColor(WHITE, BLACK);

        PRINT2_B(setGameName(game_index), tft, Serial);
        Serial.println();

        if (isTagGame)
        {
            tft.println();
            tft.print(F("Tag"));
            Serial.println(F("Tag"));
        }

        screen_redraw = false;
    }

    if (neutral_input)
    {
        if (X_RIGHT)
        {
            game_index = (game_index + n_games + 1) % n_games;
            SelectGame(game_index);
            neutral_input = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            game_index = (game_index + n_games - 1) % n_games;
            SelectGame(game_index);
            neutral_input = false;
            screen_redraw = true;
        }

        if (Y_UP || Y_DOWN)
        {
            if (game_tag > 0)
            {
                isTagGame = !isTagGame;
            }

            neutral_input = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            Serial.print(F("-> Match "));
            Serial.println(match_current + 1);
            screen_selected = Screen::PlayerSelection;
            neutral_input = false;
            screen_redraw = true;
        }
    }
}

#endif // GAME_SELECTION_H
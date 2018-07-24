#ifndef GAME_SELECTION_H
#define GAME_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\memory.h"
#include "..\stats.h"
#include "..\files.h"
#include "..\games\games.h"

void GameSelectionScreen()
{
    if (screen_redraw)
    {
        SelectGame(game_index);
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0);

        TFT_PRINT_GAME(game_index);
        SERIAL_PRINT_LN_GAME(game_index);

        if (isTagGame)
        {
            tft.println();
            tft.print(F("Tag"));
            Serial.println(F("Tag"));
        }

        screen_redraw = false;
    }

    if (input_allowed)
    {
        if (X_RIGHT)
        {
            game_index = (game_index + n_games + 1) % n_games;
            SelectGame(game_index);
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            game_index = (game_index + n_games - 1) % n_games;
            SelectGame(game_index);
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_UP || Y_DOWN)
        {
            if (game_tag > 0)
            {
                isTagGame = !isTagGame;
            }

            input_allowed = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            Serial.print(F("-> Match "));
            Serial.println(match_current + 1);
            screen_selected = Screen::PlayerSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // GAME_SELECTION_H
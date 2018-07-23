#ifndef GAME_ICON_SELECTION_H
#define GAME_ICON_SELECTION_H

#include "..\tft.h"

void GameIconSelectionScreen()
{
    if (screen_redraw)
    {
        game_index = random(n_games);
        isTagGame = random(2);
        fighter_map_selected = fighter_map[game_index];
        n_fighter_map_selected = n_fighter_map[game_index];
        game_tag = readGameTag(game_index);

        tft.fillScreen(BLACK);

        //setupBmp();
        SERIAL_PRINT_LN_GAME(game_index);

        if (game_tag == 0)
        {
            isTagGame = false;
        }

        if (isTagGame)
        {
            /*
            tft.println();
            tft.print(F("Tag"));
            */
            Serial.println(F("Tag"));
        }

        screen_redraw = false;
    }

    if (input_allowed)
    {
        if (X_RIGHT)
        {
            game_index = (game_index + n_games + 1) % n_games;
            screen_selected = Screen::GameSelection;
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            game_index = (game_index + n_games - 1) % n_games;
            screen_selected = Screen::GameSelection;
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_UP || Y_DOWN)
        {
            if (game_tag > 0)
            {
                isTagGame = !isTagGame;
            }

            screen_selected = Screen::GameSelection;
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

#endif // GAME_ICON_SELECTION_H
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
        //games_index = random(n_games);
        //isTagGame = random(2);
        fighter_map_selected = fighter_map[games_index];
        n_fighter_map_selected = n_fighter_map[games_index];
        game_tag = readGameTag(games_index);

        tft.fillScreen(BLACK);
        tft.setCursor(0, 0);

        TFT_PRINT_GAME(games_index);
        SERIAL_PRINT_GAME_LN(games_index);

        if (t_fighter_map_selected == 0)
        {
            isTagGame = false;
        }

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
            games_index = (games_index + n_games + 1) % n_games;
            fighter_map_selected = fighter_map[games_index];
            n_fighter_map_selected = n_fighter_map[games_index];
            game_tag = readGameTag(games_index);
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            games_index = (games_index + n_games - 1) % n_games;
            fighter_map_selected = fighter_map[games_index];
            n_fighter_map_selected = n_fighter_map[games_index];
            game_tag = readGameTag(games_index);
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_UP || Y_DOWN)
        {
            if (t_fighter_map_selected > 0)
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
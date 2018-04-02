#ifndef GAME_SELECTION_H
#define GAME_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\memory.h"
#include "..\stats.h"
#include "..\games\games.h"

void GameSelectionScreen()
{
    if (screen_redraw)
    {
        lcd.clear();
        lcd.setCursor(0, 0);

        LCD_PRINT(games, games_index);
        SERIAL_PRINT_LN(games, games_index);

        if (t_fighter_map_selected == 0)
        {
            isTagGame = false;
        }

        if (isTagGame)
        {
            lcd.setCursor(0, 1);
            lcd.print(F("Tag"));
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
            t_fighter_map_selected = t_fighter_map[games_index];
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            games_index = (games_index + n_games - 1) % n_games;
            fighter_map_selected = fighter_map[games_index];
            n_fighter_map_selected = n_fighter_map[games_index];
            t_fighter_map_selected = t_fighter_map[games_index];
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
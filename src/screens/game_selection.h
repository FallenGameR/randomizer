#ifndef GAME_SELECTION_H
#define GAME_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\games\games.h"

void GameSelectionScreen()
{
    if (screen_redraw)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(games[games_index]);
        Serial.println(games[games_index]);

        screen_redraw = false;
    }

    if (input_allowed)
    {
        if (X_RIGHT)
        {
            games_index = (games_index + n_games + 1) % n_games;
            fighter_map_selected = fighter_map[games_index];
            n_fighter_map_selected = n_fighter_map[games_index];
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            games_index = (games_index + n_games - 1) % n_games;
            fighter_map_selected = fighter_map[games_index];
            n_fighter_map_selected = n_fighter_map[games_index];
            input_allowed = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            Serial.println("-> Match");
            screen_selected = Screen::PlayerSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // GAME_SELECTION_H
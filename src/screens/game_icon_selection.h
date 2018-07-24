#ifndef GAME_ICON_SELECTION_H
#define GAME_ICON_SELECTION_H

#include "..\tft.h"
#include "..\games\games.h"

void GameIconSelectionScreen()
{
    if (screen_redraw)
    {
        game_index = random(n_games);
        isTagGame = random(2);
        SelectGame(game_index);

        tft.fillScreen(WHITE);
        setGamePath(game_index, path_icon);
        bmpDraw(bufferPath, false, 0, 0);

        PRINT_BS(setGameName(game_index));
        Serial.println();

        if (isTagGame)
        {
            tft.setFont(&FreeSerif24pt7b);
            tft.setCursor(340, 180);
            tft.setTextColor(BLACK);
            tft.println(F("tag"));
            tft.setFont();
            tft.setTextColor(WHITE);

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
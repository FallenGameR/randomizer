#ifndef GAME_ICON_SELECTION_H
#define GAME_ICON_SELECTION_H

#include "..\tft.h"
#include "..\games.h"

#define GAMES_START_ROW 3
#define GAMES_SPACING 5

// Update and redraw cursor that moves between selectable settings
void UpdateGameCursorPosition(int movement)
{
    // Find the new index
    size_t new_index = (game_index + movement + n_games) % n_games;

    // Clear previous value
    tft.setCursor(0 * CHAR_WIDTH, GAMES_START_ROW * CHAR_HEIGHT + game_index * (CHAR_HEIGHT + GAMES_SPACING));
    tft.setTextColor(BLACK, BLACK);
    tft.print('>');

    // Set new value
    tft.setCursor(0 * CHAR_WIDTH, GAMES_START_ROW * CHAR_HEIGHT + new_index * (CHAR_HEIGHT + GAMES_SPACING));
    tft.setTextColor(WHITE, BLACK);
    tft.print('>');

    // Update internal state
    game_index = new_index;
}

void GameIconSelectionScreen()
{
    // Full redraw
    if (screen_redraw)
    {
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE, BLACK);
        tft.setTextSize(FONT_SIZE);
        tft.setCursor(0, 0);

        tft.println(F("Games"));
        tft.setTextColor(DK_CYAN, BLACK);
        tft.println(F("-----"));
        tft.setTextColor(WHITE, BLACK);
        tft.println();

        for( int i = 0; i < n_games; i++ )
        {
            tft.print(F("  "));
            PRINT_BT(setGameName(i));
            tft.println();

            int16_t x = tft.getCursorX();
            int16_t y = tft.getCursorY();
            tft.setCursor(x, y + GAMES_SPACING);
        }

        game_index = random(n_games);
        UpdateGameCursorPosition(0);

        /*
        isTagGame = random(2);
        SelectGame(game_index);

        tft.fillScreen(WHITE);
        setGamePath(game_index, path_icon);
        bmpDraw(b_path, false, 0, 0, 1);

        Serial.print(F("Game selected: "));
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
        */

        screen_redraw = false;
    }

    if (input_allowed)
    {
        // Soft reset to do a quick reset
        if (BUTTON_JOYSTICK)
        {
            Serial.println(F("-> Init"));
            screen_selected = Screen::RandomizerInit;
            input_allowed = false;
            screen_redraw = true;
        }

        // Cursor vertical movement
        if (Y_UP || Y_DOWN)
        {
            int direction = Y_UP ? -1 : +1;
            UpdateGameCursorPosition(direction);
            input_allowed = false;
        }

        /*
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
        */

        /*
        if (Y_UP)
        {
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_DOWN)
        {
            if (game_tag > 0)
            {
                isTagGame = !isTagGame;
            }

            screen_selected = Screen::GameSelection;
            input_allowed = false;
            screen_redraw = true;
        }
        */

        if (BUTTON_BLACK)
        {
            Serial.print(F("-> Match "));
            Serial.println(n_match + 1);
            SelectGame(game_index);
            screen_selected = Screen::PlayerSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // GAME_ICON_SELECTION_H
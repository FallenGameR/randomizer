#include <Arduino.h>

#include "..\colors.h"
#include "..\input.h"
#include "..\screens.h"
#include "..\shared.h"
#include "..\stats.h"
#include "..\tft.h"

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
    int16_t halfScreen = tft.width() / 2;

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
            PRINT_BT(readGameName(i));
            tft.println();

            int16_t x = tft.getCursorX();
            int16_t y = tft.getCursorY();
            tft.setCursor(x, y + GAMES_SPACING);
        }

        int saved_index = readSelectedGame();
        Serial.print(F("Restoring game index: "));
        Serial.println(saved_index);
        game_index = saved_index < 0
            ? random(n_games)
            : (saved_index % n_games);
        UpdateGameCursorPosition(0);

        // Draw icon
        setGameRelativePathBuffer(game_index, path_icon);
        bmpDraw(b_path, false, halfScreen, 40, 1, true);

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

            // Draw icon
            tft.fillRect(halfScreen, 0, halfScreen, tft.height(), BLACK);
            setGameRelativePathBuffer(game_index, path_icon);
            bmpDraw(b_path, false, halfScreen, 40, 1, true);
        }

        if (BUTTON_BLACK)
        {
            Serial.print(F("-> Match "));
            Serial.println(n_match + 1);
            selectGame(game_index);
            selectPlayers();
            screen_selected = Screen::FighterSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}
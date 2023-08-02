#ifndef FIGHTER_SELECTION_H
#define FIGHTER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\stats.h"
#include "..\print.h"
#include "..\random.h"
#include "..\fighters.h"
#include "..\totals.h"

void FighterSelectionScreen()
{
    if (screen_redraw)
    {
        // LEDs blink to signal start of new match
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);
        delay(200);
        digitalWrite(pin_led_green, HIGH);
        digitalWrite(pin_led_blue, HIGH);
        delay(200);
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);

        // Fighter init
        fighter_index_first = nextRandom(fighters_left, n_fighters, &fighters_left_position);
        fighter_index_second = nextRandom(fighters_right, n_fighters, &fighters_right_position);
        fighter_index_first2 = NO_FIGHTER;
        fighter_index_second2 = NO_FIGHTER;
        fighter_index_first3 = NO_FIGHTER;
        fighter_index_second3 = NO_FIGHTER;
        byte part = 1;

        if (isTagGame)
        {
            if (game_tag >= 2)
            {
                fighter_index_first2 = nextRandom(fighters_left, n_fighters, &fighters_left_position);
                fighter_index_second2 = nextRandom(fighters_right, n_fighters, &fighters_right_position);
                part = 2;
            }
            if (game_tag >= 3)
            {
                fighter_index_first3 = nextRandom(fighters_left, n_fighters, &fighters_left_position);
                fighter_index_second3 = nextRandom(fighters_right, n_fighters, &fighters_right_position);
                part = 3;
            }
        }

        // TFT clear
        int16_t halfScreen = tft.width() / 2;
        int16_t partIncrement = halfScreen / part;
        int16_t position = 0;
        tft.fillScreen(BLACK);
        tft.setTextSize(FONT_SIZE);
        tft.setTextColor(WHITE, BLACK);

        // First player
        tft.setCursor(0, 0);
        PRINT_BT(readPlayerName(player_index_first));

        // Score
        byte firstWins = countPlayerWins(player_index_first);
        byte charPositions = firstWins < 10 ? 1 : 2;
        tft.setCursor(tft.width() / 2 - CHAR_WIDTH * (charPositions + 0.4), 0);
        tft.setTextColor(DK_GREY, BLACK);
        tft.print(firstWins);
        tft.print(" ");
        tft.print(countPlayerWins(player_index_second));
        tft.setTextColor(WHITE, BLACK);

        // Second player
        char* name = readPlayerName(player_index_second);
        tft.setCursor(tft.width() - strlen(name) * CHAR_WIDTH, 0);
        tft.print(name);

        // TFT and serial fighters
        PRINT(F("Fighters: "), Serial);

        FightersToBufferLine(fighter_index_first, fighter_index_first2, fighter_index_first3);
        tft.setCursor(0, tft.height() - CHAR_HEIGHT * 2 - 2);
        PRINT2(bufferLine, tft, Serial);

        PRINT(F(" vs "), Serial);

        FightersToBufferLine(fighter_index_second, fighter_index_second2, fighter_index_second3);
        tft.setCursor(tft.width() - strlen(bufferLine) * CHAR_WIDTH, tft.height() - CHAR_HEIGHT * 1);
        PRINT2(bufferLine, tft, Serial);

        Serial.println();


        // Portrait draw
        setFighterRelativePathBuffer(game_index, fighter_index_first, path_icon);
        bmpDraw(b_path, false, position, CHAR_HEIGHT, part);
        position += halfScreen;
        setFighterRelativePathBuffer(game_index, fighter_index_second, path_icon);
        bmpDraw(b_path, true, position, CHAR_HEIGHT, part);
        position -= halfScreen;

        if (part >= 2)
        {
            position += partIncrement;
            setFighterRelativePathBuffer(game_index, fighter_index_first2, path_icon);
            bmpDraw(b_path, false, position, CHAR_HEIGHT, part);
            position += halfScreen;
            setFighterRelativePathBuffer(game_index, fighter_index_second2, path_icon);
            bmpDraw(b_path, true, position, CHAR_HEIGHT, part);
            position -= halfScreen;
        }

        if (part >= 3)
        {
            position += partIncrement;
            setFighterRelativePathBuffer(game_index, fighter_index_first3, path_icon);
            bmpDraw(b_path, false, position, CHAR_HEIGHT, part);
            position += halfScreen;
            setFighterRelativePathBuffer(game_index, fighter_index_second3, path_icon);
            bmpDraw(b_path, true, position, CHAR_HEIGHT, part);
            position -= halfScreen;
        }

        // Player differentiator boxes
        tft.drawRect(0, CHAR_HEIGHT, tft.width() / 2, tft.height() - 2 - CHAR_HEIGHT * 3, BLACK);
        tft.drawRect(tft.width() / 2, CHAR_HEIGHT, tft.width() / 2, tft.height() - 2 - CHAR_HEIGHT * 3, BLACK);

        // Internal state init
        winner_selected = Winner::None;
        not_fair_win = false;
        screen_redraw = false;
    }

    // input_allowed means we just were in neutral state and now test for new input that is tested in nested ifs
    if (input_allowed)
    {
        // Black button proceeds to stats
        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Stats"));
            screen_selected = Screen::TotalsShow;
            input_allowed = false;
            screen_redraw = true;
        }

        // Soft reset to do a quick reset
        if (BUTTON_JOYSTICK)
        {
            Serial.println(F("-> Init"));
            screen_selected = Screen::RandomizerInit;
            input_allowed = false;
            screen_redraw = true;
        }

        // After fairness modifier switch disable the input so that we don't keep flipping the modifier
        if (Y_DOWN)
        {
            winner_selected = Winner::None;
            not_fair_win = !not_fair_win;
            input_allowed = false;
        }

        // Draw
        if (Y_UP)
        {
            winner_selected = Winner::Draw;
        }

        // Left won
        if (X_LEFT)
        {
            winner_selected = Winner::First;
        }

        // Right won
        if (X_RIGHT)
        {
            winner_selected = Winner::Second;
        }

        // LEDs show what the input would be on winner finalization
        digitalWrite(pin_led_green, winner_selected != Winner::None);
        digitalWrite(pin_led_blue, not_fair_win);

        // Here is what happens event-wise when we select winner:
        // - joystick selection, this one doesn't specify final win yet (since we may want to cancel this input before completing it)
        //   and it doesn't reset input_allowed, so we need to explicitly check for neutral joystick position later on
        // - neutral joystick position
        if (winner_selected != Winner::None && X_CENTER && Y_CENTER)
        {
            RecordMatchOutcome();

            Serial.print(F("-> Match "));
            Serial.println(n_match + 1);
            screen_selected = Screen::PlayerSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // FIGHTER_SELECTION_H

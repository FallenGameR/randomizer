#ifndef FIGHTER_SELECTION_H
#define FIGHTER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\stats.h"
#include "..\memory.h"
#include "..\random.h"

void FighterSelectionScreen()
{
    if (screen_redraw)
    {
        // Fighter init
        fighter_index_first = random(n_fighter_map_selected);
        fighter_index_second = random(n_fighter_map_selected);
        fighter_index_first2 = NO_FIGHTER;
        fighter_index_second2 = NO_FIGHTER;
        fighter_index_first3 = NO_FIGHTER;
        fighter_index_second3 = NO_FIGHTER;
        if (isTagGame)
        {
            if (game_tag >= 2)
            {
                RANDOM_EX1(n_fighter_map_selected, fighter_index_first2, fighter_index_first);
                RANDOM_EX1(n_fighter_map_selected, fighter_index_second2, fighter_index_second);
            }
            if (game_tag >= 3)
            {
                RANDOM_EX2(n_fighter_map_selected, fighter_index_first3, fighter_index_first, fighter_index_first2);
                RANDOM_EX2(n_fighter_map_selected, fighter_index_second3, fighter_index_second, fighter_index_second2);
            }
        }

        // TFT init
        tft.fillScreen(BLACK);

        // TFT players
        tft.setCursor(0, 0);
        TFT_PRINT_PLAYER(player_index_first);
        tft.setCursor(tft.width() / 2, 0);
        TFT_PRINT_PLAYER(player_index_second);

        // TFT output
        tft.setCursor(0, tft.height() - CHAR_HEIGHT * 2 - 2);
        TFT_PRINT(fighter_map_selected, fighter_index_first);
        TFT_OPTIONAL_FIGHTER(fighter_index_first2);
        TFT_OPTIONAL_FIGHTER(fighter_index_first3);

        int string_length = 0;
        string_length += strlen_P((char *)pgm_read_word(&(fighter_map_selected[fighter_index_second])));
        if (fighter_index_second2 != NO_FIGHTER)
        {
            string_length += strlen_P((char *)pgm_read_word(&(fighter_map_selected[fighter_index_second2])));
        }
        if (fighter_index_second3 != NO_FIGHTER)
        {
            string_length += strlen_P((char *)pgm_read_word(&(fighter_map_selected[fighter_index_second3])));
        }

        tft.setCursor(tft.width() - string_length * CHAR_WIDTH, tft.height() - CHAR_HEIGHT * 1);
        TFT_PRINT(fighter_map_selected, fighter_index_second);
        TFT_OPTIONAL_FIGHTER(fighter_index_second2);
        TFT_OPTIONAL_FIGHTER(fighter_index_second3);

        // Serial output
        SERIAL_PRINT(fighter_map_selected, fighter_index_first);
        SERIAL_OPTIONAL_FIGHTER(fighter_index_first2);
        SERIAL_OPTIONAL_FIGHTER(fighter_index_first3);
        Serial.print(F(" vs "));
        SERIAL_PRINT(fighter_map_selected, fighter_index_second);
        SERIAL_OPTIONAL_FIGHTER(fighter_index_second2);
        SERIAL_OPTIONAL_FIGHTER(fighter_index_second3);
        Serial.println();

        // LEDs blink to signal start of new match
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);
        delay(200);
        digitalWrite(pin_led_green, HIGH);
        digitalWrite(pin_led_blue, HIGH);
        delay(200);
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);

        // Internal state init
        winner_selected = Winner::None;
        not_fair_win = false;
        screen_redraw = false;
    }

    // input_allowed means we just were in neutral state and now test for new input that is tested in nested ifs
    if (input_allowed)
    {
        // Black button returns to games selection without chosing of winner
        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Game"));
            screen_selected = Screen::GameSelection;
            input_allowed = false;
            screen_redraw = true;
        }

        // Joystick button prints the current stats and resets screen
        if (BUTTON_JOYSTICK)
        {
            /*
            // Reset screen since sometimes on a loose connection it gets into weird state
            //tft. (16, 2);
            TFT_FIGHTERS(fighter_index_first, fighter_index_second);
            time_of_last_redraw = now;
            fighter_pair_shown = 0;
            */

            // Print stats to console
            Serial.println(F("-> Stats"));
            DumpStats();
            input_allowed = false;
        }

        // After fairness modifier switch disable the input so that we don't keep flipping the modifier
        if (Y_DOWN)
        {
            not_fair_win = !not_fair_win;
            input_allowed = false;
        }

        // Here is what happens event-wise when we select winner:
        // - joystick selection, this one doesn't specify final win yet (since we may want to cancel this input before completing it)
        //   and it doesn't reset input_allowed, so we need to explicitly check for neutral joystick position later on
        // - neutral joystick position
        if (winner_selected != Winner::None && X_CENTER && Y_CENTER)
        {
            RecordMatchOutcome();

            Serial.print(F("-> Match "));
            Serial.println(match_current + 1);
            screen_selected = Screen::PlayerSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }

    // Note that win selection don't reset input_allowed to allow
    // for choise change without resetting joystick postion to neutral
    if (Y_DOWN)
    {
        winner_selected = Winner::None;
    }

    if (Y_UP)
    {
        winner_selected = Winner::Draw;
    }

    if (X_LEFT)
    {
        winner_selected = Winner::First;
    }

    if (X_RIGHT)
    {
        winner_selected = Winner::Second;
    }

    // LEDs show what the input would be on winner finalization
    digitalWrite(pin_led_green, winner_selected != Winner::None);
    digitalWrite(pin_led_blue, not_fair_win);
}

#endif // PLAYER_SELECTION_H

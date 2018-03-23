#ifndef FIGHTER_SELECTION_H
#define FIGHTER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\stats.h"
#include "..\memory.h"

void FighterSelectionScreen()
{
    if (screen_redraw)
    {
        fighter_index_first = random(n_fighter_map_selected);
        fighter_index_second = random(n_fighter_map_selected);
        winner_selected = Winner::None;
        not_fair_win = false;

        lcd.clear();
        lcd.setCursor(0, 0);
        LCD_PRINT(fighter_map_selected, fighter_index_first);
        lcd.setCursor(0, 1);
        LCD_PRINT(fighter_map_selected, fighter_index_second);

        SERIAL_PRINT(fighter_map_selected, fighter_index_first);
        Serial.print(F(" vs "));
        SERIAL_PRINT(fighter_map_selected, fighter_index_second);
        Serial.println();

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

        // Joystick button prints the current stats
        if (BUTTON_JOYSTICK)
        {
            Serial.println(F("[Stats]"));
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

            Serial.println(F("-> Match"));
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

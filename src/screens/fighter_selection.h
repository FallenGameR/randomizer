#ifndef FIGHTER_SELECTION_H
#define FIGHTER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\stats.h"
#include "..\memory.h"

unsigned long time_of_last_redraw;
byte fighter_pair_shown;

void FighterSelectionScreen()
{
    if (screen_redraw)
    {
        fighter_index_first = random(n_fighter_map_selected);
        fighter_index_second = random(n_fighter_map_selected);
        fighter_index_first2 = -1;
        fighter_index_second2 = -1;
        fighter_index_first3 = -1;
        fighter_index_second3 = -1;
        if (isTagGame)
        {
            if (t_fighter_map_selected <= 2)
            {
                do
                {
                    fighter_index_first2 = random(n_fighter_map_selected);
                } while (fighter_index_first2 == fighter_index_first);

                do
                {
                    fighter_index_second2 = random(n_fighter_map_selected);
                } while (fighter_index_second2 == fighter_index_second);
            }
            if (t_fighter_map_selected <= 3)
            {
                do
                {
                    fighter_index_first3 = random(n_fighter_map_selected);
                } while ((fighter_index_first3 == fighter_index_first) || (fighter_index_first3 == fighter_index_first2));

                do
                {
                    fighter_index_second3 = random(n_fighter_map_selected);
                } while ((fighter_index_second3 == fighter_index_second) || (fighter_index_second3 == fighter_index_second2));
            }
        }
        winner_selected = Winner::None;
        not_fair_win = false;

        lcd.clear();
        lcd.setCursor(0, 0);
        LCD_PRINT(fighter_map_selected, fighter_index_first);
        lcd.setCursor(0, 1);
        LCD_PRINT(fighter_map_selected, fighter_index_second);

        SERIAL_PRINT(fighter_map_selected, fighter_index_first);
        if (fighter_index_first2 >= 0)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_first2);
        }
        if (fighter_index_first3 >= 0)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_first3);
        }
        Serial.print(F(" vs "));
        SERIAL_PRINT(fighter_map_selected, fighter_index_second);
        if (fighter_index_second2 >= 0)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_second2);
        }
        if (fighter_index_second3 >= 0)
        {
            Serial.print(F(", "));
            SERIAL_PRINT(fighter_map_selected, fighter_index_second3);
        }
        Serial.println();

        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);
        delay(200);
        digitalWrite(pin_led_green, HIGH);
        digitalWrite(pin_led_blue, HIGH);
        delay(200);
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);

        screen_redraw = false;
        time_of_last_redraw = now;
        fighter_pair_shown = 0;
    }

    // tag fighters cycling
    unsigned long elapsed = now - time_of_last_redraw;
    if (isTagGame && (elapsed > 500))
    {
        fighter_pair_shown += 1;
        fighter_pair_shown %= t_fighter_map_selected;
        lcd.clear();

        switch (fighter_pair_shown)
        {
        case 0:
            lcd.setCursor(0, 0);
            LCD_PRINT(fighter_map_selected, fighter_index_first);
            lcd.setCursor(0, 1);
            LCD_PRINT(fighter_map_selected, fighter_index_second);
            break;

        case 1:
            lcd.setCursor(0, 0);
            LCD_PRINT(fighter_map_selected, fighter_index_first2);
            lcd.setCursor(0, 1);
            LCD_PRINT(fighter_map_selected, fighter_index_second2);
            break;

        case 2:
            lcd.setCursor(0, 0);
            LCD_PRINT(fighter_map_selected, fighter_index_first3);
            lcd.setCursor(0, 1);
            LCD_PRINT(fighter_map_selected, fighter_index_second3);
            break;
        }

        time_of_last_redraw = now;
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
            // Reset screen since sometimes on a loose connection it gets into weird state
            lcd.begin(16, 2);
            lcd.clear();
            lcd.setCursor(0, 0);
            LCD_PRINT(fighter_map_selected, fighter_index_first);
            lcd.setCursor(0, 1);
            LCD_PRINT(fighter_map_selected, fighter_index_second);

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

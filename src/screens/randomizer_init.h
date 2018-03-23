#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"

bool partial_redraw = false;

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Randomizer "));
        lcd.setCursor(0, 1);
        lcd.print(F("S "));
        lcd.print(random_seed);
        lcd.print(F(" F "));
        lcd.print(random_fairness);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        screen_redraw = false;
    }

    if (partial_redraw)
    {
        lcd.setCursor(0, 1);
        lcd.print(F("                "));

        lcd.setCursor(0, 1);
        lcd.print(F("S "));
        lcd.print(random_seed);
        lcd.print(F(" F "));
        lcd.print(random_fairness);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        partial_redraw = false;
    }

    if (input_allowed)
    {
        if (Y_UP)
        {
            random_fairness = random_fairness + n_players;
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_DOWN)
        {
            random_fairness = random_fairness - n_players;
            input_allowed = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Game"));
            screen_selected = Screen::GameSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }

    // Seed should be possible to change quickly thus we
    // don't needfor joystick to return to the neutral position
    if (X_RIGHT)
    {
        random_seed++;
        input_allowed = false;
        partial_redraw = true;
    }

    if (X_LEFT)
    {
        random_seed--;
        input_allowed = false;
        partial_redraw = true;
    }
}

#endif // RANDOMIZER_INIT_H
#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Randomizer ");
        lcd.setCursor(0, 1);
        lcd.print("S ");
        lcd.print(random_seed);
        lcd.print(" F ");
        lcd.print(random_fairness);

        Serial.print("Seed = ");
        Serial.println(random_seed);
        Serial.print("Fairness = ");
        Serial.println(random_fairness);

        screen_redraw = false;
    }

    if (input_allowed)
    {
        if (X_RIGHT)
        {
            random_fairness = random_fairness + n_players;
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            random_fairness = random_fairness - n_players;
            input_allowed = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            Serial.println("-> Game");
            screen_selected = Screen::GameSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // RANDOMIZER_INIT_H
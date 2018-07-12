#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"

bool partial_redraw_seed = false;
bool partial_redraw_fairness = false;

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0);
        tft.println(F("Randomizer "));

        tft.print(F("S "));
        tft.println(random_seed);
        tft.print(F("F "));
        tft.println(random_fairness);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        screen_redraw = false;
    }

    if (partial_redraw_seed)
    {
        tft.setCursor(6 * 2 * FONT_SIZE, 8 * 1 * FONT_SIZE);
        tft.print(F("                "));
        tft.setCursor(6 * 2 * FONT_SIZE, 8 * 1 * FONT_SIZE);
        tft.print(random_seed);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);

        partial_redraw_seed = false;
    }

    if (partial_redraw_fairness)
    {
        tft.setCursor(6 * 2 * FONT_SIZE, 8 * 2 * FONT_SIZE);
        tft.print(F("                "));
        tft.setCursor(6 * 2 * FONT_SIZE, 8 * 2 * FONT_SIZE);
        tft.print(random_fairness);

        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        partial_redraw_fairness = false;
    }

    if (input_allowed)
    {
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
        partial_redraw_seed = true;
    }

    if (X_LEFT)
    {
        random_seed--;
        input_allowed = false;
        partial_redraw_seed = true;
    }

    if (Y_UP)
    {
        random_fairness = random_fairness + n_players;
        input_allowed = false;
        partial_redraw_fairness = true;
    }

    if (Y_DOWN)
    {
        random_fairness = random_fairness - n_players;
        input_allowed = false;
        partial_redraw_fairness = true;
    }
}

#endif // RANDOMIZER_INIT_H
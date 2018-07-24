#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"
#include "..\stats.h"

bool partial_redraw_seed = false;
bool partial_redraw_fairness = false;

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0);
        tft.println(F("Randomizer "));

        tft.print(F("Seed ")); // 5 chars, row 1
        tft.println(random_seed);
        tft.print(F("Fair ")); // 5 chars, row 2
        tft.println(random_fairness);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        screen_redraw = false;
    }

    if (partial_redraw_seed)
    {
        tft.setCursor(5 * CHAR_WIDTH, 1 * CHAR_HEIGHT);
        tft.print(F("                "));
        tft.setCursor(5 * CHAR_WIDTH, 1 * CHAR_HEIGHT);
        tft.print(random_seed);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);

        partial_redraw_seed = false;
    }

    if (partial_redraw_fairness)
    {
        tft.setCursor(5 * CHAR_WIDTH, 2 * CHAR_HEIGHT);
        tft.print(F("                "));
        tft.setCursor(5 * CHAR_WIDTH, 2 * CHAR_HEIGHT);
        tft.print(random_fairness);

        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        partial_redraw_fairness = false;
    }

    if (input_allowed)
    {
        if (BUTTON_BLACK)
        {
            InitPlayerPairs();
            InitStatsFile();

            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_UP)
        {
            int multiplier = random_fairness_multiplier;
            if ((multiplier + 1) * random_fairness_divider <= 255)
            {
                random_fairness_multiplier += 1;
            }
            random_fairness = random_fairness_divider * random_fairness_multiplier;
            input_allowed = false;
            partial_redraw_fairness = true;
        }

        if (Y_DOWN)
        {
            if (random_fairness_multiplier > 1)
            {
                random_fairness_multiplier -= 1;
            }
            random_fairness = random_fairness_divider * random_fairness_multiplier;
            input_allowed = false;
            partial_redraw_fairness = true;
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
}

#endif // RANDOMIZER_INIT_H
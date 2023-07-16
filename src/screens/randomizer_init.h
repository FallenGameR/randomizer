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
int previous_seed = 0;
int previous_fair = 0;

#define SET_POSITION_SEED_VALUE tft.setCursor(9 * CHAR_WIDTH, 4 * CHAR_HEIGHT);
#define SET_POSITION_FAIR_VALUE tft.setCursor(9 * CHAR_WIDTH, 5 * CHAR_HEIGHT);

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0);

        tft.println(F("Randomizer"));
        tft.println(F("=========="));
        tft.println();

        tft.print(F("  Games: "));
        tft.println(n_games);
        tft.print(F("> Seed:  "));
        tft.println(random_seed);
        previous_seed = random_seed;
        tft.print(F("  Fair:  "));
        tft.println(random_fairness);
        previous_fair = random_fairness;
        tft.println();

        tft.println(F("Players"));
        tft.println(F("-------"));
        tft.println();

        //tft.setTextSize(FONT_SIZE);
        //tft.setTextColor(WHITE, BLACK);

        PRINT_BT(setPlayerName(player_index_second));
        for (int i = 0; i < n_players; i++)
        {
            tft.print(F("  * "));
            PRINT_BT(setPlayerName(i));
            tft.println();
        }

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        screen_redraw = false;
    }

    if (partial_redraw_seed)
    {
        SET_POSITION_SEED_VALUE;
        tft.setTextColor(BLACK, BLACK);
        tft.print(previous_seed);
        tft.setTextColor(WHITE, BLACK);
        SET_POSITION_SEED_VALUE;
        tft.print(random_seed);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);

        previous_seed = random_seed;
        partial_redraw_seed = false;
    }

    if (partial_redraw_fairness)
    {
        SET_POSITION_FAIR_VALUE;
        tft.print(F("                "));
        SET_POSITION_FAIR_VALUE;
        tft.print(random_fairness);

        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        previous_fair = random_fairness;
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
    // don't need for joystick to return to the neutral position
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
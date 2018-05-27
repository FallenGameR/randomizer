#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"

bool partial_redraw = false;
int16_t redrawn_line_x = 0;
int16_t redrawn_line_y = 0;

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(0, 0);
        tft.println(F("Randomizer "));
        redrawn_line_x = tft.getCursorX();
        redrawn_line_y = tft.getCursorY();

        tft.print(F("S "));
        tft.print(random_seed);
        tft.print(F(" F "));
        tft.println(random_fairness);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        screen_redraw = false;
    }

    if (partial_redraw)
    {
        tft.setCursor(redrawn_line_x, redrawn_line_y);
        tft.print(F("                "));

        tft.setCursor(redrawn_line_x, redrawn_line_y);
        tft.print(F("S "));
        tft.print(random_seed);
        tft.print(F(" F "));
        tft.println(random_fairness);

        Serial.print(F("Seed = "));
        Serial.println(random_seed);
        Serial.print(F("Fairness = "));
        Serial.println(random_fairness);

        partial_redraw = false;
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
        partial_redraw = true;
    }

    if (X_LEFT)
    {
        random_seed--;
        input_allowed = false;
        partial_redraw = true;
    }

    if (Y_UP)
    {
        random_fairness = random_fairness + n_players;
        input_allowed = false;
        partial_redraw = true;
    }

    if (Y_DOWN)
    {
        random_fairness = random_fairness - n_players;
        input_allowed = false;
        partial_redraw = true;
    }
}

#endif // RANDOMIZER_INIT_H
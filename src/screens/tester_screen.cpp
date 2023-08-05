#include "tester_screen.h"

#include "..\screens.h"
#include "..\totals.h"
#include "..\random.h"
#include "..\input.h"

void MockRecordMatchOutcome()
{
    n_match = 0;

    for (int match = 0; match < 21; match += 1)
    {
        matches[n_match][Stats::FirstPlayer] = random(3);
        matches[n_match][Stats::SecondPlayer] = random(3);
        matches[n_match][Stats::Game] = 0;
        matches[n_match][Stats::FirstFighter] = 0;
        matches[n_match][Stats::SecondFighter] = 0;
        matches[n_match][Stats::FirstFighter2] = 0;
        matches[n_match][Stats::SecondFighter2] = 0;
        matches[n_match][Stats::FirstFighter3] = 0;
        matches[n_match][Stats::SecondFighter3] = 0;
        matches[n_match][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[n_match][Stats::NotFair] = false;
        n_match++;
    }

    for (int match = 21; match < 31; match += 1)
    {
        matches[n_match][Stats::FirstPlayer] = random(3);
        matches[n_match][Stats::SecondPlayer] = random(3);
        matches[n_match][Stats::Game] = 1;
        matches[n_match][Stats::FirstFighter] = 0;
        matches[n_match][Stats::SecondFighter] = 0;
        matches[n_match][Stats::FirstFighter2] = 0;
        matches[n_match][Stats::SecondFighter2] = 0;
        matches[n_match][Stats::FirstFighter3] = 0;
        matches[n_match][Stats::SecondFighter3] = 0;
        matches[n_match][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[n_match][Stats::NotFair] = false;
        n_match++;
    }

    for (int match = 31; match < 41; match += 1)
    {
        matches[n_match][Stats::FirstPlayer] = random(3);
        matches[n_match][Stats::SecondPlayer] = random(3);
        matches[n_match][Stats::Game] = 2;
        matches[n_match][Stats::FirstFighter] = 0;
        matches[n_match][Stats::SecondFighter] = 0;
        matches[n_match][Stats::FirstFighter2] = 0;
        matches[n_match][Stats::SecondFighter2] = 0;
        matches[n_match][Stats::FirstFighter3] = 0;
        matches[n_match][Stats::SecondFighter3] = 0;
        matches[n_match][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[n_match][Stats::NotFair] = false;
        n_match++;
    }
}

void TesterScreen()
{
    if (screen_redraw)
    {
        // reinit and redraw all
    }

    if (input_allowed)
    {
        if (X_RIGHT)
        {
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_UP || Y_DOWN)
        {
            input_allowed = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            SelectPlayers();
            screen_selected = Screen::FighterSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}
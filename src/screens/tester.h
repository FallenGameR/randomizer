#ifndef TESTER_H
#define TESTER_H

#include "screens.h"
#include "..\totals.h"
#include "..\random.h"

void MockRecordMatchOutcome()
{
    match_current = 0;

    for (int match = 0; match < 21; match += 1)
    {
        matches[match_current][Stats::FirstPlayer] = random(3);
        matches[match_current][Stats::SecondPlayer] = random(3);
        matches[match_current][Stats::Game] = 0;
        matches[match_current][Stats::FirstFighter] = 0;
        matches[match_current][Stats::SecondFighter] = 0;
        matches[match_current][Stats::FirstFighter2] = 0;
        matches[match_current][Stats::SecondFighter2] = 0;
        matches[match_current][Stats::FirstFighter3] = 0;
        matches[match_current][Stats::SecondFighter3] = 0;
        matches[match_current][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[match_current][Stats::NotFair] = false;
        match_current++;
    }

    for (int match = 21; match < 31; match += 1)
    {
        matches[match_current][Stats::FirstPlayer] = random(3);
        matches[match_current][Stats::SecondPlayer] = random(3);
        matches[match_current][Stats::Game] = 1;
        matches[match_current][Stats::FirstFighter] = 0;
        matches[match_current][Stats::SecondFighter] = 0;
        matches[match_current][Stats::FirstFighter2] = 0;
        matches[match_current][Stats::SecondFighter2] = 0;
        matches[match_current][Stats::FirstFighter3] = 0;
        matches[match_current][Stats::SecondFighter3] = 0;
        matches[match_current][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[match_current][Stats::NotFair] = false;
        match_current++;
    }

    for (int match = 31; match < 41; match += 1)
    {
        matches[match_current][Stats::FirstPlayer] = random(3);
        matches[match_current][Stats::SecondPlayer] = random(3);
        matches[match_current][Stats::Game] = 2;
        matches[match_current][Stats::FirstFighter] = 0;
        matches[match_current][Stats::SecondFighter] = 0;
        matches[match_current][Stats::FirstFighter2] = 0;
        matches[match_current][Stats::SecondFighter2] = 0;
        matches[match_current][Stats::FirstFighter3] = 0;
        matches[match_current][Stats::SecondFighter3] = 0;
        matches[match_current][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[match_current][Stats::NotFair] = false;
        match_current++;
    }
}

void TesterScreen()
{
    // MockRecordMatchOutcome();
    // RenderTotals();
    // delay(60000);

    if (screen_redraw)
    {
        //game_index = 1;
        SelectGame(game_index);
        //isTagGame = true;

        tft.fillScreen(GREEN);
        tft.setCursor(0, 0);
        tft.setTextSize(FONT_SIZE);
        tft.setTextColor(WHITE, BLACK);

        PRINT2_B(setGameName(game_index), tft, Serial);
        Serial.println();

        if (isTagGame)
        {
            tft.println();
            tft.print(F("Tag"));
            Serial.println(F("Tag"));
        }

        screen_redraw = false;
    }

    if (input_allowed)
    {
        if (X_RIGHT)
        {
            game_index = (game_index + n_games + 1) % n_games;
            SelectGame(game_index);
            input_allowed = false;
            screen_redraw = true;
        }

        if (X_LEFT)
        {
            game_index = (game_index + n_games - 1) % n_games;
            SelectGame(game_index);
            input_allowed = false;
            screen_redraw = true;
        }

        if (Y_UP || Y_DOWN)
        {
            if (game_tag > 0)
            {
                isTagGame = !isTagGame;
            }

            input_allowed = false;
            screen_redraw = true;
        }

        if (BUTTON_BLACK)
        {
            Serial.print(F("-> Match "));
            Serial.println(match_current + 1);
            screen_selected = Screen::PlayerSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // TESTER_H
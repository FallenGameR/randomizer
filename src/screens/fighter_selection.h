#ifndef FIGHTER_SELECTION_H
#define FIGHTER_SELECTION_H

#include "screens.h"
#include "..\input.h"
#include "..\stats.h"
#include "..\print.h"
#include "..\random.h"
#include "..\fighters.h"

void FighterSelectionScreen()
{
    if (screen_redraw)
    {
        // Fighter init
        fighter_index_first = nextRandom(fighters_left, n_fighters, &fighters_left_position);
        fighter_index_second = nextRandom(fighters_right, n_fighters, &fighters_right_position);
        fighter_index_first2 = NO_FIGHTER;
        fighter_index_second2 = NO_FIGHTER;
        fighter_index_first3 = NO_FIGHTER;
        fighter_index_second3 = NO_FIGHTER;
        byte part = 1;

        if (isTagGame)
        {
            if (game_tag >= 2)
            {
                fighter_index_first2 = nextRandom(fighters_left, n_fighters, &fighters_left_position);
                fighter_index_second2 = nextRandom(fighters_right, n_fighters, &fighters_right_position);
                part = 2;
            }
            if (game_tag >= 3)
            {
                fighter_index_first3 = nextRandom(fighters_left, n_fighters, &fighters_left_position);
                fighter_index_second3 = nextRandom(fighters_right, n_fighters, &fighters_right_position);
                part = 3;
            }
        }

        // TFT clear
        int16_t halfScreen = tft.width() / 2;
        int16_t partIncrement = halfScreen / part;
        int16_t position = 0;
        tft.fillScreen(BLACK);
        tft.setTextSize(FONT_SIZE);
        tft.setTextColor(WHITE, BLACK);

        // TFT players
        tft.setCursor(0, 0);
        PRINT_BT(setPlayerName(player_index_first));

        tft.setCursor(tft.width() / 2, 0);
        PRINT_BT(setPlayerName(player_index_second));

        // TFT and serial fighters
        FightersToBufferLine(fighter_index_first, fighter_index_first2, fighter_index_first3);
        tft.setCursor(0, tft.height() - CHAR_HEIGHT * 2 - 2);
        PRINT2(bufferLine, tft, Serial);

        PRINT(F(" vs "), Serial);

        FightersToBufferLine(fighter_index_second, fighter_index_second2, fighter_index_second3);
        tft.setCursor(tft.width() - strlen(bufferLine) * CHAR_WIDTH, tft.height() - CHAR_HEIGHT * 1);
        PRINT2(bufferLine, tft, Serial);

        Serial.println();

        // LEDs blink to signal start of new match
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);
        delay(200);
        digitalWrite(pin_led_green, HIGH);
        digitalWrite(pin_led_blue, HIGH);
        delay(200);
        digitalWrite(pin_led_green, LOW);
        digitalWrite(pin_led_blue, LOW);

        // Portrait draw
        setFighterPath(game_index, fighter_index_first, path_icon);
        bmpDraw(bufferPath, false, position, CHAR_HEIGHT, part);
        position += halfScreen;
        setFighterPath(game_index, fighter_index_second, path_icon);
        bmpDraw(bufferPath, true, position, CHAR_HEIGHT, part);
        position -= halfScreen;

        if (part >= 2)
        {
            position += partIncrement;
            setFighterPath(game_index, fighter_index_first2, path_icon);
            bmpDraw(bufferPath, false, position, CHAR_HEIGHT, part);
            position += halfScreen;
            setFighterPath(game_index, fighter_index_second2, path_icon);
            bmpDraw(bufferPath, true, position, CHAR_HEIGHT, part);
            position -= halfScreen;
        }

        if (part >= 3)
        {
            position += partIncrement;
            setFighterPath(game_index, fighter_index_first3, path_icon);
            bmpDraw(bufferPath, false, position, CHAR_HEIGHT, part);
            position += halfScreen;
            setFighterPath(game_index, fighter_index_second3, path_icon);
            bmpDraw(bufferPath, true, position, CHAR_HEIGHT, part);
            position -= halfScreen;
        }

        // Player differentiator boxes
        tft.drawRect(0, CHAR_HEIGHT, tft.width() / 2, tft.height() - 2 - CHAR_HEIGHT * 3, BLACK);
        tft.drawRect(tft.width() / 2, CHAR_HEIGHT, tft.width() / 2, tft.height() - 2 - CHAR_HEIGHT * 3, BLACK);

        // Internal state init
        winner_selected = Winner::None;
        not_fair_win = false;
        screen_redraw = false;
    }

    // neutral_input means we just were in neutral state and now test for new input that is tested in nested ifs
    if (neutral_input)
    {
        // Black button returns to games selection without choosing of winner
        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            neutral_input = false;
            screen_redraw = true;
        }

        // Joystick button goes to the current stats screen
        if (BUTTON_JOYSTICK)
        {
            Serial.println(F("-> Stats"));
            screen_selected = Screen::TotalsShow;
            neutral_input = false;
            screen_redraw = true;
        }

        // After fairness modifier switch disable the input so that we don't keep flipping the modifier
        if (Y_DOWN)
        {
            not_fair_win = !not_fair_win;
            neutral_input = false;
        }

        // Here is what happens event-wise when we select winner:
        // - joystick selection, this one doesn't specify final win yet (since we may want to cancel this input before completing it)
        //   and it doesn't reset neutral_input, so we need to explicitly check for neutral joystick position later on
        // - neutral joystick position
        if (winner_selected != Winner::None && X_CENTER && Y_CENTER)
        {
            RecordMatchOutcome();

            Serial.print(F("-> Match "));
            Serial.println(match_current + 1);
            screen_selected = Screen::PlayerSelection;
            neutral_input = false;
            screen_redraw = true;
        }
    }

    // Note that win selection don't reset neutral_input to allow
    // for choice change without resetting joystick postion to neutral
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

#endif // FIGHTER_SELECTION_H

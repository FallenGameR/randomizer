#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"
#include "..\stats.h"

// Structure that describes entry that can be edited on the screen
struct init_entry
{
    // Row on screen, starts with 0 from top
    int16_t row;

    // Column on screen, starts with 0 from left
    int16_t col;

    // Can this row be selected for edit
    bool is_selectable;

    // Should this entry be redrawn
    bool is_redraw_needed;

    // Currently displayed value, how exactly to
    // render it depends on the data it represents
    int value;
};

// Table of editable entries on the screen
struct init_entry init_entries[] = {
    // r  c  selectable redraw value
    {  3, 9, false,     true,  0 }, // Games
    {  4, 9, true,      true,  0 }, // Seed
    {  5, 9, true,      true,  0 }, // Fair
    { 10, 0, false,     false, 0 }, // Player 0
    { 11, 0, false,     false, 0 }, // Player 1
    { 12, 0, false,     false, 0 }, // Player 2
    { 13, 0, false,     false, 0 }, // Player 3
    { 14, 0, false,     false, 0 }, // Player 4
    { 15, 0, false,     false, 0 }, // Player 5
    { 16, 0, false,     false, 0 }, // Player 6
    { 17, 0, false,     false, 0 }, // Player 7
    { 18, 0, false,     false, 0 }, // Player 8
    { 19, 0, false,     false, 0 }, // Player 9
};

// Indexes of various entries in the table
#define IE_GAMES_IDX 0
#define IE_SEED_IDX 1
#define IE_FAIR_IDX 2
#define IE_PLAY_IDX 3
#define IE_PLAY_MAX 10

// Table length
#define IE_LENGTH 13

// Draw games value or error when games could not be read from SD card
void InitDrawGamesValue(int new_value)
{
    init_entry* entry = &init_entries[IE_GAMES_IDX];
    if( entry->value != new_value ) { entry->is_redraw_needed = true; }
    if( !entry->is_redraw_needed ) { return; }

    // Clear previous value
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(BLACK, BLACK);
    if( entry->value != 0 )
    {
        tft.print(entry->value);
    }
    else
    {
        // Erasing "SD card error" that is hard to place into PROGMEM
        for( size_t i = 0; i < 13; i++ )
        {
            tft.print(' ');
        }
    }

    // Set new value
    Serial.print(F("Games: "));
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(WHITE, BLACK);
    if( new_value != 0 )
    {
        tft.println(new_value);
        Serial.println(new_value);
    }
    else
    {
        tft.print(F("SD card error"));
        Serial.println(F("SD card error"));
    }

    // Update internal state
    entry->value = new_value;
    entry->is_redraw_needed = false;
}

// Draw an integer value
void InitDrawIntValue(size_t index, int new_value, const __FlashStringHelper *serial_title)
{
    init_entry* entry = &init_entries[index];
    if( entry->value != new_value ) { entry->is_redraw_needed = true; }
    if( !entry->is_redraw_needed ) { return; }

    // Clear previous value
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(BLACK, BLACK);
    tft.print(entry->value);

    // Set new value
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(WHITE, BLACK);
    tft.println(new_value);

    // Dump to serial
    Serial.print(serial_title);
    Serial.println(new_value);

    // Update internal state
    entry->value = new_value;
    entry->is_redraw_needed = false;
}

void RandomizerInitScreen()
{
    init_entry* entry = nullptr;

    if (screen_redraw)
    {
        tft.fillScreen(BLACK);

        // init players here as well

        tft.setCursor(0, 0);

        tft.println(F("Randomizer"));
        tft.println(F("=========="));
        tft.println();

        tft.print(F("  Games: "));
        InitDrawGamesValue(n_games);

        tft.print(F("> Seed:  "));
        InitDrawIntValue(IE_SEED_IDX, random_seed, F("Seed: "));

        tft.print(F("  Fair:  "));
        InitDrawIntValue(IE_FAIR_IDX, random_fairness, F("Fair: "));

        tft.println(F("Players"));
        tft.println(F("-------"));
        tft.println();

        for (int i = 0; i < n_players; i++)
        {
            tft.print(F("  # "));
            PRINT_BT(setPlayerName(i));
            tft.println();
        }

        screen_redraw = false;
    }

    entry = &init_entries[IE_SEED_IDX];
    if( entry->is_redraw_needed )
    {
        InitDrawIntValue(IE_SEED_IDX, random_seed, F("Seed: "));
        entry->is_redraw_needed = false;
    }

    entry = &init_entries[IE_FAIR_IDX];
    if( entry->is_redraw_needed )
    {
        InitDrawIntValue(IE_FAIR_IDX, random_fairness, F("Fair: "));
        entry->is_redraw_needed = false;
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

        entry = &init_entries[IE_FAIR_IDX];

        if (Y_UP)
        {
            int multiplier = random_fairness_multiplier;
            if ((multiplier + 1) * random_fairness_divider <= 255)
            {
                random_fairness_multiplier += 1;
            }
            random_fairness = random_fairness_divider * random_fairness_multiplier;
            input_allowed = false;
            entry->is_redraw_needed = true;
        }

        if (Y_DOWN)
        {
            if (random_fairness_multiplier > 1)
            {
                random_fairness_multiplier -= 1;
            }
            random_fairness = random_fairness_divider * random_fairness_multiplier;
            input_allowed = false;
            entry->is_redraw_needed = true;
        }
    }

    // Seed should be possible to change quickly thus we
    // don't need for joystick to return to the neutral
    // position and thus don't wait for the input_allowed

    entry = &init_entries[IE_SEED_IDX];

    if (X_RIGHT)
    {
        random_seed++;
        input_allowed = false;
        entry->is_redraw_needed = true;
    }

    if (X_LEFT)
    {
        random_seed--;
        input_allowed = false;
        entry->is_redraw_needed = true;
    }
}

#endif // RANDOMIZER_INIT_H
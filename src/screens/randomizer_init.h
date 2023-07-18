#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"
#include "..\stats.h"

size_t cursor_index = 0;

// Structure that describes entry that can be edited on the screen
struct init_entry
{
    // Row on screen, starts with 0 from top
    int16_t row;

    // Column on screen, starts with 0 from left
    int16_t col;

    // Can this row be selected for edit
    bool is_selectable;

    // Currently displayed value, how exactly to
    // render it depends on the data it represents
    int value;
};

// Table of editable entries on the screen
struct init_entry init_entries[] = {
    // r, c, sel,   val
    {  3, 9, false, 0 }, // Games
    {  4, 9, true,  0 }, // Seed
    {  5, 9, true,  0 }, // Fair
    { 10, 0, false, 0 }, // Player 0
    { 11, 0, false, 0 }, // Player 1
    { 12, 0, false, 0 }, // Player 2
    { 13, 0, false, 0 }, // Player 3
    { 14, 0, false, 0 }, // Player 4
    { 15, 0, false, 0 }, // Player 5
    { 16, 0, false, 0 }, // Player 6
    { 17, 0, false, 0 }, // Player 7
    { 18, 0, false, 0 }, // Player 8
    { 19, 0, false, 0 }, // Player 9
};

// Indexes of various entries in the table
#define IE_GAMES_IDX 0
#define IE_SEED_IDX 1
#define IE_FAIR_IDX 2
#define IE_PLAY_IDX 3
#define IE_PLAY_MAX MAX_PLAYERS

// Table length
#define IE_LENGTH 13

bool player_bool[MAX_PLAYERS] = { true, true, false, false, false, false, false, false, false, false };

// Redraw games value or error when games could not be read from SD card
void InitDrawGamesValue(int new_value)
{
    init_entry* entry = &init_entries[IE_GAMES_IDX];

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
        tft.println(F("SD card error"));
        Serial.println(F("SD card error"));
    }

    // Update internal state
    entry->value = new_value;
}

// Redraw an integer value
void InitRedrawIntValue(size_t index, int direction, const __FlashStringHelper *serial_title)
{
    // Find the new value
    init_entry* entry = &init_entries[index];
    int new_value = entry->value + direction;

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
}

// Redraw cursor
void InitRedrawCursor(int direction)
{
    // Check if redraw is needed
    if( direction == 0 ) { return; }

    // Find the new index
    size_t new_index = cursor_index;
    init_entry* new_entry;
    do
    {
        new_index = (new_index + direction + IE_LENGTH) % IE_LENGTH;
        new_entry = &init_entries[new_index];
    }
    while( !new_entry->is_selectable );

    // Clear previous value
    init_entry* old_entry = &init_entries[cursor_index];
    tft.setCursor(0 * CHAR_WIDTH, old_entry->row * CHAR_HEIGHT);
    tft.setTextColor(BLACK, BLACK);
    tft.print('>');

    // Set new value
    tft.setCursor(0 * CHAR_WIDTH, new_entry->row * CHAR_HEIGHT);
    tft.setTextColor(WHITE, BLACK);
    tft.print('>');

#ifdef DEBUG
    // Dump to serial
    Serial.print(F("Cursor: ["));
    Serial.print(new_index);
    Serial.print(F("] line "));
    Serial.print(new_entry->row);
    Serial.print(F(" value "));
    Serial.println(new_entry->value);
#endif

    // Update internal state
    cursor_index = new_index;
}

void InitTogglePlayerStatus()
{
    Serial.print(F("Player Bool before function: "));
    Serial.println(player_bool[cursor_index - IE_PLAY_IDX]);
    player_bool[cursor_index - IE_PLAY_IDX] = !player_bool[cursor_index - 3];

    init_entry* entry1 = &init_entries[cursor_index];
    if( player_bool[cursor_index - IE_PLAY_IDX] )
    {
        tft.setCursor(2 * CHAR_WIDTH, entry1->row * CHAR_HEIGHT);
        tft.setTextColor(WHITE, BLACK);
        tft.print('#');
        n_players++;
    }
    else
    {
        init_entry* old_entry = &init_entries[cursor_index];
        tft.setCursor(2 * CHAR_WIDTH, old_entry->row * CHAR_HEIGHT);
        tft.setTextColor(BLACK, BLACK);
        tft.print('#');
        n_players--;
    }
}

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
        InitDrawGamesValue(n_games);

        tft.print(F("  Seed:  "));
        InitRedrawIntValue(IE_SEED_IDX, random_seed, F("Seed: "));

        tft.print(F("  Fair:  "));
        InitRedrawIntValue(IE_FAIR_IDX, random_fairness, F("Fair: "));

        tft.println();
        tft.println(F("Players"));
        tft.println(F("-------"));
        tft.println();

        for( int i = 0; i < n_players; i++ )
        {
            init_entry* player_entry = &init_entries[IE_PLAY_IDX + i];
            player_entry->value = 1;
            player_entry->is_selectable = true;

            tft.print(F("  # "));
            PRINT_BT(setPlayerName(i));
            tft.println();
        }

        InitRedrawCursor(1);

        screen_redraw = false;
    }

    if (input_allowed)
    {
        if (BUTTON_BLACK)
        {
            input_allowed = false;

            InitPlayerPairs();
            InitStatsFile();

            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            random_seed = init_entries[IE_SEED_IDX].value;
            random_fairness = init_entries[IE_FAIR_IDX].value;

            screen_redraw = true;
        }

        if (Y_UP)
        {
            input_allowed = false;
            InitRedrawCursor(-1);
        }

        if (Y_DOWN)
        {
            input_allowed = false;
            InitRedrawCursor(+1);
        }


        // Seed should be possible to change quickly thus we
        // don't need for joystick to return to the neutral
        // position and thus don't wait for the input_allowed

        if (X_RIGHT)
        {
            if (cursor_index == IE_SEED_IDX)
            {
                InitRedrawIntValue(IE_SEED_IDX, +1, F("Seed: "));
            }
            else if (cursor_index == IE_FAIR_IDX)
            {
                input_allowed = false;
                int old_fairness = init_entries[IE_FAIR_IDX].value;
                int new_fairness = old_fairness + random_fairness_increment;
                if( new_fairness > 255 ) { new_fairness -= random_fairness_increment; }
                InitRedrawIntValue(IE_FAIR_IDX, (new_fairness - old_fairness), F("Fair: "));
            }
            else
            {
                input_allowed = false;
                InitTogglePlayerStatus();
            }
        }

        if (X_LEFT)
        {
            if (cursor_index == IE_SEED_IDX)
            {
                InitRedrawIntValue(IE_SEED_IDX, -1, F("Seed: "));
            }
            else if (cursor_index == IE_FAIR_IDX)
            {
                input_allowed = false;
                int old_fairness = init_entries[IE_FAIR_IDX].value;
                int new_fairness = old_fairness - random_fairness_increment;
                if( new_fairness <= 0 ) { new_fairness += random_fairness_increment; }
                InitRedrawIntValue(IE_FAIR_IDX, (new_fairness - old_fairness), F("Fair: "));
            }
            else
            {
                input_allowed = false;
                InitTogglePlayerStatus();
            }
        }
    }
}

#endif // RANDOMIZER_INIT_H
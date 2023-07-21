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
    { 10, 2, false, 0 }, // Player 0
    { 11, 2, false, 0 }, // Player 1
    { 12, 2, false, 0 }, // Player 2
    { 13, 2, false, 0 }, // Player 3
    { 14, 2, false, 0 }, // Player 4
    { 15, 2, false, 0 }, // Player 5
    { 16, 2, false, 0 }, // Player 6
    { 17, 2, false, 0 }, // Player 7
    { 18, 2, false, 0 }, // Player 8
    { 19, 2, false, 0 }, // Player 9
};

// Indexes of various entries in the table
#define IE_GAMES_IDX 0
#define IE_SEED_IDX 1
#define IE_FAIRNESS_IDX 2
#define IE_PLAYER_FIRST_IDX 3
#define IE_PLAYER_LAST_IDX (IE_PLAYER_FIRST_IDX + MAX_PLAYERS)

// Table length
#define IE_LENGTH 13

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
void InitRedrawIntValue(size_t index, int direction)
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
    const __FlashStringHelper *serial_title = F("");
    switch (index)
    {
        case IE_SEED_IDX: serial_title = F("Seed: "); break;
        case IE_FAIRNESS_IDX: serial_title = F("Fair: "); break;
    }
    Serial.print(serial_title);
    Serial.println(new_value);

    // Update internal state
    entry->value = new_value;
}

// Redraw cursor
void InitRedrawCursor(int direction)
{
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

// Toggle a bool value
void InitRedrawBoolValue()
{
    // Toggle the value
    init_entry* entry = &init_entries[cursor_index];
    entry->value = !entry->value;

    // Render it
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(entry->value ? WHITE : BLACK, BLACK);
    tft.print('#');

    // Dump to serial
    Serial.print("Toggled [");
    Serial.print(cursor_index);
    Serial.print("] = ");
    Serial.println(entry->value);
}

void RandomizerInitScreen()
{
    if (screen_redraw)
    {
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(0, 0);

        tft.println(F("Randomizer"));
        tft.println(F("=========="));
        tft.println();

        initSd();
        {
            n_games = readNumberOfGames();
            n_players = readNumberOfPlayers();

            tft.print(F("  Games: "));
            InitDrawGamesValue(n_games);
        }

        initRandom();
        {
            tft.print(F("  Seed:  "));
            (&init_entries[IE_SEED_IDX])->value = random_seed;
            InitRedrawIntValue(IE_SEED_IDX, 0);

            tft.print(F("  Fair:  "));
            random_fairness = n_players * (n_players - 1);
            random_fairness_increment = random_fairness;
            (&init_entries[IE_FAIRNESS_IDX])->value = random_fairness;
            InitRedrawIntValue(IE_FAIRNESS_IDX, 0);
        }

        tft.println();
        tft.println(F("Players"));
        tft.println(F("-------"));
        tft.println();

        for( int i = 0; i < MAX_PLAYERS; i++ )
        {
            init_entry* player_entry = &init_entries[IE_PLAYER_FIRST_IDX + i];

            bool is_present = i < n_players;
            player_entry->value = is_present;
            player_entry->is_selectable = is_present;

            if( is_present )
            {
                tft.print(F("  # "));
                PRINT_BT(setPlayerName(i));
            }

            tft.println();
        }

        cursor_index = 1;
        InitRedrawCursor(0);

        screen_redraw = false;
    }

    if (input_allowed)
    {
        // Soft reset to quickly fix SD reader and screen glitches
        if (BUTTON_JOYSTICK)
        {
            input_allowed = false;
            screen_redraw = true;
        }

        // Next screen
        if (BUTTON_BLACK)
        {
            InitPlayerPairs();
            InitStatsFile();

            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            random_seed = init_entries[IE_SEED_IDX].value;
            random_fairness = init_entries[IE_FAIRNESS_IDX].value;

            input_allowed = false;
            screen_redraw = true;
        }

        // Cursor vertical movement
        if (Y_UP || Y_DOWN)
        {
            int direction = Y_UP ? -1 : +1;
            InitRedrawCursor(direction);
            input_allowed = false;
        }

        // Cursor modifies selected field
        if (X_RIGHT || X_LEFT)
        {
            int direction = X_RIGHT ? +1 : -1;

            switch (cursor_index)
            {
                case IE_SEED_IDX:
                {
                    InitRedrawIntValue(IE_SEED_IDX, direction);
                    // input_allowed stays the same, seed can be changed quickly
                    break;
                }
                case IE_FAIRNESS_IDX:
                {
                    int old_fairness = init_entries[IE_FAIRNESS_IDX].value;
                    int new_fairness = old_fairness + random_fairness_increment * direction;
                    if( new_fairness <= 0 ) { new_fairness += random_fairness_increment; }
                    if( new_fairness > 255 ) { new_fairness -= random_fairness_increment; }
                    InitRedrawIntValue(IE_FAIRNESS_IDX, (new_fairness - old_fairness));
                    input_allowed = false;
                    break;
                }
                default:
                {
                    InitRedrawBoolValue();
                    input_allowed = false;
                    break;
                }
            }
        }
    }
}

#endif // RANDOMIZER_INIT_H
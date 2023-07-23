#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"
#include "..\stats.h"


// Index of the currently selected entry in the table
size_t cursor_index = 0;

// Structure that describes setting that can be edited on the init screen
struct init_setting
{
    // Row on screen, starts with 0 from top
    int16_t row;

    // Column on screen, starts with 0 from LEFT
    int16_t col;

    // Can this row be selected for edit
    bool is_selectable;

    // Currently displayed value, how exactly to
    // render it depends on the data it represents
    int value;
};

// Table of editable settings on the init screen
struct init_setting init_settings[] = {
    // r, c, sel,   val
    {  3, 9, false, 0 }, // Games
    {  4, 9, true,  0 }, // Seed
    {  5, 9, true,  0 }, // Fair
    {  7, 9, false, 0 }, // Players number
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

// Indexes of various settings in the table
#define SETTING_GAMES_IDX 0
#define SETTING_SEED_IDX 1
#define SETTING_FAIRNESS_IDX 2
#define SETTING_PLAYER_NUMBER_IDX 3
#define SETTING_PLAYER_FIRST_IDX 4
#define SETTING_PLAYER_LAST_IDX (SETTING_PLAYER_FIRST_IDX + MAX_PLAYERS)

// Settings table length
#define SETTINGS_LENGTH 13

// Combination of different player pairs
#define MIN_FAIRNESS (init_settings[SETTING_PLAYER_NUMBER_IDX].value * (init_settings[SETTING_PLAYER_NUMBER_IDX].value - 1))

// Update and redraw cursor that moves between selectable settings
void UpdateCursorPosition(int movement)
{
    // Find the new index
    size_t new_index = cursor_index;
    init_setting* new_entry;
    do
    {
        new_index = (new_index + movement + SETTINGS_LENGTH) % SETTINGS_LENGTH;
        new_entry = &init_settings[new_index];
    }
    while( !new_entry->is_selectable );

    // Clear previous value
    init_setting* old_entry = &init_settings[cursor_index];
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

// Update and redraw games setting
void UpdateGamesSetting(int new_value)
{
    init_setting* entry = &init_settings[SETTING_GAMES_IDX];

    // Clear previous value
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(BLACK, BLACK);
    if( entry->value != 0 )
    {
        tft.print(entry->value);
    }
    else
    {
        // Erasing "SD card error" string that is tricky place into PROGMEM for reuse
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

// Update and redraw an integer setting
void UpdateIntegerSetting(size_t index, int increment)
{
    // Find the new value
    init_setting* entry = &init_settings[index];
    int new_value = entry->value + increment;

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
        case SETTING_SEED_IDX: serial_title = F("Seed: "); break;
        case SETTING_FAIRNESS_IDX: serial_title = F("Fair: "); break;
    }
    Serial.print(serial_title);
    Serial.println(new_value);

    // Update internal state
    entry->value = new_value;
}

// Update and redraw a bool switch setting that the cursor is currently on
// It is caller's responsibility to make sure cursor is standing on a switch
void UpdateCurrentlySelectedSwitchSetting()
{
    // Toggle the value
    init_setting* entry = &init_settings[cursor_index];
    entry->value = !entry->value;

    // Render it
    tft.setCursor(entry->col * CHAR_WIDTH, entry->row * CHAR_HEIGHT);
    tft.setTextColor(entry->value ? WHITE : BLACK, BLACK);
    tft.print('#');

    // Dump to serial
#ifdef DEBUG
    Serial.print("Toggled [");
    Serial.print(cursor_index);
    Serial.print("] = ");
    Serial.println(entry->value);
#endif

    // Update internal state
    UpdateIntegerSetting(SETTING_PLAYER_NUMBER_IDX, entry->value ? +1 : -1);
    UpdateIntegerSetting(SETTING_FAIRNESS_IDX, MIN_FAIRNESS - (&init_settings[SETTING_FAIRNESS_IDX])->value);
}

// Entry function of the init screen
void RandomizerInitScreen()
{
    // Full settings reinit and redraw of the screen
    if (screen_redraw)
    {
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE, BLACK);
        tft.setTextSize(FONT_SIZE);
        tft.setCursor(0, 0);

        tft.println(F("Randomizer"));
        tft.println(F("=========="));
        tft.println();

        initSd();
        {
            tft.print(F("  Games: "));
            UpdateGamesSetting(readNumberOfGames());
            (&init_settings[SETTING_PLAYER_NUMBER_IDX])->value = readNumberOfPlayers();
        }

        int entropy_seed = initEntropy();
        {
            tft.print(F("  Seed:  "));
            (&init_settings[SETTING_SEED_IDX])->value = entropy_seed;
            UpdateIntegerSetting(SETTING_SEED_IDX, 0);

            tft.print(F("  Fair:  "));
            (&init_settings[SETTING_FAIRNESS_IDX])->value = MIN_FAIRNESS;
            UpdateIntegerSetting(SETTING_FAIRNESS_IDX, 0);
        }

        tft.println();
        tft.println(F("Players:"));
        UpdateIntegerSetting(SETTING_PLAYER_NUMBER_IDX, 0);
        tft.println(F("-------"));
        tft.println();

        for( int i = 0; i < MAX_PLAYERS; i++ )
        {
            init_setting* player_entry = &init_settings[SETTING_PLAYER_FIRST_IDX + i];

            bool is_present = i < init_settings[SETTING_PLAYER_NUMBER_IDX].value;
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
        UpdateCursorPosition(0);

        screen_redraw = false;
    }

    // Start processing of the input controls
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
            // If there are not enough players do soft reset
            if( init_settings[SETTING_PLAYER_NUMBER_IDX].value < MIN_PLAYERS )
            {
                input_allowed = false;
                screen_redraw = true;
                return;
            }

            // Random preparation
            int seed = init_settings[SETTING_SEED_IDX].value;
            randomSeed(seed);
            InitStatsFile(seed);

            // Command data preparation
            n_fairness = init_settings[SETTING_FAIRNESS_IDX].value;
            n_players = init_settings[SETTING_PLAYER_NUMBER_IDX].value;
            n_games = init_settings[SETTING_GAMES_IDX].value;
            n_match = 0;

            // Init players array and combine pairs
            {
                if( players != 0 ) { free(players); }
                players = (byte *)malloc(n_players);
                int cursor = 0;

                for( int i = 0; i < MAX_PLAYERS; i++ )
                {
                    init_setting* player_entry = &init_settings[SETTING_PLAYER_FIRST_IDX + i];
                    if( !player_entry->value ) { continue; }

                    players[cursor] = i;
                    cursor++;
                    Serial.print(F("Player available: "));
                    Serial.println(i);
                }

                InitPlayerPairs();
            }

            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            input_allowed = false;
            screen_redraw = true;
        }

        // Cursor vertical movement
        if (Y_UP || Y_DOWN)
        {
            int direction = Y_UP ? -1 : +1;
            UpdateCursorPosition(direction);
            input_allowed = false;
        }

        // Cursor modifies selected field
        if (X_RIGHT || X_LEFT)
        {
            int direction = X_RIGHT ? +1 : -1;

            switch (cursor_index)
            {
                case SETTING_SEED_IDX:
                {
                    UpdateIntegerSetting(SETTING_SEED_IDX, direction);
                    // input_allowed stays the same, seed can be changed quickly
                    break;
                }
                case SETTING_FAIRNESS_IDX:
                {
                    int old_fairness = init_settings[SETTING_FAIRNESS_IDX].value;
                    int new_fairness = old_fairness + MIN_FAIRNESS * direction;
                    if( new_fairness <= 0 ) { new_fairness += MIN_FAIRNESS; }
                    if( new_fairness > 255 ) { new_fairness -= MIN_FAIRNESS; }
                    UpdateIntegerSetting(SETTING_FAIRNESS_IDX, (new_fairness - old_fairness));
                    input_allowed = false;
                    break;
                }
                default:
                {
                    UpdateCurrentlySelectedSwitchSetting();
                    input_allowed = false;
                    break;
                }
            }
        }
    }
}

#endif // RANDOMIZER_INIT_H
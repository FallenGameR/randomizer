#ifndef RANDOMIZER_INIT_H
#define RANDOMIZER_INIT_H

#include "..\screens.h"
#include "..\random.h"
#include "..\input.h"
#include "..\players.h"
#include "..\tft.h"
#include "..\stats.h"
#include "..\colors.h"

// Index of the currently selected entry in the table on the current screen
extern size_t cursor_index;

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
extern struct init_setting init_settings[];

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
void UpdateInitCursorPosition(int movement);

// Update and redraw games setting
void UpdateGamesSetting(int new_value);

// Update and redraw an integer setting
void UpdateIntegerSetting(size_t index, int increment);

// Update and redraw a bool switch setting that the cursor is currently on
// It is caller's responsibility to make sure cursor is standing on a switch
void UpdateCurrentlySelectedSwitchSetting();

// Entry function of the init screen
void RandomizerInitScreen();

#endif // RANDOMIZER_INIT_H
//#define DEBUG

#include "screens\01_init_screen.h"
#include "screens\player_selection.h"
#include "screens\03_fighter_selection_screen.h"
#include "screens\02_game_selection_screen.h"
#include "screens\04_totals_show_screen.h"
#include "screens\tester_screen.h"

void setup()
{
    // Serial init
    Serial.begin(9600);

    // Pins init
    pinMode(pin_led_green, OUTPUT);
    pinMode(pin_led_blue, OUTPUT);
    pinMode(pin_button_black, INPUT_PULLUP);
    pinMode(pin_button_joystick, INPUT_PULLUP);

    // Screen init
    tft.begin(tft.readID());
    tft.setRotation(1);

    // Begin with randomizer init screen
    Serial.println(F("-> Init"));
    screen_selected = Screen::RandomizerInit;
    //screen_selected = Screen::Tester;
}

void loop()
{
    readInput();

    switch (screen_selected)
    {
    case Screen::RandomizerInit:
        RandomizerInitScreen();
        break;

    case Screen::GameIconSelection:
        GameIconSelectionScreen();
        break;

    case Screen::PlayerSelection:
        PlayerSelectionScreen();
        break;

    case Screen::FighterSelection:
        FighterSelectionScreen();
        break;

    case Screen::TotalsShow:
        TotalShowScreen();
        break;

    case Screen::Tester:
        TesterScreen();
        break;
    }
}

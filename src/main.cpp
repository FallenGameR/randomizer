// #define DEBUG

#include "screens\randomizer_init.h"
#include "screens\game_selection.h"
#include "screens\player_selection.h"
#include "screens\fighter_selection.h"
#include "screens\game_icon_selection.h"
#include "screens\totals_show.h"
#include "screens\tester.h"

void setup()
{
    // Serial init
    Serial.begin(9600);

    // Pins init
    pinMode(pin_led_green, OUTPUT);
    pinMode(pin_led_blue, OUTPUT);
    pinMode(pin_button_black, INPUT_PULLUP);
    pinMode(pin_button_joystick, INPUT_PULLUP);

    // Devices init
    initRandom();
    initSd();

    // Screen init
    tft.begin(tft.readID());
    tft.setRotation(1);
    tft.setTextSize(FONT_SIZE);
    tft.setTextColor(WHITE, BLACK);

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

    case Screen::GameSelection:
        GameSelectionScreen();
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

#include "screens\randomizer_init.h"

//#include "screens\game_selection.h"
//#include "screens\player_selection.h"
//#include "screens\fighter_selection.h"
//#include "stats.h"

#include "tft.h"
#include "touch.h"

void setup()
{
  //setupBmp();
  //setupTouch();

  Serial.begin(9600);

  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  tft.begin(HX8357D);
  tft.setRotation(3);
  tft.fillScreen(HX8357_BLACK);
  tft.setTextSize(1);
  tft.println(F("Initializing"));
  tft.println(F("Entropy"));

  initRandom();

  Serial.println(F("-> Init"));
  screen_selected = Screen::RandomizerInit;

  // For testing
  //screen_selected = Screen::PlayerSelection;
}

void loop()
{
  //loopTouch();
}

/*

void setup()
{

}

void loop()
{
  readInput();

  switch (screen_selected)
  {
  case Screen::RandomizerInit:
    RandomizerInitScreen();
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
  }
}
/**/
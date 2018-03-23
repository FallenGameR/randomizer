#include "screens\randomizer_init.h"
#include "screens\game_selection.h"
#include "screens\player_selection.h"
#include "screens\fighter_selection.h"

void setup()
{
  Serial.begin(9600);

  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing");
  lcd.setCursor(0, 1);
  lcd.print("Entropy");
  initRandom();

  Serial.println("-> Init");
  screen_selected = Screen::RandomizerInit;

  // For testing
  //screen_selected = Screen::PlayerSelection;
}

int iteration = 0;
int maxIterations = 1000;

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

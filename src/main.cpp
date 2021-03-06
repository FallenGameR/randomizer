//#define DEBUG

#include "screens\randomizer_init.h"
#include "screens\game_selection.h"
#include "screens\player_selection.h"
#include "screens\fighter_selection.h"
#include "screens\game_icon_selection.h"
#include "screens\totals_show.h"
#include "screens\tester.h"

#include "files.h"
#include "tft.h"
#include "touch.h"

void setup()
{
  Serial.begin(9600);

  initSd();
  InitPlayerColors();

  n_games = readNumberOfGames();
  Serial.print("Number of games: ");
  Serial.println(n_games);

  n_players = readNumberOfPlayers();
  Serial.print("Number of players: ");
  Serial.println(n_players);

  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(FONT_SIZE);
  tft.setTextColor(WHITE, BLACK);
  tft.print(F("Initializing "));
  tft.println(F("Entropy"));

  initRandom();

  Serial.println(F("-> Init"));
  screen_selected = Screen::RandomizerInit;

  // For testing
  // screen_selected = Screen::Tester;
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

#include <Arduino.h>
#include "pins.h"
#include "random.h"
#include "input.h"
#include "games.h"
#include "players.h"
#include "fighters.h"

enum Screen
{
  RandomizerInit = 0,
  GameSelection = 1,
  PlayerSelection = 2,
  FighterSelection = 3,
  Statistics = 4,
};

bool doUpdate = true;
bool commandAwait = true;

int screen_state = Screen::RandomizerInit;

bool redraw_needed = true;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  initRandom();

  // For testing
  screen_state = Screen::GameSelection;
}

void RandomizerInitScreen()
{
  if (redraw_needed)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Randomizer ");
    lcd.setCursor(0, 1);
    lcd.print("S ");
    lcd.print(seed);
    lcd.print(" F ");
    lcd.print(fairness_selected);
    redraw_needed = false;
  }

  if (x_right && input_allowed)
  {
    fairness_selected = fairness_selected + n_players;
    input_allowed = false;
    redraw_needed = true;
  }

  if (x_left && input_allowed)
  {
    fairness_selected = fairness_selected - n_players;
    input_allowed = false;
    redraw_needed = true;
  }

  if (button_black_pressed)
  {
    screen_state = Screen::GameSelection;
    redraw_needed = true;
  }
}

void GameSelectionScreen()
{
  if (redraw_needed)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(games[games_selected]);
    redraw_needed = false;
  }

  if (x_right && input_allowed)
  {
    games_selected = (games_selected + n_games + 1) % n_games;
    input_allowed = false;
    redraw_needed = true;
  }

  if (x_left && input_allowed)
  {
    games_selected = (games_selected + n_games - 1) % n_games;
    input_allowed = false;
    redraw_needed = true;
  }

  if (button_black_pressed)
  {
    screen_state = Screen::PlayerSelection;
    redraw_needed = true;
  }
}

void PlayerSelectionScreen()
{
  player_left = 0;
  player_right = 1;
  screen_state = Screen::FighterSelection;
}

void FighterSelectionScreen()
{
  if (redraw_needed)
  {
    /*
    fighter_left =

        int first = random(n_tekken7);
    int second = random(n_tekken7);

    lcd.setCursor(0, 0);
    lcd.print(tekken7[first]);
    lcd.setCursor(0, 1);
    lcd.print(tekken7[second]);


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(games[games_selected]);
    redraw_needed = false;
    /**/
  }
}

void StatisticsScreen()
{
}

void loop()
{
  readInput();

  switch (screen_state)
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

  case Screen::Statistics:
    StatisticsScreen();
    break;
  }

  return;

  digitalWrite(pin_led_green, button_black_pressed);
  digitalWrite(pin_led_blue, button_joystick_pressed);

  if ((x_left || x_right) && commandAwait)
  {
    doUpdate = true;
    commandAwait = false;
    Serial.println("Update");
  }

  if (x_center)
  {
    commandAwait = true;
  }

  if (doUpdate)
  {
    doUpdate = false;
    lcd.clear();

    int first = random(n_tekken7);
    int second = random(n_tekken7);

    lcd.setCursor(0, 0);
    lcd.print(tekken7[first]);
    lcd.setCursor(0, 1);
    lcd.print(tekken7[second]);
  }
}

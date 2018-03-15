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
  //screen_state = Screen::GameSelection;
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

  if (input_allowed)
  {
    if (x_right)
    {
      fairness_selected = fairness_selected + n_players;
      input_allowed = false;
      redraw_needed = true;
    }

    if (x_left)
    {
      fairness_selected = fairness_selected - n_players;
      input_allowed = false;
      redraw_needed = true;
    }

    if (button_black_pressed)
    {
      screen_state = Screen::GameSelection;
      input_allowed = false;
      redraw_needed = true;
    }
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

  if (input_allowed)
  {
    if (x_right)
    {
      games_selected = (games_selected + n_games + 1) % n_games;
      fighter_map_selected = fighter_map[games_selected];
      n_fighter_map_selected = n_fighter_map[games_selected];
      input_allowed = false;
      redraw_needed = true;
    }

    if (x_left)
    {
      games_selected = (games_selected + n_games - 1) % n_games;
      fighter_map_selected = fighter_map[games_selected];
      n_fighter_map_selected = n_fighter_map[games_selected];
      input_allowed = false;
      redraw_needed = true;
    }

    if (button_black_pressed)
    {
      screen_state = Screen::PlayerSelection;
      input_allowed = false;
      redraw_needed = true;
    }
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
    fighter_left = random(n_fighter_map_selected);
    fighter_right = random(n_fighter_map_selected);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(fighter_map_selected[fighter_left]);
    lcd.setCursor(0, 1);
    lcd.print(fighter_map_selected[fighter_right]);

    redraw_needed = false;
  }

  if (input_allowed)
  {
    if (button_black_pressed)
    {
      screen_state = Screen::FighterSelection;
      input_allowed = false;
      redraw_needed = true;
    }
  }

  digitalWrite(pin_led_green, x_left || x_right);
  digitalWrite(pin_led_blue, y_down || y_up);
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
}

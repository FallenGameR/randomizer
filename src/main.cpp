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
    lcd.print(random_seed);
    lcd.print(" F ");
    lcd.print(random_fairness);

    Serial.print("Seed: ");
    Serial.println(random_seed);
    Serial.print("Fairness: ");
    Serial.println(random_fairness);

    redraw_needed = false;
  }

  if (input_allowed)
  {
    if (X_RIGHT)
    {
      random_fairness = random_fairness + n_players;
      input_allowed = false;
      redraw_needed = true;
    }

    if (X_LEFT)
    {
      random_fairness = random_fairness - n_players;
      input_allowed = false;
      redraw_needed = true;
    }

    if (BUTTON_BLACK)
    {
      screen_state = Screen::GameSelection;
      Serial.println("-> GameSelection");

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
    lcd.print(games[games_index]);
    Serial.print("Game: ");
    Serial.println(games[games_index]);

    redraw_needed = false;
  }

  if (input_allowed)
  {
    if (X_RIGHT)
    {
      games_index = (games_index + n_games + 1) % n_games;
      fighter_map_selected = fighter_map[games_index];
      n_fighter_map_selected = n_fighter_map[games_index];
      input_allowed = false;
      redraw_needed = true;
    }

    if (X_LEFT)
    {
      games_index = (games_index + n_games - 1) % n_games;
      fighter_map_selected = fighter_map[games_index];
      n_fighter_map_selected = n_fighter_map[games_index];
      input_allowed = false;
      redraw_needed = true;
    }

    if (BUTTON_BLACK)
    {
      screen_state = Screen::PlayerSelection;
      Serial.println("-> PlayerSelection");

      input_allowed = false;
      redraw_needed = true;
    }
  }
}

void PlayerSelectionScreen()
{
  player_index_first = 0;
  player_index_second = 1;
  screen_state = Screen::FighterSelection;
  Serial.println("-> FighterSelection");
}

enum Winner
{
  None,
  First,
  Second,
  Draw,
};

int winner_selected = Winner::None;
bool not_fair_win = false;

void FighterSelectionScreen()
{
  if (redraw_needed)
  {
    winner_selected = Winner::None;
    not_fair_win = false;

    fighter_index_first = random(n_fighter_map_selected);
    fighter_index_second = random(n_fighter_map_selected);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(fighter_map_selected[fighter_index_first]);
    lcd.setCursor(0, 1);
    lcd.print(fighter_map_selected[fighter_index_second]);

    Serial.print("First: ");
    Serial.println(fighter_map_selected[fighter_index_first]);
    Serial.print("Second: ");
    Serial.println(fighter_map_selected[fighter_index_second]);

    redraw_needed = false;
  }

  if (input_allowed)
  {
    if (BUTTON_BLACK)
    {
      screen_state = Screen::GameSelection;
      Serial.println("-> GameSelection");

      input_allowed = false;
      redraw_needed = true;
    }

    if (Y_DOWN)
    {
      not_fair_win = !not_fair_win;
      input_allowed = false;
    }

    if (winner_selected != Winner::None)
    {
      Serial.print("Won: ");
      Serial.print(players[winner_selected]);
      if (not_fair_win)
      {
        Serial.print(" (opponent says not fair)");
      }
      Serial.println();

      screen_state = Screen::FighterSelection;
      Serial.println("-> FighterSelection");

      input_allowed = false;
      redraw_needed = true;
    }
  }

  if (Y_DOWN)
  {
    winner_selected = Winner::None;
  }

  if (Y_UP)
  {
    winner_selected = Winner::Draw;
  }

  if (X_LEFT)
  {
    winner_selected = Winner::First;
  }

  if (X_RIGHT)
  {
    winner_selected = Winner::Second;
  }

  digitalWrite(pin_led_green, winner_selected != Winner::None);
  digitalWrite(pin_led_blue, not_fair_win);
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
  }
}

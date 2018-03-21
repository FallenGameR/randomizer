#include <Arduino.h>
#include "games\games.h"
#include "screens\screens.h"
#include "pins.h"
#include "random.h"
#include "input.h"
#include "players.h"
#include "fighters.h"

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  initRandom();

  //Serial.println("-> Init");
  //screen_selected = Screen::RandomizerInit;

  // For testing
  screen_selected = Screen::PlayerSelection;
}

void RandomizerInitScreen()
{
  if (screen_redraw)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Randomizer ");
    lcd.setCursor(0, 1);
    lcd.print("S ");
    lcd.print(random_seed);
    lcd.print(" F ");
    lcd.print(random_fairness);

    Serial.print("Seed = ");
    Serial.println(random_seed);
    Serial.print("Fairness = ");
    Serial.println(random_fairness);

    screen_redraw = false;
  }

  if (input_allowed)
  {
    if (X_RIGHT)
    {
      random_fairness = random_fairness + n_players;
      input_allowed = false;
      screen_redraw = true;
    }

    if (X_LEFT)
    {
      random_fairness = random_fairness - n_players;
      input_allowed = false;
      screen_redraw = true;
    }

    if (BUTTON_BLACK)
    {
      Serial.println("-> Game");
      screen_selected = Screen::GameSelection;
      input_allowed = false;
      screen_redraw = true;
    }
  }
}

void GameSelectionScreen()
{
  if (screen_redraw)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(games[games_index]);
    Serial.println(games[games_index]);

    screen_redraw = false;
  }

  if (input_allowed)
  {
    if (X_RIGHT)
    {
      games_index = (games_index + n_games + 1) % n_games;
      fighter_map_selected = fighter_map[games_index];
      n_fighter_map_selected = n_fighter_map[games_index];
      input_allowed = false;
      screen_redraw = true;
    }

    if (X_LEFT)
    {
      games_index = (games_index + n_games - 1) % n_games;
      fighter_map_selected = fighter_map[games_index];
      n_fighter_map_selected = n_fighter_map[games_index];
      input_allowed = false;
      screen_redraw = true;
    }

    if (BUTTON_BLACK)
    {
      Serial.println("-> Match");
      screen_selected = Screen::PlayerSelection;
      input_allowed = false;
      screen_redraw = true;
    }
  }
}

void PlayerSelectionScreen()
{
  player_index_first = 0;
  player_index_second = 1;

  if (n_players > 2)
  {
    Serial.print(players[player_index_first]);
    Serial.print(" and ");
    Serial.println(players[player_index_second]);
  }

  screen_selected = Screen::FighterSelection;
}

enum Winner
{
  None,
  First,
  Second,
  Draw,
};

int winner_selected;
bool not_fair_win;

void FighterSelectionScreen()
{
  if (screen_redraw)
  {
    fighter_index_first = random(n_fighter_map_selected);
    fighter_index_second = random(n_fighter_map_selected);
    winner_selected = Winner::None;
    not_fair_win = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(fighter_map_selected[fighter_index_first]);
    lcd.setCursor(0, 1);
    lcd.print(fighter_map_selected[fighter_index_second]);

    Serial.print(fighter_map_selected[fighter_index_first]);
    Serial.print(" vs ");
    Serial.println(fighter_map_selected[fighter_index_second]);

    screen_redraw = false;
  }

  // Means we just were in neutral state and now test for new input
  if (input_allowed)
  {
    if (BUTTON_BLACK)
    {
      Serial.println("-> Game");
      screen_selected = Screen::GameSelection;
      input_allowed = false;
      screen_redraw = true;
    }

    // After modifier selection disable input so that we don't keep flipping the modifier
    if (Y_DOWN)
    {
      not_fair_win = !not_fair_win;
      input_allowed = false;
    }

    // We need to test for joystick neutral position since event wise it was like this:
    // - joystick selection, this one doesn't specify final win yet (since we may want to cancel this input before completing it)
    //   and doesn't reset input_allowed, so we need to explicitly check for neutral position
    // - neutral position
    if (winner_selected != Winner::None && X_CENTER && Y_CENTER)
    {
      switch (winner_selected)
      {
      case Winner::Draw:
        Serial.print("Draw");
        break;

      case Winner::First:
        Serial.print(players[player_index_first]);
        Serial.print(" won (");
        Serial.print(fighter_map_selected[fighter_index_first]);
        Serial.print(")");
        break;

      case Winner::Second:
        Serial.print(players[player_index_second]);
        Serial.print(" won (");
        Serial.print(fighter_map_selected[fighter_index_second]);
        Serial.print(")");
        break;
      }

      if (not_fair_win)
      {
        Serial.print(" (opponent says not fair)");
      }
      Serial.println();

      Serial.println("-> Match");
      screen_selected = Screen::PlayerSelection;
      input_allowed = false;
      screen_redraw = true;
    }
  }

  // Note that win selection don't reset input_allowed to allow
  // for choise change without resetting joystick postion to neutral
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

  // LEDs show what the input would be on winner finalization
  digitalWrite(pin_led_green, winner_selected != Winner::None);
  digitalWrite(pin_led_blue, not_fair_win);
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

#include <Arduino.h>
#include "pins.h"
#include "random.h"
#include "input.h"
#include "games.h"
#include "players.h"

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
bool redraw_needed = true;
int screen_state = Screen::RandomizerInit;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  initRandom();
}

void RandomizerInitScreen()
{
  if (redraw_needed)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Randomizer");
    lcd.setCursor(0, 1);
    lcd.print("Seed ");
    lcd.print(seed);
    redraw_needed = false;
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
    lcd.print("Tekken");
    lcd.setCursor(0, 1);
    lcd.print("Fairness ");
    redraw_needed = false;
  }
}

void PlayerSelectionScreen()
{
}

void FighterSelectionScreen()
{
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

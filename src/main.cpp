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
  delay(10000);
}

void loop()
{
  readInput();

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

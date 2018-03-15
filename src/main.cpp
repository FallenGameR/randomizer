#include <Arduino.h>
#include "pins.h"
#include "random.h"
#include "games.h"
#include "players.h"

bool doUpdate = true;
bool commandAwait = true;

enum State
{
  Working = 1,
  Failed = 0
};

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
  bool button_black_pressed = !digitalRead(pin_button_black);
  digitalWrite(pin_led_green, button_black_pressed);

  if (button_black_pressed)
  {
    Serial.println("test");
    Serial.print("A0 = ");
    Serial.println(analogRead(0));
    Serial.print("A1 = ");
    Serial.println(analogRead(1));
    Serial.print("A2 = ");
    Serial.println(analogRead(2));
    Serial.print("A3 = ");
    Serial.println(analogRead(3));
    Serial.print("A4 = ");
    Serial.println(analogRead(4));
    Serial.print("A5 = ");
    Serial.println(analogRead(5));
  }

  bool button_joystick_pressed = !digitalRead(pin_button_joystick);
  digitalWrite(pin_led_blue, button_joystick_pressed);

  int x = analogRead(pin_x_joystick);
  int y = analogRead(pin_y_joystick);

  bool x_left = x < 400;
  bool x_right = x > 600;
  bool x_center = !x_left && !x_right;
  bool y_up = y > 600;
  bool y_down = y < 400;
  bool y_center = !y_up && !y_down;

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

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "games.h"
#include "players.h"

// Pins used
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const int pin_led_green = 4;
const int pin_led_blue = 5;
const int pin_button_black = 6;
const int pin_button_joystick = 13;
const int pin_x_joystick = 0;
const int pin_y_joystick = 1;

bool doUpdate = true;
bool commandAwait = true;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  int noise =
      analogRead(0) *
      analogRead(1) *
      analogRead(2) *
      analogRead(3) *
      analogRead(4) *
      analogRead(5);

  randomSeed(noise);

  Serial.println(noise);
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

    int tempReading = analogRead(2);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK); //  Temp Kelvin
    float tempC = tempK - 273.15;                                                          // Convert Kelvin to Celcius
    Serial.print("t = ");
    Serial.println(tempC);
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

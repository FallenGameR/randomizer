#include <Arduino.h>
#include <LiquidCrystal.h>
#include "tekken.h"

// Arduino pin numbers
const int SW_pin = 13;
const int X_pin = 0;
const int Y_pin = 1;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int ledGreenPin = 4;
int ledBluePin = 5;
int buttonPin = 6;

bool doUpdate = false;
bool commandAwait = true;

void setup()
{
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  int noise =
      analogRead(0) *
      analogRead(1) *
      analogRead(2) *
      analogRead(3) *
      analogRead(4) *
      analogRead(5);

  randomSeed(noise);

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  Serial.println(noise);

  doUpdate = true;
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledBluePin, HIGH);
  }
  else if (digitalRead(buttonPin) == HIGH)
  {
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, LOW);
  }

  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);
  bool pressed = !digitalRead(SW_pin);

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

    int first = random(n_tekken);
    int second = random(n_tekken);

    lcd.setCursor(0, 0);
    lcd.print(tekken[first]);
    lcd.setCursor(0, 1);
    lcd.print(tekken[second]);
  }
}

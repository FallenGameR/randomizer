#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>
#include "pins.h"

// https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout/pinouts
// Uses 8-Bit Mode
Adafruit_TFTLCD tft = Adafruit_TFTLCD(pin_tft_cs, pin_tft_dc, pin_tft_wr, pin_tft_rd, pin_tft_rst);

// `Fairness` is how many games needs to be played out for everybody to play equal amount of times in all configurations.
// Minimal fairness value get a chance for everybody to play as soon as possible.
// But as it `fairness` value grows the pair distribution can become more and more strange but fair
// on the larger scale. It could be that some players would not change seats for several games in a row
// but after the `fairness` number of games all players will play equal amount of games regardless.
// `Fairness` makes sense only if there are >2 players.
byte random_fairness = 0;

byte n_players = 0;

#endif // SHARED_H
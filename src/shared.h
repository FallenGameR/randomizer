#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>
#include "screens/screens.h"
#include "pins.h"

// https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout/pinouts
// Uses 8-Bit Mode
Adafruit_TFTLCD tft = Adafruit_TFTLCD(pin_tft_cs, pin_tft_dc, pin_tft_wr, pin_tft_rd, pin_tft_rst);

// Input becomes allowed if joystick had a chance to get back
// into it's neutral position while there was no button pressed.
//
// Input gets blocked if code start to process some of the command
// that it got from buttons or from joystick. Until the processing
// is done normally this flag gets set to false. Unless the code
// processes a continuously pressed button or joystick left in a
// particular direction.
bool input_allowed = false;

// If full screen redraw is needed
bool screen_redraw = true;

// What screen is currently selected
byte screen_selected = Screen::RandomizerInit;

// `Fairness` is how many games needs to be played out for everybody to play equal amount of times in all configurations.
// Minimal fairness value get a chance for everybody to play as soon as possible.
// But as it `fairness` value grows the pair distribution can become more and more strange but fair
// on the larger scale. It could be that some players would not change seats for several games in a row
// but after the `fairness` number of games all players will play equal amount of games regardless.
// `Fairness` makes sense only if there are >2 players.
byte n_fairness = 0;

// Total number of players available for play
byte n_players = 0;

// Currently available players
byte* players = 0;

// Total number of games available for play
byte n_games = 0;

// The size is n_fairness * 2
byte *player_pairs = 0;

// Who is the first player
// NOTE: Is it index on SD or is it index in the available players array?
byte player_index_first = -1;

// Who is the second player
byte player_index_second = -1;

// Number of the current fighting match
byte n_match = 0;

#endif // SHARED_H
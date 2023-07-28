#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>

// https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout/pinouts
// Uses 8-Bit Mode
extern Adafruit_TFTLCD tft;

// Input becomes allowed if joystick had a chance to get back
// into it's neutral position while there was no button pressed.
//
// Input gets blocked if code start to process some of the command
// that it got from buttons or from joystick. Until the processing
// is done normally this flag gets set to false. Unless the code
// processes a continuously pressed button or joystick left in a
// particular direction.
extern bool input_allowed;

// If full screen redraw is needed
extern bool screen_redraw;

// What screen is currently selected
extern byte screen_selected;

// `Fairness` is how many games needs to be played out for everybody to play equal amount of times in all configurations.
// Minimal fairness value get a chance for everybody to play as soon as possible.
// But as it `fairness` value grows the pair distribution can become more and more strange but fair
// on the larger scale. It could be that some players would not change seats for several games in a row
// but after the `fairness` number of games all players will play equal amount of games regardless.
// `Fairness` makes sense only if there are >2 players.
extern byte n_fairness;

// Total number of players available for play
extern byte n_players;

// Currently available players
extern byte* players;

// Total number of games available for play
extern byte n_games;

// The size is n_fairness * 2
extern byte *player_pairs;

// Who is the first player, that is SD card index
extern byte player_index_first;

// Who is the second player, that is SD card index
extern byte player_index_second;

// Number of the current fighting match
extern byte n_match;

#endif // SHARED_H
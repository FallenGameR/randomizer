#include "shared.h"
#include "pins.h"
#include "screens.h"

Adafruit_TFTLCD tft = Adafruit_TFTLCD(pin_tft_cs, pin_tft_dc, pin_tft_wr, pin_tft_rd, pin_tft_rst);
bool input_allowed = false;
bool screen_redraw = true;
byte screen_selected = Screen::RandomizerInit;
byte n_fairness = 0;
byte n_players = 0;
byte* players = 0;
byte n_games = 0;
byte *player_pairs = 0;
byte player_index_first = -1;
byte player_index_second = -1;
byte n_match = 0;
byte n_fighters = 0;
size_t fighters_left_position = 0;
size_t fighters_right_position = 0;
byte game_index = 0;
byte game_tag = 0;
bool game_is_tag = false;
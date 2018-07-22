#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"
#include "guilty_gear_xrd_rev2.h"
#include "king_of_fighters_14.h"
#include "killer_instinct.h"
#include "mortal_kombat_xl.h"
#include "street_fighter_5.h"

byte game_index = 0;
byte game_tag = 0;
byte n_games = 0;
bool isTagGame = false;

// Table of fighter names by game
const char *const *fighter_map[] = {
    doa5,
    guilty_gear,
    killer_instinct,
    kof14,
    mortal_kombat,
    street_fighter_5,
    tekken7,
};

// Table of fighter name count by game
const byte n_fighter_map[] = {
    n_doa5,
    n_guilty_gear,
    n_killer_instinct,
    n_kof14,
    n_mortal_kombat,
    n_street_fighter_5,
    n_tekken7,
};

// Selected variables for the firts  game in the list
const char *const *fighter_map_selected = doa5;
byte n_fighter_map_selected = n_doa5;

#endif // GAMES_H
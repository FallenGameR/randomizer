#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"
#include "guilty_gear_xrd_rev2.h"
#include "king_of_fighters_14.h"
#include "killer_instinct.h"
#include "mortal_kombat_xl.h"
#include "street_fighter_5.h"

// Using PROGMEM here to save some space for variables

const char games_DeadOrAlive5[] PROGMEM = "Dead or Alive 5";
const char games_GuiltyGearXrdRev2[] PROGMEM = "Guilty Gear Xrd";
const char games_KillerInstinct[] PROGMEM = "Killer Instinct";
const char games_KingOfFighters14[] PROGMEM = "King of Fighters";
const char games_MortalKombatX[] PROGMEM = "Mortal Kombat X";
const char games_StreetFighter5[] PROGMEM = "Street Fighter";
const char games_Tekken7[] PROGMEM = "Tekken 7";

const char *const games[] PROGMEM = {
    games_DeadOrAlive5,
    games_GuiltyGearXrdRev2,
    games_KillerInstinct,
    games_KingOfFighters14,
    games_MortalKombatX,
    games_StreetFighter5,
    games_Tekken7,
};

#define n_games (sizeof(games) / sizeof(const char *))

int games_index = 0;

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

// Number of fighters in tag matches by game
const byte t_fighter_map[] = {
    2, // 2 fighters in tag match in Dead or Alive
    0, // no tag matches in Guilty Gear
    0, // no tag matches in Killer Instinct
    3, // 3 fighters teams in King of Fighters
    0, // no tag matches in Mortal Kombat
    2, // 2 fighter matches in Street Fighter (actually it could be up to 5x5, but 2x2 seem good enough)
    0, // no tag matches in Tekken
};

// Selected variables for the firts  game in the list
const char *const *fighter_map_selected = doa5;
byte n_fighter_map_selected = n_doa5;
byte t_fighter_map_selected = 0;
bool isTagGame = false;

#endif // GAMES_H
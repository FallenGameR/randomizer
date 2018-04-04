#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"
#include "guilty_gear_xrd_rev2.h"
#include "king_of_fighters_14.h"
#include "killer_instinct.h"
#include "dice.h"

// Using PROGMEM here to save some space for variables

const char games_Tekken7[] PROGMEM = "Tekken 7";
const char games_DeadOrAlive5[] PROGMEM = "Dead or Alive 5";
const char games_GuiltyGearXrdRev2[] PROGMEM = "Guilty Gear Xrd";
const char games_KingOfFighters14[] PROGMEM = "King of Fighters";
const char games_KillerInstinct[] PROGMEM = "Killer Instinct";
const char games_Dice[] PROGMEM = "Dice";

const char *const games[] PROGMEM = {
    games_Tekken7,
    games_DeadOrAlive5,
    games_GuiltyGearXrdRev2,
    games_KingOfFighters14,
    games_KillerInstinct,
    games_Dice,
};

#define n_games (sizeof(games) / sizeof(const char *))

int games_index = 0;

// Table of fighter names by game
const char *const *fighter_map[] = {
    tekken7,
    doa5,
    guilty_gear,
    kof14,
    killer_instinct,
    dice,
};

// Table of fighter name count by game
const byte n_fighter_map[] = {
    n_tekken7,
    n_doa5,
    n_guilty_gear,
    n_kof14,
    n_killer_instinct,
    n_dice,
};

// Number of fighters in tag matches by game
const byte t_fighter_map[] = {
    0, // no tag matches in Tekken
    2, // 2 fighters in tag match in Dead or Alive
    0, // no tag matches in Guilty Gear
    3, // 3 fighters teams in King of Fighters
    0, // no tag matches in Killer Instinct
    0, // no tag matches in Dice
};

// Selected variables for the firts  game in the list
const char *const *fighter_map_selected = tekken7;
byte n_fighter_map_selected = n_tekken7;
byte t_fighter_map_selected = 0;
bool isTagGame = false;

#endif // GAMES_H
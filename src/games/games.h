#ifndef GAMES_H
#define GAMES_H

#include "tekken7.h"
#include "doa5.h"
#include "guilty_gear_xrd_rev2.h"
#include "killer_instinct.h"
#include "dice.h"

// Using PROGMEM here to save some space for variables

const char games_Tekken7[] PROGMEM = "Tekken 7";
const char games_DeadOrAlive5[] PROGMEM = "Dead or Alive 5";
const char games_GuiltyGearXrdRev2[] PROGMEM = "Guilty Gear Xrd 2";
const char games_KillerInstinct[] PROGMEM = "Killer Instinct";
const char games_Dice[] PROGMEM = "Dice";

const char *const games[] PROGMEM = {
    games_Tekken7,
    games_DeadOrAlive5,
    games_GuiltyGearXrdRev2,
    games_KillerInstinct,
    games_Dice,
};

#define n_games (sizeof(games) / sizeof(const char *))

int games_index = 0;

const char *const *fighter_map[] = {
    tekken7,
    doa5,
    guilty_gear,
    killer_instinct,
    dice,
};

const byte n_fighter_map[] = {
    n_tekken7,
    n_doa5,
    n_guilty_gear,
    n_killer_instinct,
    n_dice,
};

const char *const *fighter_map_selected = tekken7;
byte n_fighter_map_selected = n_tekken7;

#endif // GAMES_H
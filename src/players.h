#ifndef PLAYERS_H
#define PLAYERS_H

// Using PROGMEM here to save some space for variables

const char players_FallenGameR[] PROGMEM = "FallenGameR";
const char players_Pobeditel[] PROGMEM = "Pobeditel";

const char *const players[] PROGMEM = {
    players_FallenGameR,
    players_Pobeditel,
};

#define n_players (sizeof(players) / sizeof(const char *))

byte player_index_first = -1;
byte player_index_second = -1;

#endif // PLAYERS_H
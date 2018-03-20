#ifndef PLAYERS_H
#define PLAYERS_H

const char *players[] = {
    "FallenGameR",
    "Pobeditel",
};

#define n_players (sizeof(players) / sizeof(const char *))

int player_index_first = -1;
int player_index_second = -1;

#endif // PLAYERS_H
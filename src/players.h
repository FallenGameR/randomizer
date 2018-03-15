#ifndef PLAYERS_H
#define PLAYERS_H

const char *players[] = {
    "FallenGameR",
    "Pobeditel",
};

#define n_players (sizeof(players) / sizeof(const char *))

int player_left = -1;
int player_right = -1;

#endif // PLAYERS_H
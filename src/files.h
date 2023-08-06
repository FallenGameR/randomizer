#ifndef FILES_H
#define FILES_H

#include <Arduino.h>

// We move as much constant strings to program memory as possible to
// free up very limited 2k of space used for variables and stats table
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

// Path constants
const char path_games[] PROGMEM = "/games/";
const char path_score[] PROGMEM = "/score/";
const char path_fighters[] PROGMEM = "/Fighters/";
const char path_name[] PROGMEM = "/name.txt";
const char path_tag[] PROGMEM = "/tag.txt";
const char path_icon[] PROGMEM = "/icon.bmp";
const char path_csv[] PROGMEM = ".csv";
const char path_separator[] PROGMEM = "/";
const char str_comma[] PROGMEM = ", ";

// The longest path should be 42 chars long
// /games/12345678/fighters/12345678/name.txt
// plus a trailing zero
#define BUFFER_PATH_MAX_LENGTH 43

// 16 is max LCD text length we could use to support
// tag games with 3 fighters plus a trailing zero
#define BUFFER_STRING_MAX_LENGTH 17

// Buffer for path to a file or folder
extern char b_path[];

// Buffer for a string that we read from a file.
// It is for a name of a game, player or fighter.
extern char b_string[];

// SD card initialization
void initSd();

// Reads number of known games
byte readNumberOfGames();

// Reads number of known players
byte readNumberOfPlayers();

// Reads number of fighters
byte readNumberOfFighters(byte game_index);

// Reads value of the game tag
byte readGameTag(byte game_index);

// Set b_string to something like "FallenGameR"
char* readPlayerName(byte player_index);

// Sets b_string to something like "Tekken 7"
char* readGameName(byte game_index);

// Sets b_string to something like "Kasumi"
char* readFighterName(byte game_index, byte fighter_index);

// Reads selected game index from /games/selected.txt
// -1 means we couldn't read the file
int readSelectedGame();

// Write selected game index to /games/selected.txt
void writeSelectedGame(byte game_index);

// Set b_path to /games/<game_name_from_index>/<progmem_path>
// progmem_path should be a path constant stored in PROGMEM
char* setGameRelativePathBuffer(byte game_index, const char *progmem_path);

// Set b_path to /games/<game_name_from_index>/fighters/<fighter_name_from_index>/<progmem_path>
// progmem_path should be a path constant stored in PROGMEM
char* setFighterRelativePathBuffer(byte game_index, byte fighter_index, const char *progmem_path);

#endif // FILES_H
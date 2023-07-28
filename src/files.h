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

// Functions below likely could be almost all made internal

// Returns unclosed <index> subfolder from /games/ folder on SD card
File openGameFolder(byte game_index);

// Returns unclosed <index> file  from /players/ folder on SD card
File openPlayerFile(byte player_index);

// Returns unclosed <fighter_index> subfolder from /games/<game_index>/fighters/ folder on SD card
File openFighterFolder(byte game_index, byte fighter_index);

// Set b_path to /games/<game_name_from_index>/<progmem_path>
// progmem_path should be a path constant stored in PROGMEM
char* setGameRelativePathBuffer(byte game_index, const char *progmem_path);

// Set b_path to /games/<game_name_from_index>/fighters/<fighter_name_from_index>/<progmem_path>
// progmem_path should be a path constant stored in PROGMEM
char* setFighterRelativePathBuffer(byte game_index, byte fighter_index, const char *progmem_path);

// Read string from the current position in a file and till the next EOL into b_string
char* readString(File file);

// Sets b_string to something like "Tekken 7"
char* setGameName(byte game_index);

// Sets b_string to something like "Kasumi"
char* setFighterName(byte gameIndex, byte fighterIndex);

// Set b_string to something like "FallenGameR"
char* setPlayerName(byte playerIndex);

// Sets b_string to something like "/SCORE/<random seed>.csv"
void setStatsPath(int random_seed);

// Reads number of fighters
byte readNumberOfFighters(byte game_index);

byte readGameTag(byte game_index);

#endif // FILES_H
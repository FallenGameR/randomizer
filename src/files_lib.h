#ifndef FILES_LIB_H
#define FILES_LIB_H

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

// Constant string for comma
const char str_comma[] PROGMEM = ", ";

// The longest path should be 42 chars long
// \games\12345678\FIGHTERS\12345678\name.txt
// plus trailing zero
#define BUFFER_PATH_MAX_LENGTH 43
extern char bufferPath[];

// 16 is max LCD text length plus trailing zero
#define BUFFER_NAME_MAX_LENGTH 17
extern char bufferName[];

// Reads number of known games
byte readNumberOfGames();

// Reads number of known players
byte readNumberOfPlayers();

// Returns unclosed <index> subfolder from /GAMES/ folder on SD card
File openGameFolder(byte gameIndex);

// Returns unclosed <index> file  from /PLAYERS/ folder on SD card
File openPlayerFile(byte playerIndex);

// Returns unclosed <index> subfolder from /GAMES/<game index> folder on SD card
File openFighterFolder(byte gameIndex, byte fighterIndex);

// Set bufferPath to something like "/GAMES/<name_from_index>/<path>"
void setGamePath(byte gameIndex, const char *path);

#endif // FILES_LIB_H
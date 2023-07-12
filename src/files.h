#ifndef FILES_H
#define FILES_H

#include <Arduino.h>
#include <SD.h>
#include "pins.h"
#include "random.h"
#include "players.h"

// We move as much constant strings to program memory as possible to
// free up very limited 2k of space used for variables and stats table
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

// Path constants
const char path_games[] PROGMEM = "/GAMES/";
const char path_score[] PROGMEM = "/SCORE/";
const char path_fighters[] PROGMEM = "/FIGHTERS/";
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
char bufferPath[BUFFER_PATH_MAX_LENGTH];

// 16 is max LCD text length plus trailing zero
#define BUFFER_NAME_MAX_LENGTH 17
char bufferName[BUFFER_NAME_MAX_LENGTH];

File empty;

// SD card initialization
void initSd()
{
    while (SD.begin(pin_sd_ccs))
    {
        Serial.println("Initializing SD card...");
    }
    Serial.println("SD card initialized");
}

// Set bufferName to content of the file, with new line chars trimmed
void setBufferName(File file)
{
    byte index = 0;
    while (file.available() && index < BUFFER_NAME_MAX_LENGTH - 1)
    {
        int c = file.read();
        if ((c == '\r') || (c == '\n'))
        {
            break;
        }
        bufferName[index++] = c;
    }
    bufferName[index++] = 0;
}

// Reads number of known games
// Takes ~88ms to finish
byte readNumberOfGames()
{
    File dir = SD.open(F("/GAMES/"));
    byte result = 0;

    while (File entry = dir.openNextFile())
    {
        if (entry.isDirectory())
        {
            result += 1;
        }

        entry.close();
    }

#ifdef DEBUG
    Serial.print("Number of games: ");
    Serial.println(result);
#endif
    return result;
}

// Reads number of players
// Takes ~88ms to finish
byte readNumberOfPlayers()
{
    File dir = SD.open(F("/PLAYERS/"));
    byte result = 0;

    while (File entry = dir.openNextFile())
    {
        if (!entry.isDirectory())
        {
            result += 1;
        }

        entry.close();
    }

#ifdef DEBUG
    Serial.print("Number of players: ");
    Serial.println(result);
#endif
    return result;
}

// Returns unclosed <index> subfolder from /GAMES/ folder on SD card
File openGameFolder(byte gameIndex)
{
    File dir = SD.open(F("/GAMES/"));
    byte skip = gameIndex;

    while (File entry = dir.openNextFile())
    {
        if (entry.isDirectory())
        {
            if (skip)
            {
                skip -= 1;
            }
            else
            {
                dir.close();
                return entry;
            }
        }

        entry.close();
    }

    dir.close();
    return empty;
}

// Returns unclosed <index> file  from /PLAYERS/ folder on SD card
File openPlayerFile(byte playerIndex)
{
    File dir = SD.open(F("/PLAYERS/"));
    byte skip = playerIndex;

    while (File entry = dir.openNextFile())
    {
        if (!entry.isDirectory())
        {
            if (skip)
            {
                skip -= 1;
            }
            else
            {
                dir.close();
                return entry;
            }
        }

        entry.close();
    }

    dir.close();
    return empty;
}

// Set bufferPath to something like "/GAMES/<name_from_index>/<path>"
void setGamePath(byte gameIndex, const char *path)
{
    File dir = openGameFolder(gameIndex);
    if (!dir)
    {
#ifdef DEBUG
        Serial.print(F("Can't open dir with index: "));
        Serial.println(gameIndex);
#endif
        return;
    }

    strcpy_P(bufferPath, path_games);
    strcpy(bufferPath + strlen_P(path_games), dir.name());
    strcpy_P(bufferPath + strlen(bufferPath), path);

    dir.close();

#ifdef DEBUG
    Serial.print(F("Path set to: "));
    Serial.println(bufferPath);
#endif
}

// Sets bufferName to something like "Tekken 7"
void setGameName(byte gameIndex)
{
    setGamePath(gameIndex, path_name);

    File file = SD.open(bufferPath);
    if (!file)
    {
        return;
    }

    setBufferName(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Game name is: "));
    Serial.println(bufferName);
#endif
}

// Sets bufferName to something like "/SCORE/<random seed>.csv"
void setStatsPath()
{
    strcpy_P(bufferPath, path_score);
    itoa(random_seed, bufferPath + strlen_P(path_score), 10);
    strcpy_P(bufferPath + strlen(bufferPath), path_csv);

#ifdef DEBUG
    Serial.print(F("Stats file: "));
    Serial.println(bufferName);
#endif
}

// Reads number of fighters
byte readNumberOfFighters(byte gameIndex)
{
    setGamePath(gameIndex, path_fighters);
    File dir = SD.open(bufferPath);
    if (!dir)
    {
        return 0;
    }

    byte result = 0;
    while (File entry = dir.openNextFile())
    {
        if (entry.isDirectory())
        {
            result += 1;
        }

        entry.close();
    }

#ifdef DEBUG
    Serial.print("Number of fighters: ");
    Serial.println(result);
#endif
    return result;
}

// Returns unclosed <index> subfolder from /GAMES/<game index> folder on SD card
File openFighterFolder(byte gameIndex, byte fighterIndex)
{
    setGamePath(gameIndex, path_fighters);
    File dir = SD.open(bufferPath);
    if (!dir)
    {
        return empty;
    }

    byte skip = fighterIndex;

    while (File entry = dir.openNextFile())
    {
        if (entry.isDirectory())
        {
            if (skip)
            {
                skip -= 1;
            }
            else
            {
                dir.close();
                return entry;
            }
        }

        entry.close();
    }

    dir.close();
    return empty;
}

// Set bufferPath to something like "/GAMES/<game index>/FIGHTERS/<fighter index>/<path>"
void setFighterPath(byte gameIndex, byte fighterIndex, const char *path)
{
    File game = openGameFolder(gameIndex);
    if (!game)
    {
        return;
    }

    File fighter = openFighterFolder(gameIndex, fighterIndex);
    if (!fighter)
    {
        game.close();
        return;
    }

    strcpy_P(bufferPath, path_games);
    strcpy(bufferPath + strlen(bufferPath), game.name());
    strcpy_P(bufferPath + strlen(bufferPath), path_fighters);
    strcpy(bufferPath + strlen(bufferPath), fighter.name());
    strcpy_P(bufferPath + strlen(bufferPath), path_separator);
    strcpy_P(bufferPath + strlen(bufferPath), path);

    game.close();
    fighter.close();

#ifdef DEBUG
    Serial.print(F("Path set to: "));
    Serial.println(bufferPath);
#endif
}

// Sets bufferName to something like "Kasumi"
void setFighterName(byte gameIndex, byte fighterIndex)
{
    setFighterPath(gameIndex, fighterIndex, path_name);

    File file = SD.open(bufferPath);
    if (!file)
    {
        return;
    }

    setBufferName(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Fighter name is: "));
    Serial.println(bufferName);
#endif
}

byte readGameTag(byte gameIndex)
{
    // No tag matches in multiplayer - too long wait time
    if (n_players >= 3)
    {
        return 0;
    }

    setGamePath(gameIndex, path_tag);

    File file = SD.open(bufferPath);
    if (!file)
    {
        return 0;
    }

    int tag = file.parseInt(SKIP_WHITESPACE);
    file.close();

#ifdef DEBUG
    Serial.print(F("Game tag is: "));
    Serial.println(tag);
#endif

    return (byte)tag;
}

// Set bufferName to something like "FallenGameR"
void setPlayerName(byte playerIndex)
{
    File file = openPlayerFile(playerIndex);
    if (!file)
    {
        return;
    }

    setBufferName(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Player name is: "));
    Serial.println(bufferName);
#endif
}

#endif // FILES_H
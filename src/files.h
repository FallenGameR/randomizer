#ifndef FILES_H
#define FILES_H

#include <Arduino.h>
#include <SD.h>
#include "pins.h"

// Path constants
const char path_games[] PROGMEM = "/GAMES/";
const char path_name[] PROGMEM = "/name.txt";
const char path_tag[] PROGMEM = "/tag.txt";

// The longest path should be 33 chars long
// \games\12345678\12345678\name.txt
// plus trailing zero
#define BUFFER_PATH_MAX_LENGTH 34
char bufferPath[BUFFER_PATH_MAX_LENGTH];

// 16 is max LCD text length plus trailing zero
#define BUFFER_NAME_MAX_LENGTH 17
char bufferName[BUFFER_NAME_MAX_LENGTH];

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
    File empty;
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
    File empty;
    return empty;
}

// Set bufferPath to something like "/GAMES/<name_from_index>/<path>"
void setGamePath(byte gameIndex, const char *path)
{
    File dir = openGameFolder(gameIndex);
    if (!dir)
    {
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

byte readGameTag(byte gameIndex)
{
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
#ifndef FILES_H
#define FILES_H

#include <Arduino.h>
#include <SD.h>
#include "pins.h"
#include "random.h"
#include "players.h"
#include "files_lib.h"


// SD card initialization
void initSd()
{
    Serial.print("Initializing SD card ");

    while( SD.begin(pin_sd_ccs) )
    {
        Serial.print("...");
    }

    Serial.println(" done");
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
void setStatsPath(int random_seed)
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
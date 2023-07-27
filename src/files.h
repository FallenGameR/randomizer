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

// Set b_name to content of the file, with new line chars trimmed
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
        b_name[index++] = c;
    }
    b_name[index++] = 0;
}

// Sets b_name to something like "Tekken 7"
void setGameName(byte game_index)
{
    File file = SD.open(setGameRelativePath(game_index, path_name));
    if (!file)
    {
        return;
    }

    setBufferName(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Game name is: "));
    Serial.println(b_name);
#endif
}

// Sets b_name to something like "/SCORE/<random seed>.csv"
void setStatsPath(int random_seed)
{
    strcpy_P(b_path, path_score);
    itoa(random_seed, b_path + strlen_P(path_score), 10);
    strcpy_P(b_path + strlen(b_path), path_csv);

#ifdef DEBUG
    Serial.print(F("Stats file: "));
    Serial.println(b_name);
#endif
}

// Reads number of fighters
byte readNumberOfFighters(byte game_index)
{
    File dir = SD.open(setGameRelativePath(game_index, path_fighters));
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

// Set b_path to something like "/GAMES/<game index>/FIGHTERS/<fighter index>/<path>"
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

    strcpy_P(b_path, path_games);
    strcpy(b_path + strlen(b_path), game.name());
    strcpy_P(b_path + strlen(b_path), path_fighters);
    strcpy(b_path + strlen(b_path), fighter.name());
    strcpy_P(b_path + strlen(b_path), path_separator);
    strcpy_P(b_path + strlen(b_path), path);

    game.close();
    fighter.close();

#ifdef DEBUG
    Serial.print(F("Path set to: "));
    Serial.println(b_path);
#endif
}

// Sets b_name to something like "Kasumi"
void setFighterName(byte gameIndex, byte fighterIndex)
{
    setFighterPath(gameIndex, fighterIndex, path_name);

    File file = SD.open(b_path);
    if (!file)
    {
        return;
    }

    setBufferName(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Fighter name is: "));
    Serial.println(b_name);
#endif
}

byte readGameTag(byte game_index)
{
    // No tag matches in multiplayer - too long wait time
    if (n_players >= 3)
    {
        return 0;
    }

    File file = SD.open(setGameRelativePath(game_index, path_tag));
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

// Set b_name to something like "FallenGameR"
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
    Serial.println(b_name);
#endif
}

#endif // FILES_H
#ifndef FILES_H
#define FILES_H

#include <Arduino.h>
#include <SD.h>
#include "pins.h"
#include "random.h"
#include "players.h"
#include "files_lib.h"

bool isEol(int c)
{
    return (c == '\r') || (c == '\n');
}

// Read string from the current position in a file and till the next EOL into b_string
char* readString(File file)
{
    // Sanity check
    if( !file )
    {
        memset(b_string, 0, BUFFER_STRING_MAX_LENGTH);
        return b_string;
    }

    // Skip EOL if we are standing on it
    for( int c = file.read(); c > 0; c = file.read() )
    {
        if( !isEol(c) )
        {
            file.seek(file.position() - 1);
            break;
        }
    }

    // Read into b_string buffer until EOL
    byte index = 0;

    for( int c = file.read(); (c > 0) && !isEol(c); c = file.read() )
    {
        b_string[index++] = c;
        if( index >= BUFFER_STRING_MAX_LENGTH - 1 ) { break; }
    }

    // Make sure b_string is null-terminated
    b_string[index++] = 0;
    return b_string;
}

// Sets b_string to something like "Tekken 7"
char* setGameName(byte game_index)
{
    File file = SD.open(setGameRelativePathBuffer(game_index, path_name));
    char* buffer = readString(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Game name is: "));
    Serial.println(buffer);
#endif

    return buffer;
}

// Sets b_string to something like "Kasumi"
char* setFighterName(byte gameIndex, byte fighterIndex)
{
    setFighterRelativePathBuffer(gameIndex, fighterIndex, path_name);

    File file = SD.open(b_path);
    char* buffer = readString(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Fighter name is: "));
    Serial.println(buffer);
#endif

    return buffer;
}

// Set b_string to something like "FallenGameR"
char* setPlayerName(byte playerIndex)
{
    File file = openPlayerFile(playerIndex);
    char* buffer = readString(file);
    file.close();

#ifdef DEBUG
    Serial.print(F("Player name is: "));
    Serial.println(b_string);
#endif

    return buffer;
}

// Sets b_string to something like "/SCORE/<random seed>.csv"
void setStatsPath(int random_seed)
{
    strcpy_P(b_path, path_score);
    itoa(random_seed, b_path + strlen_P(path_score), 10);
    strcpy_P(b_path + strlen(b_path), path_csv);

#ifdef DEBUG
    Serial.print(F("Stats file: "));
    Serial.println(b_string);
#endif
}

// Reads number of fighters
byte readNumberOfFighters(byte game_index)
{
    File dir = SD.open(setGameRelativePathBuffer(game_index, path_fighters));
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

byte readGameTag(byte game_index)
{
    // No tag matches in multiplayer - too long wait time
    if (n_players >= 3)
    {
        return 0;
    }

    File file = SD.open(setGameRelativePathBuffer(game_index, path_tag));
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

#endif // FILES_H
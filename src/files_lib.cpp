#include <SD.h>
#include "files_lib.h"
#include "pins.h"

//------------------------------------------------------------------------------/ DATA

// Empty file to return when no file is found
File empty;

char b_path[BUFFER_PATH_MAX_LENGTH];

char b_string[BUFFER_STRING_MAX_LENGTH];

//------------------------------------------------------------------------------/ PRIVATE FUNCTIONS

// Takes ~88ms to count games or players
void readElementsInFolder(const String &path, byte &files, byte &dirs)
{
    files = 0;
    dirs = 0;

    File dir = SD.open(path);

    while( File entry = dir.openNextFile() )
    {
        if( entry.isDirectory() )
        {
            dirs += 1;
        }
        else
        {
            files += 1;
        }

        entry.close();
    }
}

// Opens <index> file or folder from <path> on SD card
File openElementInFolder(const String &path, byte index, bool isDir)
{
    File dir = SD.open(path);
    byte skip = index;

    while( File entry = dir.openNextFile() )
    {
        if( entry.isDirectory() == isDir )
        {
            if( skip )
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

    Serial.print(F("Can't open "));
    Serial.print(isDir ? F("dir") : F("file"));
    Serial.print(F(" '"));
    Serial.print(path);
    Serial.print(F("'["));
    Serial.print(index);
    Serial.println(F("]"));

    dir.close();
    return empty;
}

//------------------------------------------------------------------------------/ PUBLIC FUNCTIONS

void initSd()
{
    Serial.print("Initializing SD card ");

    while( SD.begin(pin_sd_ccs) )
    {
        Serial.print("...");
    }

    Serial.println(" done");
}

byte readNumberOfGames()
{
    byte files, dirs;
    readElementsInFolder(F("/games/"), files, dirs);
    return dirs;
}

byte readNumberOfPlayers()
{
    byte files, dirs;
    readElementsInFolder(F("/players/"), files, dirs);
    return files;
}

File openGameFolder(byte game_index)
{
    return openElementInFolder(F("/games/"), game_index, true);
}

File openPlayerFile(byte player_index)
{
    return openElementInFolder(F("/players/"), player_index, false);
}

File openFighterFolder(byte game_index, byte fighter_index)
{
    return openElementInFolder(setGameRelativePathBuffer(game_index, path_fighters), fighter_index, true);
}

char* setGameRelativePathBuffer(byte game_index, const char *progmem_path)
{
    File dir = openGameFolder(game_index);
    if( !dir )
    {
        Serial.print(F("Can't open game folder: "));
        Serial.println(game_index);
        memset(b_path, 0, BUFFER_PATH_MAX_LENGTH);
        return b_path;
    }

    size_t len = strlen_P(path_games) + strlen(dir.name()) + strlen_P(progmem_path) + 1;
    if( len > BUFFER_PATH_MAX_LENGTH )
    {
        Serial.print(F("Path is too long: "));
        Serial.println(len);
        memset(b_path, 0, BUFFER_PATH_MAX_LENGTH);
    }
    else
    {
        // b_path = "/games/<game folder name>/<path>"
        strcpy_P(b_path, path_games);
        strcpy(b_path + strlen_P(path_games), dir.name());
        strcpy_P(b_path + strlen(b_path), progmem_path);
    }

    dir.close();
    return b_path;
}

char* setFighterPath(byte gameIndex, byte fighterIndex, const char *path)
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
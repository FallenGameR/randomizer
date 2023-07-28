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

char* setFighterRelativePathBuffer(byte game_index, byte fighter_index, const char *progmem_path)
{
    File game = openGameFolder(game_index);
    if( !game )
    {
        Serial.print(F("Can't open game folder: "));
        Serial.println(game_index);
        memset(b_path, 0, BUFFER_PATH_MAX_LENGTH);
        return b_path;
    }

    File fighter = openFighterFolder(game_index, fighter_index);
    if( !fighter )
    {
        Serial.print(F("Can't open fighter folder: "));
        Serial.println(fighter_index);
        game.close();
        memset(b_path, 0, BUFFER_PATH_MAX_LENGTH);
        return b_path;
    }

    size_t len_game_folder = strlen_P(path_games);
    size_t len_game_name = strlen(game.name());
    size_t len_fighter_folder = strlen_P(path_fighters);
    size_t len_fighter_name = strlen(fighter.name());
    size_t len_separator = strlen_P(path_separator);
    size_t len_progmem_path = strlen_P(progmem_path);
    size_t len_trailing_zero = 1;

    size_t len =
        len_game_folder +
        len_game_name +
        len_fighter_folder +
        len_fighter_name +
        len_separator +
        len_progmem_path +
        len_trailing_zero;

    if( len >= BUFFER_PATH_MAX_LENGTH )
    {
        Serial.print(F("Path is too long: "));
        Serial.println(len);
        game.close();
        fighter.close();
        memset(b_path, 0, BUFFER_PATH_MAX_LENGTH);
        return b_path;
    }

    len = 0;
    strcpy_P(b_path, path_games);

    len += len_game_folder;
    strcpy(b_path + len, game.name());

    len += len_game_name;
    strcpy_P(b_path + len, path_fighters);

    len += len_fighter_folder;
    strcpy(b_path + len, fighter.name());

    len += len_fighter_name;
    strcpy_P(b_path + len, path_separator);

    len += len_separator;
    strcpy_P(b_path + len, progmem_path);

    game.close();
    fighter.close();

    return b_path;
}
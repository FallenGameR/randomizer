#include <SD.h>
#include "files_lib.h"

// Empty file to return when no file is found
File empty;

char bufferPath[BUFFER_PATH_MAX_LENGTH];

char bufferName[BUFFER_NAME_MAX_LENGTH];

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
    setGamePath(game_index, path_fighters);
    return openElementInFolder(bufferPath, fighter_index, true);
}

// Set bufferPath to something like "/GAMES/<name_from_index>/<path>"
void setGamePath(byte gameIndex, const char *path)
{
    File dir = openGameFolder(gameIndex);
    if( !dir )
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
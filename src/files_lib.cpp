#include <SD.h>
#include "files_lib.h"

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
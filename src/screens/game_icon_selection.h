#ifndef GAME_ICON_SELECTION_H
#define GAME_ICON_SELECTION_H

#include "..\tft.h"

void printDirectory(File dir, int numTabs)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            // no more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            tft.print('\t');
        }
        tft.print(entry.name());
        if (entry.isDirectory())
        {
            tft.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            // files have sizes, directories do not
            tft.print("\t\t");
            tft.println(entry.size(), DEC);
        }
        entry.close();
    }
}

void GameIconSelectionScreen()
{
    tft.println("Initializing SD card...");
    while (SD.begin(pin_sd_ccs))
    {
        tft.println("failed!");
    }
    tft.println("OK!");

    File root = SD.open("/");
    printDirectory(root, 0);
    tft.println("done!");
}

#endif // GAME_ICON_SELECTION_H
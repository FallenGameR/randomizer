#ifndef GAME_ICON_SELECTION_H
#define GAME_ICON_SELECTION_H

#include "..\tft.h"
#include <SPI.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

void GameIconSelectionScreen()
{
    /*
    tft.println("Initializing SD card...");

    // we'll use the initialization code from the utility libraries
    // since we're just testing if the card is working!
    if (!card.init(SPI_HALF_SPEED, pin_sd_ccs))
    {
        tft.println("initialization failed");
        return;
    }
    else
    {
        tft.println("Wiring is correct and a card is present.");
    }

    // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
    if (!volume.init(card))
    {
        tft.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
        return;
    }

    // list all files in the card with date and size
    root.openRoot(volume);
    root.ls(LS_R | LS_DATE | LS_SIZE);
/**/
    setupBmp();
    delay(100000);
}

#endif // GAME_ICON_SELECTION_H
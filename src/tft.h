#ifndef TFT_H
#define TFT_H

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <SD.h>
#include "pins.h"

#define FONT_SIZE 2

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout/pinouts
// Uses 8-Bit Mode
Adafruit_TFTLCD tft = Adafruit_TFTLCD(pin_tft_cs, pin_tft_dc, pin_tft_wr, pin_tft_rd, pin_tft_rst);

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f)
{
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t read32(File &f)
{
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}

/*

To make new bitmaps, make sure they are less than 320 by 480 pixels and save them in 24-bit BMP format! They must be in 24-bit format, even if they are not 24-bit color as that is the easiest format for the Arduino. You can rotate images using the setRotation() procedure

?
You can draw as many images as you want - dont forget the names must be less than 8 characters long. Just copy the BMP drawing routines below loop() and call
?

/**/

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.
#define BUFFPIXEL 20

void drawImage(File bmpFile, int16_t startX, int16_t startY)
{
    uint32_t startTime = millis();

    // BMP signature
    if (read16(bmpFile) != 0x4D42)
    {
        Serial.println(F("BMP header missing"));
        return;
    }

    // BMP header
    Serial.print(F("File size: "));
    Serial.println(read32(bmpFile));
    read32(bmpFile);
    uint32_t bmpImageOffset = read32(bmpFile);
    Serial.print(F("Image offset: "));
    Serial.println(bmpImageOffset);
    Serial.print(F("Header size: "));
    Serial.println(read32(bmpFile));
    int bmpWidth = read32(bmpFile);
    int bmpHeight = read32(bmpFile);
    Serial.print(F("Image size: "));
    Serial.print(bmpWidth);
    Serial.print('x');
    Serial.println(bmpHeight);

    if (read16(bmpFile) != 1)
    {
        Serial.println(F("BMP number of planes is not 1"));
        return;
    }

    uint8_t bmpBitsPerPixel = read16(bmpFile);
    Serial.print(F("Bit Depth: "));
    Serial.println(bmpBitsPerPixel);

    if (bmpBitsPerPixel != 24)
    {
        Serial.println(F("BMP bits per pixel is not 24"));
        return;
    }

    if (read32(bmpFile) != 0)
    {
        Serial.println(F("BMP is compressed"));
        return;
    }

    // BMP rows are padded (if needed) to 4-byte boundary
    uint32_t rowSize = (bmpWidth * 3 + 3) & ~3;

    // If bmpHeight is negative, image is in top-down order.
    // This is not canon but has been observed in the wild.
    boolean flip = true; // BMP is stored bottom-to-top
    if (bmpHeight < 0)
    {
        bmpHeight = -bmpHeight;
        flip = false;
    }

    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel buffer (R+G+B per pixel)
    uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    int row, col;
    uint8_t r, g, b;
    uint32_t pos = 0;
    long pixelsWritten = 0;

    // Crop area to be loaded
    int width = bmpWidth;
    int height = bmpHeight;
    if ((startX + width - 1) >= tft.width())
    {
        width = tft.width() - startX;
    }
    if ((startY + height - 1) >= tft.height())
    {
        height = tft.height() - startY;
    }

    // Start TFT transaction
    // Set TFT address window to clipped image bounds
    tft.startWrite();
    tft.setAddrWindow(startX, startY, width, height);

    for (row = 0; row < height; row++)
    {
        // Seek to start of scan line.  It might seem labor-
        // intensive to be doing this on every line, but this
        // method covers a lot of gritty details like cropping
        // and scanline padding.  Also, the seek only takes
        // place if the file position actually needs to change
        // (avoids a lot of cluster math in SD library).
        if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
        {
            pos = bmpImageOffset + (bmpHeight - 1 - row) * rowSize;
        }
        else // Bitmap is stored top-to-bottom
        {
            pos = bmpImageOffset + row * rowSize;
        }

        if (bmpFile.position() != pos)
        {                   // Need seek?
            tft.endWrite(); // End TFT transaction
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
            tft.startWrite();           // Start new TFT transaction
        }

        for (col = 0; col < width; col++)
        {
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer))
            {                   // Indeed
                tft.endWrite(); // End TFT transaction
                bmpFile.read(sdbuffer, sizeof(sdbuffer));
                buffidx = 0;      // Set index to beginning
                tft.startWrite(); // Start new TFT transaction
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.writePixel(col + startX, row + startY, tft.color565(r, g, b));
            pixelsWritten += 1;
        }
    }

    // End last TFT transaction
    tft.endWrite();
    Serial.print(F("Pixels written: "));
    Serial.println(pixelsWritten);
    Serial.print(F("Loaded in "));
    Serial.print(millis() - startTime);
    Serial.println(" ms");
}

void bmpDraw(char *filename, int16_t startX, int16_t startY)
{
    Serial.print(F("Drawing image: "));
    Serial.println(filename);

    // Sanity check
    if ((startX >= tft.width()) || (startY >= tft.height()))
    {
        Serial.println("Image doesn't fit the screen");
        return;
    }

    // Open image file on SD card
    File bmpFile = SD.open(filename);
    if (bmpFile == 0)
    {
        Serial.println(F("Image file was not found on SD card"));
        return;
    }

    // Draw image
    drawImage(bmpFile, startX, startY);

    // Close file
    bmpFile.close();
}

void initSd()
{
    while (SD.begin(pin_sd_ccs))
    {
        Serial.println("Initializing SD card...");
    }
    Serial.println("SD card initialized");
}

void setupBmp()
{
    initSd();
    tft.fillScreen(WHITE);

    bmpDraw("GAMES/DoA_5/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/GGX_Rev/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/KI/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/KoF_14/ICON.BMP", 0, 0);

    //bmpDraw("GAMES/MK_XL/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/SF_5/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/Tek_7/ICON.BMP", 0, 0);
}

#endif // TFT_H
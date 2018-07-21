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

void bmpDraw(char *filename, uint16_t x, uint16_t y)
{
    File bmpFile;
    int bmpWidth, bmpHeight;            // W+H in pixels
    uint8_t bmpDepth;                   // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;            // Start of image data in file
    uint32_t rowSize;                   // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel buffer (R+G+B per pixel)
    uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    boolean goodBmp = false;            // Set to true on valid header parse
    boolean flip = true;                // BMP is stored bottom-to-top
    int w, h, row, col;
    uint8_t r, g, b;
    uint32_t pos = 0, startTime = millis();

    if ((x >= tft.width()) || (y >= tft.height()))
        return;

    Serial.println();
    Serial.print(F("Loading image '"));
    Serial.print(filename);
    Serial.println('\'');

    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) == NULL)
    {
        Serial.print(F("File not found"));
        return;
    }

    long pixelsWritten = 0;

    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        Serial.print(F("File size: "));
        Serial.println(read32(bmpFile));
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        Serial.print(F("Image Offset: "));
        Serial.println(bmpImageoffset, DEC);
        // Read DIB header
        Serial.print(F("Header size: "));
        Serial.println(read32(bmpFile));
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);

        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            Serial.print(F("Bit Depth: "));
            Serial.println(bmpDepth);
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            { // 0 = uncompressed

                goodBmp = true; // Supported BMP format -- proceed!
                Serial.print(F("Image size: "));
                Serial.print(bmpWidth);
                Serial.print('x');
                Serial.println(bmpHeight);

                // BMP rows are padded (if needed) to 4-byte boundary
                rowSize = (bmpWidth * 3 + 3) & ~3;

                // If bmpHeight is negative, image is in top-down order.
                // This is not canon but has been observed in the wild.
                if (bmpHeight < 0)
                {
                    bmpHeight = -bmpHeight;
                    flip = false;
                }

                // Crop area to be loaded
                w = bmpWidth;
                h = bmpHeight;
                //*
                if ((x + w - 1) >= tft.width())
                    w = tft.width() - x;
                if ((y + h - 1) >= tft.height())
                    h = tft.height() - y;
                /**/
                // Set TFT address window to clipped image bounds
                tft.startWrite(); // Start TFT transaction
                //tft.setAddrWindow(x, y, w, h);

                for (row = 0; row < h; row++)
                { // For each scanline...

                    // Seek to start of scan line.  It might seem labor-
                    // intensive to be doing this on every line, but this
                    // method covers a lot of gritty details like cropping
                    // and scanline padding.  Also, the seek only takes
                    // place if the file position actually needs to change
                    // (avoids a lot of cluster math in SD library).
                    if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    else // Bitmap is stored top-to-bottom
                        pos = bmpImageoffset + row * rowSize;
                    if (bmpFile.position() != pos)
                    {                   // Need seek?
                        tft.endWrite(); // End TFT transaction
                        bmpFile.seek(pos);
                        buffidx = sizeof(sdbuffer); // Force buffer reload
                        tft.startWrite();           // Start new TFT transaction
                    }

                    for (col = 0; col < w; col++)
                    { // For each pixel...
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
                        tft.writePixel(col + x, row + y, tft.color565(r, g, b));
                        pixelsWritten += 1;

                    }           // end pixel
                }               // end scanline
                tft.endWrite(); // End last TFT transaction
                Serial.print(F("Pixels written: "));
                Serial.println(pixelsWritten);
                Serial.print(F("Loaded in "));
                Serial.print(millis() - startTime);
                Serial.println(" ms");

                /*
                tft.print(F("Loaded in "));
                tft.print(millis() - startTime);
                tft.println(" ms");
                /**/
            } // end goodBmp
        }
    }

    bmpFile.close();
    if (!goodBmp)
        Serial.println(F("BMP format not recognized."));
}

void setupBmp()
{
    Serial.print("Initializing SD card...");
    while (SD.begin(pin_sd_ccs))
    {
        Serial.println("failed!");
    }
    Serial.println("OK!");

    tft.fillScreen(WHITE);

    //bmpDraw("GAMES/DoA_5/ICON.BMP", 0, 0);
    bmpDraw("GAMES/GGX_Rev/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/KI/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/KoF_14/ICON.BMP", 0, 0);

    //bmpDraw("GAMES/MK_XL/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/SF_5/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/Tek_7/ICON.BMP", 0, 0);
}

#endif // TFT_H
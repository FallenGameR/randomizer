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

    // Crop rendered image if it doesn't fit the screen
    int width = bmpWidth;
    int height = bmpHeight;
    if ((startX + width) > tft.width())
    {
        width = tft.width() - startX;
    }
    if ((startY + height) > tft.height())
    {
        height = tft.height() - startY;
    }

    // BMP rows are padded to 4-byte boundary
    uint32_t rowSize = (bmpWidth * 3 + 3) & ~3;

    // BMP is usually stored bottom-to-top.
    // But if bmpHeight is negative, image is in top-down order.
    boolean flip = true;
    if (bmpHeight < 0)
    {
        bmpHeight = -bmpHeight;
        flip = false;
    }

    uint8_t rgbBuffer[3 * BUFFPIXEL];
    uint8_t rgbBufferIndex = sizeof(rgbBuffer);
    uint8_t r, g, b;
    uint32_t pos = 0;
    long pixelsWritten = 0;

    // setAddrWindow looks like noop for some displays/wiring options
    tft.setAddrWindow(startX, startY, width, height);

    // Start TFT transaction
    tft.startWrite();

    for (int y = 0; y < height; y++)
    {
        // Find position of BMP row that we render on line y
        if (flip)
        {
            pos = bmpImageOffset + (bmpHeight - 1 - y) * rowSize;
        }
        else
        {
            pos = bmpImageOffset + y * rowSize;
        }

        // If seek needed, do it and force buffer reload
        if (bmpFile.position() != pos)
        {
            tft.endWrite();
            bmpFile.seek(pos);
            rgbBufferIndex = sizeof(rgbBuffer);
            tft.startWrite();
        }

        for (int x = 0; x < width; x++)
        {
            // Read pixels from SD into buffer if needed
            if (rgbBufferIndex >= sizeof(rgbBuffer))
            {
                tft.endWrite();
                bmpFile.read(rgbBuffer, sizeof(rgbBuffer));
                rgbBufferIndex = 0;
                tft.startWrite();
            }

            // Convert pixel from BMP to TFT format, push to display
            b = rgbBuffer[rgbBufferIndex++];
            g = rgbBuffer[rgbBufferIndex++];
            r = rgbBuffer[rgbBufferIndex++];
            tft.writePixel(x + startX, y + startY, tft.color565(r, g, b));
            pixelsWritten += 1;
        }
    }

    // End last TFT transaction
    tft.endWrite();
    Serial.print(F("Pixels written: "));
    Serial.println(pixelsWritten);
    Serial.print(F("Rendered in: "));
    Serial.print(millis() - startTime);
    Serial.println("ms");
}

void bmpDraw(const char *filename, int16_t startX, int16_t startY)
{
    Serial.print(F("Drawing image: "));
    Serial.println(filename);

    // Sanity check
    if ((startX >= tft.width()) || (startY >= tft.height()))
    {
        Serial.println("Image render position is outside the screen");
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

#include <Fonts/FreeSerif24pt7b.h>

//File root = SD.open(F("/GAMES/"));
//printDirectory(root, 0);
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

        if (entry.isDirectory())
        {
            Serial.println(entry.name());
            //printDirectory(entry, numTabs + 1);
        }
        else
        {
            // files have sizes, directories do not
            //Serial.print(F("____"));
            //Serial.println(entry.size());
        }

        entry.close();
    }
}

// Takes ~88ms to finish
/*
    Serial.println(F("____________________"));
    Serial.print(F("Games count: "));
    unsigned long start = millis();
    Serial.println(getNumberOfGames());
    unsigned long elapsed = millis() - start;
    Serial.print(F("Read time in ms: "));
    Serial.println(elapsed);
    */

byte getNumberOfGames()
{
    File dir = SD.open(F("/GAMES/"));
    byte result = 0;

    while (File entry = dir.openNextFile())
    {
        if (entry.isDirectory())
        {
            result += 1;
        }

        entry.close();
    }

    return result;
}

// The longest path should be 33 chars long: \games\12345678\12345678\name.txt plus trailing zero
#define BUFFER_PATH_MAX_LENGTH 34
char bufferPath[BUFFER_PATH_MAX_LENGTH];

// 16 is max LCD text length +1 trailing zero
#define BUFFER_NAME_MAX_LENGTH 17
char bufferName[BUFFER_NAME_MAX_LENGTH];

const char path_games[] PROGMEM = "/GAMES/";
const char path_name[] PROGMEM = "/name.txt";
const char path_tag[] PROGMEM = "/tag.txt";

// Returns unclosed <index> subfolder from /GAMES/ folder on SD card
File openGameFolder(byte gameIndex)
{
    File dir = SD.open(F("/GAMES/"));
    byte skip = gameIndex;

    while (File entry = dir.openNextFile())
    {
        if (entry.isDirectory())
        {
            if (skip)
            {
                skip -= 1;
            }
            else
            {
                return entry;
            }
        }

        entry.close();
    }
}

// Sets bufferPath to something like /GAMES/<name_from_index>/<path>
void setGamePath(byte gameIndex, const char *path)
{
    File dir = openGameFolder(gameIndex);
    if (!dir)
    {
        return;
    }

    Serial.print(F("Path is set to: "));
    strcpy_P(bufferPath, path_games);
    strcpy(bufferPath + strlen_P(path_games), dir.name());
    strcpy_P(bufferPath + strlen(bufferPath), path);
    Serial.println(bufferPath);

    dir.close();
}

// Reads game name into bufferName
void readGameName(byte gameIndex)
{
    setGamePath(gameIndex, path_name);

    File file = SD.open(bufferPath);
    if (!file)
    {
        return;
    }

    byte index = 0;
    while (file.available() && index < BUFFER_NAME_MAX_LENGTH - 1)
    {
        int c = file.read();
        if ((c == '\r') || (c == '\n'))
        {
            break;
        }
        bufferName[index++] = c;
    }
    bufferName[index++] = 0;

    Serial.print(F("Game name is: "));
    Serial.println(bufferName);
    file.close();
}

byte readGameTag(byte gameIndex)
{
    setGamePath(gameIndex, path_tag);

    File file = SD.open(bufferPath);
    if (!file)
    {
        return 0;
    }

    int tag = file.parseInt(SKIP_WHITESPACE);
    Serial.print(F("Game tag is: "));
    Serial.println(tag);
    file.close();
    return (byte)tag;
}

void setupBmp()
{
    readGameName(6);
    readGameTag(6);

    tft.fillScreen(WHITE);

    tft.setFont(&FreeSerif24pt7b);
    tft.setCursor(340, 180);
    tft.setTextColor(BLACK);
    tft.println(F("tag"));
    tft.setFont();

    //bmpDraw("GAMES/DoA_5/ICON.BMP", 0, 0);

    //bmpDraw("GAMES/GGX_Rev/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/KI/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/KoF_14/ICON.BMP", 0, 0);

    //bmpDraw("GAMES/MK_XL/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/SF_5/ICON.BMP", 0, 0);
    //bmpDraw("GAMES/Tek_7/ICON.BMP", 0, 0);
}

#endif // TFT_H
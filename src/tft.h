#ifndef TFT_H
#define TFT_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerif24pt7b.h>
#include <SD.h>
#include "shared.h"

#define FONT_SIZE 2
#define CHAR_WIDTH (6 * FONT_SIZE)
#define CHAR_HEIGHT (8 * FONT_SIZE)

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.
#define PIXEL_BUFFER_LENGTH 20

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

// bmpFile - bmp file to draw
// mirror - false to display picture as is, true to mirror the image left to right
// startX - screen position X where to draw the picture
// startY - screen position Y where to draw the picture
// part - what part of the picture to draw: 1 - whole, 2 - half (centred), 3 - third (centered)
void drawImage(File bmpFile, boolean mirror, int16_t startX, int16_t startY, int16_t part)
{
    uint32_t startTime = millis();

    // BMP signature
    if (read16(bmpFile) != 0x4D42)
    {
        Serial.println(F("BMP header missing"));
        return;
    }

    // BMP header
    uint32_t fileSize = read32(bmpFile);
#ifdef DEBUG
    Serial.print(F("File size: "));
    Serial.println(fileSize);
#endif
    read32(bmpFile);
    uint32_t bmpImageOffset = read32(bmpFile);
    uint32_t headerSize = read32(bmpFile);

#ifdef DEBUG
    Serial.print(F("Image offset: "));
    Serial.println(bmpImageOffset);
    Serial.print(F("Header size: "));
    Serial.println(headerSize);
#endif
    int bmpWidth = read32(bmpFile);
    int bmpHeight = read32(bmpFile);

#ifdef DEBUG
    Serial.print(F("Image size: "));
    Serial.print(bmpWidth);
    Serial.print('x');
    Serial.println(bmpHeight);
#endif

    if (read16(bmpFile) != 1)
    {
        Serial.println(F("BMP number of planes is not 1"));
        return;
    }

    uint8_t bmpBitsPerPixel = read16(bmpFile);

#ifdef DEBUG
    Serial.print(F("Bit Depth: "));
    Serial.println(bmpBitsPerPixel);
#endif

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
    int width = bmpWidth / part;
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

    uint8_t rgbBuffer[3 * PIXEL_BUFFER_LENGTH];
    uint8_t rgbBufferIndex = sizeof(rgbBuffer);
    uint8_t r, g, b;
    uint32_t pos = 0;
    long pixelsWritten = 0;
    bool wasCancelled = false;

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

        // Offset for part drawings if needed
        int trim = bmpWidth - width;
        int rowOffset = trim / 2;
        if (rowOffset > 0)
        {
            pos += rowOffset * 3;
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

            if (!mirror)
            {
                tft.writePixel(startX + x, startY + y, tft.color565(r, g, b));
            }
            else
            {
                tft.writePixel(startX + width - x, startY + y, tft.color565(r, g, b));
            }

            pixelsWritten += 1;
        }

        // User cancel if needed
        readInput();

        if (input_allowed && BUTTON_BLACK)
        {
            wasCancelled = true;
            input_allowed = false;
            break;
        }
    }

    // End last TFT transaction
    tft.endWrite();

    if( wasCancelled )
    {
        Serial.print(F(" (cancel)"));
    }
    else
    {
        Serial.print(F(" (done)"));
    }

#ifdef DEBUG
    Serial.print(F("Pixels written: "));
    Serial.println(pixelsWritten);
    Serial.print(F("Rendered in: "));
    Serial.print(millis() - startTime);
    Serial.println("ms");
#endif
}

void bmpDraw(const char *filename, boolean mirror, int16_t startX, int16_t startY, int16_t part)
{
    Serial.print(F("Drawing image: "));
    Serial.print(filename);

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
    drawImage(bmpFile, mirror, startX, startY, part);
    Serial.println();

    // Close file
    bmpFile.close();
}

#endif // TFT_H
#ifndef TFT_H
#define TFT_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerif24pt7b.h>
#include <SD.h>
#include "shared.h"
#include "input.h"

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
uint16_t read16(File &f);

uint32_t read32(File &f);

// bmpFile - bmp file to draw
// mirror - false to display picture as is, true to mirror the image left to right
// startX - screen position X where to draw the picture
// startY - screen position Y where to draw the picture
// part - what part of the picture to draw: 1 - whole, 2 - half (centred), 3 - third (centered)
void drawImage(File bmpFile, boolean mirror, int16_t startX, int16_t startY, int16_t part, bool allowInputOnCancel = false);

void bmpDraw(const char *filename, boolean mirror, int16_t startX, int16_t startY, int16_t part, bool allowInputOnCancel = false);

#endif // TFT_H
#ifndef TFT_H
#define TFT_H

#include <Arduino.h>

#define FONT_SIZE 2
#define CHAR_WIDTH (6 * FONT_SIZE)
#define CHAR_HEIGHT (8 * FONT_SIZE)

void bmpDraw(const char *filename, boolean mirror, int16_t startX, int16_t startY, int16_t part, bool allowInputOnCancel = false);

#endif // TFT_H
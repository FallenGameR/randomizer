#ifndef COLORS_H
#define COLORS_H

#include "players.h"

#define LT_BLUE 0xB6DF
#define LT_TEAL 0xBF5F
#define LT_GREEN 0xBFF7
#define LT_CYAN 0xC7FF
#define LT_RED 0xFD34
#define LT_MAGENTA 0xFD5F
#define LT_YELLOW 0xFFF8
#define LT_ORANGE 0xFE73
#define LT_PINK 0xFDDF
#define LT_PURPLE 0xCCFF
#define LT_GREY 0xE71C

#define BLUE 0x001F
#define TEAL 0x0438
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00
//#define PINK 0xF81F would be a redefinition
#define PURPLE 0x8010
#define GREY 0xC618
#define WHITE 0xFFFF
#define BLACK 0x0000

#define DK_BLUE 0x000D
#define DK_TEAL 0x020C
#define DK_GREEN 0x03E0
#define DK_CYAN 0x03EF
#define DK_RED 0x6000
#define DK_MAGENTA 0x8008
#define DK_YELLOW 0x8400
#define DK_ORANGE 0x8200
#define DK_PINK 0x9009
#define DK_PURPLE 0x4010
#define DK_GREY 0x4A49

unsigned int playerColors[MAX_PLAYERS];

void InitPlayerColors()
{
    playerColors[0] = CYAN;
    playerColors[1] = YELLOW;
    playerColors[2] = LT_PURPLE;

    playerColors[3] = BLUE;
    playerColors[4] = ORANGE;
    playerColors[5] = MAGENTA;

    playerColors[6] = DK_BLUE;
    playerColors[7] = DK_YELLOW;
    playerColors[8] = PURPLE;

    playerColors[9] = DK_CYAN;
    playerColors[10] = DK_ORANGE;
    playerColors[11] = DK_MAGENTA;

    playerColors[12] = GREEN;
    playerColors[13] = RED;
    playerColors[14] = LT_GREEN;
    playerColors[15] = LT_RED;
}

#endif // COLORS_H
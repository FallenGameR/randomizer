#ifndef COLORS_H
#define COLORS_H

#include "players.h"

#define LTBLUE 0xB6DF
#define LTTEAL 0xBF5F
#define LTGREEN 0xBFF7
#define LTCYAN 0xC7FF
#define LTRED 0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW 0xFFF8
#define LTORANGE 0xFE73
#define LTPINK 0xFDDF
#define LTPURPLE 0xCCFF
#define LTGREY 0xE71C

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

#define DKBLUE 0x000D
#define DKTEAL 0x020C
#define DKGREEN 0x03E0
#define DKCYAN 0x03EF
#define DKRED 0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW 0x8400
#define DKORANGE 0x8200
#define DKPINK 0x9009
#define DKPURPLE 0x4010
#define DKGREY 0x4A49

unsigned int playerColors[MAX_PLAYERS];

void InitPlayerColors()
{
    playerColors[0] = CYAN;
    playerColors[1] = YELLOW;
    playerColors[2] = LTPURPLE;

    playerColors[3] = BLUE;
    playerColors[4] = ORANGE;
    playerColors[5] = MAGENTA;

    playerColors[6] = DKBLUE;
    playerColors[7] = DKYELLOW;
    playerColors[8] = PURPLE;

    playerColors[9] = DKCYAN;
    playerColors[10] = DKORANGE;
    playerColors[11] = DKMAGENTA;

    playerColors[12] = GREEN;
    playerColors[13] = RED;
    playerColors[14] = LTGREEN;
    playerColors[15] = LTRED;
}

#endif // COLORS_H
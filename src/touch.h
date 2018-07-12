#ifndef TOUCH_H
#define TOUCH_H

#include "pins.h"
#include <TouchScreen.h>

// Calibration data for the raw touch data to the screen coordinates
#define TS_MINX 110
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

// For better pressure precision, we need to know the resistance between X+ and X-
// Multimeter measurement showed 279 ohms for our display.
TouchScreen ts = TouchScreen(pin_tft_xp, pin_tft_yp, pin_tft_xm, pin_tft_ym, 279);

void setupTouch()
{
    Serial.begin(115200);
    Serial.println(F("Touch Paint!"));

    tft.begin(HX8357D);
    tft.fillScreen(HX8357_BLACK);

    // make the color selection boxes
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, HX8357_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, HX8357_YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, HX8357_GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, HX8357_CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, HX8357_BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, HX8357_MAGENTA);
    tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_BLACK);
    tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);

    // select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    currentcolor = HX8357_RED;
}

void loopTouch()
{
    // Retrieve a point
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
    {
        return;
    }

    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    Serial.print("\tPressure = ");
    Serial.println(p.z);

    // Scale from ~0->1000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    /*
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
*/

    if (p.y < BOXSIZE)
    {
        oldcolor = currentcolor;

        if (p.x < BOXSIZE)
        {
            currentcolor = HX8357_RED;
            tft.drawRect(0, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }
        else if (p.x < BOXSIZE * 2)
        {
            currentcolor = HX8357_YELLOW;
            tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }
        else if (p.x < BOXSIZE * 3)
        {
            currentcolor = HX8357_GREEN;
            tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }
        else if (p.x < BOXSIZE * 4)
        {
            currentcolor = HX8357_CYAN;
            tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }
        else if (p.x < BOXSIZE * 5)
        {
            currentcolor = HX8357_BLUE;
            tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }
        else if (p.x < BOXSIZE * 6)
        {
            currentcolor = HX8357_MAGENTA;
            tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }
        else if (p.x < BOXSIZE * 7)
        {
            currentcolor = HX8357_WHITE;
            tft.drawRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_RED);
        }
        else if (p.x < BOXSIZE * 8)
        {
            currentcolor = HX8357_BLACK;
            tft.drawRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
        }

        if (oldcolor != currentcolor)
        {
            if (oldcolor == HX8357_RED)
                tft.fillRect(0, 0, BOXSIZE, BOXSIZE, HX8357_RED);
            if (oldcolor == HX8357_YELLOW)
                tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, HX8357_YELLOW);
            if (oldcolor == HX8357_GREEN)
                tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, HX8357_GREEN);
            if (oldcolor == HX8357_CYAN)
                tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, HX8357_CYAN);
            if (oldcolor == HX8357_BLUE)
                tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, HX8357_BLUE);
            if (oldcolor == HX8357_MAGENTA)
                tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, HX8357_MAGENTA);
            if (oldcolor == HX8357_WHITE)
                tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
            if (oldcolor == HX8357_BLACK)
                tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, HX8357_BLACK);
        }
    }
    if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height()))
    {
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
}

#endif // TOUCH_H

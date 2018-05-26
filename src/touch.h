#ifndef TOUCH_H
#define TOUCH_H

#include "bmp.h"
#include <TouchScreen.h>

// These are the four touchscreen analog pins
#define XP 43  // can be a digital pin
#define XM A14 // must be an analog pin, use "An" notation!
#define YP A15 // must be an analog pin, use "An" notation!
#define YM 42  // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 110
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 277);

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

#endif // TOUCH_H

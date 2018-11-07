#ifndef GRAPH_H
#define GRAPH_H

#include <Adafruit_ILI9341.h>
#include "colors.h"
#include "pins.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_MOSI, PIN_TFT_CLK, PIN_TFT_RST, PIN_TFT_MISO);

#define TITLE_PADDING_HORIZONTAL 0
#define TITLE_PADDING_VERTICAL 2

#define AXES_NAME_PADDING_Y_HORIZONTAL 2
#define AXES_NAME_PADDING_Y_VERTICAL 11
#define AXES_NAME_PADDING_X_HORIZONTAL 0
#define AXES_NAME_PADDING_X_VERTICAL -21

#define LEGEND_PADDING_Y_HORIZONTAL 2
#define LEGEND_PADDING_Y_VERTICAL 2
#define LEGEND_PADDING_X_HORIZONTAL -12
#define LEGEND_PADDING_X_VERTICAL -8

#define MAP_X(x, plot, screen) (screen.xlo + (x - plot.xlo) * (screen.xhi - screen.xlo) / (plot.xhi - plot.xlo))
#define MAP_Y(y, plot, screen) (screen.yhi - (y - plot.ylo) * (screen.yhi - screen.ylo) / (plot.yhi - plot.ylo))

struct box
{
    double xlo;
    double ylo;
    double xhi;
    double yhi;
};

void InitializeGrid(
    Adafruit_ILI9341 &d, // display object
    box &screen,
    box &plot,
    double xinc,         // increments on x axis
    double yinc,         // increments on y axis
    unsigned int gcolor, // grid color
    unsigned int tcolor, // text color
    unsigned int bcolor  // background color
)
{
    // Axis y
    for (double y = plot.ylo + yinc; y <= plot.yhi; y += yinc)
    {
        double temp = MAP_Y(y, plot, screen);
        d.drawLine(screen.xlo, temp, screen.xhi, temp, gcolor);
        d.setTextSize(1);
        d.setTextColor(tcolor, bcolor);
        d.setCursor(screen.xlo + LEGEND_PADDING_Y_HORIZONTAL, temp + LEGEND_PADDING_Y_VERTICAL);
        d.print((int)y);
    }

    // Axis x
    for (double x = plot.xlo + xinc; x <= plot.xhi; x += xinc)
    {
        double temp = MAP_X(x, plot, screen);
        d.drawLine(temp, screen.ylo, temp, screen.yhi, gcolor);
        d.setTextSize(1);
        d.setTextColor(tcolor, bcolor);
        d.setCursor(temp + LEGEND_PADDING_X_HORIZONTAL, screen.yhi + LEGEND_PADDING_X_VERTICAL);
        d.print((int)x);
    }
}

void InitializeAxes(
    Adafruit_ILI9341 &d, // display object
    box &screen,
    box &plot,
    String title,        // title of graph
    String xlabel,       // x axis label
    String ylabel,       // y axis label
    unsigned int acolor, // axes color
    unsigned int tcolor, // text color
    unsigned int bcolor  // background color
)
{
    // Draw title
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(screen.xhi - title.length() * 6 * 2 + TITLE_PADDING_HORIZONTAL, screen.ylo + TITLE_PADDING_VERTICAL);
    d.print(title);

    // Draw y axes
    d.drawLine(screen.xlo, screen.ylo, screen.xlo, screen.yhi, acolor);
    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(screen.xlo + AXES_NAME_PADDING_Y_HORIZONTAL, screen.ylo + AXES_NAME_PADDING_Y_VERTICAL);
    d.print(ylabel);

    // Draw x axes
    d.drawLine(screen.xlo, screen.yhi, screen.xhi, screen.yhi, acolor);
    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(screen.xhi - xlabel.length() * 6 + AXES_NAME_PADDING_X_HORIZONTAL, screen.yhi + AXES_NAME_PADDING_X_VERTICAL);
    d.print(xlabel);
}

void Graph(Adafruit_ILI9341 &d, box &screen, box &plot, box &line, unsigned int color)
{
    double x = MAP_X(line.xhi, plot, screen);
    double y = MAP_Y(line.yhi, plot, screen);
    d.drawLine(line.xlo, line.ylo - 1, x, y - 1, color);
    d.drawLine(line.xlo, line.ylo + 0, x, y + 0, color);
    d.drawLine(line.xlo, line.ylo + 1, x, y + 1, color);
    line.xlo = x;
    line.ylo = y;
}

#endif // GRAPH_H
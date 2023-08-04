#include "graph.h"
#include <tft.h>
#include "colors.h"
#include "input.h"

void InitializeGrid(
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
        tft.drawLine(screen.xlo, temp, screen.xhi, temp, gcolor);
        tft.setTextSize(1);
        tft.setTextColor(tcolor, bcolor);
        tft.setCursor(screen.xlo + LEGEND_PADDING_Y_HORIZONTAL, temp + LEGEND_PADDING_Y_VERTICAL);
        tft.print((int)y);
    }

    // Axis x
    for (double x = plot.xlo + xinc; x <= plot.xhi; x += xinc)
    {
        double temp = MAP_X(x, plot, screen);
        tft.drawLine(temp, screen.ylo, temp, screen.yhi, gcolor);
        tft.setTextSize(1);
        tft.setTextColor(tcolor, bcolor);
        tft.setCursor(temp + LEGEND_PADDING_X_HORIZONTAL, screen.yhi + LEGEND_PADDING_X_VERTICAL);
        tft.print((int)x);
    }
}

void InitializeAxes(
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
    tft.setTextSize(2);
    tft.setTextColor(tcolor, bcolor);
    tft.setCursor(screen.xhi - title.length() * 6 * 2 + TITLE_PADDING_HORIZONTAL, screen.ylo + TITLE_PADDING_VERTICAL);
    tft.print(title);

    // Draw y axes
    tft.drawLine(screen.xlo, screen.ylo, screen.xlo, screen.yhi, acolor);
    tft.setTextSize(1);
    tft.setTextColor(acolor, bcolor);
    tft.setCursor(screen.xlo + AXES_NAME_PADDING_Y_HORIZONTAL, screen.ylo + AXES_NAME_PADDING_Y_VERTICAL);
    tft.print(ylabel);

    // Draw x axes
    tft.drawLine(screen.xlo, screen.yhi, screen.xhi, screen.yhi, acolor);
    tft.setTextSize(1);
    tft.setTextColor(acolor, bcolor);
    tft.setCursor(screen.xhi - xlabel.length() * 6 + AXES_NAME_PADDING_X_HORIZONTAL, screen.yhi + AXES_NAME_PADDING_X_VERTICAL);
    tft.print(xlabel);
}

void Graph(box &screen, box &plot, box &line, unsigned int color, bool isBold)
{
    double x = MAP_X(line.xhi, plot, screen);
    double y = MAP_Y(line.yhi, plot, screen);

    if( isBold ) { tft.drawLine(line.xlo, line.ylo - 1, x, y - 1, color); }
    tft.drawLine(line.xlo, line.ylo + 0, x, y + 0, color);
    if( isBold ) { tft.drawLine(line.xlo, line.ylo + 1, x, y + 1, color); }
    line.xlo = x;
    line.ylo = y;
}
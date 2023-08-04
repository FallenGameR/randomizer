#ifndef GRAPH_H
#define GRAPH_H

#include <Arduino.h>

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
    box &screen,
    box &plot,
    double xinc,         // increments on x axis
    double yinc,         // increments on y axis
    unsigned int gcolor, // grid color
    unsigned int tcolor, // text color
    unsigned int bcolor  // background color
);

void InitializeAxes(
    box &screen,
    box &plot,
    String title,        // title of graph
    String xlabel,       // x axis label
    String ylabel,       // y axis label
    unsigned int acolor, // axes color
    unsigned int tcolor, // text color
    unsigned int bcolor  // background color
);

void Graph(box &screen, box &plot, box &line, unsigned int color, bool isBold);

#endif // GRAPH_H
#ifndef TESTER_H
#define TESTER_H

#include "screens.h"
#include "..\graph.h"
#include "..\random.h"

void TesterScreen()
{
    tft.fillScreen(BLACK);

    /*
      ind1 = readString.indexOf(',');  //finds location of first ,
      angle = readString.substring(0, ind1);   //captures first data String
      ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
      fuel = readString.substring(ind1+1, ind2+1);   //captures second data String
      ind3 = readString.indexOf(',', ind2+1 );
      speed1 = readString.substring(ind2+1, ind3+1);
      ind4 = readString.indexOf(',', ind3+1 );
      altidude = readString.substring(ind3+1); //captures remain part of data after last ,

int commaIndex = myString.indexOf(',');
//  Search for the next comma just after the first
int secondCommaIndex = myString.indexOf(',', commaIndex + 1);

String firstValue = myString.substring(0, commaIndex);
String secondValue = myString.substring(commaIndex + 1, secondCommaIndex);
String thirdValue = myString.substring(secondCommaIndex + 1); // To the end of the string

int r = firstValue.toInt();
int g = secondValue.toInt();
int b = thirdValue.toInt();
    */

    double x = 0;
    double y = random(10);

    box screen;
    screen.xlo = 0;
    screen.ylo = 0;
    screen.xhi = tft.width() - 1;
    screen.yhi = tft.height() - 1;

    box plot;
    plot.xlo = 0;
    plot.xhi = 60;
    plot.ylo = 0;  //(int)y - 5;
    plot.yhi = 10; //(int)y + 5;

    box line;
    line.xlo = MAP_X(x, plot, screen);
    line.ylo = MAP_Y(y, plot, screen);

    // Draw grid
    InitializeGrid(screen, plot, 10, 1, DKBLUE, WHITE, BLACK);
    InitializeAxes(screen, plot, "Totals", "matches", "wins", RED, WHITE, BLACK);

    // Draw graph
    for (double x = 1; x <= 60; x += 1)
    {
        line.xhi = x;
        line.yhi = random(10);
        Graph(screen, plot, line, GREEN);
        delay(100);
    }
}

#endif // TESTER_H
#ifndef TOTALS_SHOW_H
#define TOTALS_SHOW_H

#include "screens.h"
#include "..\totals.h"

void TotalShowScreen()
{
    if (screen_redraw)
    {
        RenderTotals();
        DumpStats();
        screen_redraw = false;
    }

    // neutral_input means we just were in neutral state and now test for new input that is tested in nested ifs
    if (neutral_input)
    {
        // Black button returns to games selection without chosing of winner
        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            neutral_input = false;
            screen_redraw = true;
        }
    }
}

#endif // TOTALS_SHOW_H
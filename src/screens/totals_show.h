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

    // input_allowed means we just were in neutral state and now test for new input that is tested in nested ifs
    if (input_allowed)
    {
        // Black button returns to games selection without chosing of winner
        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}

#endif // TOTALS_SHOW_H
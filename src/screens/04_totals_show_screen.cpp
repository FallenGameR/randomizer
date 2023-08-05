#include "..\screens.h"

#include <Arduino.h>

#include "..\totals.h"
#include "..\input.h"
#include "..\shared.h"

void TotalShowScreen()
{
    if (screen_redraw)
    {
        RenderTotals();
        DumpStats();
        screen_redraw = false;
    }

    if (input_allowed)
    {
        // Black button returns to games selection with retaining the history
        if (BUTTON_BLACK)
        {
            Serial.println(F("-> Game"));
            screen_selected = Screen::GameIconSelection;
            input_allowed = false;
            screen_redraw = true;
        }

        // Soft reset to do a soft reset
        if (BUTTON_JOYSTICK)
        {
            Serial.println(F("-> Init"));
            screen_selected = Screen::RandomizerInit;
            input_allowed = false;
            screen_redraw = true;
        }
    }
}
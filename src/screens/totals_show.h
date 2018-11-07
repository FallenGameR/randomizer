#ifndef TOTALS_SHOW_H
#define TOTALS_SHOW_H

#include "screens.h"
#include "..\totals.h"

void TotalShowScreen()
{
    //MockRecordMatchOutcome();
    RenderTotal();
    delay(5000);
}

#endif // TOTALS_SHOW_H
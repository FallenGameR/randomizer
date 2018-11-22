#ifndef TESTER_H
#define TESTER_H

#include "screens.h"
#include "..\totals.h"
#include "..\random.h"

void MockRecordMatchOutcome()
{
    match_current = 0;

    for (int match = 0; match < 42; match += 1)
    {
        matches[match_current][Stats::FirstPlayer] = random(3);
        matches[match_current][Stats::SecondPlayer] = random(3);
        matches[match_current][Stats::Game] = 0;
        matches[match_current][Stats::FirstFighter] = 0;
        matches[match_current][Stats::SecondFighter] = 0;
        matches[match_current][Stats::FirstFighter2] = 0;
        matches[match_current][Stats::SecondFighter2] = 0;
        matches[match_current][Stats::FirstFighter3] = 0;
        matches[match_current][Stats::SecondFighter3] = 0;
        matches[match_current][Stats::Won] = random(1) ? Winner::First : Winner::Second;
        matches[match_current][Stats::NotFair] = false;
        match_current++;
    }
}

void TesterScreen()
{
    MockRecordMatchOutcome();
    RenderTotals();
    delay(60000);
}

#endif // TESTER_H
#ifndef GAME_ICON_SELECTION_H
#define GAME_ICON_SELECTION_H

#include "..\tft.h"
#include "..\games.h"
#include "..\colors.h"
#include "..\input.h"
#include "..\screens.h"

#define GAMES_START_ROW 3
#define GAMES_SPACING 5

// Update and redraw cursor that moves between selectable settings
void UpdateGameCursorPosition(int movement);

void GameIconSelectionScreen();

#endif // GAME_ICON_SELECTION_H
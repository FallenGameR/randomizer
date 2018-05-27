#include "bmp.h"
#include "touch.h"

void setup()
{
  /*
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CCS))
  {
    Serial.println("failed!");
  }
  Serial.println("OK!");

  tft.begin(HX8357D);
  tft.fillScreen(HX8357_BLUE);

  bmpDraw("jumpers.bmp", 0, 0);
  /**/
  //*
  Serial.begin(115200);
  Serial.println(F("Touch Paint!"));

  tft.begin(HX8357D);
  tft.fillScreen(HX8357_BLACK);

  // make the color selection boxes
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, HX8357_RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, HX8357_YELLOW);
  tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, HX8357_GREEN);
  tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, HX8357_CYAN);
  tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, HX8357_BLUE);
  tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, HX8357_MAGENTA);
  tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_BLACK);
  tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);

  // select the current color 'red'
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
  currentcolor = HX8357_RED;
  /**/
}

void loop()
{
  // Retrieve a point
  TSPoint p = ts.getPoint();

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z < MINPRESSURE || p.z > MAXPRESSURE)
  {
    return;
  }

  Serial.print("X = ");
  Serial.print(p.x);
  Serial.print("\tY = ");
  Serial.print(p.y);
  Serial.print("\tPressure = ");
  Serial.println(p.z);

  // Scale from ~0->1000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  /*
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
*/

  if (p.y < BOXSIZE)
  {
    oldcolor = currentcolor;

    if (p.x < BOXSIZE)
    {
      currentcolor = HX8357_RED;
      tft.drawRect(0, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }
    else if (p.x < BOXSIZE * 2)
    {
      currentcolor = HX8357_YELLOW;
      tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }
    else if (p.x < BOXSIZE * 3)
    {
      currentcolor = HX8357_GREEN;
      tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }
    else if (p.x < BOXSIZE * 4)
    {
      currentcolor = HX8357_CYAN;
      tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }
    else if (p.x < BOXSIZE * 5)
    {
      currentcolor = HX8357_BLUE;
      tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }
    else if (p.x < BOXSIZE * 6)
    {
      currentcolor = HX8357_MAGENTA;
      tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }
    else if (p.x < BOXSIZE * 7)
    {
      currentcolor = HX8357_WHITE;
      tft.drawRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_RED);
    }
    else if (p.x < BOXSIZE * 8)
    {
      currentcolor = HX8357_BLACK;
      tft.drawRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
    }

    if (oldcolor != currentcolor)
    {
      if (oldcolor == HX8357_RED)
        tft.fillRect(0, 0, BOXSIZE, BOXSIZE, HX8357_RED);
      if (oldcolor == HX8357_YELLOW)
        tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, HX8357_YELLOW);
      if (oldcolor == HX8357_GREEN)
        tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, HX8357_GREEN);
      if (oldcolor == HX8357_CYAN)
        tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, HX8357_CYAN);
      if (oldcolor == HX8357_BLUE)
        tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, HX8357_BLUE);
      if (oldcolor == HX8357_MAGENTA)
        tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, HX8357_MAGENTA);
      if (oldcolor == HX8357_WHITE)
        tft.fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, HX8357_WHITE);
      if (oldcolor == HX8357_BLACK)
        tft.fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, HX8357_BLACK);
    }
  }
  if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height()))
  {
    tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
  }
}

/*
#include "screens\randomizer_init.h"
#include "screens\game_selection.h"
#include "screens\player_selection.h"
#include "screens\fighter_selection.h"
#include "stats.h"

void setup()
{
  Serial.begin(9600);

  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
  pinMode(pin_button_black, INPUT_PULLUP);
  pinMode(pin_button_joystick, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Initializing"));
  lcd.setCursor(0, 1);
  lcd.print(F("Entropy"));
  initRandom();

  Serial.println(F("-> Init"));
  screen_selected = Screen::RandomizerInit;

  // For testing
  //screen_selected = Screen::PlayerSelection;
}

void loop()
{
  readInput();

  switch (screen_selected)
  {
  case Screen::RandomizerInit:
    RandomizerInitScreen();
    break;

  case Screen::GameSelection:
    GameSelectionScreen();
    break;

  case Screen::PlayerSelection:
    PlayerSelectionScreen();
    break;

  case Screen::FighterSelection:
    FighterSelectionScreen();
    break;
  }
}
/**/
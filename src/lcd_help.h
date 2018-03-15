/*
byte smiley[8] = 
{
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

// in setup
lcd.createChar(0, smiley);

  lcd.setCursor(0, 0);  
  lcd.print("x = ");
  if( left )
  {
    lcd.print("left");
  }
  else if( right )
  {
    lcd.print("right");
  }
  else
  {
    lcd.print("center");
  }

  lcd.setCursor(0, 1);
  lcd.print("y = ");
  if( up )
  {
    lcd.print("up");
  }
  else if( down )
  {
    lcd.print("down");
  }
  else
  {
    lcd.print("center");
  }

  lcd.print(" ");

  if( pressed )
  {
    lcd.print("pressed");
  }
/**/
/*
  // set the display to automatically scroll:
  //lcd.setCursor(1, 1);
  lcd.autoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();
/**/

/*
  lcd.blink();
  delay(2000);
  lcd.noBlink();
/**/

/*
  lcd.cursor();
  delay(2000);
  lcd.noCursor();
/**/

// Smiley
//  lcd.write((byte) 0);

/*
  // highlight is still on
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
/**/

/*
  // scroll 13 positions (string length) to the left
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  } 
  /**/

//lcd.leftToRight();
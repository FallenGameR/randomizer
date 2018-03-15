#include <Arduino.h>

// Arduino pin numbers
const int SW_pin = 13;
const int X_pin = 0;
const int Y_pin = 1; 

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

const char * tekken[] = {
  "Akuma",
  "Alisa Bosconovitch",
  "Asuka Kazama",
  "Bob",
  "Bryan Fury",
  "Claudio Serafino",
  "Devil Jin",
  "Eddy Gordo",
  "Eliza",
  "Feng Wei",
  "Geese Howard",
  "Gigas",
  "Heihachi Mishima",
  "Hwoarang",
  "Jack-7",
  "Jin Kazama",
  "Josie Rizal",
  "Katarina Alves",
  "Kazumi Mishima",
  "Kazuya Mishima",
  "King",
  "Kuma",
  "Lars Alexandersson",
  "Lee Chaolan",
  "Leo",
  "Lili",
  "Ling Xiaoyu",
  "Lucky Chloe",
  "Marshall Law",
  "Master Raven",
  "Miguel",
  "Nina Williams",
  //"Noctis Lucis Caelum",
  "Panda",
  "Paul Phoenix",
  "Shaheen",
};

#define n_tekken (sizeof (tekken) / sizeof (const char *))

bool doUpdate = false;
bool commandAwait = true;

int ledGreenPin = 4;
int ledBluePin = 5;
int buttonPin = 6;

void setup() {
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.createChar(0, smiley);

  int noise = 
    analogRead(0) *
    analogRead(1) *
    analogRead(2) *
    analogRead(3) *
    analogRead(4) *
    analogRead(5);
    
  randomSeed(noise);

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  Serial.println(noise);

  doUpdate = true;
}


void loop() {
  if (digitalRead(buttonPin) == LOW)
  {
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledBluePin, HIGH);
  }
  else if (digitalRead(buttonPin) == HIGH)
  {
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, LOW);
  }
  
  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);
  bool pressed = !digitalRead(SW_pin);
  
  bool x_left = x < 400;
  bool x_right = x > 600;
  bool x_center = !x_left && !x_right;
  bool y_up = y > 600;
  bool y_down = y < 400;
  bool y_center = !y_up && !y_down;

  if( (x_left || x_right) && commandAwait )
  {
    doUpdate = true;
    commandAwait = false;
    Serial.println("Update");
  }

  if( x_center )
  {
    commandAwait = true;
  }
  
  if( doUpdate )
  {
    doUpdate = false;
    lcd.clear();
  
    int first = random(n_tekken);
    int second = random(n_tekken);
  
    lcd.setCursor(0, 0);
    lcd.print(tekken[first]);
    lcd.setCursor(0, 1);
    lcd.print(tekken[second]);
  }


/*
  return;

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

  delay(500);
}


#ifndef DICE_H
#define DICE_H

// Using PROGMEM here to save some space for variables

const char dice_White[] PROGMEM = "White";
const char dice_Black[] PROGMEM = "Black";
const char dice_Red[] PROGMEM = "Red";

const char *const dice[] PROGMEM = {
    dice_White,
    dice_Black,
    dice_Red,
};

#define n_dice (sizeof(dice) / sizeof(const char *))

#endif // DICE_H

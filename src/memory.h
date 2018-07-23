#ifndef MEMORY_H
#define MEMORY_H

// Buffer used to print all constant strings to LCD
// It has LCD width in chars (16) + 1 for trailing string null
char buffer[17];

// We move as much constant strings to program memory as possible to
// free up very limited 2k of space used for variables and stats table
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

#define TFT_PRINT(table, index)                               \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    tft.print(buffer);

#define TFT_PRINT_LN(table, index)                            \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    tft.println(buffer);

#define TFT_OPTIONAL_FIGHTER(index)             \
    if (index != NO_FIGHTER)                    \
    {                                           \
        tft.print(F(", "));                     \
        TFT_PRINT(fighter_map_selected, index); \
    }

#define TFT_PRINT_GAME(index) \
    setGameName(index);       \
    tft.print(bufferName);

#define TFT_PRINT_PLAYER(index) \
    setPlayerName(index);       \
    tft.print(bufferName);

#define SERIAL_PRINT(table, index)                            \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    Serial.print(buffer);

#define SERIAL_PRINT_LN(table, index)                         \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    Serial.println(buffer);

#define SERIAL_OPTIONAL_FIGHTER(index)             \
    if (index != NO_FIGHTER)                       \
    {                                              \
        Serial.print(F(", "));                     \
        SERIAL_PRINT(fighter_map_selected, index); \
    }

#define SERIAL_PRINT_GAME(index) \
    setGameName(index);          \
    Serial.print(bufferName);

#define SERIAL_PRINT_LN_GAME(index) \
    setGameName(index);             \
    Serial.println(bufferName);

#define SERIAL_PRINT_PLAYER(index) \
    setPlayerName(index);          \
    Serial.print(bufferName);

#endif // MEMORY_H
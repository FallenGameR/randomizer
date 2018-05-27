#ifndef MEMORY_H
#define MEMORY_H

// Buffer used to print all constant strings to LCD
// It has LCD width in chars (16) + 1 for trailing string null
char buffer[17];

// We move as much constant strings to program memory as possible to
// free up very limited 2k of space used for variables and stats table
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

#define LCD_PRINT(table, index)                               \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    tft.print(buffer);

#define LCD_PRINT_LN(table, index)                            \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    tft.println(buffer);

#define SERIAL_PRINT(table, index)                            \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    Serial.print(buffer);

#define SERIAL_PRINT_LN(table, index)                         \
    strcpy_P(buffer, (char *)pgm_read_word(&(table[index]))); \
    Serial.println(buffer);

#endif // MEMORY_H
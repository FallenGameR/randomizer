#ifndef MEMORY_H
#define MEMORY_H

// Buffer used to print all constant strings to LCD
// It has LCD width in chars (16) + 1 for trailing string null
char buffer[17];

// We move as much constant strings to program memory as possible to
// free up very limited 2k of space used for variables and stats table
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/

#define PRINT(printable, stream) \
    stream.print(printable);

#define PRINT_B(buffer_setup, stream) \
    buffer_setup;                     \
    stream.print(bufferName);

#define PRINT_P(tableElement, stream) \
    PRINT_B(strcpy_P(bufferName, (char *)pgm_read_word(&(tableElement))), stream);

#define PRINT2(printable, stream1, stream2) \
    PRINT(printable, stream1);              \
    PRINT(printable, stream2);

#define PRINT2_B(buffer_setup, stream1, stream2) \
    buffer_setup;                                \
    PRINT2(bufferName, stream1, stream2);

#define PRINT2_P(tableElement, stream1, stream2) \
    PRINT2_B(strcpy_P(bufferName, (char *)pgm_read_word(&(tableElement))), stream1, stream2);

// Print buffer on tft
#define PRINT_BT(buffer_setup) \
    PRINT_B(buffer_setup, tft);

// Print buffer on serial
#define PRINT_BS(buffer_setup) \
    PRINT_B(buffer_setup, Serial);

// print to serial, file
#define PRINT2_SF(printable) \
    PRINT2(printable, Serial, statsFile)

// print bufferName to serial, file
#define PRINT2_BSF(buffer_name_setup) \
    buffer_name_setup;                \
    PRINT2_SF(bufferName)

// print program memory to serial, file
#define PRINT2_PSF(tableElement) \
    PRINT2_P(tableElement, Serial, statsFile)

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
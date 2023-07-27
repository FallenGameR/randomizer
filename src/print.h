#ifndef PRINT_H
#define PRINT_H

#define PRINT(printable, stream) \
    stream.print(printable);

#define PRINT_B(buffer_setup, stream) \
    buffer_setup;                     \
    stream.print(b_string);

#define PRINT2(printable, stream1, stream2) \
    PRINT(printable, stream1);              \
    PRINT(printable, stream2);

#define PRINT2_B(buffer_setup, stream1, stream2) \
    buffer_setup;                                \
    PRINT2(b_string, stream1, stream2);

// Print buffer on tft
#define PRINT_BT(buffer_setup) \
    PRINT_B(buffer_setup, tft);

// Print buffer on serial
#define PRINT_BS(buffer_setup) \
    PRINT_B(buffer_setup, Serial);

// print to serial, file
#define PRINT2_SF(printable) \
    PRINT2(printable, Serial, statsFile)

// print b_string to serial, file
#define PRINT2_BSF(buffer_name_setup) \
    buffer_name_setup;                \
    PRINT2_SF(b_string)

#endif // PRINT_H
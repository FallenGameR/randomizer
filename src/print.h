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

// Print buffer on tft
#define PRINT_BT(buffer_setup) \
    PRINT_B(buffer_setup, tft);

// Print buffer on serial
#define PRINT_BS(buffer_setup) \
    PRINT_B(buffer_setup, Serial);

#endif // PRINT_H
#ifndef FILES_LIB_H
#define FILES_LIB_H

#include <Arduino.h>

// Takes ~88ms to count games or players
void readElementsInFolder(const String &path, byte &files, byte &dirs);

#endif // FILES_LIB_H
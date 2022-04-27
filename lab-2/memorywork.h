#ifndef MEMORYWORK_H
#define MEMORYWORK_H
#include "appcontext.h"
#include "entrypoint.h"

#include <fstream>

AppContext* allocateStructContext();
AppData* allocateStructData();
void freeArray(char** arr, int size);
void freeArray3D(char*** arr, size_t sizeX, size_t sizeY);
char** allocateArr(int count, int size);
struct Error* allocateStructError();

#endif // MEMORYWORK_H

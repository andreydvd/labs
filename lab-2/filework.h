#ifndef FILEWORK_H
#define FILEWORK_H
#include <fstream>
#include <cstring>
#include "appcontext.h"
#include <string.h>
#include "stringwork.h"
#include "memorywork.h"

void readfile(AppContext* context);
bool checkFile(AppContext* context);

#endif // FILEWORK_H

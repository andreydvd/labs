#ifndef STRINGWORK_H
#define STRINGWORK_H

#include <string.h>
#include "appcontext.h"
#include <stdlib.h>
#include "memorywork.h"

char** strSplit (char* line, int count);
int countFields(char* line);

#endif // STRINGWORK_H

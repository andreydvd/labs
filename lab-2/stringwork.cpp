#include "stringwork.h"

char** strSplit (char* line, int count) {
    char** newLine = allocateArr(count, CHAR_SIZE);
    char* time = (char*)calloc(CHAR_SIZE, sizeof(char));
    time = strtok(line, ",");
    for (int i = 0; i < count; i++) {
        strcpy(newLine[i], time);
        time = strtok(NULL, ",");
    }
    free(time);
    return newLine;
    freeArray(newLine, count);
}


int countFields(char* line) {
    int count = START_VALUE;
    for (int i = 0; line[i]; i++){
        if (line[i] == ',') {
            count++;
        }
    }
    return count;
}




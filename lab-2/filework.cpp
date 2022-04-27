#include "filework.h"


FILE* openFile(char* fileName) {
    return fopen(fileName, "r");
}


void readfile(AppContext* context){
    FILE* fp = openFile(context->fileName);
    char line[CHAR_SIZE];
    int llen;
    int counter = 0;
    int maxSize = START_VALUE;
    char** data = (char**)calloc(maxSize, sizeof(char *));
    while (fgets(line,CHAR_SIZE,fp)){
        if (counter >= maxSize - 1){
            data = (char**)realloc(data, maxSize * 2 * sizeof(char*));
            maxSize *= 2;
        }
        llen = strlen(line);
        data[counter] = (char *)calloc(llen + 1, sizeof(char));
        strcpy(data[counter], line);
        counter++;
    }
    context->linesCount = counter;
    context->dataLines = counter;
    context->data = data;
    fclose(fp);
}

bool checkFile(AppContext* context) {
    FILE* fp = openFile(context->fileName);
    char line[CHAR_SIZE];
    int counter = 0;
    int mainCount = countFields(fgets(line,CHAR_SIZE,fp));
    if (fp != NULL) {
        while (fgets(line,CHAR_SIZE,fp)){
            int count = countFields(line);
            if (count != mainCount || count < 2) {
                return false;
                break;
            }
            counter++;
        }
        if (counter == 0)
            return false;
        else
            return true;
    } else
        return false;
    fclose(fp);
}

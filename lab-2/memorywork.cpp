#include "memorywork.h"

AppContext* allocateStructContext() {
    return (AppContext*) malloc(sizeof(AppContext));
}

Error* allocateStructError() {
    return (Error*) malloc(sizeof(Error));
}

AppData* allocateStructData() {
    return (AppData*) malloc(sizeof(AppData));
}

void freeArray(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

void freeArray3D(char*** arr, size_t sizeX, size_t sizeY) {
    for (size_t i = 0; i < sizeX; i++) {
        freeArray(arr[i], sizeY);
    }
    free(arr);
}

char** allocateArr(int count, int size) {
    char** mas = (char**)calloc(count, sizeof(char*));
    for (int i = 0; i < count; i++) {
        mas[i] = (char*) calloc(size, sizeof(char));
    }
    return mas;
}

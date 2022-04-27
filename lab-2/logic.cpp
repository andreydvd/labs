#include "logic.h"



bool columnNumberCheck(AppContext* context) {
    if (context->columnNumber > 7 || context->columnNumber < 3)
        return false;
    else
        return true;
}


Calculations getCalculations(AppContext* context, int column) {
    int count = context->linesCount;
    Calculations calc;
    double* array = (double*)calloc(count, sizeof(double));
    for (int i = 0; i < count; i++) {
        array[i] = atof(context->regionData[i][column - 1]);
    }
    sortArray(array, count);
    calc.max = array[count - 1];
    calc.min = array[0];
    calc.med = getMediana(array, count);
    free(array);
    return calc;
}


void sortArray(double* array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array + j, array + j + 1);
            }
        }
    }
}


double getMediana(double* array, int count) {
    double med;
    if (count%2 == 0) {
        med = (array[count / 2] + array[(count / 2) + 1]) / 2;
    }else {
        med = array[count / 2];
    }
    return med;
}

void swap(double* first,double* second) {
    double temp = *first;
    *first = *second;
    *second = temp;
}

bool checkRegion(AppContext* context) {
    for (int i = 0; i < context->dataLines - 1; i++) {
        if (strstr(*(context->data + i), context->regionName)) {
            return true;
            break;
        }
    }
    return false;
}


void getRegionData(AppContext* context) {
    int fields = countFields(context->data[0]);
    if (context->dataLines == context->linesCount){
        char* line = (char*)calloc(CHAR_SIZE, sizeof(char));
        strcpy(line, context->data[0]);
        char **headers = strSplit(line, fields);
        context->headers = headers;
        free(line);
    }
    else {
        freeArray3D(context->regionData, context->linesCount, context->fieldsNum);
    }
    char ***data = (char***)calloc(context->dataLines - 1, sizeof(char**));
    int temp = 0;
    for (int i = 0; i < context->dataLines - 1; i++) {
        if (strstr(*(context->data + i), context->regionName)) {
                char* line = (char*)calloc(CHAR_SIZE, sizeof(char));
                strcpy(line, context->data[i]);
                data[temp] = strSplit(line, fields);
                temp++;
                free(line);
        }
    }
    context->linesCount = temp;
    context->fieldsNum = fields;
    context->regionData = data;
}

void checkLoadData(AppContext* context, Error* errorss) {
    if (context->linesCount == 0) {
        errorss->region = RegionError;
    }
    else {
        getRegionData(context);
        errorss->region = Region;
    }
}

void checkLoadFile(AppContext* context, Error* errors) {
    if (checkFile(context) == true) {
        readfile(context);
        errors->file = File;
    } else {
        errors->file = FileError;
    }
}

void checkCalculateMetrics(AppContext* context, Error* errorss) {
    if (!columnNumberCheck(context))
        errorss->metrics = MetricsError;
    else {
        context->calc = getCalculations(context, context->columnNumber);

        errorss->metrics = Metrics;
    }
}

#ifndef LOGIC_H
#define LOGIC_H
#include <fstream>
#include <cstring>
#include "appcontext.h"
#include "memorywork.h"
#include "stringwork.h"
#include "entrypoint.h"
#include "filework.h"


FILE* openFile(char* fileName);
void readFromFile(FILE* file, AppContext *context);
bool columnNumberCheck(AppContext* context);
void getRegionData(AppContext* context);
void sortArray(double* array, int size);
bool checkRegion(AppContext* context);
void swap(double* first,double* second);
void checkLoadData(AppContext* context, Error* errors);
void checkLoadFile(AppContext* context, Error* errors);
void checkCalculateMetrics(AppContext* context, Error* errorss);
double getMediana(double* array, int count);
Calculations getCalculations(AppContext* context, int column);

#endif // LOGIC_H

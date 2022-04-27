#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "string.h"
#include "filework.h"

enum Operation {
    LoadFile,
    LoadData,
    CalculateMetrics
};

enum Errors {
    File,
    Region,
    Metrics,
    FileError,
    RegionError,
    MetricsError,
    NonAction
};

typedef struct Error {
    Errors region;
    Errors metrics;
    Errors file;
}Error;

Errors doOperations(Operation operation, AppContext* context, Error* errors);

#endif // ENTRYPOINT_H

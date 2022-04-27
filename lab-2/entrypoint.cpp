#include "logic.h"
#include "entrypoint.h"

Errors doOperations(Operation operation, AppContext* context, Error* errors) {
    switch (operation) {
        case LoadFile:
            checkLoadFile(context, errors);
            return errors->file;

        case LoadData:
            checkLoadData(context, errors);
            return errors->region;

        case CalculateMetrics:
            checkCalculateMetrics(context, errors);
            return errors->metrics;

    }
}








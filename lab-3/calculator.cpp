#include "calculator.h"

void calc_metric(vector<double> arr, int col_metric, double* min, double* max, double* med)
{
    sort(arr.begin(), arr.end());
    *min = 0;
    *max = 0;
    *med = 0;
    if (arr.size() != 0){
        *min = arr[0];
        *max = arr[arr.size() - 1];
        if (arr.size() % 2 == 0){
            *med = (arr[arr.size() / 2] + arr[arr.size() / 2 - 1]) / 2.0;
        } else {
            *med = arr[arr.size() / 2];
        }
    }
}


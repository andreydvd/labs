#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <iostream>
#include <QStandardItemModel>


using namespace std;
using std::vector;//строка сообщает что будем использовать объект vector из пространства имен std
using std::string;//строка сообщает что будем использовать объект vector из пространства имен std

void calc_metric(std::vector<double> arr, int col_metric, double* min, double* max, double* med);

#endif // CALCULATOR_H

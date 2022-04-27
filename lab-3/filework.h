#ifndef FILEWORK_H
#define FILEWORK_H

#include <iostream>
#include <QStandardItemModel>


using namespace std;
using std::vector;//строка сообщает что будем использовать объект vector из пространства имен std
using std::string;//строка сообщает что будем использовать объект vector из пространства имен std

vector<vector<string>> read_csv_file(string path);

#endif // FILEWORK_H

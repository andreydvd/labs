#ifndef WORKWITHGRAPH_H
#define WORKWITHGRAPH_H

#include "mainwindow.h"

#include <iostream>
#include <QStandardItemModel>
#include <QPainter>
#include <QPicture>

using namespace std;
using std::vector;//строка сообщает что будем использовать объект vector из пространства имен std
using std::string;//строка сообщает что будем использовать объект vector из пространства имен std

void draw_dot(vector<QPen> pens, QPainter &painter, double met, int year, double max, double min, vector<double> positions);
void draw_line(QPainter &painter, vector<int> years, vector<double> metric, double min, double max);
void draw_values(QPainter &painter, vector<int> years, double min, double max, double med);
void draw_axis(QPainter &painter);
void draw_med(QPainter &painter, vector<int> years, double min, double max, double med);
void line(QPainter &painter, vector<int> years, vector<double> metric, double min, double max);
QPicture draw_picture(vector<int> years, vector<double> metric, QString metric_name, double min, double max, double med);



#endif // WORKWITHGRAPH_H

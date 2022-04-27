#include "workwithgraph.h"

void draw_dot(vector<QPen> pens, QPainter &painter, double met, int year, double max, double min, vector<double> positions)//функция проставления точек
{
    double posX = positions.at(0), posY = positions.at(1), horY = positions.at(2), verX = positions.at(3),
            SIZEY = positions.at(4), BORDER = positions.at(5);//с помощью .at() мы обращаемся к нужной ячейке в векторе positions
    painter.setPen(pens.at(1));// устанавливаем пероhorizontal_pen
    painter.drawLine(posX + 1, horY , posX + 1, SIZEY - BORDERXTEXT*BORDER);//рисуем пунктир на годах
    painter.setPen(pens.at(0));// устанавливае перо default_pen
    painter.drawLine(posX + 1, horY + SHIFT - 1, posX + 1, horY - SHIFT + 1);//рисуем засечки на годах
    painter.rotate(-90); //поворачивает систему координат по часовой стрелке
    painter.drawText(-(SIZEY - BORDER/2), posX + OFFSET, QString::number(year, 'g', 6)); //подписываем года
    painter.rotate(90);//поворачиваем систему координат обратно
    if (met == min) {//если метрика равна минимуму
        painter.drawLine(verX - SHIFT + 1, posY, verX + SHIFT - 1, posY);//рисуем засечку
        painter.drawText(0, posY - 1, QString::number(met, 'g', 4));//подписываем метрику, именно число
        painter.drawText(verX - BORDER/2 + BORDERXTEXT + 1, posY - 1, "min");//делаем подпись метрики
        painter.setPen(pens.at(1));//меняем перо на horizontal_pen
        painter.drawLine(verX, posY, posX, posY);//рисуем пунктир на метриках
    }
    if (met == max) {
        painter.drawLine(verX - SHIFT +1, posY, verX + SHIFT - 1, posY);
        painter.drawText(0, posY - 1, QString::number(met, 'g', 4));
        painter.drawText(verX - BORDERXTEXTMAX*BORDER + 4, posY - 1, "max");
        painter.setPen(pens.at(1));
        painter.drawLine(verX, posY, posX, posY);
    }
    pens.at(2).setColor(Qt::darkBlue);//перу dot_pen начначаем темно-синий цвет
    painter.setPen(pens.at(2));//меняем перо на dot_pen
    painter.drawPoint(posX, posY); //рисуем точки
}

void draw_line(QPainter &painter, vector<int> years, vector<double> metric, double min, double max)//функция рисует линию графика
{
    const int horY = SIZEY - BORDER - GRAPHICYCLOSE / 2, verX = BORDER + GRAPHICXCLOSE;//определяем размеры наших величин по Оу и Ох
    int size = years.size();//находим количество годов
    QPen dot_pen = painter.pen(), default_pen = painter.pen(), horizontal_pen = painter.pen(), line_pen = painter.pen();
    double min_year = years.at(0), max_year = years.at(years.size()-1);//минимальный год - нулевой в векторе, максимальный - последний
    dot_pen.setWidth(4);//устанавливаем толщину пера dot_pen в пикселях
    dot_pen.setColor(Qt::darkBlue);//установим цвет пера dot_pen темно-синим
    horizontal_pen.setWidth(0.8);//установим толщину пера horizontsl_pen в пикселях
    horizontal_pen.setStyle(Qt::DotLine);//установим стиль пера horizontal_pen на пунктир
    line_pen.setColor(Qt::red);//установим цвет пера line_dot на красный
    vector<QPen> pens = {default_pen, horizontal_pen, dot_pen};//инициализируем вектор пера
    double delX = max_year - min_year, delY = max - min, posX, posY;//дельта по годам, по метрикам; расположение на Ох, Оу
    for(int i = 0; i < size; i++){
        posX = verX + OFFSET + ((years[i] - min_year) / delX) * (SIZEX - SHIFT * BORDER - verX);//вычисляем позицию точки по Х
        if (delY == 0) {
            posY = horY - BORDER - ((metric[i] - min)) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;//вычисляем позицию точки по У
        } else {
            posY = horY - BORDER - ((metric[i] - min) / delY) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;//вычисляем позицию точки по У
        }
        vector<double> positions = {posX, posY, horY, verX, SIZEY, BORDER};//вектор позиций
        draw_dot(pens, painter, metric[i], years[i], max, min, positions);//рисуем точку
    }
    painter.setPen(line_pen);//меняем перо на line_pen
    line(painter, years, metric, min, max);
}

void line(QPainter &painter, vector<int> years, vector<double> metric, double min, double max)
{
    double min_year = years.at(0), max_year = years.at(years.size()-1);//минимальный год - нулевой в векторе, максимальный - последний
    const int horY = SIZEY - BORDER - GRAPHICYCLOSE / 2, verX = BORDER + GRAPHICXCLOSE;//определяем размеры наших величин по Оу и Ох
    int size = years.size();//находим количество годов
    double delX = max_year - min_year, delY = max - min;//дельта по годам, по метрикам; расположение на Ох, Оу
    for (int i=0; i< size -1; i++) {
        double posX1 = verX + OFFSET + ((years[i] - min_year) / delX) * (SIZEX - SHIFT * BORDER - verX);
        double posX2 = verX + OFFSET + ((years[i+1] - min_year) / delX) * (SIZEX - SHIFT * BORDER - verX);
        double posY1, posY2;
        if (delY == 0) {
             posY1 = horY - BORDER - ((metric[i] - min)) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;
             posY2 = horY - BORDER - ((metric[i+1] - min)) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;
           /* QPoint point1(posX1, posY1);
            QPoint point2 (posX2, posY2);
            painter.drawLine(point1, point2);//соединяем 2 точки   */
        } else {
         posY1 = horY - BORDER - ((metric[i] - min) / delY) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;
         posY2 = horY - BORDER - ((metric[i+1] - min) / delY) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;
        }
        QPoint point1(posX1, posY1);
        QPoint point2 (posX2, posY2);
        painter.drawLine(point1, point2);//соединяем 2 точки
    }
}

void draw_values(QPainter &painter, vector<int> years, double min, double max, double med)//финкция которой наносим на Оу еще значения помимо максимума, минимума, медианы
{
    const int horY = SIZEY - BORDER - GRAPHICYCLOSE / 2, verX = BORDER + GRAPHICXCLOSE;//определяем размеры наших величин по Оу и Ох
    double min_year = years.at(0), max_year = years.at(years.size()-1);//минимальный год - нулевой в векторе, максимальный - последний
    double delX = max_year - min_year, delY = max - min, posX, posY1, posY2, posY3;
    posX = verX + OFFSET + ((max_year - min_year) / delX) * (SIZEX - SHIFT * BORDER - verX);
    if (((med + 1) > min) && ((med + 1) < max)) {
        posY1 = horY - BORDER - ((med + 1 - min) / delY) * (horY - BORDERXPOS * BORDER) * DECOMPRETION ;
        painter.drawLine(verX - SHIFT + 1, posY1, verX + SHIFT - 1, posY1);
        painter.drawLine(verX, posY1, posX, posY1);
        painter.drawText(0, posY1 - 1, QString::number(med + 1, 'g', 4));
        painter.drawLine(verX - SHIFT + 1, posY1, verX + SHIFT - 1, posY1);
    }
    if (((med - 0.75) > min) && ((med - 0.75) < max)) {
        posY2 = horY - BORDER - ((med - 0.75 - min) / delY) * (horY - 4 * BORDER) * DECOMPRETION ;
        painter.drawLine(verX - SHIFT + 1, posY2, verX + SHIFT - 1, posY2);
        painter.drawLine(verX, posY2, posX, posY2);
        painter.drawText(0, posY2 - 1, QString::number(med - 0.75, 'g', 4));
        painter.drawLine(verX - SHIFT + 1, posY2, verX + SHIFT - 1, posY2);
    }
    if (((med - 1) > min) && ((med - 1) < max)) {
        posY3 = horY - BORDER - ((max - 1 - min) / delY) * (horY - 4 * BORDER) * DECOMPRETION ;
        painter.drawLine(verX - 2, posY3, verX + 2, posY3);
        painter.drawLine(verX, posY3, posX, posY3);
        painter.drawText(0, posY3 - 1, QString::number(max -1, 'g', 4));
        painter.drawLine(verX - SHIFT + 1, posY3, verX + SHIFT - 1, posY3);
    }
}

void draw_med(QPainter &painter, vector<int> years, double min, double max, double med)
{
    double min_year = years.at(0), max_year = years.at(years.size()-1);
    QPen default_pen = painter.pen(), horizontal_pen = painter.pen();
    default_pen.setColor(Qt::black);
    horizontal_pen.setWidth(0.8);
    horizontal_pen.setStyle(Qt::DotLine);
    horizontal_pen.setColor(Qt::black);
    const int horY = SIZEY - BORDER - GRAPHICYCLOSE / 2, verX = BORDER + GRAPHICXCLOSE;
    double diffX = max_year - min_year, diffY = max - min, posX, posY;
    if (diffY == 0) {
        med = max;
        posX = verX + OFFSET + ((max_year - min_year) / diffX) * (SIZEX - SHIFT * BORDER - verX);
        posY = horY - BORDER - ((med - min)) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;
        painter.setPen(default_pen);
        painter.drawText(0, posY - 1, QString::number(med, 'g', 4));
        painter.drawLine(verX - SHIFT + 1, posY, verX + SHIFT - 1, posY);
        painter.drawText(posX, posY - 1, "med");
    }
    posX = verX + OFFSET + ((max_year - min_year) / diffX) * (SIZEX - SHIFT * BORDER - verX);
    posY = horY - BORDER - ((med - min) / diffY) * (horY - BORDERXPOS * BORDER) * DECOMPRETION;
    painter.setPen(default_pen);
    painter.drawText(0, posY - 1, QString::number(med, 'g', 4));
    painter.drawLine(verX - SHIFT + 1, posY, verX + SHIFT - 1, posY);
    painter.drawText(posX, posY - 1, "med");
    painter.setPen(horizontal_pen);
    painter.drawLine(verX, posY, posX, posY);
}

void draw_axis(QPainter &painter)//функция рисования осей
{
    const int horY = SIZEY - BORDER - GRAPHICYCLOSE / 2, verX = BORDER + GRAPHICXCLOSE;//определяем размеры наших величин по Оу и Ох
    painter.drawLine(verX, horY, SIZEX - BORDER, horY); // Ox
    painter.drawLine(SIZEX - BORDER, horY, SIZEX - BORDER - OFFSET, horY - SHIFT);//верхняя стрелочки Ох
    painter.drawLine(SIZEX - BORDER, horY, SIZEX - BORDER - OFFSET, horY + SHIFT);//нижняя стрелочка Ох
    painter.drawLine(verX, horY, verX, SIZEY - BORDERXTEXT*BORDER); // Oy
    painter.drawLine(verX, SIZEY - BORDERXTEXT*BORDER, verX - SHIFT,SIZEY - BORDERXTEXT*BORDER + OFFSET);//левая стрелочка Оу
    painter.drawLine(verX, SIZEY - BORDERXTEXT*BORDER, verX + SHIFT, SIZEY - BORDERXTEXT*BORDER + OFFSET);//правая стрелочка Оу
}

QPicture draw_picture(vector<int> years, vector<double> metric, QString metric_name, double min, double max, double med)
{
    QPainter painter;
    QPen horizontal_pen = painter.pen(), line_pen = painter.pen();
    horizontal_pen.setWidth(0.8);
    horizontal_pen.setStyle(Qt::DotLine);
    line_pen.setColor(Qt::darkBlue);
    QPicture picture;//устройство рисования которое записывает и воспроизводит команды QPainter
    picture.setBoundingRect(QRect(QPoint(0, 0), QPoint(SIZEX, SIZEY)));//setBoundingRect создает ограничивающий прямоугольник в соответственные координаты
    painter.begin(&picture);
    const int horY = SIZEY - BORDER - GRAPHICYCLOSE / 2;
    draw_axis(painter);
    draw_line(painter, years, metric, min, max);
    draw_med(painter, years, min, max, med);
    painter.setPen(horizontal_pen);
    draw_values(painter, years, min, max, med);
    painter.drawText(0, SIZEY - BORDERXTEXT*BORDER + OFFSET, metric_name);
    painter.drawText(SIZEX - BORDER - OFFSET, horY, "Year");
    return picture;
}

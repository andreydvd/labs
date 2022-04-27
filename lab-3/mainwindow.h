#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <fstream>
#include <QShortcut>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace std;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *csv_model;

private slots:
    void on_btn_load_clicked();
    void on_btn_loadfile_clicked();
    void on_btn_calculate_and_draw_clicked();
    void on_btn_formateddata_clicked();
    //void draw_picture(vector<int> years, vector<double> metric, QString metric_name, double min, double max, double med);

    void on_line_col_textChanged(const QString &arg1);

    void on_line_region_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void setupWindow();
    QString filename = nullptr;
    QStandardItemModel *model = new QStandardItemModel;
    QStringList headers;
    vector<vector<string>> csv_read;
    QString col;
};

const int SIZEX = 580,
          SIZEY = 380,
          BORDER = 60,//граница
          GRAPHICYCLOSE = 20,//для размерности горизонтали
          GRAPHICXCLOSE = 10,//для размерности вертикали
          DECOMPRETION = 3,//растяжение по Оу
          OFFSET = 5,//для позиций точек по Ох и стрелочек
          SHIFT = 3,//для отрисовки стрелочек осей и линий, а также штрихов
          BORDERXPOS = 4,//для корректного расположения значений на Оу
          BORDERXTEXT = 6;//для подписи столбца и отрисовки Оу

const double BORDERXTEXTMAX = 0.8;//для корректной постановки максимума


#endif // MAINWINDOW_H


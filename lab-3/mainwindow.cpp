#include "mainwindow.h"
#include "workwithgraph.h"
#include "ui_mainwindow.h"
#include "calculator.h"
#include "proverochki.h"
#include "filework.h"

#include <QFile>
#include <QFileDialog>
#include <QAbstractItemModel>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupWindow();
    csv_model = new QStandardItemModel(this);
    csv_model->setColumnCount(7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWindow()//изначальное положение кнопок
{
    ui->btn_calculate_and_draw->setEnabled(0);
    ui->btn_formateddata->setEnabled(0);
    ui->btn_load->setEnabled(0);
}

void model_cpy(QStandardItemModel* from, QStandardItemModel* to)//функция копирования из одной модельки в другeю
{
    to->clear();
    for (int row = 0 ; row < from->rowCount() ; row++){
        QList<QStandardItem *> res;
        for (int col = 0; col < from->columnCount(); col++){
            res.append(new QStandardItem(from->item(row, col)->text()));
        }
       to->appendRow(res);//добавляет строку, содержащую элементы. ПРи необходимости кол-во столбцовувелич до размера элементов
    }
}

void MainWindow::on_btn_loadfile_clicked()//кнопка загрузки файла
{
    filename = QFileDialog::getOpenFileName(this, "Choose file", "", "*.csv");//класс QFileDialog предоставляет диалоговое окно для выбора файлов/каталогов
        csv_read = read_csv_file(filename.toStdString());
    if (csv_read.size() == 0){
        ui->label_title->setText("Нет таблицы");
        ui->label_result->setText("Невозможно открыть файл");
        ui->line_region->setText("");
        ui->line_col->setText("");
    } else {
        csv_model->clear();
        csv_model->setColumnCount(csv_read.at(0).size());
        headers.clear();
        for (string str : csv_read.at(0)) {//цикл for на основе диапозона для итерации по вектору csv_read; доступ по значению с исп копии объявленной как опред тип
          headers.push_back(QString::fromStdString(str));
        }
        csv_model->setHorizontalHeaderLabels(headers);
        bool is_header = true;
        for (vector<string> item_list : csv_read) {
            if (is_header){
                is_header = false;
                continue;
            }
            QList<QStandardItem *> standardItemsList;
            for (string item_str : item_list){
                QString q_item_str = QString::fromStdString(item_str);
                standardItemsList.append(new QStandardItem(q_item_str));
            }
            csv_model->insertRow(csv_model->rowCount(), standardItemsList);
        }
        model_cpy(csv_model, model);
        ui->label_title->setText(filename);
    }
    ui->btn_load->setEnabled(true);
}


void MainWindow::on_btn_load_clicked()//кнопка загрузки данных
{
    ui->table_metric->setModel(csv_model);
    ui->table_metric->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->btn_formateddata->setEnabled(true);
}

int check_column(QString col)//проверка колонки на целое число
{
    bool flag = true;
    int res = col.toInt(&flag);
    if (flag)
        return res;
    return -1;
}

void MainWindow::on_btn_formateddata_clicked()//кнопка отформатированных данных
{
    QString region = ui->line_region->text();
    QString column = ui->line_col->text();
    model->clear();
    model->setColumnCount(7);
    model->setHorizontalHeaderLabels(headers);
    for (int row = 0; row < csv_model->rowCount(); ++row){//выбираем нужные записи
        if ((csv_model->item(row, 1)->text() == region || region == "")){
            QList<QStandardItem *> res;
            for (int i = 0; i < csv_model->columnCount(); ++i){
                res.append(new QStandardItem(csv_model->item(row, i)->text()));
            }
            model->insertRow(model->rowCount(), res);
        }
    }
    ui->table_metric->setModel(model);
    if ((region == "") || (column == "") || ((column > "7") || (column < "3"))) {
        ui->btn_calculate_and_draw->setEnabled(false);//блочим кнопку
        ui->label_result->setText("Проверьте регион и колонку!" "\nКнопка CALC разблокируется \nпосле введения колонки и \nнажатия кнопки FORMATED DATA");
    } else {
        ui->btn_calculate_and_draw->setEnabled(true);
    }
}

void MainWindow::on_btn_calculate_and_draw_clicked()//кнопка подсчета метрик и рисования графика
{
    QString column = ui->line_col->text();
    if (!column.isEmpty() && col != column) {
        col = column;
        double minimum = 0, maximum = 0, mediana = 0;
        int col_metric = check_column(column) - 1;
        vector<double> arr;
        vector<int> years;
        for (int row = 0; row < model->rowCount(); ++row){//считаем метрики по нужным данным
            QString str = model->item(row, col_metric)->text();
            QString str_year = model->item(row, 0)->text();
            if (is_normal_metric(str.toStdString()) && is_normal_metric(str_year.toStdString())){
                arr.push_back(model->item(row, col_metric)->text().toDouble());
                years.push_back(model->item(row, 0)->text().toInt());
            }
        }
        calc_metric(arr, col_metric, &minimum, &maximum, &mediana);
        QString result_text = "Минимум: "+ QString::number(minimum) +"\nМаксимум: "+ QString::number(maximum)
                +"\nМедиана: "+ QString::number(mediana) + "\n кнопка CALCULATE AND DRAW" "\nразблокируется после нажания" "\nкнопки FORNATED DATA";
        if (arr.size() == 0){
            result_text = "Нет результатов. Проверьте назва" "\nние региона"  "\n или выбранную колонку.";
             ui->label_result->setText(result_text);
             ui->graphic->clear();
             return;
        }
        ui->label_result->setText(result_text);
        QString col_name = headers.at(col_metric);
        QPicture picture = draw_picture(years, arr, col_name, minimum, maximum, mediana);
        ui->graphic->setPicture(picture);
    }
    ui->btn_calculate_and_draw->setEnabled(false);
}



void MainWindow::on_line_col_textChanged(const QString &arg1)
{
    if (col.isEmpty() || ui->label_col->text().isEmpty()) {
        ui->btn_calculate_and_draw->setEnabled(false);
    } else
    if (col != ui->label_col->text()) {
        ui->btn_calculate_and_draw->setEnabled(true);
    }
}


void MainWindow::on_line_region_textChanged(const QString &arg1)
{
    col = "";
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    context = allocateStructContext();
    errors = allocateStructError();
    connect(ui->buttonLoadFile, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(ui->buttonLoadData, &QPushButton::clicked, this, &MainWindow::onLoadDataClicked);
    connect(ui->buttonCalculateMetrics, &QPushButton::clicked, this, &MainWindow::onCalculateMetricsClicked);
}

MainWindow::~MainWindow() //?
{
    free(context);
    free(data);
    freeArray(context->data, context->linesCount);
    fclose(file);
    delete ui;
}

void MainWindow::onLoadFileClicked()
{
    QString filenameStr = QFileDialog::getOpenFileName(this, "Выберите файл", QDir::currentPath(), "*.csv"); //QDir-возвращает путь директории файла
    char* filename = QstringToCharArray(filenameStr);
    context->fileName = filename;
    if (doOperations(LoadFile, context, errors) == File)
        ui->showFileName->setText(filenameStr);
    else
        showErrorWindow("Данные отсутствуют");
}


void MainWindow::showErrorWindow(char* nameError)
{
    QMessageBox::warning(this, "ERROR", nameError);
}


void MainWindow::onLoadDataClicked()
{
    if (ui->showFileName->text().isEmpty())
        showErrorWindow("Вы не выбрали файл");
    else {
        QString regionNameString = ui->regionLineEdit->text();
        context->regionName = QstringToCharArray(regionNameString);
        if (doOperations(LoadData, context, errors) == RegionError)
        {
            showErrorWindow("Неверно указан регион");
        }
        else
        {
            ui->regionInformationLabel->setText(context->regionName);
            showData(context);
        }
    }
}

void MainWindow::onCalculateMetricsClicked()
{
    if (ui->regionLineEdit->text().isEmpty() || ui->showFileName->text().isEmpty())
        showErrorWindow("Введите недостающие данные");
    else
    {
        QString columnNumberString = ui->columnLineEdit->text();
        context->columnNumber = columnNumberString.toInt();
        if (doOperations(CalculateMetrics, context, errors) == MetricsError)
        {
            showErrorWindow("Номер колонки введен неверно");
        }
        else
        {
            ui->lineMax->setText(QString::number(context->calc.max));
            ui->lineMin->setText(QString::number(context->calc.min));
            ui->lineMed->setText(QString::number(context->calc.med));
        }
    }
}


void MainWindow::showData(AppContext* context)
{
    ui->tableWidget->setColumnCount(context->fieldsNum);
    QStringList QColumns = ConvertRowToQTFormat(context->headers, context->fieldsNum);
    ui->tableWidget->setHorizontalHeaderLabels(QColumns);
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < context->linesCount; i++)
    {
        QStringList currentRow = ConvertRowToQTFormat(context->regionData[i], context->fieldsNum);
        ui->tableWidget->setRowCount(i + 1);
        for (int j = 0; j < currentRow.count(); j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setData(Qt::EditRole, currentRow.at(j).toDouble());
            item->setText(currentRow.at(j));
            ui->tableWidget->setItem(i, j, item);
        }
    }
}


QStringList MainWindow::ConvertRowToQTFormat(char **row, int size) {
    QStringList qsl = {};
    for(int i = 0; i < size; i++) {
        qsl.append(QString::fromUtf8(row[i]));
    }
    return qsl;
}

char* MainWindow::QstringToCharArray(QString string) //преобразование строки в массив символов
{
    char *str = (char*)malloc(sizeof(char)*(string.size() + 1));
    int i;
    for (i = 0; i < string.size(); i++)
    {
        str[i] = string.at(i).unicode();
    }
    str[i] = 0;
    return str;
}

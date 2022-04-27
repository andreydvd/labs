#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "logic.h"
#include "entrypoint.h"
#include "appcontext.h"
#include "memorywork.h"
#include "filework.h"
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadFileClicked();
    void onLoadDataClicked();
    void onCalculateMetricsClicked();

private:
    AppContext* context;
    AppData* data;
    Error* errors;
    FILE* file;
    char* QstringToCharArray(QString string);
    QStringList ConvertRowToQTFormat(AppContext* context);
    void showData(AppContext* context);
    QStringList ConvertRowToQTFormat(char** row, int size);
    void showErrorWindow(char* nameError);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

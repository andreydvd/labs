#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double firstNumber;

private slots:
    void digitsNumbers();
    void on_pushButton_dot_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_equal_clicked();
    void operations();
    void sqrtButton();
    void on_pushButton_del_clicked();
    void signClicked();
    void findSymbolE();
    void connectingButtons();
    void setEnabledButtons(bool value);
    void setEnabledDigits(bool value);
};
#endif // MAINWINDOW_H

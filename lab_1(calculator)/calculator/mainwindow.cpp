#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) //конструктор
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectingButtons();
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow() //диструктор
{
    delete ui;
}

void MainWindow::digitsNumbers()
{
    QPushButton *button = (QPushButton *)sender(); //получение данных кнопки, на которую мы нажали
    double allNumbers;
    QString newLabel;
    if (ui->result->text().contains(".") && button->text() == "0")
    {
        newLabel = ui->result->text() + button->text();
    }
    else
    {
        allNumbers = (ui->result->text() + button->text()).toDouble(); //соединение чисел с новыми и перевод в тип double
        newLabel = QString::number(allNumbers,'g',10); //перевод из типа double обратно в строку
    }
    ui->result->setText(newLabel);
    if(ui->result->text().contains("e"))
        {
            setEnabledDigits(0);
        }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result->text().contains('.'))) //условие того, чтобы кнопка-разделитель появлялась только один раз
        ui->result->setText(ui->result->text()+'.');
}

void MainWindow::operations()
{
    setEnabledDigits(1);

    QPushButton *button = (QPushButton *)sender();
    firstNumber = ui->result->text().toDouble();
    ui->result->setText("");
    button->setChecked(true); //?
    setEnabledButtons(0);
}


void MainWindow::on_pushButton_ac_clicked()
{
    setEnabledDigits(1);
    setEnabledButtons(1);
    ui->result->setText("0");
    //setEnabledButtons(1);
}


void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, secondNumber;
    QString newLabel;
    secondNumber = ui->result->text().toDouble();
    if (ui->pushButton_plus->isChecked()){
        labelNumber = firstNumber + secondNumber;
        newLabel = QString::number(labelNumber,'g',10); //перевод из типа double обратно в строку
        ui->result->setText(newLabel);
        ui->pushButton_plus->setChecked(false);}
    else if (ui->pushButton_minus->isChecked()){
        labelNumber = firstNumber - secondNumber;
        newLabel = QString::number(labelNumber,'g',10); //перевод из типа double обратно в строку
        ui->result->setText(newLabel);
        ui->pushButton_minus->setChecked(false);}
    else if (ui->pushButton_mult->isChecked()){
        labelNumber = firstNumber * secondNumber;
        newLabel = QString::number(labelNumber,'g',10); //перевод из типа double обратно в строку
        ui->result->setText(newLabel);
        ui->pushButton_mult->setChecked(false);}
    else if (ui->pushButton_divide->isChecked()){
        if(secondNumber == 0){
            QMessageBox::critical(this, "warning", "На ноль делить нельзя!");
            ui->result->setText("0");}
        else{
            labelNumber = firstNumber / secondNumber;
            newLabel = QString::number(labelNumber,'g',10); //перевод из типа double обратно в строку
            ui->result->setText(newLabel);}
        ui->pushButton_divide->setChecked(false);}
    if(ui->result->text().contains("e"))
        {
            setEnabledDigits(0);
        }
    setEnabledButtons(1);
}

void MainWindow::sqrtButton()
{
    QPushButton *button = (QPushButton *)sender(); //получение данных кнопки, на которую мы нажали

    double allNumbers;
    QString newLabel;

    if(button->text() == "√")
    {
            allNumbers = (ui->result->text()).toDouble();
            if(allNumbers < 0){
                QMessageBox::critical(this, "warning", "Отрицательный корень!");
                ui->result->setText("0");
            }
            else{
                allNumbers = sqrt(allNumbers);
                newLabel = QString::number(allNumbers, 'g', 10);
                ui->result->setText(newLabel);
            }
     }
}


void MainWindow::on_pushButton_del_clicked()
{
    QString strnum;
    strnum = ui->result->text();
    if (strnum!="ОШИБКА")
    {
        strnum.chop(1);
         ui->result->setText(strnum);
    }
    else
    {
        ui->result->setText("");
    }
}


void MainWindow::signClicked()
{
    QPushButton *button = (QPushButton *)sender(); //получение данных кнопки, на которую мы нажали

    double allNumbers;
    QString newLabel;
    if (button->text() == "+/-")
    {
        allNumbers = (ui->result->text()).toDouble(); //соединение чисел с новыми и перевод в тип double
        allNumbers = allNumbers * (-1);
        newLabel = QString::number(allNumbers,'g',10); //перевод из типа double обратно в строку
        ui->result->setText(newLabel);
    }
}

void MainWindow::findSymbolE()
{
    if(ui->result->text().contains("e"))
    {
        setEnabledDigits(0);
    }
}

void MainWindow:: connectingButtons()
{
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digitsNumbers()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(sqrtButton()));
    connect(ui->pushButton_sign,SIGNAL(clicked()),this,SLOT(signClicked()));
}

void MainWindow:: setEnabledDigits(bool value)
{
    ui->pushButton_0->setEnabled(value);
    ui->pushButton_1->setEnabled(value);
    ui->pushButton_2->setEnabled(value);
    ui->pushButton_3->setEnabled(value);
    ui->pushButton_4->setEnabled(value);
    ui->pushButton_5->setEnabled(value);
    ui->pushButton_6->setEnabled(value);
    ui->pushButton_7->setEnabled(value);
    ui->pushButton_8->setEnabled(value);
    ui->pushButton_9->setEnabled(value);
    ui->pushButton_del->setEnabled(value);
    ui->pushButton_dot->setEnabled(value);
}

void MainWindow:: setEnabledButtons(bool value)
{
    ui->pushButton_plus->setEnabled(value);
    ui->pushButton_minus->setEnabled(value);
    ui->pushButton_mult->setEnabled(value);
    ui->pushButton_divide->setEnabled(value);
    ui->pushButton_sqrt->setEnabled(value);
}


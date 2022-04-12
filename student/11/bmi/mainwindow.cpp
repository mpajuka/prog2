#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::result);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::result()
{
    if (ui->weightLineEdit->text() != "" && ui->heightLineEdit->text() != "")
    {
        double weight = ui->weightLineEdit->text().toDouble();
        double height = ui->heightLineEdit->text().toDouble();

        double new_height = height / 100;
        double bmi = weight / (new_height * new_height);

        ui->resultLabel->setText(QString::number(bmi));

        if (bmi < 25 && bmi > 18.5)
        {
            ui->infoTextBrowser->setText("Your weight is normal.");
        }
        if (bmi < 18.5)
        {
            ui->infoTextBrowser->setText("You are underweight.");
        }
        if (bmi > 25)
        {
            ui->infoTextBrowser->setText("You are overweight.");
        }
    }
}



void MainWindow::on_closeButton_clicked()
{
    close();
}


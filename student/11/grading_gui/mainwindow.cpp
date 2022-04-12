#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countPushButton, &QPushButton::clicked, this, &MainWindow::result);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::result()
{
    n = ui->spinBoxN->value();
    g = ui->spinBoxG->value();
    p = ui->spinBoxP->value();
    e = ui->spinBoxE->value();

    int score = count_final_grade(n, g, p, e);

    ui->textBrowser->setText(QString::fromStdString("Total grade: " + std::to_string(score)));
}




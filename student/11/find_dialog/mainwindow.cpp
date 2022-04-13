#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::findText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::findText()
{
    std::string file_name = ui->fileLineEdit->text().toStdString();
    std::string key_text = ui->keyLineEdit->text().toStdString();

    std::fstream file(file_name);

    if (not file)
    {
        ui->textBrowser->setText("File not found");
    }
    if (file && key_text == "") {
        ui->textBrowser->setText("File found");
    }



    if (file && key_text != "")
    {
        ui->textBrowser->setText("Word not found");
    }

}


void MainWindow::on_closePushButton_clicked()
{
    close();
}



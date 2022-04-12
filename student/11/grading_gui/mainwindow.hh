#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "gradecounter.hh"

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

public slots:
    void result();

private:
    Ui::MainWindow *ui;
    int n, g, p, e = 0;
};
#endif // MAINWINDOW_HH

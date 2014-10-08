#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Simulation* simulation, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_rotateRightButton_clicked();

    void on_rotateLeftButton_clicked();

    void on_openButton_clicked();

    void on_closeButton_clicked();

    void on_upButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();
    void on_rightButton_clicked();

private:
    Ui::MainWindow *ui;

    Simulation* simulation;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
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



    void on_leftButton_pressed();
    void on_leftButton_released();
    void on_rightButton_pressed();
    void on_rightButton_released();
    void on_upButton_pressed();
    void on_upButton_released();
    void on_downButton_pressed();
    void on_downButton_released();
    void on_rotateLeftButton_pressed();
    void on_rotateLeftButton_released();
    void on_rotateRightButton_pressed();
    void on_rotateRightButton_released();
    void on_openButton_pressed();
    void on_openButton_released();
    void on_closeButton_pressed();
    void on_closeButton_released();

	void on_runScriptButton_clicked();

    void on_openScriptAction_triggered();

	void on_runScriptAction_triggered();

	void on_actionOpen_shape_triggered();

private:
    Ui::MainWindow *ui;

    Simulation* simulation;
	QSettings settings;

    void updateScoreDisplay();

	void openScriptFile();
	void openShapeFile();
};

#endif // MAINWINDOW_H

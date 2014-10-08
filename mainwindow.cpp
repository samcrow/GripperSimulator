#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Simulation* simulation, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    simulation(simulation)
{
    ui->setupUi(this);
    ui->simulationDisplay->setSimulation(simulation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rotateRightButton_clicked()
{
    simulation->rotateGripperRight();
    ui->simulationDisplay->repaint();
}

void MainWindow::on_rotateLeftButton_clicked()
{
    simulation->rotateGripperLeft();
    ui->simulationDisplay->repaint();
}

void MainWindow::on_openButton_clicked()
{
    simulation->openGripperSomewhat();
    ui->simulationDisplay->repaint();
}

void MainWindow::on_closeButton_clicked()
{
    simulation->closeGripperSomewhat();
    ui->simulationDisplay->repaint();
}

void MainWindow::on_upButton_clicked()
{
    simulation->nudgeGripperUp();
    ui->simulationDisplay->repaint();
}
void MainWindow::on_downButton_clicked()
{
    simulation->nudgeGripperDown();
    ui->simulationDisplay->repaint();
}
void MainWindow::on_leftButton_clicked()
{
    simulation->nudgeGripperLeft();
    ui->simulationDisplay->repaint();
}
void MainWindow::on_rightButton_clicked()
{
    simulation->nudgeGripperRight();
    ui->simulationDisplay->repaint();
}

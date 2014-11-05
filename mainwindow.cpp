#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JavaScript/javascriptevaluator.h"
#include <sstream>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(Simulation* simulation, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    simulation(simulation)
{
    ui->setupUi(this);
    ui->simulationDisplay->setSimulation(simulation);
    ui->rightPane->setVisible(false);
    ui->console->setScriptEngine(&simulation->scriptEvaluator().engine());

    connect(simulation, &Simulation::scoreChanged, this, &MainWindow::updateScoreDisplay);

    updateScoreDisplay();
}

void MainWindow::updateScoreDisplay() {
    std::stringstream stream;
    stream << "Total score " << simulation->scoreCalculator().netScore() << " (movement " << simulation->scoreCalculator().movementScore() << ", information " << simulation->scoreCalculator().informationScore() << ")";
    ui->statusBar->showMessage(QString::fromStdString(stream.str()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_leftButton_pressed()
{
    simulation->startMovingGripperLeft();
}
void MainWindow::on_leftButton_released()
{
    simulation->stopMovingGripperHorizontally();
}
void MainWindow::on_rightButton_pressed()
{
    simulation->startMovingGripperRight();
}
void MainWindow::on_rightButton_released()
{
    simulation->stopMovingGripperHorizontally();
}
void MainWindow::on_upButton_pressed()
{
    simulation->startMovingGripperUp();
}
void MainWindow::on_upButton_released()
{
    simulation->stopMovingGripperVertically();
}
void MainWindow::on_downButton_pressed()
{
    simulation->startMovingGripperDown();
}
void MainWindow::on_downButton_released()
{
    simulation->stopMovingGripperVertically();
}
void MainWindow::on_rotateLeftButton_pressed()
{
    simulation->startRotatingGripperCounterclockwise();
}
void MainWindow::on_rotateLeftButton_released()
{
    simulation->stopRotatingGripper();
}
void MainWindow::on_rotateRightButton_pressed()
{
    simulation->startRotatingGripperClockwise();
}
void MainWindow::on_rotateRightButton_released()
{
    simulation->stopRotatingGripper();
}
void MainWindow::on_openButton_pressed() {
    simulation->startOpeningGripper();
}
void MainWindow::on_openButton_released() {
    simulation->stopOpeningClosingGripper();
}
void MainWindow::on_closeButton_pressed() {
    simulation->startClosingGripper();
}
void MainWindow::on_closeButton_released() {
    simulation->stopOpeningClosingGripper();
}

void MainWindow::on_testButton_clicked()
{
    if(simulation->scriptEvaluator().hasScriptFile()) {
        const QScriptValue result = simulation->scriptEvaluator().executeScriptFile();
        if(result.isError()) {
            ui->statusBar->showMessage(result.toString(), 1000);
        }
    }
}

void MainWindow::on_openScriptAction_triggered()
{
    const QString path = QFileDialog::getOpenFileName(this, "Open a script file", QDir::homePath(), "JavaScript files (*.js)");
    if(!path.isEmpty()) {
        simulation->scriptEvaluator().setScriptFile(path);
    }
}

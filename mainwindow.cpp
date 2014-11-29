#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JavaScript/javascriptevaluator.h"
#include "IO/objectio.h"
#include <sstream>
#include <QDebug>
#include <QStringBuilder>
#include <QFileDialog>
#include <QMessageBox>

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

void MainWindow::openScriptFile() {
	QString initialPath = settings.value("simulation.script", QDir::homePath()).toString();
	// Ensure that the initial path is a directory
	const QFileInfo initialInfo(initialPath);
	if(!initialInfo.isDir()) {
		initialPath = initialInfo.dir().path();
	}

	const QString newPath = QFileDialog::getOpenFileName(this, "Choose a script to open", initialPath, "JavaScript files (*.js)");

	if(newPath.isEmpty()) {
		// User cancelled operation
		return;
	}

	QFile scriptFile(newPath);
	bool success = scriptFile.open(QIODevice::ReadOnly | QIODevice::Text);
	if(!success) {
		QMessageBox::critical(this, "Could not open file", QStringLiteral("The script file ") % newPath % QStringLiteral(" could not be opened."));
		return;
	}

	simulation->scriptEvaluator().setScriptFile(newPath);
	simulation->reset();
	settings.setValue("simulation.script", newPath);
}

void MainWindow::openShapeFile() {
	QString initialPath = settings.value("simulation.shape", QDir::homePath()).toString();
	// Ensure that the initial path is a directory
	const QFileInfo initialInfo(initialPath);
	if(!initialInfo.isDir()) {
		initialPath = initialInfo.dir().path();
	}

	const QString newPath = QFileDialog::getOpenFileName(this, "Choose a shape to open", initialPath, "Shape files (*.shape)");

	if(newPath.isEmpty()) {
		// User cancelled operation
		return;
	}

	QFile scriptFile(newPath);
	bool success = scriptFile.open(QIODevice::ReadOnly | QIODevice::Text);
	if(!success) {
		QMessageBox::critical(this, "Could not open file", QStringLiteral("The shape file ") % newPath % QStringLiteral(" could not be opened."));
		return;
	}

	simulation->object().polygon() = ObjectIO::readPolygon(&scriptFile);

	settings.setValue("simulation.shape", newPath);
	simulation->reset();
	ui->simulationDisplay->repaint();
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
    simulation->stopMovingGripper();
}
void MainWindow::on_rightButton_pressed()
{
    simulation->startMovingGripperRight();
}
void MainWindow::on_rightButton_released()
{
    simulation->stopMovingGripper();
}
void MainWindow::on_upButton_pressed()
{
    simulation->startMovingGripperUp();
}
void MainWindow::on_upButton_released()
{
    simulation->stopMovingGripper();
}
void MainWindow::on_downButton_pressed()
{
    simulation->startMovingGripperDown();
}
void MainWindow::on_downButton_released()
{
    simulation->stopMovingGripper();
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

void MainWindow::on_runScriptButton_clicked()
{
    if(simulation->scriptEvaluator().hasScriptFile()) {
		simulation->reset();
        const QScriptValue result = simulation->scriptEvaluator().executeScriptFile();
        if(result.isError()) {
			ui->statusBar->showMessage(result.toString(), 5000);
        }
    }
}

void MainWindow::on_openScriptAction_triggered()
{
	openScriptFile();
}

void MainWindow::on_runScriptAction_triggered()
{
	on_runScriptButton_clicked();
}

void MainWindow::on_actionOpen_shape_triggered()
{
	openShapeFile();
}

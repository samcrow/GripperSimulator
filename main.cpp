#include "mainwindow.h"
#include <QApplication>
#include "Models/simulation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QApplication::setApplicationName("Gripper Simulator");
	QApplication::setApplicationDisplayName("Gripper simulator");
	QApplication::setOrganizationDomain("edu.washington.cs.sensor");
	QApplication::setOrganizationName("Sensor Systems Lab");
	QApplication::setApplicationVersion("1.0.0");

    Simulation simulation;

    MainWindow w(&simulation);
    w.show();

    return a.exec();
}

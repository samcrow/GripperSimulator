#include "mainwindow.h"
#include <QApplication>
#include "Models/simulation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Simulation simulation;

    MainWindow w(&simulation);
    w.show();

    return a.exec();
}

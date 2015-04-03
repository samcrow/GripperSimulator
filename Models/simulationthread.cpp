#include "simulationthread.h"
#include "simulation.h"
#include <QDebug>

SimulationThread::SimulationThread(Simulation& simulation, QObject *parent) :
	QThread(parent),
	simulation_(simulation)
{

}

void SimulationThread::run() {
	qDebug() << "Running";
//	result_ = simulation_.scriptEvaluator().executeScriptFile();
}

QScriptValue SimulationThread::result() const {
	return result_;
}

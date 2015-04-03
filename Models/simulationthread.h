#ifndef SIMULATIONTHREAD_H
#define SIMULATIONTHREAD_H

#include <QObject>
#include <QScriptValue>
#include <QThread>

class Simulation;

class SimulationThread : public QThread
{
	Q_OBJECT
public:
	explicit SimulationThread(Simulation& simulation, QObject *parent = 0);

	QScriptValue result() const;

protected:
	virtual void run() override;

public slots:
private:
	Simulation& simulation_;
	QScriptValue result_;
};

#endif // SIMULATIONTHREAD_H

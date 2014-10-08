#ifndef SIMULATIONDISPLAYWIDGET_H
#define SIMULATIONDISPLAYWIDGET_H

#include <QWidget>
#include "../Models/simulation.h"

class SimulationDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimulationDisplayWidget(QWidget *parent = 0);

    void setSimulation(Simulation* simulation);

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    Simulation* simulation = nullptr;

};

#endif // SIMULATIONDISPLAYWIDGET_H

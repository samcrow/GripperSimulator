#include "linearvaluechanger.h"
#include <QDebug>

LinearValueChanger::LinearValueChanger(double rate, double initialValue, QObject* parent) :
    QObject(parent),
    value_(initialValue),
    rate_(rate)
{
}

LinearValueChanger::LinearValueChanger(QObject* parent) :
    LinearValueChanger(0, 0, parent)
{

}

double LinearValueChanger::value() const {
    return value_;
}
void LinearValueChanger::setValue(double newValue) {
    value_ = newValue;
}
double LinearValueChanger::rate() const {
    return rate_;
}
void LinearValueChanger::setRate(double newRate) {
    rate_ = newRate;
}


void LinearValueChanger::timerEvent(QTimerEvent*) {
    const qint64 elapsed = timeCounter.elapsed();
    // Convert from milliseconds to secionds
    const double dt = (elapsed - lastTime) / 1000.0;

    value_ += dt * rate_;
    try {
        emit valueChanged(value_);
    }
    catch(...) {
        qWarning() << "emit valueChanged threw exception. Pausing.";
        pause();
    }

    lastTime = elapsed;
}

void LinearValueChanger::start() {
    if(timerId == 0) {
        timerId = startTimer(0);
        timeCounter.start();
        lastTime = timeCounter.elapsed();
        if(timerId == 0) {
            throw std::runtime_error("Could not start timer");
        }
    }
}

void LinearValueChanger::pause() {
    if(timerId != 0) {
        killTimer(timerId);
        timeCounter.invalidate();
        timerId = 0;
    }
}

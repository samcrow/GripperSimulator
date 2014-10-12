#ifndef LINEARVALUECHANGER_H
#define LINEARVALUECHANGER_H

#include <QObject>
#include <QElapsedTimer>

/**
 * Changes a value at a specified rate
 */
class LinearValueChanger : public QObject
{
    Q_OBJECT
public:
    LinearValueChanger(double rate, double initialValue = 0, QObject* parent = 0);
    LinearValueChanger(QObject* parent = 0);

    double value() const;
    void setValue(double newValue);
    double rate() const;
    void setRate(double newRate);

protected:

    virtual void timerEvent(QTimerEvent* event) override;

private:
    double value_;
    double rate_;
    int timerId = 0;
    qint64 lastTime = 0;
    QElapsedTimer timeCounter;

signals:
    void valueChanged(double newValue);

public slots:
    void start();
    void pause();

};

#endif // LINEARVALUECHANGER_H

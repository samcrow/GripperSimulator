#ifndef JAVASCRIPTGRIPPER_H
#define JAVASCRIPTGRIPPER_H

#include <QObject>

class Simulation;
class Gripper;

/**
 * Provides an interface that JavaScript code uses
 * to control the gripper
 */
class JavaScriptGripper : public QObject
{
    Q_OBJECT

    // These properties are available to JavaScript code
    Q_PROPERTY(double x READ getX WRITE setX)
    Q_PROPERTY(double y READ getY WRITE setY)
    Q_PROPERTY(double angle READ getAngle WRITE setAngle)
    Q_PROPERTY(double openDistance READ getOpenDistance WRITE setOpenDistance)
    Q_PROPERTY(bool beamBlocked READ isBeamBlocked)
public:
    explicit JavaScriptGripper(Simulation& simulation, QObject *parent = 0);

    double getX() const;
    void setX(double newX);
    double getY() const;
    void setY(double newY);
    double getAngle() const;
    void setAngle(double angle);
    double getOpenDistance() const;
    void setOpenDistance(double newDistance);

    bool isBeamBlocked() const;

public slots:

    // These methods are available to JavaScript code

    void startOpening();
    void startClosing();

    void startMovingLeft();
    void startMovingRight();
    void startMovingUp();
    void startMovingDown();

    void startRotatingCounterclockwise();
    void startRotatingClockwise();

    void stop();

private:

    /**
     * A reference to the Gripper that is being controlled by the script
     */
    Gripper& gripper;
    Simulation& simulation;

signals:

};

#endif // JAVASCRIPTGRIPPER_H

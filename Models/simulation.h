#ifndef SIMULATION_H
#define SIMULATION_H
#include <QObject>
#include "linearvaluechanger.h"
#include "gripper.h"
#include "object.h"
#include "objectinformation.h"

/**
 * Contains all components of the simulation.
 *
 * Distances are in meters.
 * The coordinate system is centered on (0, 0).
 * The gripper starts centered on (0, 0) with angle 0,
 * which means that fingertip 1 points in the +X direction
 * and fingertip 2 points in the -X direction.
 */
class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation(QObject* parent = 0);

    Gripper* gripper();
    Object* object();
    ObjectInformation* objectInformation();

public slots:
    void rotateGripperRight();
    void rotateGripperLeft();
    void openGripperSomewhat();
    void closeGripperSomewhat();
    void nudgeGripperUp();
    void nudgeGripperDown();
    void nudgeGripperLeft();
    void nudgeGripperRight();

    void startMovingGripperUp();
    void startMovingGripperDown();
    void stopMovingGripperVertically();
    void startMovingGripperLeft();
    void startMovingGripperRight();
    void stopMovingGripperHorizontally();

    void startRotatingGripperClockwise();
    void startRotatingGripperCounterclockwise();
    void stopRotatingGripper();

    void startOpeningGripper();
    void startClosingGripper();
    void stopOpeningClosingGripper();


signals:

    void changed();

private:
    Gripper gripper_;
    Object object_;
    ObjectInformation info_;

    LinearValueChanger xChanger;
    LinearValueChanger yChanger;
    LinearValueChanger angleChanger;
    LinearValueChanger openChanger;

    /// Gripper move rate, meters/second
    static constexpr double MOVE_RATE = 0.01;
    /// Gripper rotation rate, radians/second
    static constexpr double ROTATE_RATE = 0.2;

    void checkCollisions();
    void checkInfraredBeam();

    bool collides(const QPolygonF& p1, const QPolygonF& p2);

private slots:
    void check();

};

#endif // SIMULATION_H

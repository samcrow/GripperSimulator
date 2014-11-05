#ifndef SIMULATION_H
#define SIMULATION_H
#include <QObject>
#include "linearvaluechanger.h"
#include "gripper.h"
#include "object.h"
#include "objectinformation.h"
#include "scorecalculator.h"
#include "../JavaScript/javascriptevaluator.h"

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

    Gripper& gripper();
    Object& object();
    ObjectInformation& objectInformation();
    ScoreCalculator& scoreCalculator();
    JavaScriptEvaluator& scriptEvaluator();

    /// Returns whether the infrared beam is blocked by an object
    bool isBeamBlocked() const;

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

private slots:

    inline void emitScoreChanged() { emit scoreChanged(); }

signals:

    void changed();

    void scoreChanged();

private:
    Gripper gripper_;
    Object object_;
    ObjectInformation info_;
    ScoreCalculator scoreCalculator_;

    JavaScriptEvaluator scripting;

    LinearValueChanger xChanger;
    LinearValueChanger yChanger;
    LinearValueChanger angleChanger;
    LinearValueChanger openChanger;

    bool beamBlocked_ = true;

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

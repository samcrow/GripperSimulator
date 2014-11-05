#include "simulation.h"
#include <QDebug>
#include <QtMath>

Simulation::Simulation(QObject* parent) :
    QObject(parent),
    scoreCalculator_(gripper_, info_),
    scripting(*this)
{
    // Test

    // Set up the object as a square
    constexpr double SQUARE_HALF_SIDE_LENGTH = 0.01;
    object_.polygon() = QPolygonF(QRectF(-SQUARE_HALF_SIDE_LENGTH, -SQUARE_HALF_SIDE_LENGTH, 2 * SQUARE_HALF_SIDE_LENGTH, 2 * SQUARE_HALF_SIDE_LENGTH));

    connect(&gripper_, &Gripper::geometryChanged, this, &Simulation::check);

    connect(&xChanger, &LinearValueChanger::valueChanged, [this](double newValue) { gripper_.setXOffset(newValue); });
    connect(&yChanger, &LinearValueChanger::valueChanged, [this](double newValue) { gripper_.setYOffset(newValue); });
    connect(&openChanger, &LinearValueChanger::valueChanged, [this](double newValue) { gripper_.setOpenDistance(newValue); });
    connect(&angleChanger, &LinearValueChanger::valueChanged, [this](double newValue) { gripper_.setAngle(newValue); });

    connect(&gripper_, &Gripper::geometryChanged, &scoreCalculator_, &ScoreCalculator::gripperGeometryChanged);
    connect(&scoreCalculator_, &ScoreCalculator::scoreChanged, this, &Simulation::emitScoreChanged);
}

void Simulation::rotateGripperLeft() {
    gripper_.setAngle(gripper_.angle() + qDegreesToRadians(10.0));
}
void Simulation::rotateGripperRight() {
    gripper_.setAngle(gripper_.angle() - qDegreesToRadians(10.0));
}
void Simulation::openGripperSomewhat() {
    try {
        gripper_.setOpenDistance(gripper_.openDistance() + 0.01);
    }
    catch (...) {

    }
}
void Simulation::closeGripperSomewhat() {
    try {
        gripper_.setOpenDistance(gripper_.openDistance() - 0.01);
    }
    catch (...) {

    }
}

void Simulation::nudgeGripperUp() {
    gripper_.setYOffset(gripper_.yOffset() - 0.01);
}
void Simulation::nudgeGripperDown() {
    yChanger.pause();
    gripper_.setYOffset(gripper_.yOffset() + 0.01);
}
void Simulation::nudgeGripperLeft() {
    gripper_.setXOffset(gripper_.xOffset() - 0.01);
}
void Simulation::nudgeGripperRight() {
    gripper_.setXOffset(gripper_.xOffset() + 0.01);
}

void Simulation::startMovingGripperUp() {
    yChanger.setValue(gripper_.yOffset());
    yChanger.setRate(-MOVE_RATE);
    yChanger.start();
}
void Simulation::startMovingGripperDown() {
    yChanger.setValue(gripper_.yOffset());
    yChanger.setRate(MOVE_RATE);
    yChanger.start();
}
void Simulation::stopMovingGripperVertically() {
    yChanger.pause();
}
void Simulation::startMovingGripperLeft() {
    xChanger.setValue(gripper_.xOffset());
    xChanger.setRate(-MOVE_RATE);
    xChanger.start();
}
void Simulation::startMovingGripperRight() {
    xChanger.setValue(gripper_.xOffset());
    xChanger.setRate(MOVE_RATE);
    xChanger.start();
}
void Simulation::stopMovingGripperHorizontally() {
    xChanger.pause();
}
void Simulation::startRotatingGripperCounterclockwise() {
    angleChanger.setValue(gripper_.angle());
    angleChanger.setRate(ROTATE_RATE);
    angleChanger.start();
}
void Simulation::startRotatingGripperClockwise() {
    angleChanger.setValue(gripper_.angle());
    angleChanger.setRate(-ROTATE_RATE);
    angleChanger.start();
}
void Simulation::stopRotatingGripper() {
    angleChanger.pause();
}
void Simulation::startOpeningGripper() {
    openChanger.setValue(gripper_.openDistance());
    openChanger.setRate(MOVE_RATE);
    openChanger.start();
}
void Simulation::startClosingGripper() {
    openChanger.setValue(gripper_.openDistance());
    openChanger.setRate(-MOVE_RATE);
    openChanger.start();
}
void Simulation::stopOpeningClosingGripper() {
    openChanger.pause();
}

Gripper& Simulation::gripper() {
    return gripper_;
}

Object& Simulation::object() {
    return object_;
}

ObjectInformation& Simulation::objectInformation() {
    return info_;
}

ScoreCalculator& Simulation::scoreCalculator() {
    return scoreCalculator_;
}

JavaScriptEvaluator& Simulation::scriptEvaluator() {
    return scripting;
}

bool Simulation::isBeamBlocked() const {
    return beamBlocked_;
}

void Simulation::check() {
    checkInfraredBeam();
    checkCollisions();
    emit changed();
}

void Simulation::checkCollisions() {
    const QPolygonF& objectPolygon = object_.polygon();
    const QPolygonF fingertip1 = gripper_.fingertip1Polygon();
    const QPolygonF fingertip2 = gripper_.fingertip2Polygon();

    bool collided = false;

    if(objectPolygon.boundingRect().intersects(fingertip1.boundingRect())) {
        // Detailed collision check between object and fingertip 1
        collided = collides(objectPolygon, fingertip1) ? true : collided;
    }
    if(objectPolygon.boundingRect().intersects(fingertip2.boundingRect())) {
        // Detailed collision check between object and fingertip 2
        collided = collides(objectPolygon, fingertip2) ? true : collided;
    }

    if(collided) {

    }
    else {
        // Mark the areas around the fingertips as clear
        info_.markClear(gripper_.fingertip1Polygon());
        info_.markClear(gripper_.fingertip2Polygon());
    }
}

void Simulation::checkInfraredBeam() {
    if(object_.hitsObject(gripper_.infraredBeamLine())) {
        // Blocked
        beamBlocked_ = true;
    }
    else {
        // Clear
        beamBlocked_ = false;
        info_.markClear(gripper_.infraredBeamLine());
    }
}

bool Simulation::collides(const QPolygonF& p1, const QPolygonF& p2) {
    // Check each point of each polygon for being inside the other polygon
    for(const QPointF& point : p1) {
        if(p2.containsPoint(point, Qt::OddEvenFill)) {
            return true;
        }
    }
    for(const QPointF& point : p2) {
        if(p1.containsPoint(point, Qt::OddEvenFill)) {
            return true;
        }
    }
    return false;
}


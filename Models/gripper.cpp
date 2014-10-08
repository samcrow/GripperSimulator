#include "gripper.h"
#include <QTransform>
#include <stdexcept>
#include <cmath>

Gripper::Gripper()
{
}

double Gripper::angle() const
{
    return angle_;
}

void Gripper::setAngle(double newAngle)
{
    angle_ = newAngle;
}

double Gripper::openDistance() const
{
    return openDistance_;
}

void Gripper::setOpenDistance(double newOpenDistance)
{
    // Verify distance
    if(newOpenDistance < 0) {
        throw std::out_of_range("Gripper open distance cannot be negative");
    }
    if(newOpenDistance > MAX_OPEN_DISTANCE) {
        throw std::out_of_range("Gripper open distance cannot be greater than the maximum allowed distance");
    }

    openDistance_ = newOpenDistance;
}

double Gripper::xOffset() const {
    return xOffset_;
}
void Gripper::setXOffset(double newOffset) {
    xOffset_ = newOffset;
}
double Gripper::yOffset() const {
    return yOffset_;
}
void Gripper::setYOffset(double newOffset) {
    yOffset_ = newOffset;
}

QPointF Gripper::fingertip1Position() const {
    const double halfDistance = openDistance_ / 2;
    return QPointF(xOffset_ + halfDistance * std::cos(angle_), yOffset_ + halfDistance * std::sin(angle_));
}

QPointF Gripper::fingertip2Position() const {
    const double halfDistance = openDistance_ / 2;
    return QPointF(xOffset_ + halfDistance * -std::cos(angle_), yOffset_ + halfDistance * -std::sin(angle_));
}

QPolygonF Gripper::fingertip1Polygon() const {
    // Dimensions of a fingertip, in meters
    constexpr double WIDTH = 0.02;
    constexpr double DEPTH = 0.01;
    // Create a rectangle with the midpoint of its left side
    // at x = half open distance, y = 0
    // Then rotate it according to the gripper angle
    const double halfDistance = openDistance_ / 2;
    const QRectF rectangle(halfDistance, -WIDTH / 2, DEPTH, WIDTH);

    // Transform
    const QPolygonF rotatedRectangle = QTransform().rotateRadians(angle_).map(rectangle);

    return rotatedRectangle;
}

QPolygonF Gripper::fingertip2Polygon() const {
    // Take the fingertip 1 polygon and rotate it by 180º
    return QTransform().rotate(180).map(fingertip1Polygon());
}

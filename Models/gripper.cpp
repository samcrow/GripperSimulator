#include "gripper.h"
#include <QTransform>
#include <stdexcept>
#include <cmath>
#include <QtMath>
#include <QDebug>

Gripper::Gripper(QObject* parent) :
    QObject(parent)
{
}

double Gripper::angle() const
{
    return angle_;
}

void Gripper::setAngle(double newAngle)
{
    angle_ = newAngle;
    emit geometryChanged();
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
    emit geometryChanged();
}

double Gripper::xOffset() const {
    return xOffset_;
}
void Gripper::setXOffset(double newOffset) {
    xOffset_ = newOffset;
    emit geometryChanged();
}
double Gripper::yOffset() const {
    return yOffset_;
}
void Gripper::setYOffset(double newOffset) {
    yOffset_ = newOffset;
    emit geometryChanged();
}

QPointF Gripper::fingertip1Position() const {
    const double halfDistance = openDistance_ / 2;
    return QPointF(xOffset_ + halfDistance * std::cos(angle_), yOffset_ - halfDistance * std::sin(angle_));
}

QPointF Gripper::fingertip2Position() const {
    const double halfDistance = openDistance_ / 2;
    return QPointF(xOffset_ + halfDistance * -std::cos(angle_), yOffset_ + halfDistance * std::sin(angle_));
}

QPolygonF Gripper::fingertip1Polygon() const {
    // Dimensions of a fingertip, in meters
    constexpr double WIDTH = 0.02;
    constexpr double DEPTH = 0.01;
    // Create a rectangle with the midpoint of its left side
    // at x = half open distance, y = 0
    // Then rotate it according to the gripper angle
    // and translate it according to the X and Y offsets
    const double halfDistance = openDistance_ / 2;
    const QRectF rectangle(halfDistance, -WIDTH / 2 , DEPTH, WIDTH);

    // Transform
    const QPolygonF rotatedRectangle = QTransform().translate(xOffset_, yOffset_).rotateRadians(-angle_).map(rectangle);

    return rotatedRectangle;
}

QPolygonF Gripper::fingertip2Polygon() const {
    // Dimensions of a fingertip, in meters
    constexpr double WIDTH = 0.02;
    constexpr double DEPTH = 0.01;
    // Create a rectangle with the midpoint of its left side
    // at x = half open distance, y = 0
    // Then rotate it according to the gripper angle
    // and translate it according to the X and Y offsets
    const double halfDistance = openDistance_ / 2;
    const QRectF rectangle(halfDistance, -WIDTH / 2 , DEPTH, WIDTH);

    // Transform
    const QPolygonF rotatedRectangle = QTransform().translate(xOffset_, yOffset_).rotateRadians(-angle_ - qDegreesToRadians(180.0)).map(rectangle);

    return rotatedRectangle;
}

QLineF Gripper::infraredBeamLine() const {
    // Between the two gripper points
    return QLineF(fingertip1Position(), fingertip2Position());
}

void Gripper::reset() {
	angle_ = 0;
	openDistance_ = MAX_OPEN_DISTANCE;
	xOffset_ = 0;
	yOffset_ = 0;
	emit geometryChanged();
}

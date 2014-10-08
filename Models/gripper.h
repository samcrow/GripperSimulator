#ifndef GRIPPER_H
#define GRIPPER_H
#include <QPointF>
#include <QPolygonF>

/**
 * Models the PR2 gripper
 */
class Gripper
{
public:

    /**
     * The distance between fingertips when the gripper is fully open
     */
    static constexpr double MAX_OPEN_DISTANCE = 0.09;

    Gripper();

    double angle() const;
    void setAngle(double newAngle);
    double openDistance() const;
    void setOpenDistance(double newOpenDistance);
    double xOffset() const;
    void setXOffset(double newOffset);
    double yOffset() const;
    void setYOffset(double newOffset);


    /**
     * @return The coordinates of fingertip 1
     */
    QPointF fingertip1Position() const;
    /**
     * @return The coordinates of fingertip 2
     */
    QPointF fingertip2Position() const;

    /**
     * @return A polygon that represents fingertip 1
     */
    QPolygonF fingertip1Polygon() const;
    /**
     * @return A polygon that represents fingertip 2
     */
    QPolygonF fingertip2Polygon() const;

private:
    /**
     * Angle of the wrist roll joint, which rotates the gripper.
     * This angle is in radians. Zero corresponds to fingertip 1
     * pointing in the positive X direction.
     */
    double angle_ = 0;

    /**
     * The distance between fingertips, in meters
     */
    double openDistance_ = MAX_OPEN_DISTANCE;

    /**
     * X offset, in meters. Positive is right.
     */
    double xOffset_ = 0;
    /**
     * Y offset, in meters. Positive is up.
     */
    double yOffset_ = 0;
};

#endif // GRIPPER_H

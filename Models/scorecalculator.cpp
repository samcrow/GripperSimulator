#include "scorecalculator.h"
#include <cmath>
#include <QDebug>

ScoreCalculator::ScoreCalculator(Gripper &gripper, ObjectInformation& objectInfo, QObject *parent) :
    QObject(parent),
    gripper(gripper),
    objectInfo(objectInfo)
{
    // Set initial gripper positions
    oldGripperX = gripper.xOffset();
    oldGripperY = gripper.yOffset();
    oldGripperAngle = gripper.angle();

    connect(&gripper, &Gripper::geometryChanged, this, &ScoreCalculator::gripperGeometryChanged);
}

void ScoreCalculator::gripperGeometryChanged() {
    updateMovmementScore();
    updateInformationScore();

    emit scoreChanged();
}

void ScoreCalculator::updateInformationScore() {

    int clearPixels = 0;
    // Count the number of white (1) pixels in the object information bitmap
    const QImage& image = objectInfo.bitmap();
    for(int x = 0; x < image.width(); x++) {
        for(int y = 0; y < image.height(); y++) {
            const QRgb color = image.pixel(x, y);
            if((color & 1) == 1) {
                clearPixels++;
            }
        }
    }

    informationScore_ = clearPixels * PIXEL_SCORE;
}

void ScoreCalculator::updateMovmementScore() {
    const double newX = gripper.xOffset();
    const double newY = gripper.yOffset();
    const double newAngle = gripper.angle();

    const double dx = newX - oldGripperX;
    const double dy = newY - oldGripperY;
    const double dAngle = std::abs(newAngle - oldGripperAngle);

    const double moveDistance = std::hypot(dx, dy);

    movementScore_ -= moveDistance * MOVE_COST;
    movementScore_ -= dAngle * ROTATE_COST;


    // Store values for later use
    oldGripperX = newX;
    oldGripperY = newY;
    oldGripperAngle = newAngle;
}

int ScoreCalculator::netScore() const {
    return std::round(informationScore_ + movementScore_);
}

int ScoreCalculator::movementScore() const {
    return std::round(movementScore_);
}

int ScoreCalculator::informationScore() const {
    return std::round(informationScore_);
}

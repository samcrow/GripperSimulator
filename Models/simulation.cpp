#include "simulation.h"
#include <QDebug>
#include <QtMath>

Simulation::Simulation()
{
    // Test

    // Set up the object as a square
    constexpr double SQUARE_HALF_SIDE_LENGTH = 0.01;
    object_.polygon() = QPolygonF(QRectF(-SQUARE_HALF_SIDE_LENGTH, -SQUARE_HALF_SIDE_LENGTH, 2 * SQUARE_HALF_SIDE_LENGTH, 2 * SQUARE_HALF_SIDE_LENGTH));
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
    gripper_.setYOffset(gripper_.yOffset() + 0.01);
}
void Simulation::nudgeGripperDown() {
    gripper_.setYOffset(gripper_.yOffset() - 0.01);
}
void Simulation::nudgeGripperLeft() {
    gripper_.setXOffset(gripper_.xOffset() + 0.01);
}
void Simulation::nudgeGripperRight() {
    gripper_.setXOffset(gripper_.xOffset() - 0.01);
}

Gripper* Simulation::gripper() {
    return &gripper_;
}

Object* Simulation::object() {
    return &object_;
}


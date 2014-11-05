#include "javascriptgripper.h"
#include "../Models/simulation.h"
#include <QCoreApplication>

JavaScriptGripper::JavaScriptGripper(Simulation& simulation, QObject* parent) :
    QObject(parent),
    gripper(simulation.gripper()),
    simulation(simulation)
{
}

double JavaScriptGripper::getX() const {
    return gripper.xOffset();
}
void JavaScriptGripper::setX(double newX) {
    gripper.setXOffset(newX);
}
double JavaScriptGripper::getY() const {
    return gripper.yOffset();
}
void JavaScriptGripper::setY(double newY) {
    gripper.setYOffset(newY);
}

void JavaScriptGripper::startOpening() {
    simulation.startOpeningGripper();
}
void JavaScriptGripper::startClosing() {
    simulation.startClosingGripper();
}

void JavaScriptGripper::startMovingLeft() {
    simulation.startMovingGripperLeft();
}
void JavaScriptGripper::startMovingRight() {
    simulation.startMovingGripperRight();
}
void JavaScriptGripper::startMovingUp() {
    simulation.startMovingGripperUp();
}
void JavaScriptGripper::startMovingDown() {
    simulation.startMovingGripperDown();
}
double JavaScriptGripper::getAngle() const {
    return gripper.angle();
}
void JavaScriptGripper::setAngle(double angle) {
    gripper.setAngle(angle);
}
double JavaScriptGripper::getOpenDistance() const {
    return gripper.openDistance();
}
void JavaScriptGripper::setOpenDistance(double newDistance) {
    gripper.setOpenDistance(newDistance);
}

void JavaScriptGripper::startRotatingCounterclockwise() {
    simulation.startRotatingGripperCounterclockwise();
}
void JavaScriptGripper::startRotatingClockwise() {
    simulation.startRotatingGripperClockwise();
}

bool JavaScriptGripper::isBeamBlocked() const {
    return simulation.isBeamBlocked();
}

void JavaScriptGripper::stop() {
    simulation.stopOpeningClosingGripper();
    simulation.stopMovingGripperHorizontally();
    simulation.stopMovingGripperVertically();
    simulation.stopRotatingGripper();
}

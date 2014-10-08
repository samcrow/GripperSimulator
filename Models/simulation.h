#ifndef SIMULATION_H
#define SIMULATION_H
#include "gripper.h"
#include "object.h"

/**
 * Contains all components of the simulation.
 *
 * Distances are in meters.
 * The coordinate system is centered on (0, 0).
 * The gripper starts centered on (0, 0) with angle 0,
 * which means that fingertip 1 points in the +X direction
 * and fingertip 2 points in the -X direction.
 */
class Simulation
{
public:
    Simulation();

    Gripper* gripper();
    Object* object();

    void rotateGripperRight();
    void rotateGripperLeft();
    void openGripperSomewhat();
    void closeGripperSomewhat();
    void nudgeGripperUp();
    void nudgeGripperDown();
    void nudgeGripperLeft();
    void nudgeGripperRight();

private:
    Gripper gripper_;
    Object object_;
};

#endif // SIMULATION_H

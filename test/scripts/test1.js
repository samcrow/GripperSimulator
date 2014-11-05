
gripper.startMovingUp();
while(gripper.beamBlocked) { yield(); }
gripper.stop();

gripper.startRotatingClockwise();
while(gripper.angle > -Math.PI / 2.0) { yield(); }
gripper.stop();

gripper.startMovingRight();
while(gripper.beamBlocked) { yield(); }
gripper.stop();

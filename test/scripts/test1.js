
console.log("Moving griper up...");
gripper.startMovingUp();
while(gripper.beamBlocked) { yield(); }
gripper.stop();
console.log("Reached top");

gripper.startRotatingClockwise();
while(gripper.angle > -Math.PI / 2.0) { yield(); }
gripper.stop();
console.log("Finished rotating 90º");

gripper.startMovingRight();
while(gripper.beamBlocked) { yield(); }
gripper.stop();
console.log("At right");

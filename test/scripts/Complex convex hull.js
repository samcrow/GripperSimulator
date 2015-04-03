
/*
 *
 *
 */

function rotateCounterclockwiseTo(angle) {
    gripper.startRotatingCounterclockwise();
    while(gripper.angle < angle) { yield(); }
    gripper.stop();
}


function findCorner() {
    gripper.startMovingPositiveV();
    while(gripper.beamBlocked) { yield(); }
    gripper.moveToCenter();
    gripper.startMovingNegativeV();
    while(gripper.beamBlocked) { yield(); }

    // Move back to center
    gripper.moveToCenter();
}

// Rotate in increments
var increment = Math.PI * 0.125;
var angle = 0;
while(angle < Math.PI * 2) {
    // Each time, move V+ until the beam is not blocked
    // Then rotate to the next increment and move back to the center

    gripper.startMovingPositiveV();
    while(gripper.beamBlocked) { yield(); }
    gripper.stop();

    angle += increment;
    console.log('Rotating to ' + angle)
    rotateCounterclockwiseTo(angle);

    console.log("moving to center...");
    gripper.moveToCenter();
    console.log("Done moving to center");

}

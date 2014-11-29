
/*
 *
 *
 */

function rotateCounterclockwiseTo(angle) {
    gripper.startRotatingCounterclockwise();
    while(gripper.angle < angle) { yield(); }
    gripper.stop();
}


function findEdges() {
    gripper.startMovingPositiveV();
    while(gripper.beamBlocked) { yield(); }
    gripper.moveToCenter();
    gripper.startMovingNegativeV();
    while(gripper.beamBlocked) { yield(); }

    // Move back to center
    gripper.moveToCenter();
}

// Rotate in 45º increments
for(var angle = 0; angle < Math.PI; angle += Math.PI * 0.25) {
    console.log('Rotating to ' + angle)
    rotateCounterclockwiseTo(angle);
    findEdges();
}

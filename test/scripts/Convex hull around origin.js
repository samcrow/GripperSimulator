
function rotateCounterclockwiseTo(angle) {
    var currentAngle = gripper.angle
    gripper.startRotatingCounterclockwiseAroundOrigin();
    while(currentAngle < angle) {
        currentAngle = gripper.angle
        yield();
    }
    gripper.stop();
}

function moveOutwards() {
    gripper.startMovingPositiveV();
    while(gripper.beamBlocked) {
        yield();
    }
    sleep(100);
    gripper.stop();
}

function findCorner() {
    gripper.startMovingNegativeV();
    while(!gripper.beamBlocked) {
        yield();
    }
    gripper.stop();
}

// Rotate in increments
var increment = Math.PI * 0.01;
var angle = 0;
while(angle <= 2 * Math.PI) {
    moveOutwards();
    rotateCounterclockwiseTo(angle);
    findCorner();

    angle += increment;
}


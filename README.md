# Gripper Simulator #

## Introduction ##

This software simulates a [PR2](http://www.willowgarage.com/pages/pr2/overview)'s gripper from a 2-dimensional top-down view. It can run JavaScript code to control the gripper's motion.

## License ##

This software is licensed under the MIT license (see LICENSE.txt).

## Compiling ##

Gripper Simulator can be compiled on many platforms with the [Qt](http://www.qt.io/developers/) libraries and tools. Version 5.0 or later of Qt should work.

## JavaScript specification ##

JavaScript code has access to a global `gripper` object. This object has functions and properties as described in src/JavaScript/JavaScriptGripper.h

The global `yield()` function allows the application to respond to events from the operating system. Since the application currently runs JavaScript in the main application thread, this method should be called from the body of each loop.

The global `sleep(milliseconds)` function suspends JavaScript execution for the specified number of milliseconds.

The global `console` object has a `log(text)` method that displays text in the console.

Example scripts are located in the test/scripts folder.

## Shape file specification ##

A shape file contains a list of points. These points define a polygon. The polygon must not intersect itself.

A shape file looks like this:

    x0 y0
    x1 y1
    x2 y2
    x3 y3

`(x0, y0)` is the position of the first point in the polygon. Each subsequent line is another point. The coordinates are in units of meters. Since the gripper can only open 90 millimeters, typical shapes will have coordinates in the tens-of-millimeters range.

Example shapes are located in the test/Shapes folder.

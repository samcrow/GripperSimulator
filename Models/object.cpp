#include "object.h"
#include <iterator>

Object::Object()
{
}

bool Object::hitsObject(const QLineF& infraredBeam) const {

    // Check each line that makes up the polygon and see if
    // any of them intersects the infrared beam

    // If the polygon has fewer points then a triangle, it does not exist for the purposes of this function
    if(polygon_.size() < 3) {
        return false;
    }
    // Create an iterator to element 1 and an iterator to element 0
    auto iter = polygon_.cbegin();
    auto previous = iter;
    std::advance(iter, 1);

    while(iter != polygon_.cend()) {
        const QLineF polygonLine(*previous, *iter);

        const QLineF::IntersectType intersectType = infraredBeam.intersect(polygonLine, nullptr);
        if(intersectType == QLineF::BoundedIntersection) {
            // The two lines intersected within their bounds
            return true;
        }
        // Move to the next line
        std::advance(iter, 1);
        std::advance(previous, 1);
    }
    // Now iter points to the past-the-end position and previous points to the last point.
    // Check the line between the last point and the first point
    const QLineF closingLine(*previous, polygon_.front());
    if(infraredBeam.intersect(closingLine, nullptr) == QLineF::BoundedIntersection) {
        return true;
    }

    // No intersection
    return false;
}

QPolygonF& Object::polygon() {
    return polygon_;
}

const QPolygonF& Object::polygon() const {
    return polygon_;
}

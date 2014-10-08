#ifndef OBJECT_H
#define OBJECT_H
#include <QPolygonF>
#include <QLineF>

/**
 * Represents the object that the system is trying to gather information on
 */
class Object
{
public:
    Object();

    /**
     * Returns whether an infrared beam along
     * the specified line intersects the object
     * @param infaredBeam
     * @return
     */
    bool hitsObject(const QLineF& infraredBeam) const;

    const QPolygonF& polygon() const;
    QPolygonF& polygon();

private:
    QPolygonF polygon_;
};

#endif // OBJECT_H

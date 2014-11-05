#ifndef OBJECTINFORMATION_H
#define OBJECTINFORMATION_H
#include <QBitmap>
#include <QPolygonF>
#include <QLineF>
#include <QTransform>

/**
 * Stores information that has been gathered about the object
 * in a bitmap.
 *
 * Black pixels are unkown; white pixels are clear
 */
class ObjectInformation
{
public:
    ObjectInformation();

    const QImage& bitmap() const;

    void markClear(const QPolygonF& polygon);
    void markClear(const QLineF& line);

private:

    QImage bitmap_;
    const QTransform transform;
};

#endif // OBJECTINFORMATION_H

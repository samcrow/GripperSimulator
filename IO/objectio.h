#ifndef OBJECTIO_H
#define OBJECTIO_H
#include <QPolygonF>
#include <QIODevice>

namespace ObjectIO {

/**
 * Reads a polygon from the provided IO device and returns it.
 * Throws some exception if the polygon could not be read
 * @param device
 * @return
 */
QPolygonF readPolygon(QIODevice* device);

}

#endif // OBJECTIO_H

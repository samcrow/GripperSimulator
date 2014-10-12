#include "objectinformation.h"
#include <QPainter>

ObjectInformation::ObjectInformation() :
    // A 200x200 bitmap for a 20x20 centimeter area
    // 1 pixel per millimeter
    bitmap_(200, 200),
    transform(QTransform().translate(bitmap_.width() / 2.0, bitmap_.height() / 2.0).scale(1000, 1000))
{
    bitmap_.fill(Qt::black);
}

const QBitmap& ObjectInformation::bitmap() const {
    return bitmap_;
}

void ObjectInformation::markClear(const QPolygonF &polygon)
{
    QPainter painter(&bitmap_);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::white);
    painter.drawPolygon(transform.map(polygon));
}

void ObjectInformation::markClear(const QLineF& line)
{
    QPainter painter(&bitmap_);
    painter.setPen(Qt::white);
    painter.drawLine(transform.map(line));
}

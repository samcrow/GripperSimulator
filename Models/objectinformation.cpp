#include "objectinformation.h"
#include <QPainter>

ObjectInformation::ObjectInformation() :
    // A 200x200 bitmap for a 20x20 centimeter area
    // 1 pixel per millimeter
    // Format_Mono creates a binary 1-bit-per-pixel image
    bitmap_(200, 200, QImage::Format_Mono),
    transform(QTransform().translate(bitmap_.width() / 2.0, bitmap_.height() / 2.0).scale(1000, 1000))
{
    // Fill the image with black. Using Qt::black does not work with Format_Mono.
    bitmap_.fill(0);
}

const QImage& ObjectInformation::bitmap() const {
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

void ObjectInformation::reset() {
	bitmap_.fill(0);
}

int ObjectInformation::countPixels(const QPolygonF& polygon) const {
	QImage image(bitmap_.size(), bitmap_.format());
	image.fill(0);

	QPainter painter(&image);
	painter.setBrush(Qt::white);
	painter.drawPolygon(transform.map(polygon));

	int sum = 0;
	for(int x = 0; x < image.width(); x++) {
		for(int y = 0; y < image.height(); y++) {
			const QRgb pixel = image.pixel(x, y);
			if((pixel & 1) == 1) {
				sum++;
			}
		}
	}
	return sum;
}

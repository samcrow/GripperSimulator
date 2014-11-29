#include "objectio.h"
#include <QTextStream>

namespace ObjectIO {

QPolygonF readPolygon(QIODevice* device) {
	QTextStream stream(device);

	QPolygonF polygon;

	while(!stream.atEnd()) {
		// Read a point
		double x = 0;
		double y = 0;
		stream >> x;
		stream >> y;

		polygon << QPointF(x, y);

		stream.skipWhiteSpace();
	}

	return polygon;
}

}

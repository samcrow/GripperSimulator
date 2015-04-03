#include "pixelcount.h"
#include <stdexcept>

namespace PixelCount {


namespace {
bool isBlack(QRgb pixel);

int countBlackPixels(const QImage& image, bool** visited, int x, int y);
}

int countBlackPixels(const QImage& image, int startX, int startY) {
	if(image.isNull() || image.width() == 0 || image.height() == 0) {
		return 0;
	}
	if(image.format() != QImage::Format_Mono) {
		throw std::invalid_argument("countBlackPixels only works with images of Format_Mono");
	}

	const int width = image.width();
	const int height = image.height();

	bool** visited = new bool* [width];
	for(int i = 0; i < width; i++) {
		bool* column = new bool[height];
		// Initialize to false
		std::fill(column, column + height, false);
		visited[i] = column;
	}

	if(isBlack(image.pixel(startX, startY))) {
		const int total = countBlackPixels(image, visited, startX, startY);
		return total;
	}
	else {
		return 0;
	}

	// Clean up
	for(int i = 0; i < width; i++) {
		delete[] visited[i];
	}
	delete[] visited;
}

namespace {

int countBlackPixels(const QImage& image, bool** visited, int x, int y) {
	if(x < 0 || y < 0 || x >= image.width() || y >= image.height()) {
		return 0;
	}
	if(visited[x][y]) {
		return 0;
	}
	if(!isBlack(image.pixel(x, y))) {
		return 0;
	}
	int sum = 1;
	visited[x][y] = true;

	sum += countBlackPixels(image, visited, x - 1, y);
	sum += countBlackPixels(image, visited, x, y + 1);
	sum += countBlackPixels(image, visited, x + 1, y);
	sum += countBlackPixels(image, visited, x, y - 1);
	return sum;
}

bool isBlack(QRgb pixel) {
	// Only works for ImageFormat_Mono
	return (pixel & 1) == 0;
}

}
}

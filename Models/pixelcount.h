#ifndef PIXELCOUNT_H
#define PIXELCOUNT_H

#include <QImage>
namespace PixelCount {

/**
 * Returns the number of contiguous black pixels at the center
 * and surrounding adjacent pixels. Diagonally adjacent pixels are not
 * considered adjacent.
 * @param image the image to count pixels from
 * @return the number of black pixels around the center
 */
int countBlackPixels(const QImage& image, int startX, int startY);


}

#endif // PIXELCOUNT_H


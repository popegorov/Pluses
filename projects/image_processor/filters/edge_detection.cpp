#include "edge_detection.h"
#include "matrix.h"

namespace {

void CheckPixel(Color *pixel, double threshold) {
    if (pixel->blue > threshold) {
        pixel->blue = 1;
        pixel->green = 1;
        pixel->red = 1;
    } else {
        pixel->blue = 0;
        pixel->green = 0;
        pixel->red = 0;
    }
}

} // namespace


EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = threshold;
}

void EdgeDetection::Modify(Image &im) {
    Image::Picture picture_copy(im.GetPicture());

    for (size_t y = 0; y < im.GetHeight(); ++y) {
        for (size_t x = 0; x < im.GetWidth(); ++x) {
            matrix::SubtractAllNeighbours(im, picture_copy, x, y);
            matrix::ChangeColor(im, picture_copy, x, y, x, y, 3);
            CheckPixel(im.GetPixel(x, y), threshold_);
        }
    }
}
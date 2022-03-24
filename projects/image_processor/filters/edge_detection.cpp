#include "edge_detection.h"
#include "grayscale.h"

namespace {

void ApplyThreshold(Color& pixel, double threshold) {
    if (pixel.blue > threshold) {
        pixel.blue = 1;
        pixel.green = 1;
        pixel.red = 1;
    } else {
        pixel.blue = 0;
        pixel.green = 0;
        pixel.red = 0;
    }
}

}  // namespace

EdgeDetection::EdgeDetection(double threshold)
    : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), threshold_(threshold) {
}

void EdgeDetection::Modify(Image& im) {
    GrayScale g;
    g.Modify(im);

    ApplyMatrix(im);

    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            ApplyThreshold(pixel, threshold_);
        }
    }
}

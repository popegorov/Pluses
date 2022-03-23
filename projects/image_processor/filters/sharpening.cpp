#include "sharpening.h"
#include <algorithm>

namespace {

void CheckPixel(Color& pixel) {
    pixel.blue = std::clamp(pixel.blue, 0.0, 1.0);
    pixel.green = std::clamp(pixel.green, 0.0, 1.0);
    pixel.red = std::clamp(pixel.red, 0.0, 1.0);
}

} // namespace

void Sharpening::Modify(Image& im) {
    Image::Picture picture_copy(im.GetPicture());
    matrix_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    ApplyMatrix(im);

    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            CheckPixel(pixel);
        }
    }
}

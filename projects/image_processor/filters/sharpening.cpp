#include "sharpening.h"

Sharpening::Sharpening() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}) {}

void Sharpening::Modify(Image& im) {
    ApplyMatrix(im);

    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            pixel.Clamp();
        }
    }
}

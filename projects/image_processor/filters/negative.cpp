#include "negative.h"

void Neg::Modify(Image& im) {
    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            pixel.blue = 1 - pixel.blue;
            pixel.green = 1 - pixel.green;
            pixel.red = 1 - pixel.red;
        }
    }
}
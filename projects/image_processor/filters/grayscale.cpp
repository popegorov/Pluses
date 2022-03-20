#include "grayscale.h"

void Gs::Modify(Image& im) {
    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            pixel.blue = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
            pixel.green = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
            pixel.red = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
        }
    }
}

#include "negative.h"

void Negative::Modify(Image &im) {
    for (size_t y = 0; y < im.GetHeight(); ++y) {
        for (size_t x = 0; x < im.GetWidth(); ++x) {
            im.GetPixel(x, y).blue = 1 - im.GetPixel(x, y).blue;
            im.GetPixel(x, y).green = 1 - im.GetPixel(x, y).green;
            im.GetPixel(x, y).red = 1 - im.GetPixel(x, y).red;
        }
    }
}
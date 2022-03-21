#include "negative.h"

void Negative::Modify(Image &im) {
    for (size_t y = 0; y < im.GetHeight(); ++y) {
        for (size_t x = 0; x < im.GetWidth(); ++x) {
            auto cur_pixel = im.GetPixel(x, y);

            cur_pixel->blue = 1 - cur_pixel->blue;
            cur_pixel->green = 1 - cur_pixel->green;
            cur_pixel->red = 1 - cur_pixel->red;
        }
    }
}

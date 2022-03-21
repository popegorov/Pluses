#include "grayscale.h"

void GrayScale::Modify(Image &im) {
    for (size_t y = 0; y < im.GetHeight(); ++y) {
        for (size_t x = 0; x < im.GetWidth(); ++x) {
            auto cur_pixel = im.GetPixel(x, y);
            auto gray_pixel = cur_pixel->blue * 0.114 + cur_pixel->green * 0.587 + cur_pixel->blue * 0.299;

            cur_pixel->blue = gray_pixel;
            cur_pixel->green = gray_pixel;
            cur_pixel->red = gray_pixel;
        }
    }
}
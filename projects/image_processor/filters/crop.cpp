#include "crop.h"

Crop::Crop(size_t width, size_t height) {
    new_width_ = width;
    new_height_ = height;
}

void Crop::Modify(Image& im) {
    if (new_height_ < im.GetHeight() || new_width_ < im.GetWidth()) {
        Image new_im(new_width_, new_height_);

        for (size_t y = 0; y < new_height_; ++y) {
            for (size_t x = 0; x < new_width_; ++x) {
                new_im.GetPixel(x, y) = im.GetPixel(x, y);
            }
        }

        im = new_im;
    }
}

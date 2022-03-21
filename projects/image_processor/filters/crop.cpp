#include "crop.h"

Crop::Crop(size_t width, size_t height) {
    new_width_ = width;
    new_height_ = height;
}

void Crop::Modify(Image &im) {
    if (new_height_ < im.GetHeight() && new_width_ < im.GetWidth()) {

        im.GetPicture().resize(new_height_);
        for (auto &cur_row: im.GetPicture()) {
            cur_row.resize(new_width_);
        }

    } else if (new_height_ < im.GetHeight()) {

        im.GetPicture().resize(new_height_);

    } else if (new_width_ < im.GetWidth()) {

        for (auto &cur_row: im.GetPicture()) {
            cur_row.resize(new_width_);
        }

    }
}

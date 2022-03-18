#include "filters.h"

void Filter::Modificate(Image &im) {}

Crop::Crop(size_t width, size_t height) {
    new_width_ = width;
    new_height_ = height;
}

void Crop::Modificate(Image &im) {
    if (new_height_ < im.GetHeight() && new_width_ < im.GetWidth()) {

        im.GetPicture().resize(new_height_);
        for (auto &cur_row: im.GetPicture()) {
            cur_row.resize(new_width_);
        }
        im.SetHeight(new_height_);
        im.SetWidth(new_width_);
        im.SetPadding(new_width_);

    } else if (new_height_ < im.GetHeight()) {

        im.GetPicture().resize(new_height_);
        im.SetHeight(new_height_);

    } else if (new_width_ < im.GetWidth()) {

        for (auto &cur_row: im.GetPicture()) {
            cur_row.resize(new_width_);
        }
        im.SetWidth(new_width_);
        im.SetPadding(new_width_);

    }
}
#pragma once

#include "base_filter.h"

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);

    void Modify(Image &im) override;

private:
    size_t new_width_;
    size_t new_height_;
};

#pragma once

#include "image_processor.h"

class Filter {
public:
    virtual void Modificate(Image &im);
};

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);

    void Modificate(Image &im) override;

private:
    size_t new_width_;
    size_t new_height_;
};

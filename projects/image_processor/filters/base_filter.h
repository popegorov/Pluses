#pragma once

#include "../image.h"

class Filter {
public:
    virtual void Modify(Image &im);
    virtual ~Filter();
};
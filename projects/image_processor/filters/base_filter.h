#pragma once

#include "../image.h"

class Filter {
public:
    virtual void Modify(Image& im) = 0;
    virtual ~Filter() = default;
};
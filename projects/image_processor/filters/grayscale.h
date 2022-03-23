#pragma once

#include "base_filter.h"

class GrayScale : public Filter {
public:
    void Modify(Image& im) override;
};

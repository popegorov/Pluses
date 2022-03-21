#pragma once

#include "base_filter.h"

class Sharpening : public Filter {
public:
    void Modify(Image &im) override;
};

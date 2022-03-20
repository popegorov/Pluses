#pragma once

#include "base_filter.h"

class Neg : Filter {
public:
    void Modify(Image& im) override;
};

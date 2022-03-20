#pragma once

#include "base_filter.h"

class Gs : Filter {
public:
    void Modify(Image& im) override;
};
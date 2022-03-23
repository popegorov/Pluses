#pragma once

#include "base_filter.h"

class Negative : public Filter {
public:
    void Modify(Image& im) override;
};

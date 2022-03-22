#pragma once

#include "base_filter.h"

class Blur : public Filter {
public:
    Blur(double sigma);

    void Modify(Image &im) override;

private:
    double sigma_;
};

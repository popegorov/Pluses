#pragma once

#include "base_filter.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);

    void Modify(Image &im) override;

private:
    double threshold_;
};

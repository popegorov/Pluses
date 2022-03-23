#pragma once

#include "matrix.h"

class EdgeDetection : public MatrixFilter {
public:
    EdgeDetection(double threshold);

    void Modify(Image& im) override;

private:
    double threshold_;
};

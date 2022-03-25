#pragma once

#include "matrix.h"

class Blur : public MatrixFilter {
public:
    Blur(double sigma);

    void Modify(Image& im) override;

private:
    double sigma_;
};

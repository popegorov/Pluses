#pragma once

#include "matrix.h"

class Blur : public MatrixFilter {
public:
    Blur(int sigma);

    void Modify(Image& im) override;

private:
    int sigma_;
};

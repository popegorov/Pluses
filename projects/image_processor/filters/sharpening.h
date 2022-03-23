#pragma once

#include "matrix.h"

class Sharpening : public MatrixFilter {
public:
    void Modify(Image& im) override;
};

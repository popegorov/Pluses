#pragma once

#include "matrix.h"

class Sharpening : public MatrixFilter {
public:
    Sharpening();
    void Modify(Image& im) override;
};

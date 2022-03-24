#pragma once

#include "base_filter.h"
#include "../image.h"

class MatrixFilter : public Filter {
public:
    using Matrix = std::vector<std::vector<double>>;

    MatrixFilter() = default;
    MatrixFilter(Matrix m);

    void ApplyMatrix(Image& im);

protected:
    Matrix matrix_;
};

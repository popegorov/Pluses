#include "blur.h"
#include <cmath>
#include <numbers>

double pi = std::numbers::pi_v<double>;

namespace {

double DoGaussFunction(int sigma, int delta_c) {
    double sigma_sq = 2 * sigma * sigma;
    return 1 / std::sqrt(pi * sigma_sq) / exp(delta_c * delta_c / sigma_sq);
}

MatrixFilter::Matrix GenerateRowMatrix(int sigma) {
    int matrix_size = sigma * 8 + 1;
    MatrixFilter::Matrix res(1, std::vector<double>(matrix_size, 0));

    int half_size = matrix_size / 2;
    for (int i = -1 * half_size; i < half_size + 1; ++i) {
        res[0][i + half_size] = DoGaussFunction(sigma, i);
    }

    return res;
}

MatrixFilter::Matrix GenerateColumnMatrix(int sigma) {
    int matrix_size = sigma * 8 + 1;
    MatrixFilter::Matrix res(matrix_size, std::vector<double>(1, 0));

    int half_size = matrix_size / 2;
    for (int i = -1 * half_size; i < half_size + 1; ++i) {
        res[i + half_size][0] = DoGaussFunction(sigma, i);
    }

    return res;
}

} // namespace

Blur::Blur(int sigma) {
    sigma_ = sigma;
}

void Blur::Modify(Image& im) {
    matrix_ = GenerateRowMatrix(sigma_);
    ApplyMatrix(im);
    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            pixel.Clamp();
        }
    }

    matrix_ = GenerateColumnMatrix(sigma_);
    ApplyMatrix(im);
    for (auto& row : im.GetPicture()) {
        for (auto& pixel : row) {
            pixel.Clamp();
        }
    }
}

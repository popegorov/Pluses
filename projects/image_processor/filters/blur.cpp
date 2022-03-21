#include "blur.h"
#include "matrix.h"
#include <cmath>
#include <numbers>


double pi = std::numbers::pi_v<double>;
double e = std::numbers::e_v<double>;

namespace {

double DoGaussFunction(double val, double sigma, size_t c0, size_t c) {
    double abs_c = abs(static_cast<int>(c0) - static_cast<int>(c));
    double sigma_sq = 2 * sigma * sigma;
    return val / std::sqrt(pi * sigma_sq) * exp(-1 * abs_c * abs_c) / sigma_sq;
}

void ChangeColorByColumns(Image &im, const Image::Picture &picture_copy, size_t x0, size_t y0, double sigma) {
    int sigma_4 = std::ceil(sigma * 4);
    for (size_t y = static_cast<size_t>(std::max(0, static_cast<int>(y0) - sigma_4));
         y < std::min(picture_copy.size(), y0 + sigma_4); ++y) {
        im.GetPixel(x0, y0)->blue += DoGaussFunction(picture_copy[y][x0].blue, sigma, y0, y);
        im.GetPixel(x0, y0)->green += DoGaussFunction(picture_copy[y][x0].green, sigma, y0, y);
        im.GetPixel(x0, y0)->red += DoGaussFunction(picture_copy[y][x0].red, sigma, y0, y);
    }
}

void ChangeColorByRows(Image &im, const Image::Picture &picture_copy, size_t x0, size_t y0, double sigma) {
    int sigma_4 = std::ceil(sigma * 4);
    for (size_t x = static_cast<size_t>(std::max(0, static_cast<int>(x0) - sigma_4));
         x < std::min(picture_copy.size(), x0 + sigma_4); ++x) {
        im.GetPixel(x0, y0)->blue += DoGaussFunction(picture_copy[y0][x].blue, sigma, x0, x);
        im.GetPixel(x0, y0)->green += DoGaussFunction(picture_copy[y0][x].green, sigma, x0, x);
        im.GetPixel(x0, y0)->red += DoGaussFunction(picture_copy[y0][x].red, sigma, x0, x);
    }
}

} // namespace

Blur::Blur(double sigma) {
    sigma_ = sigma;
}

void Blur::Modify(Image &im) {
    Image::Picture picture_copy(im.GetPicture());
    im.GetPicture().assign(im.GetHeight(), std::vector<Color>(im.GetWidth(), {0, 0, 0}));

    for (size_t y0 = 0; y0 < im.GetHeight(); ++y0) {
        for (size_t x0 = 0; x0 < im.GetWidth(); ++x0) {
            ChangeColorByRows(im, picture_copy, x0, y0, sigma_);
            matrix::CheckPixel(im.GetPixel(x0, y0));
        }
    }

    picture_copy = im.GetPicture();

    for (size_t y0 = 0; y0 < im.GetHeight(); ++y0) {
        for (size_t x0 = 0; x0 < im.GetWidth(); ++x0) {
            ChangeColorByColumns(im, picture_copy, x0, y0, sigma_);
            matrix::CheckPixel(im.GetPixel(x0, y0));
        }
    }
}

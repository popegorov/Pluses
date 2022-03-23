#include "matrix.h"

namespace {

void ChangeColor(Image& im, Image::Picture& picture, MatrixFilter::Matrix matrix, size_t x0, size_t y0) {
    int mid_y = matrix.size() / 2;
    int mid_x = matrix[0].size() / 2;

    for (int delta_y = -1 * mid_y; delta_y < mid_y + 1; ++delta_y) {
        for (int delta_x = -1 * mid_x; delta_x < mid_x + 1; ++delta_x) {
            auto matrix_y = mid_y + delta_y;
            auto matrix_x = mid_x + delta_x;
            auto cur_y = y0 + delta_y;
            auto cur_x = x0 + delta_x;

            if (cur_x >= picture[0].size()) {
                cur_x = x0;
            }
            if (cur_y >= picture.size()) {
                cur_y = y0;
            }

            im.GetPixel(x0, y0).blue += picture[cur_y][cur_x].blue * matrix[matrix_y][matrix_x];
            im.GetPixel(x0, y0).green += picture[cur_y][cur_x].green * matrix[matrix_y][matrix_x];
            im.GetPixel(x0, y0).red += picture[cur_y][cur_x].red * matrix[matrix_y][matrix_x];
        }
    }
}

}  // namespace

void MatrixFilter::ApplyMatrix(Image& im) {
    auto picture_copy = im.GetPicture();
    im.GetPicture().assign(im.GetHeight(), std::vector<Color>(im.GetWidth()));

    for (size_t y = 0; y < im.GetHeight(); ++y) {
        for (size_t x = 0; x < im.GetWidth(); ++x) {
            ChangeColor(im, picture_copy, matrix_, x, y);
        }
    }
}

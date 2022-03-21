#include "matrix.h"
#include <algorithm>

void matrix::ChangeColor(Image& im, const Image::Picture& picture_copy, size_t x, size_t y, size_t new_x, size_t new_y, int val) {
    im.GetPixel(x, y)->blue += picture_copy[new_y][new_x].blue * val;
    im.GetPixel(x, y)->green += picture_copy[new_y][new_x].green * val;
    im.GetPixel(x, y)->red += picture_copy[new_y][new_x].red * val;
}

void CheckPixel(Color *pixel) {
    pixel->blue = std::clamp(pixel->blue, 0.0, 1.0);
    pixel->green = std::clamp(pixel->green, 0.0, 1.0);
    pixel->red = std::clamp(pixel->red, 0.0, 1.0);
}

void matrix::SubtractNeighbours(Image& im, const Image::Picture& picture_copy, size_t x, size_t y, bool is_y) {
    for (int delta : {-1, 1}) {
        size_t new_y, new_x;
        if (is_y) {
            new_y = y + delta;
            new_x = x;
        } else {
            new_y = y;
            new_x = x + delta;
        }

        if (new_y < im.GetHeight() && new_x < im.GetWidth()) {
            ChangeColor(im, picture_copy, x, y, new_x, new_y, -1);
        } else if (new_y < im.GetHeight()) {
            ChangeColor(im, picture_copy, x, y, x, new_y, -1);
        } else if (new_y < im.GetHeight()) {
            ChangeColor(im, picture_copy, x, y, new_x, y, -1);
        } else {
            ChangeColor(im, picture_copy, x, y, x, y, -1);
        }
    }
}

void matrix::SubtractAllNeighbours(Image& im, const Image::Picture& picture_copy, size_t x, size_t y) {
    SubtractNeighbours(im, picture_copy, x, y, false);
    SubtractNeighbours(im, picture_copy, x, y, true);
}

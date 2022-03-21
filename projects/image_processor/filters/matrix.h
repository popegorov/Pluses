#pragma once

#include "../image.h"

namespace matrix {

void ChangeColor(Image &im, const Image::Picture &picture_copy, size_t x, size_t y, size_t new_x, size_t new_y, int val);

void CheckPixel(Color *pixel);

void SubtractNeighbours(Image &im, const Image::Picture &picture_copy, size_t x, size_t y, bool is_y);

void SubtractAllNeighbours(Image &im, const Image::Picture &picture_copy, size_t x, size_t y);

} //namespace matrix
